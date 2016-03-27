/**
 * @file    Options.cpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/
#include "Options.hpp"

// C++ Libraries
#include <fstream>
#include <iostream>

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

}


/***************************************/
/*      Parse Command-Line Options     */
/***************************************/
void Options::Parse_Command_Line( int argc, char* argv[] )
{


}


/***************************************/
/*       Parse Configuration File      */
/***************************************/
void Options::Parse_Configuration_File()
{


}


/************************************/
/*        Initialize Logging        */
/************************************/
void Options::Initialize_Logging()
{
    Initialize_Logger( m_log_level );
}

} // End of PiDef Namespace

