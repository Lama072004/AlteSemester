from __future__ import annotations

class Subscriber:
    def on_box_was_written(self, box: PieBoxPublishing):
        print("Box '%s' was written. Value is:" % box.id(), box.value())

    def box_value_has_changed(self, box: PieBoxPublishing):
        print("Box '%s' has new value. Value is: " % box.id(), box.value())


class PieBox:
    def __init__(self, id, inital_value) -> None:
        self.__value = inital_value
        self.__id = id
        self._type_ =  type(inital_value) #_type_ is constructor for given type. Returns a callable object

    def __eq__(self, other):
        return self.value() == other.value()
    
    def __ne__(self, other):
        return not self == other

    def value(self, value = None):
        if None == value:
            return self.__value
        
        self.__value = self._type_(value)
        return self
    
    def id(self, id = None):
        if None == id:
            return self.__id
        self.__id = id
        return self

class PieBoxPublishing(PieBox):

    def __init__(self, id, inital_value, cb_on_write = None, cb_on_change = None) -> None:
        super().__init__(id, inital_value)
        self._callbacks_on_change_ =[]
        self._callbacks_on_write_ = []

    def value(self, value = None):
        value_old = super().value()
        
        result = super().value(value)

        if value is not None: #identity
            for callback in self._callbacks_on_write_:
                callback(self)

            if value != value_old:
                for callback in self._callbacks_on_change_:
                    callback(self)

        return result
    
    def register_cb_on_change(self, cb_on_change: callable): #cb_on_change or subscriber for var_name
        if self._callbacks_on_change_.count(cb_on_change) == 0:
            self._callbacks_on_change_.append(cb_on_change)
        return self

    def register_cb_on_write(self, cb_on_write: callable): #cb_on_write or subscriber for var_name
        if self._callbacks_on_write_.count(cb_on_write) == 0:
            self._callbacks_on_write_.append(cb_on_write)
        return self

def fun (arg: PieBox):
    arg.value(42)

box = PieBoxPublishing("pbp 1", 42.)
sub1 = Subscriber()
sub2 = Subscriber()
box.register_cb_on_write(sub1.on_box_was_written)
box.register_cb_on_write(sub2.on_box_was_written)
box.register_cb_on_change(sub1.box_value_has_changed)
box.register_cb_on_change(sub2.box_value_has_changed)

box.value(42.)
box.value(411.)


