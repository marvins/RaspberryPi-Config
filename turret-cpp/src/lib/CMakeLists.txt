#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/10/2016
#    
#    Purpose:  Construct PiDef Library
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

#-------------------------#
#-     Find WiringPi     -#
#-------------------------#
set(PIDEF_USE_WIRINGPI 0)
if( USE_WIRINGPI )

    set(PIDEF_USE_WIRINGPI 1)
    find_package( wiringPi )

endif()


#-------------------------------------#
#-   Create the Configuration File   -#
#-------------------------------------#
configure_file( "${CMAKE_SOURCE_DIR}/src/lib/PiDefender.hpp.in"
                "${CMAKE_SOURCE_DIR}/src/lib/PiDefender.hpp" )


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


#------------------------#
#-     Find WiringPi    -#
#------------------------#
message("WiringPi Found     : ${WIRINGPI_FOUND}")
message("WiringPi Include   : ${WIRINGPI_INCLUDE_DIR}")
message("WiringPi Library   : ${WIRINGPI_LIBRARY}")
message("WiringPiDev Library: ${WIRINGPI_DEV_LIBRARY}")

#-----------------------------------#
#-     Define our Header Files     -#
#-----------------------------------#
set( PI_DEFENDER_HEADERS
     PiDefender.hpp
     PiDef/camera/Tracker.hpp
     PiDef/core/Enumerations.hpp
     PiDef/core/GPIO_Utilities.hpp
     PiDef/core/Log_Utilities.hpp
     PiDef/core/String_Utilities.hpp
     PiDef/pwm/PWM_Driver.hpp
     PiDef/pwm/Turret_Controller.hpp
)

#-----------------------------------#
#-     Define our Source Files     -#
#-----------------------------------#
set( PI_DEFENDER_SOURCES 
     PiDef/camera/Tracker.cpp
     PiDef/core/Enumerations.cpp
     PiDef/core/GPIO_Utilities.cpp
     PiDef/core/Log_Utilities.cpp
     PiDef/core/String_Utilities.cpp
     PiDef/pwm/PWM_Driver.cpp
     PiDef/pwm/Turret_Controller.cpp
)


#------------------------------------#
#-       Construct the Library      -#
#------------------------------------#
add_library( PiDef SHARED
             ${PI_DEFENDER_HEADERS}
             ${PI_DEFENDER_SOURCES}
)


target_link_libraries( PiDef
                       ${WIRINGPI_LIBRARY}
                       ${Boost_LIBRARIES}
                       pthread
                       ${OpenCV_LIBS}
                       ncurses
)


