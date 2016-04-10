#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/10/2016
#
#    Purpose:  Construct PiDefender Application
#

#-------------------------#
#-     CMake Version     -#
#-------------------------#
cmake_minimum_required( FATAL_ERROR VERSION 2.8 )


#---------------------------------#
#-      Project Information      -#
#---------------------------------#
project(Pi-Defender)


#------------------------------------------#
#-     Add C++ Compile Flags Support      -#
#------------------------------------------#
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall" )


#-----------------------------------#
#-     Include PiDef Libraries     -#
#-----------------------------------#
include_directories( ../../lib )


#-------------------------------#
#-     Find Boost Libraries    -#
#-------------------------------#
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package( Boost REQUIRED
               COMPONENTS
                    system
                    filesystem
                    log
                    thread )
include_directories( ${Boost_INCLUDE_DIRS} )


#-----------------------------------#
#-     Define our Source Files     -#
#-----------------------------------#
set( PI_DEFENDER_SOURCES 
     main.cpp
     calibration/Calibration_Mode.cpp
     core/Enumerations.cpp
     core/Options.cpp
)


#---------------------------------#
#-    Define our Header Files    -#
#---------------------------------#
set( PI_DEFENDER_HEADERS
     calibration/Calibration_Mode.hpp
     core/Enumerations.hpp
     core/Options.hpp
)


#------------------------------------#
#-    Construct the Application     -#
#------------------------------------#
add_executable( pi-defender
                ${PI_DEFENDER_SOURCES}
                ${PI_DEFENDER_HEADERS}
)


#-----------------------#
#-   Link Libraries    -#
#-----------------------#
target_link_libraries( pi-defender
                       PiDef
                       ${Boost_LIBRARIES}
                       pthread
)
