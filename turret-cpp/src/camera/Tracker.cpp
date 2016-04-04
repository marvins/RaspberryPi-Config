/**
 * @file    Tracker.cpp
 * @author  Marvin Smith
 * @date    4/1/2016
*/
#include "Tracker.hpp"

// PiDef Libraries
#include "../core/Log_Utilities.hpp"

namespace PiDef{


/*********************************/
/*          Constructor          */
/*********************************/
Target::Target()
 : m_active(false),
   m_pos(std::make_tuple(-1,-1))
{
}

/*********************************/
/*          Constructor          */
/*********************************/
Target::Target( const int& x,
                const int& y )
 : m_active(true),
   m_pos(std::make_tuple(x,y))
{
}


/*********************************/
/*          Constructor          */
/*********************************/
Target_Config::Target_Config( const std::string& haar_pathname )
  : m_haar_pathname(haar_pathname)
{

}


/*********************************/
/*          Constructor          */
/*********************************/
Tracker::Tracker( const Target_Config& config )
  : m_config(config)
{
    // Open the Video Capture
    m_cap = cv::VideoCapture(0);

    // Check if open
    if( m_cap.isOpened() == false ){
        BOOST_LOG_TRIVIAL(error) << "Unable to open the camera.";
        std::exit(1);
    }

}


/***************************************/
/*          Update the Tracker         */
/***************************************/
void Tracker::Update()
{
    // Update
    BOOST_LOG_TRIVIAL(debug) << "Updating Camera";

    // Get the next frame
    if( m_cap.read(m_latest_image) == false )
    {
        BOOST_LOG_TRIVIAL(error) << "Unable to read camera";
    }
}


} // End of PiDef Namespace

