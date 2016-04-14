/**
 * @file    Calibration_Mode.cpp
 * @author  Marvin Smith
 * @date    3/30/2016
*/
#include "Calibration_Mode.hpp"

// C++ Libraries
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>


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

        mvprintw( 12, 3, ("Pixel: " + std::to_string(x)  + ", " + std::to_string(y)).c_str());
        mvprintw( 13, 3, ("Servo: " + std::to_string(tx) + ", " + std::to_string(ty)).c_str());
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
void Calibration_Mode( Options const&            options,
                       PiDef::Turret_Controller& controller )
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
        
        // Iterate over files
        std::ofstream fout;
        fout.open("data/point-match.txt");

        for( size_t i=0; i<cal_config->pixels.size(); i++ ){
            fout << cal_config->pixels[i].x << " " << cal_config->pixels[i].y;
            fout << " " << cal_config->turret_positions[i].x << " " << cal_config->turret_positions[i].y << std::endl;
        }

        fout.close();

        
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
void Calibration_Test( Options const&             options,
                       PiDef::Turret_Controller&  controller )
{
    // Create Window
    cv::namedWindow("Calibration Test");

    // Update the Camera
    controller.Get_Tracker()->Update();
    int divisor = 128, ch;
    cv::Mat image;

    // Compute the Test Range
    bool exit_loop = false;
    for( int x=0; x<640 && !exit_loop; x += divisor )
    for( int y=0; y<480 && !exit_loop; y += divisor )
    {
        // Grab the Latest Frame
        image = controller.Get_Tracker()->Get_Latest_Camera_Frame();

        // Draw the Circle
        cv::circle( image, 
                    cv::Point2i( x,y), 
                    5, 
                    cv::Scalar(0,255,0),
                    2);

        // Apply the Transform
        controller.Move_To_Pixel( x, y );
        
        // Print the 
        std::cout << x << ", " << y << std::endl;
        cv::imshow( "Calibration Test", 
                    image );
        ch = cv::waitKey(0);


        // Check the value
        if( ch == 'q' ){
            exit_loop = true;
        }

    }

}


/************************************/
/*           Defend Mode            */
/************************************/
void Defend_Mode( Options const&             options,
                  PiDef::Turret_Controller&  controller )
{

    // Start the main loop
    cv::namedWindow("Calibration Test");

    // Update the Camera
    controller.Get_Tracker()->Update();
    int ch, x, y;
    bool active;
    cv::Mat image;

    // Compute the Test Range
    bool exit_loop = false;
    while( !exit_loop )
    {
        // Update
        controller.Get_Tracker()->Update();
        
        // Grab the Latest Frame
        image = controller.Get_Tracker()->Get_Latest_Camera_Frame();

        controller.Get_Tracker()->Get_Active_Target( active );

        // Draw the Circle
        if( active )
        {
            x = std::get<0>(controller.Get_Tracker()->Get_Active_Target().Get_Position());
            y = std::get<1>(controller.Get_Tracker()->Get_Active_Target().Get_Position());

            // Draw the circle
            cv::circle( image, 
                        cv::Point2i( x,y), 
                        5, 
                        cv::Scalar(0,255,0),
                        2);

            // Apply the Transform
            controller.Move_To_Pixel( x, y );
        
        }
        else{
            x = 320;
            y = 240;

            // Draw the circle
            cv::circle( image, 
                        cv::Point2i(x,y), 
                        5, 
                        cv::Scalar(255,0,0),
                        2);

            // Apply the Transform
            controller.Move_To_Pixel( x, y );
        }

        // Print the 
        cv::imshow( "Calibration Test", 
                    image );
        ch = cv::waitKey( options.Get_Time_Step_ms());


        // Check the value
        if( ch == 'q' ){
            exit_loop = true;
        }

    }

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
        A.at<double>(i,2) = 1;
    } 

    // Construct X and Y transforms
    cv::Mat x = cv::Mat::zeros( cal_config.turret_positions.size(), 1, CV_64FC1 );
    cv::Mat y = cv::Mat::zeros( cal_config.turret_positions.size(), 1, CV_64FC1 );
    for( size_t i=0; i<cal_config.turret_positions.size(); i++ ){
        x.at<double>(i,0) = cal_config.turret_positions[i].x;
        y.at<double>(i,0) = cal_config.turret_positions[i].y;
    }

    // Solve
    cv::Mat AXinv, AYinv;
    
    if( cv::solve( A, x, AXinv, cv::DECOMP_SVD ) == false ){
        BOOST_LOG_TRIVIAL(error) << "Unable to calibrate.";
        return;
    }
    if( cv::solve( A, y, AYinv, cv::DECOMP_SVD ) == false ){
        BOOST_LOG_TRIVIAL(error) << "Unable to calibrate.";
        return;
    }

    // Otherwise, set the matrix
    std::cout << AXinv << ", " << AYinv  << std::endl;
    std::cin.get();

}


