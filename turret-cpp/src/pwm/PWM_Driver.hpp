/**
 * @file    PWM_Driver.hpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/
#ifndef __PI_DEFENDER_PWM_PWM_DRIVER_HPP__
#define __PI_DEFENDER_PWM_PWM_DRIVER_HPP__

// C++ Libraries
#include <memory>
#include <string>


namespace PiDef{

namespace PWM{

// Register Information
const int __MODE1              = 0x00;
const int __MODE2              = 0x01;
const int __SUBADR1            = 0x02;
const int __SUBADR2            = 0x03;
const int __SUBADR3            = 0x04;
const int __PRESCALE           = 0xFE;
const int __LED0_ON_L          = 0x06;
const int __LED0_ON_H          = 0x07;
const int __LED0_OFF_L         = 0x08;
const int __LED0_OFF_H         = 0x09;
const int __ALL_LED_ON_L       = 0xFA;
const int __ALL_LED_ON_H       = 0xFB;
const int __ALL_LED_OFF_L      = 0xFC;
const int __ALL_LED_OFF_H      = 0xFD;

// Bits
const int __RESTART            = 0x80;
const int __SLEEP              = 0x10;
const int __ALLCALL            = 0x01;
const int __INVRT              = 0x10;
const int __OUTDRV             = 0x04;

} // End of PWM Namespace


/**
 * @class PWM_I2C_Driver
*/
class PWM_I2C_Driver
{

    public:
       
        /// Pointer Type
        typedef std::shared_ptr<PWM_I2C_Driver> ptr_t;

        /**
         * @brief Constructor
        */
        PWM_I2C_Driver( const int& dev_id );
        
        
        /**
         * @brief Initialize the PWM Driver
        */
        bool Initialize();
        

        /**
         * @brief Set PWM Channel Data
        */
        void Set_PWM( const int& channel,
                      const int& on,
                      const int& off );


        /**
         * @brief Set App PWM Data Channels
        */
        void Set_All_PWM( const int& off, 
                          const int& on );
    
    private:
        
        /// Device ID
        int m_device_id;

        /// Servo Device ID
        int m_servo_fd;

}; // End of PWM_I2C_Driver Class


} // End of PiDef Namespace

#endif
