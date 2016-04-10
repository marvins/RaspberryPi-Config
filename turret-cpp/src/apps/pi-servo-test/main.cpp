/**
 * @file    main.cpp
 * @author  Marvin Smith
 * @date    4/10/2016
*/

// PiDef Libraries
#include "core/Options.hpp"


// C++ Libraries
#include <iostream>
#include <string>
#include <vector>

// OpenCV Libraries
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>


/**
 * @brief Main Application
*/
int main( int argc, char* argv[] )
{
    // Parse Command-Line Options
    Options options( argc, argv );


    // Create Tracking Module
    PiDef::Tracker::ptr_t  tracker = std::make_shared<PiDef::Tracker>( options.Get_Target_Config() );
    
    
    // Create Turret-Controller
    PiDef::Turret_Controller controller( options.Get_Turret_Config(),
                                         tracker );

    
    // Initialize the controller
    controller.Initialize();

    
    // Create Window
    cv::namedWindow("Calibration Test");
    
    
    // Update the Camera
    controller.Get_Tracker()->Update();
    
    
    //  Get list of points to move to
    std::vector<cv::Point2i> point_list;
    point_list.push_back(cv::Point2i(346,276));
    point_list.push_back(cv::Point2i(244,260));
    point_list.push_back(cv::Point2i(246,168));
    point_list.push_back(cv::Point2i(344,190));

    //  Corners: Top-Left:  (  20,  13) -> ( 346, 276)
    //  Corners: Top-Right: ( 635,   9) -> ( 244, 260)
    //  Corners: Bot-Right: ( 620, 451) -> ( 246, 168)
    //  Corners: Bot-Left:  (  48, 465) -> ( 344, 190)
    
    int ch;
    cv::Mat image;

    for( int i=0; i<point_list.size(); i++ )
    {
        // Grab the Latest Frame
        image = controller.Get_Tracker()->Get_Latest_Camera_Frame();


        // Apply the Transform
        controller.Rotate_Servo_X( point_list[i].x );
        controller.Rotate_Servo_Y( point_list[i].y );
        
        // Print the 
        cv::imshow( "Calibration Test", 
                    image );
        ch = cv::waitKey(0);

    }


    return 0;
}

