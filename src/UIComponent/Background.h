/**
 *  Background.h
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
