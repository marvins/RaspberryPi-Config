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
  : m_config(config),
    m_active(false)
{
    // Open the Video Capture
    m_cap = cv::VideoCapture(0);

    // Check if open
    if( m_cap.isOpened() == false ){
        BOOST_LOG_TRIVIAL(error) << "Unable to open the camera.";
        std::exit(1);
    }

    // Look for Faces
    BOOST_LOG_TRIVIAL(error) << "Loading Haar Cascade";
    if( !m_face_cascade.load( m_config.Get_Haar_Pathname() ) )
    {
        BOOST_LOG_TRIVIAL(error) << "Unable to read haar classifier.";
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
        std::exit(1);
    }
    

    // Detect
    std::vector<cv::Rect> targets;
    m_face_cascade.detectMultiScale( m_latest_image, 
                                     targets,
                                     1.1, 2, 0|CV_HAAR_SCALE_IMAGE, 
                                     cv::Size(30, 30) );
    
    // Print
    if( targets.size() > 0 ){
        m_current_target = Target( targets[0].x + targets[0].width/2,
                                   targets[0].y + targets[0].height/2);
        m_active = true;
    }
    else{
        m_active = false;
    }
}


} // End of PiDef Namespace

