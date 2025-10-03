#!/usr/bin/env python3
#   -*- coding: utf8 -*-
#
#   FILE:
#       /atlantis/s/swdevmnt/tau/toolboxes/pie/pieDataManagement.py
#
################################################################################################

import collections


class PieBox:

    """Eine Box verwaltet ein Element (Zahlenwerte als Element scheinen am sinnvollsten): Lesen, Schreiben, Subscribers über Lese-, Schreib-, Änderungs-Events informieren.

    Zwar verwaltet die Box (Zahlen-) Werte, aber es kann auch ein Label und eine Dimension definiert
    werden. Beides kann nützlich sein, wenn die Box in einem GUI zum Einsatz kommt.

    Parameters:
        value (any):
            (Zahlen-) Wert, der verwaltet werden soll. Der Typ des Arguments ``value``, das hier
            übergeben wird, bestimmt den Typ der Box.

        id (str):
            Optional, eine (eindeutige) Identifikation.

    Examples:
        ```python
        box = PieBox( 42)

        box = PieBox( 42)
        box.label( "Spannung").dim( "V")

        box = PieBox( 42).label( "Spannung").dim( "V")
        ```
    """

    def __init__( self, value, id: str=None, label="", dim=""):
        self.__id = id
        self.__value = value
        self.__label = label
        self.__dim = dim

        self.__type = type( value)
        self.__callbacks_on_value_changed = []
        self.__callbacks_on_value_written = []
        return

    def __str__( self):
        """String-Repräsentation der Box.
        """
        return "%s: %s %s" % (self.__label, self.__value, self.__dim)

    def dim( self, arg=None):
        """Lesen/Schreiben der dimension des Wertes wie V, A, m/s usw.

        Die Dimension hat nur informativen Charakter und wird insbesondere **nicht** für (automatische)
        Umrechnungen verwendet.
        """
        if arg is None:
            return self.__dim

        self.__dim = arg
        return self

    def id( self):
        """Identifikation der Box, wie beim Instanzieren übeergeben.
        """
        return self.__id

    def label( self, arg=None):
        """Lesen/Schreiben des Labels.
        """
        if arg is None:
            return self.__label

        self.__label = arg
        return self

    def reg_callback_on_value_changed( self, callback: callable):
        """Registrierung des Callbacks, der ausgeführt wird, wenn der Wert der Box **geändert** worden ist - und nur dann!

        Parameters:
            callback (callable):
                Methode oder Funktion, die einen Aktualparameter übernehmen können muss (= einen
                Formalparameter haben muss). Dieder Parameter wird unsere Box sein, damit der
                Subscriber deren Wert lesen kann.

        2DOs:
            Absicherung gegen Mehrfachregistrierung implementieren.
        """
        self.__callbacks_on_value_changed.append( callback)
        return

    def reg_callback_on_value_written( self, callback: callable):
        """Registrierung des Callbacks, der ausgeführt wird, wenn der Wert geschrieben worden ist, egal ob er auch geändert worden ist.

        Parameters:
            callback (callable):
                Methode oder Funktion, die einen Aktualparameter übernehmen können muss (= einen
                Formalparameter haben muss). Dieder Parameter wird unsere Box sein, damit der
                Subscriber deren Wert lesen kann.

        2DOs:
            Absicherung gegen Mehrfachregistrierung implementieren.
        """
        self.__callbacks_on_value_written.append( callback)
        return

    def value( self, arg=None):
        """Lesen/Schreiben des Wertes.

        Dabei wird der Wert gecastet, also in jenen Typ umgewandelt, der der Wert bei Ausführung
        des Ctor hatte.

        Beim Schreiben werden folgende Callbacks ausgeführt:

        -   *Callbacks on value changed*
        -   *Callbacks on value written*
        """
        if arg is None:
            return self.__value

        old_value = self.__value

        self.__value = self.__type( arg)

        if True:
                                        # Wir sind geschrieben worden, also entsprechende
                                        #   Callbacks ausführen.
            for callback in self.__callbacks_on_value_written:
                callback( self)

        if self.__value != old_value:
                                        # Wir sind geändert worden, also entsprechende Callbacks
                                        #   ausführen.
            for callback in self.__callbacks_on_value_changed:
                callback( self)

        return self


class PieRingbuffer:

    """Ringpuffer mit Größe, die man beim Instanzieren angeben muss.

    PARAMETERS:
        num_elems (int):
            Anzahl Elemente, die der Ringpuffer maximal halten können soll.

    Vielfältige Verwendung ist denkbar, so auch für die Berechnung gleitender
    Durchschnitte - siehe :class:`pieStatistix.PieStatistix`.

    SEE ALSO:
        :class:`pieStatistix.PieStatistix`.

    """

    def __init__( self, num_elems):
        self.__elems = collections.deque( maxlen=num_elems)
        return

    def elem_add( self, elem):
        """Neuen Wert in den Ringpuffer aufnehmen.

        Wenn der Ringpuffer voll ist, fliegt das älteste Element raus.
        """
        self.__elems.append( elem)
        return

    def elems( self):
        """Alle Elemente.

        IMPORTANT:
            Es wird eine Referenz auf die Elemente geliefert, keine Kopie!
        """
        return self.__elems

    def num_elems( self):
        """
        """
        return len( self.__elems)


if __name__ == "__main__":
    def callback_on_box_has_changed( box):
        print( box.value())
        return


    class Multimeter:

        def __init__( self):
            return

        def callback_on_current_has_changed( self, box_in_a_currentsensor):
            print( box_in_a_currentsensor.value())
            return

        def callback_on_current_has_been_written( self, box_in_a_currentsensor):
            print( box_in_a_currentsensor.value())
            return


    mm = Multimeter()
    box = PieBox( value=42.0)
    print( box._callbacks_on_value_changed)
    box.label( "Current").dim( "A")
    box.reg_callback_on_value_changed( callback_on_box_has_changed)
    box.reg_callback_on_value_changed( mm.callback_on_current_has_changed)
    box.reg_callback_on_value_written( mm.callback_on_current_has_been_written)
    box.value( 13)
    box.value( 13)

    print( box)
    print( box)
