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
        screen = pygame.display.set_mode ((320,240))
        index = 0
        exit_loop = False

        while exit_loop is False:

            for event in pygame.event.get():

                #  Check if User wants to Exit Game
                if event.type == pygame.QUIT:
                    print('Exiting Application')
                    sys.exit()

                #  Keyboard Down
                elif event.type == pygame.KEYDOWN:

                    if event.key == pygame.K_LEFT:
                        print('Detected Left Arrow Key')
                        pwm_driver.Rotate_X(-5)

                    elif event.key == pygame.K_RIGHT:
                        print('Detected Right Arrow Key')
                        pwm_driver.Rotate_X(5)

                    #  Check the Up Buttom
                    elif event.key == pygame.K_UP:
                        print('Detected Up Arrow Key')
                        pwm_driver.Rotate_Y(5)

                    #  Check the Down Button
                    elif event.key == pygame.K_DOWN:
                        print('Detected Down Arrow Key')
                        pwm_driver.Rotate_Y(-5)

                    #  Check the Escape Button
                    elif event.key == pygame.K_ESCAPE:
                        exit_loop = True

                index += 1


if __name__ == '__main__':
    Main()
