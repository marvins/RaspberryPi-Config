/**
 * @file    PWM_Driver.cpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/
#include "PWM_Driver.hpp"

// PiDef Libraries
#include "../core/GPIO_Utilities.hpp"
#include "../core/Log_Utilities.hpp"

// C++ Libraries
#include <unistd.h>

// WiringPi Libraries
#include <wiringPiI2C.h>


namespace PiDef{


/**********************************/
/*          Constructor           */
/**********************************/
PWM_I2C_Driver::PWM_I2C_Driver( const int& dev_id,
                                const int& channel_id )
 : m_device_id(dev_id),
   m_channel_id(channel_id)
{
    // Configure I2C
    if( ( m_servo_fd = Initialize_I2C( 0x40 ) ) < 0 ){
        BOOST_LOG_TRIVIAL(fatal) << "Unable to Initialize I2C.";
        return;
    }
    BOOST_LOG_TRIVIAL(info) << "Returned Device FD: " << m_servo_fd;

    // Write 

}


/*************************************/
/*      Initialize the Interface     */
/*************************************/
bool PWM_I2C_Driver::Initialize()
{
    // Set the drivers
    wiringPiI2CWriteReg8( m_servo_fd, PWM::__MODE2, PWM::__OUTDRV );
    wiringPiI2CWriteReg8( m_servo_fd, PWM::__MODE1, PWM::__ALLCALL );
    
    // Sleep, waiting for oscillator
    usleep( 0.005 );

    // Read the Results
    int mode1 = wiringPiI2CReadReg8( m_servo_fd, PWM::__MODE1 );
    
    // Reset the sleep
    mode1 &= PWM::__SLEEP;
    wiringPiI2CWriteReg8( m_servo_fd, PWM::__MODE1, mode1 );
    usleep( 0.005 );

}


/*****************************/
/*          Set PWM          */
/*****************************/
void PWM_I2C_Driver::Set_PWM( const int& channel,
                              const int& on,
                              const int& off )
{

    wiringPiI2CWriteReg8( m_servo_fd, PWM::__LED0_ON_L+4*channel, on & 0xFF );
    wiringPiI2CWriteReg8( m_servo_fd, PWM::__LED0_ON_H+4*channel, on >> 8);

    wiringPiI2CWriteReg8( m_servo_fd, PWM::__LED0_OFF_L+4*channel, off & 0xFF)
    wiringPiI2CWriteReg8( m_servo_fd, PWM::__LED0_OFF_H+4*channel, off >> 8);
}

/****************************/
/*        Set All PWM       */
/****************************/
void PWM_I2C_Driver::Set_All_PWM( const int& off, 
                                  const int& on )
{


}
/*
  def setPWMFreq(self, freq):
    "Sets the PWM frequency"
    prescaleval = 25000000.0    # 25MHz
    prescaleval /= 4096.0       # 12-bit
    prescaleval /= float(freq)
    prescaleval -= 1.0
    if (self.debug):
      print "Setting PWM frequency to %d Hz" % freq
      print "Estimated pre-scale: %d" % prescaleval
    prescale = math.floor(prescaleval + 0.5)
    if (self.debug):
      print "Final pre-scale: %d" % prescale

    oldmode = self.i2c.readU8(self.__MODE1);
    newmode = (oldmode & 0x7F) | 0x10             # sleep
    self.i2c.write8(self.__MODE1, newmode)        # go to sleep
    self.i2c.write8(self.__PRESCALE, int(math.floor(prescale)))
    self.i2c.write8(self.__MODE1, oldmode)
    time.sleep(0.005)
    self.i2c.write8(self.__MODE1, oldmode | 0x80)

  def setPWM(self, channel, on, off):
    "Sets a single PWM channel"

  def setAllPWM(self, on, off):
    "Sets a all PWM channels"
    self.i2c.write8(self.__ALL_LED_ON_L, on & 0xFF)
    self.i2c.write8(self.__ALL_LED_ON_H, on >> 8)
    self.i2c.write8(self.__ALL_LED_OFF_L, off & 0xFF)
    self.i2c.write8(self.__ALL_LED_OFF_H, off >> 8)
*/

} // End of PiDef Namespace

