/**
 * @file    Tracker.hpp
 * @author  Marvin Smith
 * @date    4/1/2016
*/
#ifndef __PIDEF_CAMERA_TRACKER_HPP__
#define __PIDEF_CAMERA_TRACKER_HPP__

// C++ Libraries
#include <memory>
#include <tuple>

// OpenCV Libraries
#include <opencv2/opencv.hpp>


namespace PiDef{


/**
 * @class Target
*/
class Target
{
    public:
       
        /**
         * @brief Default Constructor
        */
        Target();


        /**
         * @brief Target
        */
        Target( const int& x, 
                const int& y );

        
        /**
         * @brief Update the Tracker
        */
        void Update();


        /**
         * @brief Get Position
        */
        inline std::tuple<int,int> Get_Position()const{
            return m_pos;
        }


        /**
         * @brief 
        */
        inline bool Is_Active()const{
            return m_active;
        }


    private:
        
        /// Active
        bool m_active;

        /// Position
        std::tuple<int,int> m_pos;

}; // End of Target Class


/**
 * @brief Target_Config
*/
class Target_Config
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<Target_Config> ptr_t;


        /**
         * @brief Constructor
        */
        Target_Config( const std::string& haar_pathname );


        /**
         * @brief Get the Haar Pathname.
        */
        inline std::string Get_Haar_Pathname()const{
            return m_haar_pathname;
        }

    private:
        
        /// Haar Pathname
        std::string m_haar_pathname;

}; // End of Target_Config Class
                       

/** 
 * @class Tracker
*/
class Tracker
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<Tracker> ptr_t;


        /**
         * @brief Constructor
        */
        Tracker( const Target_Config& config );
        

        /**
         * @brief Get Target 
        */
        inline Target Get_Active_Target( bool& active )const{
            active = m_active;
            return m_current_target;
        }

        
        /**
         * @brief Get Target 
        */
        inline Target Get_Active_Target()const{
            return m_current_target;
        }


        /**
         * @brief Update the Tracker
        */
        void Update();


        /**
         * @brief Get the latest image
        */
        inline cv::Mat Get_Latest_Camera_Frame()const{
            return m_latest_image;
        }


    private:

        /// Target Configuration
        Target_Config m_config;

        ///  Current Target
        Target m_current_target;
        bool m_active;
        
        /// Video Capture
        cv::VideoCapture m_cap;

        /// Latest Image
        cv::Mat m_latest_image;

        /// Classifier
        cv::CascadeClassifier m_face_cascade;

}; // End of Tracker Class


} // End of PiDef Namespace

#endif
