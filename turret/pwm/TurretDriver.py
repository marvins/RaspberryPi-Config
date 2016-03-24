#!/usr/bin/python

from .Adafruit_PWM_Servo_Driver import PWM
import time


class Turret:

    channel = 0
    pulse = 500

    min_pulse = 150
    max_pulse = 650

    y_pulse = 500

    min_y_pulse = 150
    max_y_pulse = 650

    def __init__(self, options):

        #  Set the PWM Driver
        i2c_address = int(options.cfg_options.get('turret','i2c_address'), 16)
        self.pwm = PWM(i2c_address)

        self.pwm.setPWM(self.channel, 0, self.pulse)


    def Turn(self, value):

        self.pulse += value
        self.pulse = min( self.pulse, self.max_pulse)
        self.pulse = max( self.pulse, self.min_pulse)

        self.pwm.setPWM(0, 0, self.pulse)

    def Pitch(self, value):

        self.y_pulse += value
        self.y_pulse = min(self.y_pulse, self.max_y_pulse)
        self.y_pulse = max(self.y_pulse, self.min_y_pulse)

        self.pwm.setPWM(1, 0, self.y_pulse)

    def setServoPulse(self, channel, pulse):
        self.pulseLength = 1000000                   # 1,000,000 us per second
        self.pulseLength /= 60                       # 60 Hz
        print "%d us per period" % self.pulseLength
        self.pulseLength /= 4096                     # 12 bits of resolution
        print "%d us per bit" % self.pulseLength
        self.pulse *= 1000
        self.pulse /= self.pulseLength


