/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/

// C++ Libraries
#include <iostream>
#include <string>

// I2C Libraries
#include "core/Log_Utilities.hpp"
#include "core/Options.hpp"
#include "pwm/Turret_Controller.hpp"


/**
 * @brief Main Application
*/
int main( int argc, char* argv[] )
{
    wiringPiSetupGPIO();

    // Parse Options
    PiDef::Options options( argc, argv );


    // Create Turret-Controller
    PiDef::Turret_Controller turret_controller( PiDef::Turret_Config( 0x40, 1, 0 ));
   

    // Initialize the controller
    turret_controller.Initialize();

    // Rotate Upwards
    for( int i=0; i<100; i++ ){
        turret_controller.Rotate_Y( 1 );
        BOOST_LOG_TRIVIAL(info) << "Rotating";
        sleep(1);
    }

    return 0;
}

