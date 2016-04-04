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


#------------------------------#
#-     Application Flags      -#
#------------------------------#
option( USE_WIRINGPI "Use WiringPi for I2C Servo Control" ON )


#-------------------------#
#-     Find WiringPi     -#
#-------------------------#
set(PIDEF_USE_WIRINGPI 0)
if( USE_WIRINGPI )

    set(WIRINGPI_LIBRARY wiringPi)
    set(PIDEF_USE_WIRINGPI 1)
endif()

#-------------------------------#
#-     Find OpenCV Libraries   -#
#-------------------------------#
find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

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


#-------------------------------------#
#-   Create the Configuration File   -#
#-------------------------------------#
configure_file( "${PROJECT_SOURCE_DIR}/src/PiDefender.hpp.in"
                "${PROJECT_SOURCE_DIR}/src/PiDefender.hpp" )


#-----------------------------------#
#-     Define our Source Files     -#
#-----------------------------------#
set( PI_DEFENDER_SOURCES 
     src/main.cpp
     src/PiDefender.hpp
     src/calibration/Calibration_Mode.cpp
     src/calibration/Calibration_Mode.hpp
     src/camera/Tracker.cpp
     src/camera/Tracker.hpp
     src/core/Enumerations.cpp
     src/core/Enumerations.hpp
     src/core/GPIO_Utilities.cpp
     src/core/GPIO_Utilities.hpp
     src/core/Log_Utilities.cpp
     src/core/Log_Utilities.hpp
     src/core/Options.cpp
     src/core/Options.hpp
     src/core/String_Utilities.cpp
     src/core/String_Utilities.hpp
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
                       ${WIRINGPI_LIBRARY}
                       ${Boost_LIBRARIES}
                       ${OpenCV_LIBS}
                       pthread
                       ncurses
)

