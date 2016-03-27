#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    3/26/2016
#
#    Purpose: Construct the Turret Project
#

#----------------------------------#
#-     Set CMake Requirements     -#
#----------------------------------#
cmake_minimum_required( FATAL_ERROR VERSION 2.8 )

#------------------------------#
#-     Define our Project     -#
#------------------------------#
project( Pi-Defender)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

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
     src/main.cpp
     src/core/GPIO_Utilities.cpp
     src/core/GPIO_Utilities.hpp
     src/core/Log_Utilities.cpp
     src/core/Log_Utilities.hpp
     src/core/Options.cpp
     src/core/Options.hpp
     src/pwm/PWM_Driver.cpp
     src/pwm/PWM_Driver.hpp
     src/pwm/Turret_Controller.cpp
     src/pwm/Turret_Controller.hpp
)

#------------------------------------#
#-    Construct the Application     -#
#------------------------------------#
add_executable( pi-defender
                ${PI_DEFENDER_SOURCES} )


#-----------------------#
#-   Link Libraries    -#
#-----------------------#
target_link_libraries( pi-defender
                       wiringPi
                       ${Boost_LIBRARIES} )

