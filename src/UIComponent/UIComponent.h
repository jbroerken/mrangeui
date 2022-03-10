/**
 *  UIComponent.h
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

#ifndef UIComponent_h
#define UIComponent_h

// C / C++
#include <memory>

// External
#include <SDL2/SDL.h>

// Project
#include "../Clock.h"
#include "../Exception.h"


class UIComponent
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
     */
    
    UIComponent(SDL_Renderer* p_Renderer,
                SDL_Rect const& c_Position) : p_Target(NULL)
    {
        this->c_Position.x = c_Position.x;
        this->c_Position.y = c_Position.y;
        this->c_Position.w = c_Position.w;
        this->c_Position.h = c_Position.h;
        
        p_Target = SDL_CreateTexture(p_Renderer, 
                                     SDL_PIXELFORMAT_RGBA8888, 
                                     SDL_TEXTUREACCESS_TARGET, 
                                     c_Position.w, c_Position.h);
        
        if (p_Target == NULL)
        {
            throw Exception("Failed to create ui component target texture!");
        }
        
        SDL_SetTextureBlendMode(p_Target, SDL_BLENDMODE_BLEND);
    }
    
    /**
     *  Default destructor.
     */
    
    ~UIComponent() noexcept
    {
        if (p_Target != NULL)
        {
            SDL_DestroyTexture(p_Target);
        }
    }
    
    //*************************************************************************************
    // Update
    //*************************************************************************************
    
    /**
     *  Update the UI component.
     *  
     *  \param p_Renderer The renderer to use for updating.
     *  \param c_Clock The clock in use.
     */
    
    virtual void Update(SDL_Renderer* p_Renderer, Clock const& c_Clock) noexcept
    {}
    
    //*************************************************************************************
    // Getters
    //*************************************************************************************
    
    /**
     *  Get the component texture.
     *  
     *  \return The component texture.
     */
    
    SDL_Texture* GetTexture() noexcept
    {
        return p_Target;
    }
    
    /**
     *  Get the component position.
     *  
     *  \return The component position.
     */
    
    SDL_Rect const& GetPosition() const noexcept
    {
        return c_Position;
    }
    
private:
    
    //*************************************************************************************
    // Data
    //*************************************************************************************
    
    SDL_Rect c_Position;
    
protected:
    
    //*************************************************************************************
    // Data
    //*************************************************************************************
    
    SDL_Texture* p_Target;
};

#endif /* UIComponent_h */
