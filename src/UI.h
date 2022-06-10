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

#ifndef UI_h
#define UI_h

// C / C++
#include <list>

// External

// Project
#include "./UIComponent/UIComponent.h"
#include "./Clock.h"


class UI
{
public:
    
    //*************************************************************************************
    // Constructor / Destructor
    //*************************************************************************************
    
    /**
     *  Default constructor.
     *  
     *  \param i_W The user interface width.
     *  \param i_H The user interface height.  
     */
    
    UI(int i_W,
       int i_H);
    
    /**
     *  Default destructor.
     */
    
    ~UI() noexcept;
    
    //*************************************************************************************
    // Update
    //*************************************************************************************
    
    /**
     *  Update the user interface size.
     *  
     *  \param i_W The user interface width.
     *  \param i_H The user interface height.
     */
    
    void UpdateSize(int i_W, int i_H) noexcept;
    
    //*************************************************************************************
    // Draw
    //*************************************************************************************
    
    /**
     *  Update the user interface.
     *  
     *  \param c_Clock The clock in use.
     */
    
    void Draw(Clock const& c_Clock) noexcept;
    
private:
    
    //*************************************************************************************
    // Data
    //*************************************************************************************
    
    SDL_Window* p_Window;
    SDL_Renderer* p_Renderer;
    
    int i_W;
    int i_H;
    
    std::list<UIComponent*> l_Component;
    
protected:
    
};

#endif /* UI_h */
