/**
 * @file    Turret_Controller.cpp
 * @author  Marvin Smith
 * @date    3/28/2016
*/
#include "Turret_Controller.hpp"

// C++ Libraries
#include <cstdlib>

// PiDef Libraries
#include "../core/Log_Utilities.hpp"

namespace PiDef{

/********************************/
/*          Constructor         */
/********************************/
Turret_Config::Turret_Config( const int& i2c_device_id,
                              const int& x_servo_channel,
                              const int& y_servo_channel )
 : m_i2c_device_id(m_i2c_device_id),
   m_x_servo_channel(x_servo_channel),
   m_y_servo_channel(y_servo_channel)
{
}


/*********************************/
/*          Constructor          */
/*********************************/
Turret_Controller::Turret_Controller( const Turret_Config& config )
 : m_config(config)
{
}

/************************************************/
/*          Initialize the Controller           */
/************************************************/
void Turret_Controller::Initialize()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(debug) << "Initializing Turret-Controller";

    // Create the PWM Driver
    m_x_servo_driver = std::make_shared<PWM_I2C_Driver>( 0x40, 1);
    m_y_servo_driver = std::make_shared<PWM_I2C_Driver>( 0x40, 0);

    if( !m_x_servo_driver->Initialize() )
    {
        std::exit(-1);
    }
    if( !m_y_servo_driver->Initialize() )
    {
        std::exit(-1);
    }
}


} // End of PiDef Namespace

