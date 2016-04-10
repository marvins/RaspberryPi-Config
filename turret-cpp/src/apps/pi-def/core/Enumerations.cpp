/**
 * @file    Enumerations.cpp
 * @author  Marvin Smith
 * @date    4/10/2016
*/
#include "Enumerations.hpp"
 
 
/****************************************************/
/*          Convert String to Program Mode          */
/****************************************************/
ProgramMode StringToProgramMode( const std::string& mode )
{
    // KEYBOARD
    if( mode == "keyboard" || mode == "KEYBOARD" )
    {
        return ProgramMode::KEYBOARD;
    }
    
    // Calibrate
    if( mode == "calibration" || mode == "CALIBRATION" ){
        return ProgramMode::CALIBRATION;
    }

    // Cal Test
    if( mode == "cal_test" || mode == "CAL_TEST" ){
        return ProgramMode::CAL_TEST;
    }
    
    if( mode == "DEFEND" ){
        return ProgramMode::DEFEND;
    }

    // Unknown
    return ProgramMode::UNKNOWN;
}



