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
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Project
#include "./TodayInfo.h"
#include "../Logger.h"


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

TodayInfo::TodayInfo(SDL_Renderer* p_Renderer,
                     SDL_Rect const& c_Position,
                     std::string const& s_FontFilePath) : UIComponent(p_Renderer, 
                                                                      c_Position),
                                                          s_FontFilePath(s_FontFilePath),
                                                          i_LastMinute(-1)
{}

TodayInfo::~TodayInfo() noexcept
{}

//*************************************************************************************
// Update
//*************************************************************************************

void TodayInfo::Update(SDL_Renderer* p_Renderer, Clock const& c_Clock) noexcept
{
    // Check the current time first
    if (i_LastMinute == c_Clock.GetMinutes())
    {
        // No need to redraw
        return;
    }
    else
    {
        // We check minute changes for updates
        i_LastMinute = c_Clock.GetMinutes();
    }
    
    // Build
    SDL_Texture* p_Time = NULL;
    SDL_Texture* p_Date = NULL;
    
    try
    {
        p_Time = CreateStringTexture(p_Renderer, 
                                     c_Clock.GetTimeString(),
                                     156);
        p_Date = CreateStringTexture(p_Renderer, 
                                     c_Clock.GetDateString(),
                                     48);
    }
    catch (Exception& e)
    {
        if (p_Time != NULL)
        {
            SDL_DestroyTexture(p_Time);
        }
        
        Logger::Singleton().Log(Logger::ERROR, e.what(), 
                                "Date.cpp", __LINE__);
        return;
    }
    
    // Prepare target
    SDL_SetRenderTarget(p_Renderer, p_Target);
    SDL_SetRenderDrawColor(p_Renderer, 0, 0, 0, 0);
    SDL_RenderClear(p_Renderer);
    
    // Define render positions and draw
    SDL_Rect c_TimeRect;
    SDL_Rect c_DateRect;
    
    if (SDL_QueryTexture(p_Time, NULL, NULL, &(c_TimeRect.w), &(c_TimeRect.h)) < 0 ||
        SDL_QueryTexture(p_Date, NULL, NULL, &(c_DateRect.w), &(c_DateRect.h)) < 0)
    {
        Logger::Singleton().Log(Logger::ERROR, "Failed to querry textures!", 
                                "Date.cpp", __LINE__);
    }
    else
    {
        SDL_Rect const& c_Position = GetPosition();
        
        c_TimeRect.w = (c_Position.w < c_TimeRect.w ? c_Position.w : c_TimeRect.w);
        c_TimeRect.h = ((c_Position.h / 2) < c_TimeRect.h ? (c_Position.h / 2) : c_TimeRect.h);
        c_DateRect.w = (c_Position.w < c_DateRect.w ? c_Position.w : c_DateRect.w);
        c_DateRect.h = ((c_Position.h / 2) < c_DateRect.h ? (c_Position.h / 2) : c_DateRect.h);
        
        c_TimeRect.x = (c_Position.w / 2) - (c_TimeRect.w / 2);
        c_TimeRect.y = (c_Position.h / 2) - ((c_TimeRect.h + c_DateRect.h) / 2);
        c_DateRect.x = (c_Position.w / 2) - (c_DateRect.w / 2);
        c_DateRect.y = (c_TimeRect.y + c_TimeRect.h);
        
        if (SDL_RenderCopy(p_Renderer, p_Time, NULL, &c_TimeRect) < 0 || 
            SDL_RenderCopy(p_Renderer, p_Date, NULL, &c_DateRect) < 0)
        {
            Logger::Singleton().Log(Logger::ERROR, "Failed to draw textures!", 
                                    "Date.cpp", __LINE__);
        }
    }
    
    // Finish target
    SDL_DestroyTexture(p_Time);
    SDL_DestroyTexture(p_Date);
    
    SDL_SetRenderTarget(p_Renderer, NULL);
}

//*************************************************************************************
// Textures
//*************************************************************************************

SDL_Texture* TodayInfo::CreateStringTexture(SDL_Renderer* p_Renderer, std::string const& s_String, int i_Size)
{
    // Get font first
    TTF_Font* p_Font = NULL;
    
    if ((p_Font = TTF_OpenFont(s_FontFilePath.c_str(), i_Size)) == NULL)
    {
        throw Exception("Failed to load font file: " + s_FontFilePath + "!");
    }
    
    // Now create a surface from the font
    SDL_Color c_Color = { 255, 255, 255 };
    SDL_Surface* p_Surface = TTF_RenderUTF8_Blended(p_Font, 
                                                    s_String.c_str(), 
                                                    c_Color);
    TTF_CloseFont(p_Font);
    
    if (p_Surface == NULL)
    {
        throw Exception("Failed to render text!");
    }
    
    SDL_Texture* p_Texture = SDL_CreateTextureFromSurface(p_Renderer, 
                                                          p_Surface);
    SDL_FreeSurface(p_Surface);
    
    if (p_Texture == NULL)
    {
        throw Exception("Failed to create texture!");
    }
    
    return p_Texture;
}
