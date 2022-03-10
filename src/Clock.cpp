/**
 *  Clock.cpp
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

// C / C++
#include <time.h>

// External

// Project
#include "./Clock.h"


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

Clock::Clock() noexcept : i_Minutes(0),
                          i_Hours(0),
                          i_Day(0),
                          i_Month(0),
                          i_Year(0)
{}

Clock::~Clock() noexcept
{}

//*************************************************************************************
// Update
//*************************************************************************************

int i_TMinutes = 0;
int i_THours = 0;
int i_TDay = 1;

void Clock::Update() noexcept
{
    time_t us_Time = time(NULL);
    struct tm c_LocalTime = *localtime(&us_Time);
    
    i_Minutes = c_LocalTime.tm_min;
    i_Hours = c_LocalTime.tm_hour;
    
    i_Day = c_LocalTime.tm_mday;
    i_Month = c_LocalTime.tm_mon + 1;
    i_Year = c_LocalTime.tm_year + 1900;
}

//*************************************************************************************
// Getters
//*************************************************************************************

int Clock::GetMinutes() const noexcept
{
    return i_Minutes;
}

int Clock::GetHours() const noexcept
{
    return i_Hours;
}

int Clock::GetDay() const noexcept
{
    return i_Day;
}

int Clock::GetMonth() const noexcept
{
    return i_Month;
}

int Clock::GetYear() const noexcept
{
    return i_Year;
}

std::string Clock::GetTimeString() const noexcept
{
    std::string s_Time = std::to_string(i_Hours);
    
    if (i_Hours < 10)
    {
        s_Time.insert(0, "0");
    }
    
    s_Time += ":";
    
    if (i_Minutes < 10)
    {
        s_Time += "0";
    }
    
    s_Time += std::to_string(i_Minutes);
    
    return s_Time;
}

std::string Clock::GetDateString() const noexcept
{
    std::string s_Date = std::to_string(i_Day);
    
    if (i_Day < 10)
    {
        s_Date.insert(0, "0");
    }
    
    s_Date += ".";
    
    if (i_Month < 10)
    {
        s_Date += "0";
    }
    
    s_Date += std::to_string(i_Month);
    s_Date += ".";
    
    s_Date += std::to_string(i_Year);
    
    return s_Date;
}
