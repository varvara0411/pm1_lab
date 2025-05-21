/// \file  football.cpp
/// \brief Implementation of the Football class methods and operator overloading.

#include "football.h"

/// \brief Default constructor of the Football class.
Football::Football() {
    country = "";
    club = "";
    city = "";
    year = 0;
    trainer = "";
    points = 0;
}

/// \brief Parameterized constructor of the Football class.
Football::Football(std::string country_new, std::string club_new, std::string city_new, int year_new, std::string trainer_new, int points_new) {
    country = country_new;
    club = club_new;
    city = city_new;
    year = year_new;
    trainer = trainer_new;
    points = points_new;
}

/// \brief Copy constructor of the Football class.
Football::Football(const Football& other) {
    country = other.country;
    club = other.club;
    city = other.city;
    year = other.year;
    trainer = other.trainer;
    points = other.points;
}

/// \brief Overloading operator '>' based on key fields.
bool Football::operator>(const Football& other) const {  
    if (country != other.country) {
        return (country > other.country);
    }
    if (club != other.club) { 
        return (club > other.club);
    }
    if (year != other.year) {
        return year > other.year;
    }
    return points > other.points;  
}

/// \brief Overloading operator '>=' based on key fields.
bool Football::operator>=(const Football& other) const {
    if ((*this == other) || (*this > other)) 
    {
        return true;
    }
    return false; 
}

/// \brief Overloading operator '<' based on key fields.
bool Football::operator<(const Football& other) const {
    return !(*this >= other);  
}

/// \brief Overloading operator '<=' based on key fields.
bool Football::operator<=(const Football& other) const {
    return !(*this > other);  
}

/// \brief Overloading operator '==' based on key fields.
bool Football::operator==(const Football& other) const {
    if (country == other.country && club == other.club && city == other.city && year == other.year && trainer == other.trainer && points == other.points) {
        return true;
    }
    return false;
}

/// \brief Overloading the assignment operator based on key fields.
Football& Football::operator=(const Football& other) {
    country = other.country;
    club = other.club;
    city = other.city;
    year = other.year;
    trainer = other.trainer;
    points = other.points;
    return *this;
}

/// \brief Overloading the output operator '<<'
std::ostream& operator<<(std::ostream& out, const Football& football) {
    out << football.country << " " << football.club << " " << football.city << " " << football.year << " " << football.trainer << " " << football.points;
    return out;
}