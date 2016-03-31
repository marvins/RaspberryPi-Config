/**
 * @file    Calibration_Mode.cpp
 * @author  Marvin Smith
 * @date    3/30/2016
*/
#include "Calibration_Mode.hpp"

// C++ Libraries
#include <ncurses.h>
#include <string>

namespace PiDef{


/*************************************/
/*          Calibration Mode         */
/*************************************/
void Calibration_Mode( Options const&     options,
                       Turret_Controller& controller )
{

    // Log Entry
    BOOST_LOG_TRIVIAL(debug) << "Starting Calibration Mode";

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
        mvprintw( 3, 3, "PiDefender Calibration");
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
   
    std::stringstream sin;
    sin << "Exiting on " << ((char)ch) << ", Value: " << (int)ch;
    mvprintw( 3, 3, sin.str().c_str());
    ch = getch();

    // Close Screen
    endwin();

}


} // End of PiDef Module

