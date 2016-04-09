/**
 * @file    Calibration_Mode.cpp
 * @author  Marvin Smith
 * @date    3/30/2016
*/
#include "Calibration_Mode.hpp"

// C++ Libraries
#include <ncurses.h>
#include <string>
#include <vector>


namespace PiDef{


/*********************************************************/
/*          Camera Calibration Callback Function         */
/*********************************************************/
void CameraCalibrationCallbackFunc( int   event, 
                                    int   x, 
                                    int   y, 
                                    int   flags, 
                                    void* userdata)
{

    // Convert to Cal config
    Cal_Config* cal_config = (Cal_Config*)userdata;


    if  ( event == cv::EVENT_LBUTTONDOWN )
    {
        // Get the turret position
        int tx = cal_config->turret_controller->Get_Current_X(); 
        int ty = cal_config->turret_controller->Get_Current_Y(); 
        
        // Set the Pixel Value
        cal_config->pixels.push_back(cv::Point2i( x, y));
        cal_config->turret_positions.push_back(cv::Point2i( tx, ty));

        std::cout << "Found Point at (" << x << ", " << y << ")" << std::endl;
        std::cout << "      Servo ( " << tx << ", " << ty << ")" << std::endl;
        std::cin.get();
    }
    else if  ( event == cv::EVENT_RBUTTONDOWN )
    {
    }
    else if  ( event == cv::EVENT_MBUTTONDOWN )
    {
    }
    else if ( event == cv::EVENT_MOUSEMOVE )
    {
    }    
}

/*************************************/
/*          Calibration Mode         */
/*************************************/
void Calibration_Mode( Options const&     options,
                       Turret_Controller& controller )
{

    // Log Entry
    BOOST_LOG_TRIVIAL(debug) << "Starting Calibration Mode";

    try{

        //  Initialize UI 
        initscr();
        keypad(stdscr, true);
        noecho();

        int ch;
        bool exit_loop = true;
        while(exit_loop)
        {

            clear();

            // Print Screen
            mvprintw( 3, 3, "Pi-Defender Servo Calibration");
            mvprintw( 4, 3, ("Current X  : " + std::to_string(controller.Get_Current_X())).c_str());
            mvprintw( 5, 3, ("Current Y  : " + std::to_string(controller.Get_Current_Y())).c_str());
            mvprintw( 6, 3, ("Servo X Min: " + std::to_string(controller.Get_Servo_X_Min())).c_str());
            mvprintw( 7, 3, ("Servo X Max: " + std::to_string(controller.Get_Servo_X_Max())).c_str());
            mvprintw( 8, 3, ("Servo Y Min: " + std::to_string(controller.Get_Servo_Y_Min())).c_str());
            mvprintw( 9, 3, ("Servo Y Max: " + std::to_string(controller.Get_Servo_Y_Max())).c_str());
            mvprintw(10, 3, ("Last Key Value: " + std::to_string(ch)).c_str()); 
            // Refresh the screen
            refresh();

            // Get the next key
            ch = getch();

            //  Check Key
            switch(ch)
            {
                // Escape Key or Q
                case 27:
                case 'q':
                    exit_loop = false;
                    break;

                    // Arrow Keys
                case KEY_UP:
                    controller.Rotate_Y(1);
                    break;

                case KEY_DOWN:
                    controller.Rotate_Y(-1);
                    break;

                case KEY_LEFT:
                    controller.Rotate_X(-1);
                    break;

                case KEY_RIGHT:
                    controller.Rotate_X(1);

                default:
                    break;
            }

        }  // End of While Loop

        // Create Cal Config
        Cal_Config* cal_config = new Cal_Config();
        cal_config->turret_controller = &controller; 


        // Create the Camera Track Calibration
        cv::namedWindow("Camera Tracking Calibration");
        

        //set the callback function for any mouse event
        cv::setMouseCallback( "Camera Tracking Calibration", 
                              CameraCalibrationCallbackFunc, 
                              cal_config );

        // Update the Timeout
        timeout(10);

        // Start the GUI
        exit_loop = true;
        while(exit_loop)
        {
            // Update the Camera
            controller.Get_Tracker()->Update();
            cv::imshow("Camera Tracking Calibration", controller.Get_Tracker()->Get_Latest_Camera_Frame());

            // Clear the Screen
            clear();

            // Print Screen
            mvprintw( 3, 3, "Pi-Defender Camera Calibration");
            mvprintw( 4, 3, "------------------------------");
            mvprintw( 5, 3, "  Turn on the laser pointer and align.");
            mvprintw( 6, 3, "  Align the camera until both laser pointer and camera are covering the same region.");
            mvprintw( 7, 3, "  Select the Point on the Image Where the Laser Pointer is At.");

            // Refresh the screen
            refresh();

            // Get the next key
            ch = cv::waitKey(5);
            ch = getch();

            //  Check Key
            switch(ch)
            {
                // Escape Key or Q
                case 27:
                case 'q':
                    exit_loop = false;
                    break;

                    // Arrow Keys
                case KEY_UP:
                    controller.Rotate_Y(1);
                    break;

                case KEY_DOWN:
                    controller.Rotate_Y(-1);
                    break;

                case KEY_LEFT:
                    controller.Rotate_X(-1);
                    break;

                case KEY_RIGHT:
                    controller.Rotate_X(1);

                default:
                    break;
            }

        }  // End of While Loop
        
        // Solve the Transforms
        Solve_Camera_Calibration( *cal_config );

        // Close the Cal Config
        cal_config->turret_controller = nullptr;
        delete [] cal_config;

        // Close Screen
        endwin();
    }
    catch(...){
        endwin();
    }
}


/********************************************/
/*          Calibration Test Mode           */
/********************************************/
void Calibration_Test( Options const&      options,
                       Turret_Controller&  controller )
{
    // Create Window
    cv::namedWindow("Calibration Test");

    // Update the Camera
    controller.Get_Tracker()->Update();
    int divisor = 32, ch;
    
    // Compute the Test Range
    for( int x=0; x<640; x += divisor )
    for( int y=0; y<480; y += divisor )
    {
        // Print the 
        std::cout << x << ", " << y << std::endl;
        cv::imshow("Calibration Test", controller.Get_Tracker()->Get_Latest_Camera_Frame());
        ch = cv::waitKey(0);

        // Apply the Transform
        controller.Move_To_Pixel( x, y );
    }

}


/************************************/
/*           Defend Mode            */
/************************************/
void Defend_Mode( Options const&      options,
        Turret_Controller&  controller )
{

    // Start the main loop


}


/********************************************************/
/*          Solve Camera Calibration Equations          */
/********************************************************/
void Solve_Camera_Calibration( Cal_Config& cal_config )
{

    //  Create Transform
    cv::Mat A = cv::Mat::ones( cal_config.pixels.size(), 3, CV_64FC1);
    for( size_t i=0; i<cal_config.pixels.size(); i++ ){
        A.at<double>(i,0) = cal_config.pixels[i].x;
        A.at<double>(i,1) = cal_config.pixels[i].y;
    } 

    // Construct X and Y transforms
    cv::Mat xy = cv::Mat::zeros( cal_config.turret_positions.size(), 2, CV_64FC1 );
    for( size_t i=0; i<cal_config.turret_positions.size(); i++ ){
        xy.at<double>(i,0) = cal_config.turret_positions[i].x;
        xy.at<double>(i,1) = cal_config.turret_positions[i].y;
    }

    // Solve
    cv::Mat Ainv;
    
    if( cv::solve( A, xy, Ainv, cv::DECOMP_SVD ) == false ){
        BOOST_LOG_TRIVIAL(error) << "Unable to calibrate.";
        return;
    }

    // Otherwise, set the matrix
    std::cout << Ainv << std::endl;
    std::cin.get();

}


} // End of PiDef Module

