#!/usr/bin/env python3
#   -*- coding: utf8 -*-
#
#   FILE:
#       /atlantis/s/swdevmnt/tau/toolboxes/pie/pieControlEngineering.py
#
################################################################################################

"""
.. inheritance-diagram:: pieControlEngineering
    :parts: 1
    :private-bases:

========

.. autosummary::

    PieRegulator

========

"""

import abc

from pieCore import PieIdentifyable
from pieActuators import PieActuator
from pieSensors import PieSensor


class PieRegulator( PieIdentifyable):

    """Ein SISO-Regler, der an seinen Einsatz angepasst werden kann.

    Note:
        Diese Klasse ist so **noch nicht einsatzfähig!** Was zu tun ist, mag folgender Sample-Code andeuten:

        ```python
        class uPieRegulator( pieCE.PieRegulator):

            class ActuatorU( pieCE.PieRegulator.ActuatorU):
                '''Stellgröße.'''

                def read_from_haedware( self): # override
                    pass

                def write_to_hardware( self): # override
                    print( self.odata().value())


            class SensorW( pieCE.PieRegulator.SensorW):
                '''Sollwert.'''

                def read_from_hardware( self): # override
                    self.odata().value( 42)

                def write_to_hardware( self): # override
                    pass

            class SensorY( pieCE.PieRegulator.SensorY):
                '''Istwert.'''

                def read_from_hardware( self): # override
                    self.odata().value( 41)

                def write_to_hardware( self): # override
                    pass
        ```
    """

    class ActuatorU( PieActuator):
        """Hält nur den Wert, der auf die HW zu schreiben ist und die Methode (`write_to_hardware`) muss in einer Subclass implementiert werden - wenn diese Klasse Verwednung finden soll.

        Diese Klasse muss nicht unbedingt verwendet werden, es kann auch `actuatorU_new`
        überschrieben werden, die einen Aktuator liefert.
        """
        pass


    class SensorW( PieSensor):
        """Hält nur den Wert, der von der HW zu lesen ist und die Methode (`read_from_hardware`) muss in einer Subclass implementiert werden - wenn diese Klasse Verwednung finden soll.

        Diese Klasse muss nicht unbedingt verwendet werden, es kann auch `sensorW_new`
        überschrieben werden, die einen Aktuator liefert.
        """
        pass


    class SensorY( PieSensor):
        """Hält nur den Wert, der von der HW zu lesen ist und die Methode (`read_from_hardware`) muss in einer Subclass implementiert werden - wenn diese Klasse Verwednung finden soll.

        Diese Klasse muss nicht unbedingt verwendet werden, es kann auch `sensorY_new`
        überschrieben werden, die einen Aktuator liefert.
        """
        pass


    def __init__( self, id: str):
        super().__init__( id)
        self.__sensorW = self.sensorW_new()
        assert isinstance( self.__sensorW, self.SensorW)
        self.__sensorY = self.sensorY_new()
        assert isinstance( self.__sensorY, self.SensorY)
        self.__actuatorU = self.actuatorU_new()
        assert isinstance( self.__actuatorU, self.ActuatorU)
        return

    @abc.abstractmethod
    def actuatorU_new( self):
        """Liefert den Aktuator, der den Stellwert (in die Hardware) schreibt.

        Kann überschrieben werden, muss aber nicht.

        Wird diese Methode nicht überschrieben, retourniert sie :class:`PieRegulator.ActuatorU`, d.h.
        man hat über die Ableitung der Klasse :class:`PieRegulator.ActuatorU` ebensogute Steuerungsmöglichkeiten.
        """
        return self.ActuatorU( "actuator 0")

    def execute( self) -> bool:
        with (self.__sensorW, self.__sensorY):
            self.__sensorW.read_from_hardware()
            self.__sensorY.read_from_hardware()
            e = self.__sensorW.odata().value() - self.__sensorY.odata().value()

        u = e # YOUR ALGORITHM GOES HERE

        with self.__actuatorU:
            self.__actuatorU.idata().value( u)
            self.__actuatorU.write_to_hardware()

        return

    def sensorW_new( self):
        """Liefert den Sensor, der den Sollwert (von der Hardware) liest.

        Kann überschrieben werden, muss aber nicht.

        Wird diese Methode nicht überschrieben, retourniert sie `PieRegulator.SesnorW`, d.h.
        man hat über die Ableitung der Klasse `PieRegulator.SesnorW` ebensogute Steuerungsmöglichkeiten.
        """
        return self.SensorW( "sensorW 0")

    @abc.abstractmethod
    def sensorY_new( self):
        """Liefert den Sensor, der den Istwert (von der Hardware) liest.

        Kann überschrieben werden, muss aber nicht.

        Wird diese Methode nicht überschrieben, retourniert sie :class:`PieRegulator.SensorY`, d.h.
        man hat über die Ableitung der Klasse `PieRegulator.SensorY` ebensogute Steuerungsmöglichkeiten.
        """
        return self.SensorY( "sensorY 0")

