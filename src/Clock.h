/**
 *  Clock.h
 *
 *  This file is part of the MRH project.
 *  See the AUTHORS file for Copyright information.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef Clock_h
#define Clock_h

// C / C++
#include <string>

// External

// Project


class Clock
{
public:
    
    //*************************************************************************************
    // Constructor / Destructor
    //*************************************************************************************
    
    /**
     *  Default constructor.
     */
    
    Clock() noexcept;
    
    /**
     *  Copy constructor. Disabled for this class.
     *
     *  \param c_Clock Clock class source.
     */
    
    Clock(Clock const& c_Clock) = delete;
    
    /**
     *  Default destructor.
     */
    
    ~Clock() noexcept;
    
    //*************************************************************************************
    // Update
    //*************************************************************************************
    
    /**
     *  Update the clock.
     */
    
    void Update() noexcept;
    
    //*************************************************************************************
    // Getters
    //*************************************************************************************
    
    /**
     *  Get the clock minutes.
     *
     *  \return The clock minutes.
     */
    
    int GetMinutes() const noexcept;
    
    /**
     *  Get the clock hours.
     *  
     *  \return The clock hours.
     */
    
    int GetHours() const noexcept;
    
    /**
     *  Get the current day.
     *  
     *  \return The current day.
     */
    
    int GetDay() const noexcept;
    
    /**
     *  Get the current month.
     *  
     *  \return The current month.
     */
    
    int GetMonth() const noexcept;
    
    /**
     *  Get the current year.
     *  
     *  \return The current year.
     */
    
    int GetYear() const noexcept;
    
    /**
     *  Get the time string.
     *  
     *  \return The time string.
     */
    
    std::string GetTimeString() const noexcept;
    
    /**
     *  Get the date string.
     *  
     *  \return The date string.
     */
    
    std::string GetDateString() const noexcept;
    
private:
    
    //*************************************************************************************
    // Data
    //*************************************************************************************
    
    int i_Minutes;
    int i_Hours;
    
    int i_Day;
    int i_Month;
    int i_Year;
    
protected:
    
};

#endif /* Clock_h */
