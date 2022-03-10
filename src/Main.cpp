/**
 *  Main.cpp
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
#include <csignal>
#include <cstdlib>
#include <new>
#include <clocale>

// External
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Project
#include "./UI.h"
#include "./Locale.h"
#include "./Logger.h"
#include "./Revision.h"

// Pre-defined
namespace
{
    // Signal
    int i_LastSignal = -1;
    
    // Locale
    std::string s_DefaultLocale = "en_US.UTF-8";
}


//*************************************************************************************
// Signal Handler
//*************************************************************************************

// Prevent name wrangling
extern "C"
{
    void SignalHandler(int i_Signal)
    {
        switch (i_Signal)
        {
            case SIGILL:
            case SIGTRAP:
            case SIGFPE:
            case SIGABRT:
            case SIGSEGV:
                Logger::Singleton().Backtrace(25, "Caught Signal: " + std::to_string(i_Signal));
                exit(EXIT_FAILURE);
                break;
                
            case SIGTERM:
            case SIGHUP:
                i_LastSignal = i_Signal;
                break;
                
            default:
                i_LastSignal = -1;
                break;
        }
    }
}

//*************************************************************************************
// Locale
//*************************************************************************************

static void SetLocale() noexcept
{
    Logger& s_Logger = Logger::Singleton();
    s_Logger.Log(Logger::INFO, "Updating locale...",
                 "Main.cpp", __LINE__);
    
    std::string s_Locale;
    
    try
    {
        Locale s_File;
        s_Locale = s_File.GetLocale();
    }
    catch (Exception& e)
    {
        s_Logger.Log(Logger::WARNING, "Failed to read locale file: " +
                                      e.what2(),
                     "Main.cpp", __LINE__);
        s_Locale = s_DefaultLocale;
    }
    
    std::setlocale(LC_ALL, s_Locale.c_str());
    
    if (s_Locale.compare(std::setlocale(LC_ALL, NULL)) != 0)
    {
        s_Logger.Log(Logger::WARNING, "Failed to set locale to " + s_Locale + "!",
                     "Main.cpp", __LINE__);
        std::setlocale(LC_ALL, s_DefaultLocale.c_str());
    }
    else
    {
        s_Logger.Log(Logger::INFO, "Locale set to " + s_Locale + "!",
                     "Main.cpp", __LINE__);
    }
}

//*************************************************************************************
// Main
//*************************************************************************************

int main(int argc, char* argv[])
{
    // Log Setup
    Logger& c_Logger = Logger::Singleton();
    c_Logger.Log(Logger::INFO, "=============================================", "Main.cpp", __LINE__);
    c_Logger.Log(Logger::INFO, "= Started MRange UI (" + std::string(VERSION_NUMBER) + ")", "Main.cpp", __LINE__);
    c_Logger.Log(Logger::INFO, "=============================================", "Main.cpp", __LINE__);
    
    // Install signal handlers
    std::signal(SIGTERM, SignalHandler);
    std::signal(SIGILL, SignalHandler);
    std::signal(SIGTRAP, SignalHandler);
    std::signal(SIGFPE, SignalHandler);
    std::signal(SIGABRT, SignalHandler);
    std::signal(SIGSEGV, SignalHandler);
    std::signal(SIGHUP, SignalHandler);
    
    // Load configuration
    SetLocale();
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        c_Logger.Log(Logger::ERROR, "Failed to initialize SDL!", "Main.cpp", __LINE__);
        return EXIT_FAILURE;
    }
    else if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        c_Logger.Log(Logger::ERROR, "Failed to initialize SDL_image!", "Main.cpp", __LINE__);
        return EXIT_FAILURE;
    }
    else if (TTF_Init() < 0)
    {
        c_Logger.Log(Logger::ERROR, "Failed to initialize SDL_ttf!", "Main.cpp", __LINE__);
        return EXIT_FAILURE;
    }
    
    // Update UI
    try
    {
        UI c_UI(1920,
                1080);
        Clock c_Clock;
        SDL_Event c_Event;
        
        do
        {
            // Update clock first
            c_Clock.Update();
            
            // Draw the UI
            c_UI.Draw(c_Clock);
            
            // Now update all recieved events
            while (SDL_PollEvent(&c_Event) > 0)
            {
                // Close ui?
                if (c_Event.type == SDL_QUIT)
                {
                    i_LastSignal = SIGTERM;
                    break;
                }
                
                // Window event to handle
                if (c_Event.type == SDL_WINDOWEVENT)
                {
                    switch (c_Event.window.event)
                    {
                            /**
                             *  Resize
                             */
                            
                        case SDL_WINDOWEVENT_RESIZED:
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            c_UI.UpdateSize(c_Event.window.data1, c_Event.window.data2);
                            break;
                            
                            /**
                             *  Unk
                             */
                            
                        default:
                            break;
                    }
                }
            }
        }
        while (i_LastSignal != SIGTERM);
    }
    catch (std::exception& e)
    {
        c_Logger.Log(Logger::ERROR, e.what(), "Main.cpp", __LINE__);
    }
    
    // All done, now terminate
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    c_Logger.Log(Logger::INFO, "Successfully closed MRange UI.", "Main.cpp", __LINE__);
    return EXIT_SUCCESS;
}
