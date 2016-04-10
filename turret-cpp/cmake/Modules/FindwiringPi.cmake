#   Try to Find WiringPi Library
#
#
# Once Finish, this will define
#  
#   WIRINGPI_FOUND
#   WIRINGPI_INCLUDE_DIR
#   WIRINGPI_LIBRARY
#   WIRINGPI_DEV_LIBRARY
#   WIRINGPI_VERSION
#

#----------------------------------------------#
#-    Look for the Base WiringPi Directory    -#
#----------------------------------------------#
find_path(WIRINGPI_INCLUDE_DIR wiringPi.h)


#------------------------------------#
#-      Look for the Libraries      -#
#------------------------------------#
find_library( WIRINGPI_LIBRARY
                NAMES
                    wiringPi
                HINTS
                    ENV WIRINGPI_ROOT
                PATH_SUFFIXES
                    lib
                    lib64
                PATHS
                    /usr/lib
                    /usr/lib64
                    /usr/local/lib
                    /usr/local/lib64
)

find_library( WIRINGPI_DEV_LIBRARY
                NAMES
                    wiringPiDev
                HINTS
                    ENV WIRINGPI_ROOT
                PATH_SUFFIXES
                    lib
                    lib64
                PATHS
                    /usr/lib
                    /usr/lib64
                    /usr/local/lib
                    /usr/local/lib64
)

#-------------------------------------------#
#-      Make sure we found everything      -#
#-------------------------------------------#
if( WIRINGPI_INCLUDE_DIR AND WIRINGPI_LIBRARY AND WIRINGPI_DEV_LIBRARY )
    SET( WIRINGPI_FOUND TRUE )
else()
    SET( WIRINGPI_FOUND FALSE )
endif()


