/**
 * @file    Calibration_Mode.hpp
 * @author  Marvin Smith
 * @date    3/30/2016
*/
#ifndef __PIDEF_CAL_CALIBRATION_MODE_HPP__
#define __PIDEF_CAL_CALIBRATION_MODE_HPP__

// PiDef Libraries
#include "../core/Options.hpp"
#include "../pwm/Turret_Controller.hpp"


namespace PiDef{



/**
 * @brief Calibration Mode
 *
 * @param[in] options
 * @param[in] controller
*/
void Calibration_Mode( Options const&      options,
                       Turret_Controller&  controller );


/**
 * @brief Defend_Mode
*/
void Defend_Mode( Options const&      options,
                  Turret_Controller&  controller );

} // End of PiDef Namespace

#endif
