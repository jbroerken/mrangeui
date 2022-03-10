/**
 *  TodayInfo.h
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

#ifndef TodayInfo_h
#define TodayInfo_h

// C / C++

// External

// Project
#include "./UIComponent.h"


class TodayInfo : public UIComponent
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
     *  \param s_FontFilePath The path to the font file to use.
     */
    
    TodayInfo(SDL_Renderer* p_Renderer,
              SDL_Rect const& c_Position,
              std::string const& s_FontFilePath);
    
    /**
     *  Default destructor.
     */
    
    ~TodayInfo() noexcept;
    
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
    // Textures
    //*************************************************************************************
    
    /**
     *  Create a texture for a string.
     *  
     *  \param p_Renderer The renderer to use for drawing.  
     *  \param s_String The string to draw.
     *  \param i_Size The font size to use.
     *  
     *  \return A SDL_Texture for the given string.
     */
    
    SDL_Texture* CreateStringTexture(SDL_Renderer* p_Renderer, std::string const& s_String, int i_Size);
    
    //*************************************************************************************
    // Data
    //*************************************************************************************
    
    std::string s_FontFilePath;
    
    int i_LastMinute;
    
protected:
    
};

#endif /* TodayInfo_h */
