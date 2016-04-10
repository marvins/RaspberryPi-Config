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


#----------------------------------#
#-     Update the Output Paths    -#
#----------------------------------#
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
set( LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib )
set( CMAKE_MODULE_PATH      ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules" )


#------------------------------#
#-     Application Flags      -#
#------------------------------#
option( USE_WIRINGPI "Use WiringPi for I2C Servo Control" ON )


#-----------------------------#
#-     Build Source Code     -#
#-----------------------------#
add_subdirectory(src)



