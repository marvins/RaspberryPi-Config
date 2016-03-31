/**
 * @file    Enumerations.hpp
 * @author  Marvin Smith
 * @date    3/27/2016
*/
#ifndef __PIDEF_CORE_ENUMERATIONS_HPP__
#define __PIDEF_CORE_ENUMERATIONS_HPP__

// C++ Libraries
#include <cinttypes>
#include <string>


namespace PiDef{


/**
 * @enum ProgramMode
*/
enum class ProgramMode : int8_t
{
    UNKNOWN     = 0 /**< This should be an error condition.*/,
    KEYBOARD    = 1 /**< Control using the keyboard.*/,
    CALIBRATION = 2 /**< Calibrate System.*/,
    DEFEND      = 3 /**< Standard Mode.*/,
}; // End of ProgramMode Enumeration


/**
 * @brief Convert String to ProgramMode
*/
ProgramMode StringToProgramMode( const std::string& mode );

} // End of PiDef Namespace


#endif
