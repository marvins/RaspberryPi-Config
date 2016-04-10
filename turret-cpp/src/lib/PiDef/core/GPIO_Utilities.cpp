/**
 * @file    GPIO_Utilities.cpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/
#include "GPIO_Utilities.hpp"

// PiDef Libraries
#include "../../PiDefender.hpp"
#include "Log_Utilities.hpp"


#if PIDEF_USE_WIRINGPI == 1
// WiringPi Libraries
#include <wiringPiI2C.h>
#endif


namespace PiDef{


/*************************************/
/*          Initialize I2C           */
/*************************************/
int Initialize_I2C( const int& device_id )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(info) << "Initializing I2C Interface for Device " << std::hex << device_id << std::dec;
    
    // Call on the setup
#if PIDEF_USE_WIRINGPI == 1
    int res = wiringPiI2CSetup( device_id );
    
    return res;
#else
    return true;
#endif

}


} // End of PiDef Namespace

