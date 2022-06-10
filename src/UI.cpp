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

// External

// Project
#include "./UI.h"
#include "./UIComponent/Background.h"
#include "./UIComponent/TodayInfo.h"
#include "./Logger.h"

// Pre-defined
#ifndef UI_ASSET_DIR
    #define UI_ASSET_DIR "/var/mrh/mrangeui"
#endif
#ifndef UI_FONT_PATH
    #define UI_FONT_PATH "/var/mrh/mrangeui/Font.ttf"
#endif


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

UI::UI(int i_W,
       int i_H) : p_Window(NULL),
                  p_Renderer(NULL),
                  i_W(-1), // Keep -1 for UpdateSize()
                  i_H(-1)
{
    // Set Hints
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
    // Build the ui window first
    p_Window = SDL_CreateWindow("MRange", 
                                0, 0, 
                                i_W, i_H, 
                                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    if (p_Window == NULL)
    {
        throw Exception("Failed to create window!");
    }
    
    // Next create a renderer for this window
    p_Renderer = SDL_CreateRenderer(p_Window, 
                                    0, 
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    
    if (p_Renderer == NULL)
    {
        SDL_DestroyWindow(p_Window);
        throw Exception("Failed to create renderer!");
    }
    
    // Now we update the UI with the size
    UpdateSize(i_W, i_H);
}

UI::~UI() noexcept
{
    for (auto& Component : l_Component)
    {
        delete Component;
    }
    
    if (p_Renderer == NULL)
    {
        SDL_DestroyRenderer(p_Renderer);
    }
    
    if (p_Window == NULL)
    {
        SDL_DestroyWindow(p_Window);
    }
}

//*************************************************************************************
// Update
//*************************************************************************************

void UI::UpdateSize(int i_W, int i_H) noexcept
{
    // Same size?
    if (this->i_W == i_W && this->i_H == i_H)
    {
        return;
    }
    
    this->i_W = i_W;
    this->i_H = i_H;
    
    // Clear old UI elements
    for (auto& Component : l_Component)
    {
        delete Component;
    }
    
    l_Component.clear();
    
    // Now rebuild all components
    SDL_Rect c_Position;
    
    try
    {
        // Background
        c_Position.x = 0;
        c_Position.y = 0;
        c_Position.w = i_W;
        c_Position.h = i_H;
        
        l_Component.emplace_back(new Background(p_Renderer,
                                                c_Position,
                                                UI_ASSET_DIR));
        // Today Info
        c_Position.x = i_W / 4;
        c_Position.y = i_H / 4;
        c_Position.w = i_W / 2;
        c_Position.h = i_H / 2;
        
        l_Component.emplace_back(new TodayInfo(p_Renderer,
                                               c_Position,
                                               UI_FONT_PATH));
    }
    catch (std::exception& e)
    {
        Logger::Singleton().Log(Logger::ERROR, "Failed to create components: " + 
                                               std::string(e.what()), 
                                "UI.cpp", __LINE__);
    }
}

//*************************************************************************************
// Draw
//*************************************************************************************

void UI::Draw(Clock const& c_Clock) noexcept
{
    Logger& c_Logger = Logger::Singleton();
    
    SDL_SetRenderTarget(p_Renderer, NULL);
    SDL_SetRenderDrawColor(p_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(p_Renderer);
    
    SDL_Texture* p_Texture;
    
    for (auto& Component : l_Component)
    {
        // Update component first
        if (Component == NULL)
        {
            c_Logger.Log(Logger::ERROR, "Invalid component!", 
                         "UI.cpp", __LINE__);
            continue;
        }
        
        Component->Update(p_Renderer, c_Clock);
        
        // Updated, draw component texture
        if ((p_Texture = Component->GetTexture()) == NULL)
        {
            c_Logger.Log(Logger::ERROR, "Invalid component texture!", 
                         "UI.cpp", __LINE__);
        }
        else if (SDL_RenderCopy(p_Renderer,
                                p_Texture,
                                NULL, &(Component->GetPosition())) < 0)
        {
            c_Logger.Log(Logger::ERROR, "Failed to draw component!", 
                         "UI.cpp", __LINE__);
        }
    }
    
    SDL_RenderPresent(p_Renderer);
}
