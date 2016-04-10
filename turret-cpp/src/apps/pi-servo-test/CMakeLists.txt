#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/10/2016
#
#    Purpose:  Construct Pi-Servo-Test Application
#

#-------------------------#
#-     CMake Version     -#
#-------------------------#
cmake_minimum_required( FATAL_ERROR VERSION 2.8 )


#---------------------------------#
#-      Project Information      -#
#---------------------------------#
project(Pi-Servo-Test)


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
set( PI_SERVO_TEST_SOURCES 
     main.cpp
     core/Options.cpp
)


#---------------------------------#
#-    Define our Header Files    -#
#---------------------------------#
set( PI_SERVO_TEST_HEADERS
     core/Options.hpp
)


#------------------------------------#
#-    Construct the Application     -#
#------------------------------------#
add_executable( pi-servo-test
                ${PI_SERVO_TEST_SOURCES}
                ${PI_SERVO_TEST_HEADERS}
)


#-----------------------#
#-   Link Libraries    -#
#-----------------------#
target_link_libraries( pi-servo-test
                       PiDef
                       ${Boost_LIBRARIES}
                       pthread
)
