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
