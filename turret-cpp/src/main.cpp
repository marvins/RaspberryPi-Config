/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/

// C++ Libraries
#include <iostream>
#include <string>

// I2C Libraries
#include "calibration/Calibration_Mode.hpp"
#include "core/Log_Utilities.hpp"
#include "core/Options.hpp"
#include "pwm/Turret_Controller.hpp"


/**
 * @brief Main Application
*/
int main( int argc, char* argv[] )
{

    // Parse Options
    PiDef::Options options( argc, argv );


    // Create Turret-Controller
    PiDef::Turret_Controller turret_controller( options.Get_Turret_Config() );
   

    // Initialize the controller
    turret_controller.Initialize();

    
    // Check if we want Calibration Mode
    if( options.Get_Program_Mode() == PiDef::ProgramMode::CALIBRATION )
    {
        PiDef::Calibration_Mode( options,
                                 turret_controller );
    }
    else{
        BOOST_LOG_TRIVIAL(error) << "Unknown Program Mode";
        return 1;
    }

    return 0;
}

