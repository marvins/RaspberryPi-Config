#!/usr/bin/python

from .Adafruit_PWM_Servo_Driver import PWM
import time, logging


class Turret:

    #  I2C Address
    i2c_address = 0

    x_channel = 0
    x_pulse = 500

    min_x_pulse = 150
    max_x_pulse = 650

    x_channel = 1
    y_pulse = 500

    min_y_pulse = 150
    max_y_pulse = 650

    def __init__(self, options):

        #  Set the PWM Driver
        self.i2c_address = int(options.cfg_options.get('turret','i2c_address'), 16)
        self.x_channel   = int(options.cfg_options.get('turret','x_servo_device'), 16)
        self.y_channel   = int(options.cfg_options.get('turret','y_servo_device'), 16)

        #  Logging
        logging.info('Loading Driver: ' + str(self.i2c_address))
        
        #  Construct PWM Driver
        self.pwm = PWM(self.i2c_address)

        #  Initialize the PWM Device
        self.pwm.setPWM(self.x_channel, 0, self.x_pulse )
        self.pwm.setPWM(self.y_channel, 0, self.y_pulse )


    def Rotate_X(self, value):

        self.x_pulse += value
        self.x_pulse = min( self.x_pulse, self.max_x_pulse)
        self.x_pulse = max( self.x_pulse, self.min_x_pulse)

        self.pwm.setPWM(self.x_channel, 0, self.x_pulse)

    def Rotate_Y(self, value):

        self.y_pulse += value
        self.y_pulse = min(self.y_pulse, self.max_y_pulse)
        self.y_pulse = max(self.y_pulse, self.min_y_pulse)

        self.pwm.setPWM(self.y_channel, 0, self.y_pulse)


    def setServoPulse(self, channel, pulse):
        self.pulseLength = 1000000                   # 1,000,000 us per second
        self.pulseLength /= 60                       # 60 Hz
        print "%d us per period" % self.pulseLength
        self.pulseLength /= 4096                     # 12 bits of resolution
        print "%d us per bit" % self.pulseLength
        self.pulse *= 1000
        self.pulse /= self.pulseLength


