#!/usr/bin/env python3
#   -*- coding: utf8 -*- #
#
#   FILE
#       /atlantis/s/swdevmnt/tau/toolboxes/pie/pieCore__test.py
#
################################################################################

import time
import unittest

from toolboxes.dreizax.dxTime import DxRuntimemeter

from pie import pieCore as pieC


class _TESTCASE__PieIdentifyable( unittest.TestCase):

    def test__uniqueness_is_forced( self):
        """
        """
        print()

        class Class( pieC.PieIdentifyable):

            def __init__( self, id):
                super().__init__( id)
                return


        inst = Class( "eins")
        inst = Class( "zwei")

        with self.assertRaises( ValueError):
            inst = Class( "zwei")

        return


_Testsuite = unittest.makeSuite( _TESTCASE__PieIdentifyable)


class _TESTCASE__PieLockable( unittest.TestCase):

    def test__basic_use( self):
        """
        """
        print()

        class Class( pieC.PieIdentifyable, pieC.PieLockable):

            def __init__( self, id):
                pieC.PieIdentifyable.__init__( self, id)
                pieC.PieLockable.__init__( self)
                return


        with Class( "ID") as inst:
            self.assertTrue( inst.is_locked())

        return


_Testsuite.addTest( unittest.makeSuite( _TESTCASE__PieLockable))


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




