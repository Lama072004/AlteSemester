#!/usr/bin/env python3
#   -*- coding: utf8 -*-
#
#   FILE:
#       /atlantis/s/swdevmnt/tau/toolboxes/pie/pieSensors.py
#
################################################################################################

"""
.. inheritance-diagram:: pieSensors
    :parts: 1
    :private-bases:

========

.. autosummary::

    PieSensor

========

"""

import abc


from pieCore import PieIdentifyable, PieLockable


class PieSensor( PieIdentifyable, PieLockable, abc.ABC):

    """
    """

    class IData:
        """
        """

        def __init__( self, parent):
            self.__parent = parent

        def parent( self):
            return self.__parent


    class OData:
        """
        """

        def __init__( self, parent):
            self.__parent = parent
            self.__value = 0.0

        def parent( self):
            return self.__parent

        def value( self, arg=None):
            if arg is None:
                return self.__value

            self.__value = arg
            return self


    class SData:
        """
        """

        def __init__( self, parent):
            self.__parent = parent

        def parent( self):
            return self.__parent


    def __init__( self, id: str):
        PieIdentifyable.__init__( self, id)
        PieLockable.__init__( self)

        self.__idata = self.IData( self)
        self.__odata = self.OData( self)
        self.__sdata = self.SData( self)
        return

    def idata( self):
        """
        """
        return self.__idata

    def odata( self):
        """
        """
        return self.__odata

    def sdata( self):
        """
        """
        return self.__sdata

    @abc.abstractmethod
    def write_to_hardware( self):
        """:class:`PieSensor.IData` auf die Hardware schreiben.
        """
        pass

    @abc.abstractmethod
    def read_from_hardware( self):
        """Daten von der Hardware lesen und in die :class:`PieSensor.OData` schreiben.
        """
        pass


