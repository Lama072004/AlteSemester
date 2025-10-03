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


class _TESTCASE__0( unittest.TestCase):

    def test__basic_use( self):
        """
        """
        print()

        return


_Testsuite = unittest.makeSuite( _TESTCASE__0)


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




