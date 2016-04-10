/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/

// C++ Libraries
#include <iostream>
#include <string>

// PiDef Libraries
#include <PiDefender.hpp>

// Application Libraries
#include "calibration/Calibration_Mode.hpp"
#include "core/Options.hpp"

/**
 * @brief Main Application
*/
int main( int argc, char* argv[] )
{

    // Parse Options
    Options options( argc, argv );


    // Create Tracking Module
    PiDef::Tracker::ptr_t  tracker = std::make_shared<PiDef::Tracker>( options.Get_Target_Config() );
    
    
    // Create Turret-Controller
    PiDef::Turret_Controller turret_controller( options.Get_Turret_Config(),
                                                tracker );
   

    // Initialize the controller
    turret_controller.Initialize();

    
    // Check if we want Calibration Mode
    if( options.Get_Program_Mode() == ProgramMode::CALIBRATION )
    {
        Calibration_Mode( options,
                          turret_controller );
    }
    
    // Calibration Test
    else if( options.Get_Program_Mode() == ProgramMode::CAL_TEST )
    {
        Calibration_Test( options,
                          turret_controller );
    }

    // Check if we want defensive mode
    else if( options.Get_Program_Mode() == ProgramMode::DEFEND )
    {
        Defend_Mode( options,
                     turret_controller );
    }

    // Otherwise, unknown mode
    else{
        BOOST_LOG_TRIVIAL(error) << "Unknown Program Mode";
        return 1;
    }


    return 0;
}

