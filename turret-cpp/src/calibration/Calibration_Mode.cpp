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


void CameraCalibrationCallbackFunc( int event, int x, int y, int flags, void* userdata)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if  ( event == EVENT_RBUTTONDOWN )
    {
        cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if  ( event == EVENT_MBUTTONDOWN )
    {
        cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if ( event == EVENT_MOUSEMOVE )
    {
        cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
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


        // Create the Camera Track Calibration
        cv::namedWindow("Camera Tracking Calibration");
        
        //set the callback function for any mouse event
        cv::setMouseCallback("Camera Tracking Calibration", CameraCalibrationCallBackFunc, NULL);

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


        // Close Screen
        endwin();
    }
    catch(...){
        endwin();
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


} // End of PiDef Module

