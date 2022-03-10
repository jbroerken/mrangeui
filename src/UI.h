/**
 *  UI.h
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
