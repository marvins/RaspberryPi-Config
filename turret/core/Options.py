
#  Python Libraries
import argparse, ConfigParser


class Options:

    cmd_options = None
    cfg_options = None

    def __init__(self):

        #  Parse Command-Line Options
        self.cmd_options = self.Parse_Command_Line()

        #  Parse Config-File
        self.cfg_options = self.Parse_Config_File()


    def Parse_Command_Line(self):
        '''
        Parse Command-Line Options.
        :return:
        '''

        #  Create parser
        parser = argparse.ArgumentParser(description='Turret Application')

        #  Add Option for Keyboard Control
        parser.add_argument('-k','--keyboard-control',
                            default=True,
                            required=False,
                            dest='keyboard_control',
                            action='store_true',
                            help='Control the Turret Using the Keyboard.')

        #  Parse Arguments
        return parser.parse_args()


    def Parse_Config_File(self):

        #  Create parser
        parser = ConfigParser.ConfigParser()
        parser.read('options.cfg')

        return parser
