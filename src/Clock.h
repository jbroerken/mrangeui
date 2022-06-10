/**
 *  Copyright (C) 2021 - 2022 The MRH Project Authors.
 * 
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
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
