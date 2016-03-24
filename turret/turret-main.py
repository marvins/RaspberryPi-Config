#!/usr/bin/env python

#  Turret Libraries
from core.Options import Options

#  Python Libraries
import pygame
from pygame.locals import *


# ----------------------------- #
# -     Main Application      - #
# ----------------------------- #
def Main():

    #  Parse Command-Line Options
    options = Options()

    #  Initialize Pygame
    pygame.init()


if __name__ == '__main__':
    Main()
