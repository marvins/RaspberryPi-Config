/**
 * @file    GPIO_Utilities.cpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/
#include "GPIO_Utilities.hpp"

// PiDef Libraries
#include "Log_Utilities.hpp"

// WiringPi Libraries
#include <wiringPiI2C.h>


namespace PiDef{


/*************************************/
/*          Initialize I2C           */
/*************************************/
int Initialize_I2C( const int& device_id )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(info) << "Initializing I2C Interface for Device " << std::hex << device_id << std::dec;
    
    // Call on the setup
    int res = wiringPiI2CSetup( device_id );
    
    return res;
}


} // End of PiDef Namespace

