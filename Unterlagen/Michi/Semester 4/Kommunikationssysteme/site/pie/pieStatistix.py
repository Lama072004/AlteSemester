#!/usr/bin/env python3
#   -*- coding: utf8 -*-
#
#   FILE:
#       /atlantis/s/swdevmnt/tau/toolboxes/pie/pieStatistix.py
#
################################################################################################


import statistics

from pie.pieDataManagement import PieRingbuffer


class PieStatistix( PieRingbuffer):

    """Ringpuffer, der Mittelwert und Standardabweichung aus seinen *numerischen* Elementen berechnen kann.

    Somit lässt sich mit dieser Klasse der *gleitende Durchschnitt* von Signalen berechnen.
    """

    def elems_add( self, elem): # override
        """Element hinzufügen.

        Override, der sicherstellt, dass nur numerische Elemente (Werte) aufgenommen werden können.

        Parameters:
            elem (float, int):
                Wert, der hinzugefüht werden soll und - bei vollem Puffer - den ältesten verdrängt.

        Errors:
            TypeError, wenn ``elem`` nicht numerisch ist.
        """
        if not isinstance( elem, (float, int)):
            raise TypeError( "Only numerical values make sense here!")

        return super().elem_add( elem)

    def mean( self):
        """Mittwelwert.
        """
        mean = statistics.mean( self.elems())
        return mean

    def stdev( self):
        """Standardabweichung.
        """
        if self.num_elems() >= 2:
            stdev = statistics.stdev( self.elems())

        else:
            stdev = 0.0

        return stdev


if __name__ == "__main__":
    stats = PieStatistix( 5)
    stats.elem_add( 1)
    stats.elem_add( 2)
    mean = stats.mean()

    stats.elems_add( "Hollodrio")
    mean = stats.mean()


