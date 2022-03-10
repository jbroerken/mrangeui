/**
 *  Background.cpp
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

// C / C++
#include <math.h>

// External
#include <SDL2/SDL_image.h>

// Project
#include "./Background.h"
#include "../Logger.h"

// Pre-defined
namespace
{
    enum Asset
    {
        BACKGROUND = 0,
        FOREGROUND_LEFT = 1,
        FOREGROUND_RIGHT = 2,
        SUN = 3,
        MOON = 4,
        
        ASSET_MAX = MOON,
        
        ASSET_COUNT = ASSET_MAX + 1
    };
    
    const char* p_Asset[ASSET_COUNT] =
    {
        "Background.png",
        "Foreground_Left.png",
        "Foreground_Right.png",
        "Sun.png",
        "Moon.png"
    };
    
    enum Colors
    {
        NIGHT = 0,
        MORNING = 1,
        DAY = 2,
        EVENING = 3,
        
        COLORS_MAX = EVENING,
        
        COLORS_COUNT = COLORS_MAX + 1
    };
    
    Uint8 p_Colors[COLORS_COUNT][3] =
    {
        { 0, 43, 72 },
        { 247, 186, 0 },
        { 0, 161, 254 },
        { 238, 94, 73 },
    };
    
    constexpr Uint8 u8_MorningBegin = 6;
    constexpr Uint8 u8_MorningEnd = 7;
    constexpr Uint8 u8_DayBegin = 7;
    constexpr Uint8 u8_DayEnd = 19;
    constexpr Uint8 u8_EveningBegin = 19;
    constexpr Uint8 u8_EveningEnd = 20;
    constexpr Uint8 u8_NightBegin = 20;
    constexpr Uint8 u8_NightEnd = 6;
}


//*************************************************************************************
// Constructor / Destructor
//*************************************************************************************

Background::Background(SDL_Renderer* p_Renderer,
                       SDL_Rect const& c_Position,
                       std::string const& s_AssetDir) : UIComponent(p_Renderer, 
                                                                    c_Position),
                                                        i_LastMinute(-1)
{
    for (size_t i = 0; i < ASSET_COUNT; ++i)
    {
        std::string s_FilePath = s_AssetDir +
                                 "/" +
                                 p_Asset[i];
        
        SDL_Surface* p_Surface = IMG_Load(s_FilePath.c_str());
        
        if (p_Surface == NULL)
        {
            throw Exception("Failed to load file: " + s_FilePath + "!");
        }
        
        SDL_Texture* p_Texture = SDL_CreateTextureFromSurface(p_Renderer, p_Surface);
        SDL_FreeSurface(p_Surface);
        
        if (p_Texture == NULL)
        {
            throw Exception("Failed to create texture for file: " + s_FilePath + "!");
        }
        
        try
        {
            dq_Asset.emplace_back(p_Texture);
        }
        catch (...)
        {
            SDL_DestroyTexture(p_Texture);
            throw Exception("Failed to store texture!");
        }
    }
}

Background::~Background() noexcept
{
    for (auto& Asset : dq_Asset)
    {
        SDL_DestroyTexture(Asset);
    }
}

//*************************************************************************************
// Update
//*************************************************************************************

void Background::Update(SDL_Renderer* p_Renderer, Clock const& c_Clock) noexcept
{
    Logger& c_Logger = Logger::Singleton();
    
    // Check the current time first
    if (i_LastMinute == c_Clock.GetMinutes())
    {
        return;
    }
    else
    {
        i_LastMinute = c_Clock.GetMinutes();
    }
    
    // Set the color to use for drawing
    SDL_Color c_Color = CalculateTintColor(c_Clock);
    
    // Prepare target
    SDL_SetRenderTarget(p_Renderer, p_Target);
    SDL_SetRenderDrawColor(p_Renderer, 0, 0, 0, 0);
    SDL_RenderClear(p_Renderer);
    
    // Define render positions
    SDL_Rect c_Rect;
    
    // Draw background first
    c_Rect.x = 0;
    c_Rect.y = 0;
    c_Rect.w = GetPosition().w;
    c_Rect.h = GetPosition().h;
    
    SDL_SetTextureColorMod(dq_Asset[BACKGROUND], c_Color.r, c_Color.g, c_Color.b);
    
    if (SDL_RenderCopy(p_Renderer, dq_Asset[BACKGROUND], NULL, &c_Rect) < 0)
    {
        c_Logger.Log(Logger::ERROR, "Failed to draw background texture!", 
                     "Background.cpp", __LINE__);
    }
    
    // Solar Body (covered by foreground)
    SDL_Texture* p_SolarBody = NULL;
    
    if (c_Clock.GetHours() >= u8_MorningBegin && c_Clock.GetHours() <= u8_EveningEnd)
    {
        p_SolarBody = dq_Asset[SUN];
    }
    else if (c_Clock.GetHours() >= u8_NightBegin || c_Clock.GetHours() <= u8_NightEnd)
    {
        p_SolarBody = dq_Asset[MOON];
    }
    
    if (p_SolarBody != NULL)
    {
        if (SDL_QueryTexture(p_SolarBody, NULL, NULL, &(c_Rect.w), &(c_Rect.h)) == 0)
        {
            SDL_Point c_Point = CalculateSolarBodyPosition(c_Clock);
            
            c_Rect.x = c_Point.x - (c_Rect.w / 2);
            c_Rect.y = c_Point.y - (c_Rect.h / 2);
            
            if (SDL_RenderCopy(p_Renderer, p_SolarBody, NULL, &c_Rect) < 0)
            {
                c_Logger.Log(Logger::ERROR, "Failed to draw solar body texture!", 
                             "Background.cpp", __LINE__);
            }
        }
        else
        {
            c_Logger.Log(Logger::ERROR, "Failed to query solar body texture!", 
                         "Background.cpp", __LINE__);
        }
    }
    
    // Foreground
    SDL_Rect c_RectB;
    
    if (SDL_QueryTexture(dq_Asset[FOREGROUND_LEFT], NULL, NULL, &(c_Rect.w), &(c_Rect.h)) == 0 &&
        SDL_QueryTexture(dq_Asset[FOREGROUND_RIGHT], NULL, NULL, &(c_RectB.w), &(c_RectB.h)) == 0)
    {
        c_Rect.x = 0;
        c_Rect.y = GetPosition().h - c_Rect.h;
        
        c_RectB.x = GetPosition().w - c_RectB.w;
        c_RectB.y = GetPosition().h - c_RectB.h;
        
        SDL_SetTextureColorMod(dq_Asset[FOREGROUND_LEFT], c_Color.r, c_Color.g, c_Color.b);
        SDL_SetTextureColorMod(dq_Asset[FOREGROUND_RIGHT], c_Color.r, c_Color.g, c_Color.b);
        
        if (SDL_RenderCopy(p_Renderer, dq_Asset[FOREGROUND_LEFT], NULL, &c_Rect) < 0 || 
            SDL_RenderCopy(p_Renderer, dq_Asset[FOREGROUND_RIGHT], NULL, &c_RectB) < 0)
        {
            c_Logger.Log(Logger::ERROR, "Failed to draw foreground textures!", 
                         "Background.cpp", __LINE__);
        }
    }
    else
    {
        c_Logger.Log(Logger::ERROR, "Failed to query foreground textures!", 
                     "Background.cpp", __LINE__);
    }
    
    // Reset target
    SDL_SetRenderTarget(p_Renderer, NULL);
}

//*************************************************************************************
// Color
//*************************************************************************************

static inline Uint8 MixColor(Uint8 u8_CurrentColor, Uint8 u8_NextColor, float f32_Percent) noexcept
{
    return (u8_CurrentColor * (1 - f32_Percent)) + (u8_NextColor * f32_Percent);
}

SDL_Color Background::CalculateTintColor(Clock const& c_Clock)
{
    // Get percentage of mix
    int i_Hour = c_Clock.GetHours();
    float f32_Percent = (float)(c_Clock.GetMinutes()) / 60.f;
    
    // Decide on the two tint colors to use
    if (i_Hour == u8_MorningBegin)
    {
        /**
         *  Night -> Morning
         */
        
        return { MixColor(p_Colors[NIGHT][0], p_Colors[MORNING][0], f32_Percent),
                 MixColor(p_Colors[NIGHT][1], p_Colors[MORNING][1], f32_Percent),
                 MixColor(p_Colors[NIGHT][2], p_Colors[MORNING][2], f32_Percent) };
    }
    else if (i_Hour == u8_DayBegin)
    {
        /**
         *  Morning -> Day
         */
        
        return { MixColor(p_Colors[MORNING][0], p_Colors[DAY][0], f32_Percent),
                 MixColor(p_Colors[MORNING][1], p_Colors[DAY][1], f32_Percent),
                 MixColor(p_Colors[MORNING][2], p_Colors[DAY][2], f32_Percent) };
    }
    else if (i_Hour == u8_EveningBegin)
    {
        /**
         *  Day -> Evening
         */
        
        return { MixColor(p_Colors[DAY][0], p_Colors[EVENING][0], f32_Percent),
                 MixColor(p_Colors[DAY][1], p_Colors[EVENING][1], f32_Percent),
                 MixColor(p_Colors[DAY][2], p_Colors[EVENING][2], f32_Percent) };
    }
    else if (i_Hour == u8_NightBegin)
    {
        /**
         *  Evening -> Night
         */
        
        return { MixColor(p_Colors[EVENING][0], p_Colors[NIGHT][0], f32_Percent),
                 MixColor(p_Colors[EVENING][1], p_Colors[NIGHT][1], f32_Percent),
                 MixColor(p_Colors[EVENING][2], p_Colors[NIGHT][2], f32_Percent) };
    }
    else if (i_Hour >= u8_NightBegin || i_Hour <= u8_NightEnd)
    {
        /**
         *  Night
         */
        
        return { p_Colors[NIGHT][0], 
                 p_Colors[NIGHT][1], 
                 p_Colors[NIGHT][2] };
    }
    else
    {
        /**
         *  Day
         */
        
        return { p_Colors[DAY][0], 
                 p_Colors[DAY][1], 
                 p_Colors[DAY][2] };
    }
}

//*************************************************************************************
// Solar Body
//*************************************************************************************

SDL_Point Background::CalculateSolarBodyPosition(Clock const& c_Clock)
{
    // Get amount moved in minutes
    int i_Hour = c_Clock.GetHours();
    int i_Minutes = c_Clock.GetMinutes();
    int i_HourInterval = 0;
    
    if (i_Hour >= u8_MorningBegin && i_Hour <= u8_EveningEnd)
    {
        i_HourInterval = u8_EveningEnd - u8_MorningBegin;
        i_Hour -= u8_MorningBegin;
    }
    else
    {
        i_HourInterval = (24 - u8_NightBegin) + u8_NightEnd;
        
        // Correct hours due to 23->0 change
        if (i_Hour >= u8_NightBegin)
        {
            i_Hour -= u8_NightBegin;
        }
        else if (i_Hour <= u8_NightEnd)
        {
            i_Hour += 24 - u8_NightBegin;
        }
    }
    
    int i_MinutesMoved = (i_Hour * 60) + i_Minutes;
    
    // We check the progress of total move time next
    float f32_MovePercent = (float)i_MinutesMoved / ((float)i_HourInterval * 60.f);
    
    // Now we can check where the body is, based on a half circle
    // @NOTE: sin and cos work on radians, not degrees!
    double f64_Angle = (M_PI * f32_MovePercent) + ((90.f * M_PI) / 180.f);
    
    // Now return the points based on R of background W
    int i_HalfW = GetPosition().w / 2;
    
    int i_X = i_HalfW - (int)(i_HalfW * sin(f64_Angle));
    int i_Y = GetPosition().h + (int)(i_HalfW * cos(f64_Angle));
    
    return { i_X,
             i_Y };
}
