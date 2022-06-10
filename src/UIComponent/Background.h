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

#ifndef Background_h
#define Background_h

// C / C++
#include <deque>

// External

// Project
#include "./UIComponent.h"


class Background : public UIComponent
{
public:
    
    //*************************************************************************************
    // Constructor / Destructor
    //*************************************************************************************
    
    /**
     *  Default constructor.
     *  
     *  \param p_Renderer The renderer to use for construction.
     *  \param c_Position The component position in pixels.  
     *  \param s_AssetDir The directory to load assets from.
     */
    
    Background(SDL_Renderer* p_Renderer,
               SDL_Rect const& c_Position,
               std::string const& s_AssetDir);
    
    /**
     *  Default destructor.
     */
    
    ~Background() noexcept;
    
    //*************************************************************************************
    // Update
    //*************************************************************************************
    
    /**
     *  Update the UI component.
     *  
     *  \param p_Renderer The renderer to use for updating.
     *  \param c_Clock The clock in use.  
     */
    
    void Update(SDL_Renderer* p_Renderer, Clock const& c_Clock) noexcept override;
    
private:
    
    //*************************************************************************************
    // Color
    //*************************************************************************************
    
    /**
     *  Get the tint color for assets.
     *  
     *  \param c_Clock The clock to use for time tinting.    
     *  
     *  \return The tint color.
     */
    
    SDL_Color CalculateTintColor(Clock const& c_Clock);
    
    //*************************************************************************************
    // Solar Body
    //*************************************************************************************
    
    /**
     *  Calculate the position of the solar body.
     *  
     *  \param c_Clock The clock to use for position calculations.    
     *  
     *  \return The point on which the body should be drawn.
     */
    
    SDL_Point CalculateSolarBodyPosition(Clock const& c_Clock);
    
    //*************************************************************************************
    // Data
    //*************************************************************************************
    
    std::deque<SDL_Texture*> dq_Asset;
    
    int i_LastMinute;
    
protected:
    
};

#endif /* Background_h */
