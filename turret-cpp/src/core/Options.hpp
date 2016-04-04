/**
 * @file    Options.hpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/
#ifndef __PI_DEFENDER_CORE_OPTIONS_HPP__
#define __PI_DEFENDER_CORE_OPTIONS_HPP__

// C++ Libraries
#include <map>
#include <string>

// PiDef Libraries
#include "Enumerations.hpp"
#include "Log_Utilities.hpp"
#include "../camera/Tracker.hpp"
#include "../pwm/Turret_Controller.hpp"


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
        
        /**
         * @brief Print Usage
        */
        void Usage();

        
        /**
         * @brief Get the Program Name
        */
        inline std::string Get_Program_Name()const{
            return m_program_name;
        }


        /**
         * @brief Get the Program Mode
        */
        inline ProgramMode Get_Program_Mode()const{
            return m_program_mode;
        }

        
        /**
         * @brief Get the Target Config
        */
        inline Target_Config Get_Target_Config()const{
            return (*m_target_config);
        }


        /**
         * @brief Get the Turret-Configuration
        */
        inline Turret_Config Get_Turret_Config()const{
            return (*m_turret_config);
        }

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

        /// Program Name
        std::string m_program_name;
        std::map<std::string,std::string> m_config_file_data;

        /// Default Log Level
        std::string m_log_level;

        /// Config Path
        std::string m_config_file_path;

        /// Program Mode
        ProgramMode m_program_mode;

        /// Turret-Configuration
        Turret_Config::ptr_t m_turret_config;
        
        /// Target-Configuration
        Target_Config::ptr_t m_target_config;

}; // End of Options Class

} // End of PiDef Namespace


#endif
