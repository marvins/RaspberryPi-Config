/**
 * @file   String_Utilities.cpp
 * @author Marvin Smith
 * @date   3/30/2016
*/
#include "String_Utilities.hpp"

// Boost Libraries
#include <boost/algorithm/string.hpp>

/***********************************************************/
/*       Trim a string of leading and trailing spaces.     */
/***********************************************************/
std::string String_Trim( const std::string& str )
{    
    std::string tstr = str;
    boost::algorithm::trim( tstr );
    return tstr;
}


/****************************************************/
/*          Split a String based on a pattern.      */
/****************************************************/
std::vector<std::string> String_Split( const std::string& str, 
                                       const std::string& pattern )
{

    std::vector<std::string> output;
    boost::split( output, str, boost::is_any_of(pattern));
    return output;
}

