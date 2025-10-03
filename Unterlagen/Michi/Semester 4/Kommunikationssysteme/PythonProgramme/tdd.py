import unittest
from ringbuffer import PieRingbuffer 

class _TESTCASE__PieRingbuffer(unittest.TestCase):
    def test__basic_use(self): #can be any name starting with test_
        rb = PieRingbuffer(42)

        