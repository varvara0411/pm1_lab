/**
 * \file  main.cpp
 * \brief Reading datasets, sorting them, recording the time of sorting and saving the results.
 *
 * Iterates over multiple CSV files containing arrays of different sizes, as defined in the `sizes` array. 
 * For each dataset, it loads the data into an array of `Football` objects using `readCSV`, performs sorting, measures the execution time.
 * Also it saves the sorted arrays into files within the `sorted_datasets` directory.
 */


#include <iostream>
#include <functional> // for std::greater
#include <fstream>
#include <sstream>
#include "football.h"
#include <chrono>


/// \brief       Descending Shaker Sort algorithm.
/// \tparam T The type of elements in the array.
/// \param a  The name of the array.
/// \param size  Number of elements.
template<class T> 
void shakerSort(T a[], long size)
{
  long j, k = size-1;
  long lb=1, ub = size-1; // bounds of unsorted part of the array
  T x;

  do
  {
    // from bottom to top passage 
    for( j=ub; j>0; j-- )
   {
      if ( a[j-1] < a[j] )
      {
        x=a[j-1]; a[j-1]=a[j]; a[j]=x;
        k=j;
      }
    }

    lb = k+1;

    // passage from top to bottom 
    for (j=1; j<=ub; j++)
    {
      if ( a[j-1] < a[j] )
      {
        x=a[j-1]; a[j-1]=a[j]; a[j]=x;
        k=j;
      }
    }

    ub = k-1;
  }
  while ( lb < ub );
}

/// \brief      Descending Quick Sort algorithm.
/// \tparam T The type of elements in the array.
/// \param a  The name of the array.
/// \param N  Number of elements.
template<class T>
void quickSort(T* a, long N) {
    long i = 0, j = N - 1;      // Initialize bounds
    T p = a[N >> 1];            // Pivot: middle element

    // Partitioning phase
    do {
        while (a[i] > p) i++;
        while (a[j] < p) j--;

        if (i <= j) {
            //std::swap(a[i], a[j]);
            T x = a[i];
            a[i] = a[j];
            a[j] = x;
            i++;
            j--;
        }
    } while (i <= j);

    // Recursively sort the partitions
    if (j > 0) quickSort(a, j + 1);
    if (N > i) quickSort(a + i, N - i);
}

/// \brief       Helper function for Heap Sort algorithm.
/// \tparam T The type of elements in the array.
/// \param a  The name of the array.
/// \param k  The starting node for the heapifying process.
/// \param n  Number of elements.
template<class T> void downHeap(T a[], long k, long n)
{
  //  before sift procedure: a[k+1]...a[n]  - is a pyramid 
  //  after:                 a[k]...a[n]  - is a pyramid
  T new_elem;
  long child;
  new_elem = a[k];
  
  while(k <= n/2)
  {  // while a[k] has childs 
    child = 2*k;
    //  choose bigger son 
    if( child < n && a[child] > a[child+1] ) 
		child++;
    if( new_elem <= a[child] ) break; 
    // otherwise 
    a[k] = a[child]; 	// move the son up 
    k = child;
  }
  a[k] = new_elem;
}


/// \brief     Descending  Heap Sort algorithm.
/// \tparam T The type of elements in the array.
/// \param a  The name of the array.
/// \param size  Number of elements.
template<class T> void heapSort(T a[], long size)
{
  long i;
  T temp;

  for(i=size/2-1; i >= 0; i--)	 // build pyramid 
	downHeap(a, i, size-1);
					// now a[0]...a[size-1] is a pyramid 
  for(i=size-1; i > 0; i--)
  {
	//std::swap(a[i], a[0]);		// swap first and last 
	T x = a[i];
	a[i] = a[0];
	a[0] = x;
	downHeap(a, 0, i-1); 	// restore the pyramid a[0]...a[i-1]
  }
}

/// \brief       std::sort algorithm.
/// \tparam T The type of elements in the array.
/// \param arr  The name of the array.
/// \param size  Number of elements.
template <class T>
void sort_new(T* arr, long size)
{
    std::sort(arr, arr + size, std::greater<T>());
}

/// \brief       Reads football data from a CSV file into an array of Football objects.
/// \param filename The path to the CSV file to read.
/// \param N        The number of rows (records) to read from the file.
/// \param result   Pointer to the array where the read Football objects will be stored.
void readCSV(std::string filename, int N, Football* result) {
    std::ifstream in(filename);
    std::string line, country_new, club_new, city_new, trainer_new;
    int i = 0;

    if (in.is_open()) {
        std::getline(in, line);  // skip first line (dataframe header)

        while (std::getline(in, line) && i < N) {
            std::stringstream ss(line);
            std::string year_str, points_str;

            std::getline(ss, country_new, ',');
            std::getline(ss, club_new, ',');
            std::getline(ss, city_new, ',');
            std::getline(ss, year_str, ',');
            std::getline(ss, trainer_new, ',');
            std::getline(ss, points_str, ',');

            int year_new = std::stoi(year_str);
            int points_new = std::stoi(points_str);

            Football f(country_new, club_new, city_new, year_new, trainer_new, points_new);
            result[i] = f;
            ++i;
        }

        in.close();
    }
}

/**
 * @brief Entry point of the program.
 *
 * Iterates through datasets, applies different sorting algorithms
 * to each dataset, measures their execution time, and saves results.
 */
int main() {

    std::ofstream out("/home/install/pm1_lab/times.csv");
    
    out << "size,std::sort,quickSort,heapSort,shakerSort\n";

    int sizes[10] = {100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000};

    std::string filenames[10] = {
        "dataset_100.csv",
        "dataset_200.csv",
        "dataset_500.csv",
        "dataset_1000.csv",
        "dataset_2000.csv",
        "dataset_5000.csv",
        "dataset_10000.csv",
        "dataset_20000.csv",
        "dataset_50000.csv",
        "dataset_100000.csv"
    };

    std::string path = "/home/install/pm1_lab/datasets/";

    std::string path_sort = "/home/install/pm1_lab/sorted_datasets/";

    for (int i = 0; i < 10; ++i) {
      std::string full_path = path + filenames[i];
      int N = sizes[i];
      Football* original = new Football[N];
      readCSV(full_path, N, original);
      // --- STD::SORT  ---

      //std::copy(original, original + N, a1);
      Football* a1 = new Football[N];
      for (int i = 0; i < N; ++i) {
        a1[i] = original[i];  
      }
      auto t1_start = std::chrono::high_resolution_clock::now();
      sort_new(a1, N);
      auto t1_end = std::chrono::high_resolution_clock::now();
      auto t_stdsort = std::chrono::duration<double, std::milli>(t1_end - t1_start).count();

      std::ofstream fout1(path_sort + "stdsort_" + std::to_string(N) + ".txt"); 
      for (int j = 0; j < N; ++j) {
        fout1 << a1[j] << "\n"; 
      }
      fout1.close(); 
      std::cout << "std::sort for dataset of size " << N << " is finished." << std::endl;

      delete[] a1;

      // --- quickSort  ---

      //std::copy(original, original + N, a2);
      Football* a2 = new Football[N];
      for (int i = 0; i < N; ++i) {
        a2[i] = original[i];  
      }
      auto t2_start = std::chrono::high_resolution_clock::now();
      quickSort(a2, N);
      auto t2_end = std::chrono::high_resolution_clock::now();
      auto t_quicksort = std::chrono::duration<double, std::milli>(t2_end - t2_start).count();
      
      std::ofstream fout2(path_sort + "quicksort_" + std::to_string(N) + ".txt"); 
      for (int j = 0; j < N; ++j) {
        fout2 << a2[j] << "\n"; 
      }
      fout2.close(); 
      std::cout << "quickSort for dataset of size " << N << " is finished." << std::endl;

      delete[] a2;

      // --- heapSort  ---

      //std::copy(original, original + N, a3);
      Football* a3 = new Football[N];
      for (int i = 0; i < N; ++i) {
        a3[i] = original[i];  
      }
      auto t3_start = std::chrono::high_resolution_clock::now();
      heapSort(a3, N);
      auto t3_end = std::chrono::high_resolution_clock::now();
      auto t_heapsort = std::chrono::duration<double, std::milli>(t3_end - t3_start).count();
      
      std::ofstream fout3(path_sort + "heapsort_" + std::to_string(N) + ".txt"); 
      for (int j = 0; j < N; ++j) {
        fout3 << a3[j] << "\n"; 
      }
      fout3.close(); 
      std::cout << "heapSort for dataset of size " << N << " is finished." << std::endl;

      delete[] a3;

      // --- shakerSort  ---

      //std::copy(original, original + N, a4);
      Football* a4 = new Football[N];
      for (int i = 0; i < N; ++i) {
        a4[i] = original[i];  
      }
      auto t4_start = std::chrono::high_resolution_clock::now();
      shakerSort(a4, N);
      auto t4_end = std::chrono::high_resolution_clock::now();
      auto t_shakersort = std::chrono::duration<double, std::milli>(t4_end - t4_start).count();
      
      std::ofstream fout4(path_sort + "shakersort_" + std::to_string(N) + ".txt"); 
      for (int j = 0; j < N; ++j) {
        fout4 << a4[j] << "\n"; 
      }
      fout4.close(); 
      std::cout << "shakerSort for dataset of size " << N << " is finished." << std::endl;

      delete[] a4;

      delete[] original;

      out << N << "," << t_stdsort << "," << t_quicksort << "," << t_heapsort << "," << t_shakersort << "\n";
    }

    out.close();

    return 0;
}
