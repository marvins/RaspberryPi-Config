#!/bin/bash

#  Build Directory
BUILD_TYPE='release'

#  Number of Build Threads
NUM_THREADS=1

#  Arguments to PiDefender
PIDEF_ARGS=""

#------------------------------------#
#-     Print Usage Instructions     -#
#------------------------------------#
usage()
{
    echo "usage: $0 [options]"

    echo "-m | --make  : Build Software"
    echo "-c | --clean : Clean software builds."
    echo '-r | --run   : Run Software.'
    echo ''
    echo '--cal           : Run in Calibration Mode.'
    echo '--skip-wiringpi : Build without WiringPi Support.'
    echo ''

}


#-------------------------------#
#-     Construct Software      -#
#-------------------------------#
build_software()
{
    #  Log Entry
    echo "Building Software. Build-Type : $BUILD_TYPE"
    echo "                   Num-Threads: ${NUM_THREADS}"

    #  Create Build Directory and enter
    mkdir -p ${BUILD_TYPE}
    pushd ${BUILD_TYPE}

    #  Run CMake
    cmake ${CMAKE_ARGS} .. 
    if [ ! "$?" = '0' ]; then
        echo 'error with CMake. Aborting.'
        exit 1
    fi

    #  Run Make
    make -j${NUM_THREADS}
    if [ ! "$?" = '0' ]; then
        echo 'error with Make. Aborting.'
        exit 1
    fi
    

    #  Exit Build Directory
    popd
}


#---------------------------#
#-      Clean Software     -#
#---------------------------#
clean_software()
{
    echo "Removing ${BUILD_TYPE} Build"
    rm -r ${BUILD_TYPE}
}


#-----------------------------#
#-      Run the Software     -#
#-----------------------------#
run_software()
{
    #  Log Entry
    echo "Running Software. Build Type: ${BUILD_TYPE}"
    
    #  Create CMD
    CMD="${BUILD_TYPE}/pi-defender ${PIDEF_ARGS}"

    # Run Command
    $CMD

}


#----------------------------------------------#
#-      Parse the Command-Line Arguments      -#
#----------------------------------------------#
RUN_MAKE=0
RUN_CLEAN=0
RUN_BIN=0

#  Temp Flags
NUM_THREADS_FLAG=0

#  Iterate over arguments
for ARG in "$@"; do
    case $ARG in

        #  Usage Instructions
        '-h'|'--help')
            usage
            exit 0
            ;;

        #  Clean
        '-c'|'--clean')
            RUN_CLEAN=1
            ;;

        # Build Software
        '-m' | '--make')
            RUN_MAKE=1
            ;;

        #  Run Software
        '-r'|'--run')
            RUN_BIN=1
            ;;

        #  Skip Wiring Pi
        '--skip-wiringpi')
            CMAKE_ARGS="$CMAKE_ARGS -DUSE_WIRINGPI=OFF"
            ;;
        
        #  Run Calibration
        '--cal')
            PIDEF_ARGS="--cal"
            ;;

        #  Number of Threads
        '-j')
            NUM_THREADS_FLAG=1
            ;;

        #  Otherwise, error
        *)
            #  Check if Number of threads flag set
            if [ "$NUM_THREADS_FLAG" = '1' ]; then
                NUM_THREADS_FLAG=0
                NUM_THREADS=$ARG

            #  Otherwise, error
            else
                echo "Unknown Argument ($ARG)"
                exit 1
            fi
    esac
done


#   Check if no args provided
if [ "$RUN_MAKE" = '0' -a "$RUN_CLEAN" = '0' -a "$RUN_BIN" = '0' ]; then
    RUN_MAKE=1
fi

#  Clean the Software
if [ "$RUN_CLEAN" = '1' ]; then
    clean_software
fi

#  Build the Software
if [ "$RUN_MAKE" = '1' ]; then
    build_software
fi

#  Run the Software
if [ "$RUN_BIN" = '1' ]; then
    run_software
fi


