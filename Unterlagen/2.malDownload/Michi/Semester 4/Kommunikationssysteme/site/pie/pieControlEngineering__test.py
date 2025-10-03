#!/usr/bin/env python3
#   -*- coding: utf8 -*- #
#
#   FILE
#       /atlantis/s/swdevmnt/tau/toolboxes/pie/__test.py
#
################################################################################

import time
import unittest

from toolboxes.dreizax.dxTime import DxRuntimemeter

from pie import pieControlEngineering as pieCE


class _TESTCASE__PieRegulator( unittest.TestCase):

    def test__basic_use( self):
        """
        """
        print()

        class uPieRegulator( pieCE.PieRegulator):

            class ActuatorU( pieCE.PieRegulator.ActuatorU):

                def read_from_haedware( self): # override
                    pass

                def write_to_hardware( self): # override
                    print( self.odata().value())


            class SensorW( pieCE.PieRegulator.SensorW):

                def read_from_hardware( self): # override
                    self.odata().value( 42)

                def write_to_hardware( self): # override
                    pass

            class SensorY( pieCE.PieRegulator.SensorY):

                def read_from_hardware( self): # override
                    self.odata().value( 41)

                def write_to_hardware( self): # override
                    pass


        r = uPieRegulator( "ID")
        r.execute()
        return


_Testsuite = unittest.makeSuite( _TESTCASE__PieRegulator)


class _TESTCASE__( unittest.TestCase):

    def test__basic_use( self):
        """
        """
        print()
        return


_Testsuite.addTest( unittest.makeSuite( _TESTCASE__))


def _Lab_():
    return


def _Test_():
    unittest.TextTestRunner( verbosity=2).run( _Testsuite)


if __name__ == '__main__':
    _Test_()
    _Lab_()
    input( u"Press any key to exit...")




