/**
 * @file    Options.hpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/
#ifndef __PI_DEFENDER_CORE_OPTIONS_HPP__
#define __PI_DEFENDER_CORE_OPTIONS_HPP__

// C++ Libraries
#include <string>

// PiDef Libraries
#include "Log_Utilities.hpp"

namespace PiDef{

/**
 * @class Options
*/
class Options
{
    public:
        
        /**
         * @brief Constructor
        */
        Options( int argc, char* argv[] );

    private:
        
        /**
         * @brief Set Defaults
        */
        void Set_Defaults();

        /**
         * @brief Parse Command-Line Options
        */
        void Parse_Command_Line( int argc, char* argv[] );

        /**
         * @brief Parse Configuration File
        */
        void Parse_Configuration_File();

        /**
         * @brief Initialize Logging
        */
        void Initialize_Logging();

        /// Default Log Level
        std::string m_log_level;

        /// Config Path
        std::string m_config_file_path;

}; // End of Options Class

} // End of PiDef Namespace


#endif
