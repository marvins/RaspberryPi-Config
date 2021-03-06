/**
 * @file    Enumerations.hpp
 * @author  Marvin Smith
 * @date    4/10/2016
*/
#ifndef __PI_DEFENDER_APP_PIDEF_CORE_ENUMERATIONS_HPP__
#define __PI_DEFENDER_APP_PIDEF_CORE_ENUMERATIONS_HPP__

// C++ Libraries
#include <cinttypes>
#include <string>

/**
 * @enum ProgramMode
*/
enum class ProgramMode : int8_t
{
    UNKNOWN     = 0 /**< This should be an error condition.*/,
    KEYBOARD    = 1 /**< Control using the keyboard.*/,
    CALIBRATION = 2 /**< Calibrate System.*/,
    CAL_TEST    = 3 /**< Test the Calibration Settings.*/,
    DEFEND      = 4 /**< Standard Mode.*/,
}; // End of ProgramMode Enumeration


/**
 * @brief Convert String to ProgramMode
*/
ProgramMode StringToProgramMode( const std::string& mode );



#endif
