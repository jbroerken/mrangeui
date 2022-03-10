#########################################################################
#
#  CMAKE
#
#########################################################################

###
#  Minimum Version
#  ---------------
#  The CMake version required.
###
cmake_minimum_required(VERSION 3.1)

###
#  CMake Configuration
#  -------------------
#  Configuration settings for CMake.
#
#  NOTE:
#  These settings have to be applied before the project() setting!
###
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 14)

###
#  Project Info
#  ------------
#  General simple information about our project.
###
project(mrangeui VERSION 1.0.0
                 DESCRIPTION "MRange UI"
                 LANGUAGES CXX)

#########################################################################
#
#  PATHS
#
#########################################################################

###
#  Install Paths
#  -------------
#  The paths for our created binary file(s).
###
set(BIN_INSTALL_PATH "/usr/local/bin/")

###
#  Build Paths
#  -----------
#  The paths for the cmake build.
###
set(BUILD_DIR_PATH "${CMAKE_SOURCE_DIR}/build/")
file(MAKE_DIRECTORY ${BUILD_DIR_PATH})

###
#  Source Paths
#  ------------
#  The paths to the source files to use.
#  Add OS specific source files in their own list.
###
set(SRC_DIR_PATH "${CMAKE_SOURCE_DIR}/src/")

set(SRC_LIST_MRANGEUI "${SRC_DIR_PATH}/UIComponent/Background.cpp"
                      "${SRC_DIR_PATH}/UIComponent/Background.h"
                      "${SRC_DIR_PATH}/UIComponent/TodayInfo.cpp"
                      "${SRC_DIR_PATH}/UIComponent/TodayInfo.h"
                      "${SRC_DIR_PATH}/UIComponent/UIComponent.h"
                      "${SRC_DIR_PATH}/UI.cpp"
                      "${SRC_DIR_PATH}/UI.h"
                      "${SRC_DIR_PATH}/Locale.cpp"
                      "${SRC_DIR_PATH}/Locale.h"
                      "${SRC_DIR_PATH}/Clock.cpp"
                      "${SRC_DIR_PATH}/Clock.h"
                      "${SRC_DIR_PATH}/Logger.cpp"
                      "${SRC_DIR_PATH}/Logger.h"
                      "${SRC_DIR_PATH}/Exception.h"
                      "${SRC_DIR_PATH}/Main.cpp"
                      "${SRC_DIR_PATH}/Revision.h")

#########################################################################
#
#  TARGET
#
#########################################################################

###
#  Target
#  ------
#  The target(s) to build.
###
add_executable(mrangeui ${SRC_LIST_MRANGEUI})

###
#  Required Libraries
#  ------------------
#  Libraries required by this application.
###
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(SDL2 REQUIRED)
find_library(libmrhbf NAMES mrhbf REQUIRED)

target_link_libraries(mrangeui ${SDL2_LIBRARIES})
target_link_libraries(mrangeui PUBLIC mrhbf)

###
#  Source Definitions
#  ------------------
#  Preprocessor source definitions.
###
target_compile_definitions(mrangeui PRIVATE MRANGEUI_LOG_FILE_PATH="/var/log/mrh/mrangeui.log")
target_compile_definitions(mrangeui PRIVATE MRANGEUI_BACKTRACE_FILE_PATH="/var/log/mrh/bt_mrangeui.log")
target_compile_definitions(mrangeui PRIVATE MRANGEUI_LOGGER_PRINT_CLI=0)
target_compile_definitions(mrangeui PRIVATE MRH_LOCALE_FILE_PATH="/usr/local/etc/mrh/MRH_Locale.conf")
target_compile_definitions(mrangeui PRIVATE UI_ASSET_DIR="/var/mrh/mrangeui")
target_compile_definitions(mrangeui PRIVATE UI_FONT_PATH="/var/mrh/mrangeui/Font.ttf")

###
#  Install
#  -------
#  Application installation.
###
install(TARGETS mrangeui
        DESTINATION ${BIN_INSTALL_PATH})