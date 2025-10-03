#!/usr/bin/env python3
#   -*- coding: utf8 -*-
#
#   FILE:
#       /atlantis/s/swdevmnt/tau/toolboxes/pie/pieCore.py
#
################################################################################################

import threading


class PieIdentifyable:

    """Verwendung als Base Class, die einer Ableitung eine eindeutige (wird überprüft!) zuordnet.

    Errors:
        ValueError:
            ``id`` ist schon vergeben.
    """

    _Ids = set()

    def __init__( self, id: str):
        ids = self.__class__._Ids
        if id in ids:
            raise ValueError( "An object '%s' is already alive!" % id)

        ids.add( id)
        self.__id = id
        return

    def id( self) -> str:
        """
        """
        return self.__id


class PieLockable:

    """Verwendung als Base Class, die es einer Ableitung erlaubt, per ``with``-Statement gelockt zu werden.

    Examples:
        ```python
        ### Define the Resource
        #
        class SharedResource( PieLockable):

            pass

        ### Use the Resource
        #
        r = SharedResource()
        with r:
            # DO SOMETHING WITH r HERE
        ```
    """

    def __init__( self):
        self.__lock = threading.Lock()
        return

    def __enter__( self):
        self.__lock.acquire()
        return self

    def __exit__( self, *args, **kwargs):
        self.__lock.release()
        return

    def is_locked( self) -> bool:
        return self.__lock.locked()
