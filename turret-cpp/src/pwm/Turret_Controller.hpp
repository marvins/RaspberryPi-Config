/**
 * @file    Turret_Controller.hpp
 * @author  Marvin Smith
 * @date    3/28/2016
*/
#ifndef __PI_DEFENDER_PWM_TURRET_CONTROLLER_HPP__
#define __PI_DEFENDER_PWM_TURRET_CONTROLLER_HPP__

// PiDef Libraries
#include "../camera/Tracker.hpp"
#include "PWM_Driver.hpp"

// C++ Libraries
#include <string>
#include <vector>


namespace PiDef{

/**
 * @class Turret_Config
*/
class Turret_Config
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<Turret_Config> ptr_t;


        /**
         * @brief Constructor
        */
        Turret_Config( const int&                  i2c_device_id,
                       const int&                  x_servo_channel,
                       const int&                  y_servo_channel,
                       const int&                  x_servo_start,
                       const int&                  y_servo_start,
                       const int&                  x_servo_min,
                       const int&                  x_servo_max,
                       const int&                  y_servo_min,
                       const int&                  y_servo_max,
                       const std::vector<double>&  cal_transform );

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
        
        inline int Get_X_Servo_Start()const{
            return m_x_servo_start;
        }

        inline int Get_Y_Servo_Start()const{
            return m_y_servo_start;
        }

        /**
         * @brief Get the Y Servo Channel
        */
        inline int Get_Y_Servo_Channel()const{
            return m_y_servo_channel;
        }
        
        inline int Get_X_Servo_Min()const{
            return m_x_servo_min;
        }
        
        inline int Get_X_Servo_Max()const{
            return m_x_servo_max;
        }
        
        inline int Get_Y_Servo_Min()const{
            return m_y_servo_min;
        }
        
        inline int Get_Y_Servo_Max()const{
            return m_y_servo_max;
        }

        /**
         * @brief Get the Calibration Transform
        */
        inline std::vector<double> Get_Cal_Transform()const{
            return m_cal_transform;
        }


    private:
        
        /// Device ID
        int m_i2c_device_id;

        /// X Servo Channel
        int m_x_servo_channel;

        /// Y Servo_Channel
        int m_y_servo_channel;

        /// Start Values
        int m_x_servo_start;
        int m_y_servo_start;

        int m_x_servo_min;
        int m_x_servo_max;
        int m_y_servo_min;
        int m_y_servo_max;

        std::vector<double> m_cal_transform;

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
        Turret_Controller( Turret_Config const&  config,
                           Tracker::ptr_t        tracker );
        

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
        
        
        /**
         * @brief Get the Current X Value
        */
        inline int Get_Current_X()const{
            return m_current_x_value;
        }


        /**
         * @brief Get hte Current Y Value
        */
        inline int Get_Current_Y()const{
            return m_current_y_value;
        }


        /**
         * @brief Get the Servo Ranges
        */
        inline int Get_Servo_X_Min()const{
            return m_servo_x_min;
        }


        inline int Get_Servo_X_Max()const{
            return m_servo_x_max;
        }


        /**
         * @brief Get the Servo Ranges
        */
        inline int Get_Servo_Y_Min()const{
            return m_servo_y_min;
        }


        inline int Get_Servo_Y_Max()const{
            return m_servo_y_max;
        }
        
        /**
         * @brief Get the Tracker
        */
        inline Tracker::ptr_t Get_Tracker()const{
            return m_tracker;
        }


        /**
         * @brief Move to the specified pixel location.
        */
        void Move_To_Pixel( const int& x,
                            const int& y );

    private:
        
        /// Configuration
        Turret_Config m_config;

        /// Servo Driver
        PWM_I2C_Driver::ptr_t m_servo_driver;

        /// Current Values
        int m_current_x_value;
        int m_current_y_value;

        /// Servo Ranges
        int m_servo_x_min;
        int m_servo_x_max;
        int m_servo_y_min;
        int m_servo_y_max;

        /// Transform
        

        /// Tracker
        Tracker::ptr_t m_tracker;

}; // End of Turret_Controller Class


} // End of PiDef Namespace

#endif
