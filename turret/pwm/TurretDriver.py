#!/usr/bin/python

from .Adafruit_PWM_Servo_Driver import PWM
import time


class Turret:

    channel = 0
    pulse = 500

    def __init__(self, options):

        #  Set the PWM Driver
        i2c_address = int(options.cfg_options.get('turret','i2c_address'), 16)
        print('I2C: ' + str(i2c_address))
        self.pwm = PWM(i2c_address)

        servoMin = 150  # Min pulse length out of 4096
        servoMax = 600  # Max pulse length out of 4096

        self.pwm.setPWM(self.channel, 0, self.pulse)


    def Turn(self, value):

        self.pulse += value
        self.pwm.setPWM(0, 0, self.pulse)

    def setServoPulse(self, channel, pulse):
        self.pulseLength = 1000000                   # 1,000,000 us per second
        self.pulseLength /= 60                       # 60 Hz
        print "%d us per period" % self.pulseLength
        self.pulseLength /= 4096                     # 12 bits of resolution
        print "%d us per bit" % self.pulseLength
        self.pulse *= 1000
        self.pulse /= self.pulseLength


