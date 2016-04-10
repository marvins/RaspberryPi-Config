/** 
 * @file    GPIO_Utilities.hpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/
#ifndef __PI_DEFENDER_CORE_GPIO_UTILITIES_HPP__
#define __PI_DEFENDER_CORE_GPIO_UTILITIES_HPP__

namespace PiDef{

/**
 * @brief Initialize the Pi's I2C Interface
 *
 * @param[in] device_id ID of the device to initialize.
*/
int Initialize_I2C( const int& device_id );


} // End of PiDef Namespace

#endif
