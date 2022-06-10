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
