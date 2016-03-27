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
    m_servo_driver = std::make_shared<PWM_I2C_Driver>( 0x40 );

    if( !m_servo_driver->Initialize() )
    {
        std::exit(-1);
    }

    // Initialize the Starting Values
    m_current_x_value = 500;
    m_current_y_value = 500;

    // Set the Values
    Rotate_X(0);
    Rotate_Y(0);
}


/**********************************/
/*          Rotate X Axis         */
/**********************************/
void Turret_Controller::Rotate_X( const int& value )
{
    // Set the values
    m_current_x_value = std::min( 800, m_current_x_value + value );
    m_current_x_value = std::max(   0, m_current_x_value + value );

    // Move
    m_servo_driver->Set_PWM( m_config.Get_X_Servo_Channel(),
                             0, 
                             m_current_x_value );
                                    
}


/**********************************/
/*          Rotate Y Axis         */
/**********************************/
void Turret_Controller::Rotate_Y( const int& value )
{

    // Set the values
    m_current_y_value = std::min( 800, m_current_y_value + value );
    m_current_y_value = std::max(   0, m_current_y_value + value );

    // Move
    m_servo_driver->Set_PWM( m_config.Get_Y_Servo_Channel(),
                             0, 
                             m_current_y_value );

}

} // End of PiDef Namespace

