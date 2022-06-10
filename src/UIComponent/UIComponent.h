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
