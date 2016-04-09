/**
 * @file    Options.cpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/
#include "Options.hpp"

// C++ Libraries
#include <deque>
#include <fstream>
#include <iostream>

// PiDef Libraries
#include "String_Utilities.hpp"


namespace PiDef{

/********************************/
/*          Constructor         */
/********************************/
Options::Options( int argc, char* argv[] )
{
    // Set Program Defaults
    Set_Defaults();

    // Parse Command-Line
    Parse_Command_Line( argc, argv );

    // Parse Configuration File
    Parse_Configuration_File();

    // Initialize Logging
    Initialize_Logging();


    // Build the Cal Transform
    std::vector<double> cal_transform;
    cal_transform.push_back(std::stod(m_config_file_data["CAL_X_0"]));
    cal_transform.push_back(std::stod(m_config_file_data["CAL_X_1"]));
    cal_transform.push_back(std::stod(m_config_file_data["CAL_X_2"]));
    cal_transform.push_back(std::stod(m_config_file_data["CAL_Y_0"]));
    cal_transform.push_back(std::stod(m_config_file_data["CAL_Y_1"]));
    cal_transform.push_back(std::stod(m_config_file_data["CAL_Y_2"]));


    // Build the Turret-Config
    m_turret_config = std::make_shared<Turret_Config>( std::stoi(m_config_file_data["PWM_I2C_CHANNEL"]),
                                                       std::stoi(m_config_file_data["PWM_X_SERVO_CHANNEL"]),
                                                       std::stoi(m_config_file_data["PWM_Y_SERVO_CHANNEL"]),
                                                       std::stoi(m_config_file_data["PWM_X_SERVO_START"]),
                                                       std::stoi(m_config_file_data["PWM_Y_SERVO_START"]),
                                                       std::stoi(m_config_file_data["PWM_X_SERVO_MIN"]),
                                                       std::stoi(m_config_file_data["PWM_X_SERVO_MAX"]),
                                                       std::stoi(m_config_file_data["PWM_Y_SERVO_MIN"]),
                                                       std::stoi(m_config_file_data["PWM_Y_SERVO_MAX"]),
                                                       cal_transform );

    // Target-Config
    m_target_config = std::make_shared<Target_Config>( m_config_file_data["TARGET_HAAR_PAATHNAME"] );

}


/************************/
/*      Print Usage     */
/************************/
void Options::Usage()
{
    std::cout << "usage: " << m_program_name << " [options]" << std::endl;
    std::cout << std::endl;
    
    // Command-Modes
    std::cout << "Command-Modes:" << std::endl;
    std::cout << "--cal      : Calibrate Turret" << std::endl;
    std::cout << "--cal-test : Calibration Test" << std::endl;
    std::cout << std::endl;
}


/***************************************/
/*      Set Application Defaults       */
/***************************************/
void Options::Set_Defaults()
{
    // Set Log Level
    m_log_level = "trace";

    // Default Configuration File
    m_config_file_path = "data/options.cfg";
    
    // Program Mode
    m_program_mode = ProgramMode::DEFEND;
}


/***************************************/
/*      Parse Command-Line Options     */
/***************************************/
void Options::Parse_Command_Line( int argc, char* argv[] )
{
    // Push args onto list
    std::deque<std::string> args;
    for( int i=1; i<argc; i++ ){
        args.push_back(argv[i]);
    }
    std::string arg;

    // Parse Arguments
    while( args.size() > 0 )
    {
        // Grab the next argument
        arg = args.front();
        args.pop_front();


        // Check Help
        if( arg == "-h" ||
            arg == "--help" )
        {
            Usage();
            std::exit(0);
        }

        // Check Program Mode
        else if( arg == "--cal" )
        {
            m_program_mode = ProgramMode::CALIBRATION;
        }

        // Calibration Test
        else if( arg == "--cal-test" )
        {
            m_program_mode = ProgramMode::CAL_TEST;
        }

        // Error
        else{
            std::cerr << "Unknown Command-Line Argument (" << arg << ")" << std::endl;
            Usage();
            std::exit(-1);
        }

    }

}


/***************************************/
/*       Parse Configuration File      */
/***************************************/
void Options::Parse_Configuration_File()
{

    // Open the Config File
    std::ifstream fin;
    fin.open(m_config_file_path.c_str());

    // Get the line
    std::string line;
    std::getline( fin, line );

    while( fin.good() )
    {
        // Parse the Data
        line = String_Trim( line );

        // Check if Comment
        if( line.size() <= 0 || line[0] == '#' ){
            std::getline( fin, line );
            continue;
        }

        // Check if Empty
        std::vector<std::string> comps = String_Split(line, "=");

        if( comps.size() == 2 ){
            m_config_file_data[ comps[0] ] = comps[1];
        }

        // Get next line
        std::getline( fin, line );

    }

    // Close the Config File
    fin.close();

    // Print List of Fields Parsed
    std::stringstream sin;
    sin << "Config File Params Parsed\n";
    for( auto it=m_config_file_data.begin(); it != m_config_file_data.end(); it++ )
    {
        sin << it->first << " = " << it->second << std::endl;
    }

    BOOST_LOG_TRIVIAL(debug) << sin.str();
}


/************************************/
/*        Initialize Logging        */
/************************************/
void Options::Initialize_Logging()
{
    Initialize_Logger( m_log_level );
}

} // End of PiDef Namespace

