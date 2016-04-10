/**
 * @file    Calibration_Mode.hpp
 * @author  Marvin Smith
 * @date    3/30/2016
*/
#ifndef __PIDEF_CAL_CALIBRATION_MODE_HPP__
#define __PIDEF_CAL_CALIBRATION_MODE_HPP__

// Application Libraries
#include "../core/Options.hpp"


// PiDef Libraries
#include <PiDef/core/Log_Utilities.hpp>
#include <PiDef/pwm/Turret_Controller.hpp>


// OpenCV Libraries
#include <opencv2/core.hpp>


/**
 * @struct Cal_Config
*/
struct Cal_Config
{
    /// Points
    std::deque<cv::Point2i> pixels;
    std::deque<cv::Point2i> turret_positions;

    PiDef::Turret_Controller*  turret_controller;

}; // End of Cal_Config Struct


/**
 * @brief Calibration Mode
 *
 * @param[in] options
 * @param[in] controller
*/
void Calibration_Mode( Options const&             options,
                       PiDef::Turret_Controller&  controller );


/**
 * @brief Calibration Test.
*/
void Calibration_Test( Options const&             options,
                       PiDef::Turret_Controller&  controller );

/**
 * @brief Defend_Mode
*/
void Defend_Mode( Options const&             options,
                  PiDef::Turret_Controller&  controller );


/**
 * @brief Solve Camera Calibration
*/
void Solve_Camera_Calibration( Cal_Config& cal_config );


#endif
