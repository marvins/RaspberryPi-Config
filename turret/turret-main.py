#!/usr/bin/env python

#  Turret Libraries
from core.Options import Options

#  Python Libraries
import pygame, sys
from pygame.locals import *


# ----------------------------- #
# -     Main Application      - #
# ----------------------------- #
def Main():

    #  Parse Command-Line Options
    options = Options()

    # Check if Using Keyboard
    if options.cmd_options.keyboard_control is True:

        #  Initialize Pygame
        pygame.init()
        #screen = pygame.display.set_mode ( ( 320 , 240 ) )
        index = 0

        while True:

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    print('Exiting Application')
                    sys.exit()
                elif event.type == pygame.KEYDOWN:
                    print "{0}: You pressed {1:c}".format ( index , event.key )
                elif event.type == pygame.KEYUP:
                    print "{0}: You released {1:c}".format ( index , event.key )
                index += 1



if __name__ == '__main__':
    Main()
