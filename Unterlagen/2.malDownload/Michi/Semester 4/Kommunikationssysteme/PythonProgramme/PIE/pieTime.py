#!/usr/bin/env python3
#   -*- coding: utf8 -*-
#
#   FILE:
#       /atlantis/s/swdevmnt/tau/toolboxes/pie/pieTime.py
#
################################################################################################

import time

from pieStatistix import PieStatistix


class PieRuntimemeter:

    """Klasse zum Messen von Laufzeiten.

    Parameters:
        info (str):
            Wenn angegeben, dann verwendet als Überschrift im Report.

    Examples:
        ```python
        rtm = PieRuntimemeter( "YOUR INFO HERE")
        for wurscht in range( 1000):
            with rtm:
                funktion_die_getimet_werden soll()

            funktion_die_nicht_in_zeitmessung_eingehen_soll()

        rtm.report( print)
        ```
    """

    def __init__( self, info=""):
        self.__info = info
        self.__starttime = 0.0
        self.__statistix = PieStatistix( 100)
        return

    def __enter__( self):
        """Enter-Methode des Context-Manager-Interfaces - siehe [https://docs.python.org/3/library/contextlib.html](https://docs.python.org/3/library/contextlib.html).
        """
        self.__starttime = time.time()
        return self

    def __exit__( self, *args, **kwargs):
        """Exit-Methode des Context-Manager-Interfaces - siehe [https://docs.python.org/3/library/contextlib.html](https://docs.python.org/3/library/contextlib.html).
        """
        if args[ 1] is not None:
            raise args[ 1]

        duration = time.time() - self.__starttime
        self.__statistix.elem_add( duration)
        return

    def report( self, renderer: callable=print):
        """Report generieren, retournieren und evtl anzeigen.

        Parameters:
            renderer (callable):
                Callable wie z.B. ``print``, um den Report auszugeben. Keine Ausgabe, wenn dieser
                Parameter ``None`` ist.

        Returns:
            str:
                Report als String, der auch per ``renderer`` ausgegeben wird, wenn ``renderer``
                nicht ``None`` ist.
        """
        if self.__info:
            s = "\n"
            s += self.__info
            s += "\n"
            s += "=" * len( self.__info)
            s += "\n"

        s += """\
Runtime as measured:
    Mean:   %.3f ms
    Stdev:  %.3f ms
""" % ( self.__statistix.mean() * 1000, self.__statistix.stdev() * 1000)

        if renderer:
            renderer( s)

        return s


if __name__ == "__main__":
    rtm = PieRuntimemeter( "time.sleep( 1)")
    for _ in range( 1000):
        with rtm:
            time.sleep( 0.001)

    rtm.report()

