#!/usr/bin/env python

#  Turret Libraries
from core.Options import Options
from pwm.TurretDriver import Turret


#  Python Libraries
import pygame, sys
from pygame.locals import *


# ----------------------------- #
# -     Main Application      - #
# ----------------------------- #
def Main():

    #  Parse Command-Line Options
    options = Options()

    #  Initialize the Turret Driver
    pwm_driver = Turret(options)

    # Check if Using Keyboard
    if options.cmd_options.keyboard_control is True:

        #  Initialize Pygame
        pygame.init()
        screen = pygame.display.set_mode ()
        index = 0

        while True:

            for event in pygame.event.get():

                #  Check if User wants to Exit Game
                if event.type == pygame.QUIT:
                    print('Exiting Application')
                    sys.exit()

                #  Keyboard Down
                elif event.type == pygame.KEYDOWN:

                    if event.key == pygame.K_LEFT:
                        print "You pressed left key."

                    elif event.key == pygame.K_RIGHT:
                        print "You pressed right key."
                index += 1


if __name__ == '__main__':
    Main()
