#!/usr/bin/env python3
#   -*- coding: utf8 -*-
#
#   FILE:
#       /atlantis/s/swdevmnt/tau/toolboxes/pie/pieActuators.py
#
################################################################################################


"""
.. inheritance-diagram:: pieActuators
    :parts: 1
    :private-bases:

========

.. autosummary::

    PieActuator

========

"""

import abc

from pieCore import PieIdentifyable, PieLockable


class PieActuator( PieIdentifyable, PieLockable, abc.ABC):
    """
    """

    class IData:
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


    class OData:
        """
        """

        def __init__( self, parent):
            self.__parent = parent

        def parent( self):
            return self.__parent

        def value( self):
            return self.parent().idata().value()


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
        pass

    @abc.abstractmethod
    def read_from_haedware( self):
        pass
