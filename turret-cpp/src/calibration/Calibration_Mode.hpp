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

// OpenCV Libraries
#include <opencv2/core.hpp>


namespace PiDef{


/**
 * @struct Cal_Config
*/
struct Cal_Config
{
    /// Points
    std::deque<cv::Point2i> pixels;
    std::deque<cv::Point2i> turret_positions;

    // Turret Controller
    Turret_Controller*  turret_controller;
}; // End of Cal_Config Struct


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
