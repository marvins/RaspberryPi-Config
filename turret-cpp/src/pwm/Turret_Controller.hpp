/**
 * @file    Turret_Controller.hpp
 * @author  Marvin Smith
 * @date    3/28/2016
*/
#ifndef __PI_DEFENDER_PWM_TURRET_CONTROLLER_HPP__
#define __PI_DEFENDER_PWM_TURRET_CONTROLLER_HPP__

// PiDef Libraries
#include "PWM_Driver.hpp"


namespace PiDef{

/**
 * @class Turret_Config
*/
class Turret_Config
{
    public:
        
        /**
         * @brief Constructor
        */
        Turret_Config( const int& i2c_device_id,
                       const int& x_servo_channel,
                       const int& y_servo_channel );

        /**
         * @brief Get the I2C Device ID
        */
        inline int Get_I2C_Device_ID()const{
            return m_i2c_device_id;
        }

        /**
         * @brief Get the X Servo Channel
        */
        inline int Get_X_Servo_Channel()const{
            return m_x_servo_channel;
        }


        /**
         * @brief Get the Y Servo Channel
        */
        inline int Get_Y_Servo_Channel()const{
            return m_y_servo_channel;
        }

    private:
        
        /// Device ID
        int m_i2c_device_id;

        /// X Servo Channel
        int m_x_servo_channel;

        /// Y Servo_Channel
        int m_y_servo_channel;

}; // End of Turret_Config Class


/**
 * @class Turret_Controller
*/
class Turret_Controller
{
    public:
        
        /**
         * @brief Constructor
        */
        Turret_Controller( Turret_Config const& config );
        

        /**
         * @brief Initialize the Turret-Controller.
        */
        void Initialize();

        
        /**
         * @brief Rotate Along X Axis
        */
        void Rotate_X( const int& value );


        /**
         * @brief Rotate Along Y Axis
        */
        void Rotate_Y( const int& value );


    private:
        
        /// Configuration
        Turret_Config m_config;

        /// Servo Driver
        PWM_I2C_Driver::ptr_t m_servo_driver;

        /// Current Values
        int m_current_x_value;
        int m_current_y_value;

}; // End of Turret_Controller Class


} // End of PiDef Namespace

#endif
