/**
 * @file    Log_Utilities.hpp
 * @author  Marvin Smith
 * @date    3/26/2016
*/
#ifndef __PI_DEFENDER_CORE_LOG_UTILITIES_HPP__
#define __PI_DEFENDER_CORE_LOG_UTILITIES_HPP__

// Boost Libraries
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sink.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/trivial.hpp>

// C++ Standard Libraries
#include <string>


using namespace boost::log::trivial;

namespace PiDef{

/**
 * @brief Macro for logging inside one of the classes.
*/
#define CLASS_LOG m_class_name + "::" + std::string(__func__) 

/**
 * @brief Initialize the Logger
 *
 * @param[in] severity Severity of messages to keep.
 * @param[in] log_path Path to logfile to write to.
 */
void Initialize_Logger( const std::string& severity = "info",
                        const std::string& log_path = "" );


} // End of PiDef Namespace



#endif

