/// \file  football.h
/// \brief Declaration of the Football class.

#ifndef FOOTBALL_H
#define FOOTBALL_H

#include <string>
#include <iostream>

/// \brief The Football class contains information about country, club, city, year, trainer and points of football team.

class Football
{
private:
    std::string country; ///< The country that the football team represents.
    std::string club; ///< The club that the football team represents.
    std::string city; ///< The city that the football team represents.
    int year; ///< The year in which the football team plays.
    std::string trainer; ///< The trainer of the football team.
    int points; ///< Points scored by the football team.

public:
    /// \name Constructors and Destructor
    /// @{
    /// \brief Default constructor.
    Football();
    /// \brief Parameterized constructor.
    Football(std::string country_new, std::string club_new, std::string city_new, int year_new, std::string trainer_new, int points_new); 
    /// \brief Copy constructor.
    Football(const Football& other); 
    /// \brief Default destructor.
    ~Football() = default;
    /// @}

    /// \name Overloading Comparison Operators and Assignment Operator
    /// \details Comparison based on key fields (country, club, year, points).
    /// @{
    bool operator>(const Football& other) const;
    bool operator<(const Football& other) const;
    bool operator<=(const Football& other) const;
    bool operator>=(const Football& other) const;
    bool operator==(const Football& other) const;
    Football& operator=(const Football& other);
    /// @}

    /// \name Overloading the output operator
    /// @{
    /// \brief Declaring a friend function for overloading
    friend std::ostream& operator<<(std::ostream& out, const Football& football);
    /// @}

};

#endif