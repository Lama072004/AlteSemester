from os import getcwd
from locale import setlocale, getlocale, LC_ALL 
from datetime import datetime
from MenueTexts import texts_answer, texts_menue

class Menuline:
    def __init__(self, key: str, callback_requests = None, callback_answers = None):
        self.__key = key
        self.__callback_requests = callback_requests
        if type(self.__callback_requests) is not list: self.__callback_requests = [ self.__callback_requests  ]
        #self.__callback_requests = callback_requests if isinstance(callback_requests, list) else list(callback_requests)
        self.__callback_answers = callback_answers
        if type(self.__callback_answers) is not list: self.__callback_answers = [ self.__callback_answers ]
        
    def key(self):
        return self.__key
    
    def on_callback_request(self, key = None):
        for callback in self.__callback_requests:
            if None is not callback:
                if key is not None:
                    callback(key)
                else:
                    callback()

    def on_callback_answer(self, key = None):
        for callback in self.__callback_answers:
            if None is not callback:
                if key is not None:
                    callback(key)
                else:
                    callback()


class Textparser:
    def __init__(self, texts: dict, answers: dict,
                 filling_char='.', input_line_tag='in', filling_space=3):
        self.__texts = texts
        self.__answers = answers
        self.__longest_msg = 0
        self.__filling_char = filling_char
        self.__filling_space = filling_space
        self.__input_tag = input_line_tag
        self.refresh_longest_msg()

    def refresh_longest_msg(self, key = None):
        self.__longest_msg = 0
        for message_key in self.__texts.keys():
            try:
                message = self.__texts[message_key][getlocale()[0]]
                if len(message) > self.__longest_msg:
                    self.__longest_msg = len(message)      
            except:
                print(getlocale()[0] + " is not in translation list")
            

    def get_text(self, key):
        return self.__texts[key][getlocale()[0]]
    
    def print_formatted_text(self, val):
        str_to_print = self.get_text(val)
        filling_space = self.__longest_msg + self.__filling_space
        str_to_print = str_to_print.ljust(filling_space, self.__filling_char if val != self.__input_tag else ' ') #do not add dots to input line
        str_to_print = str_to_print + (val if val != self.__input_tag else '')#do not add key to input line
        print(str_to_print)
    
    def print_answer_for_key(self, key):
        print(self.__answers[key][getlocale()[0]])


class ActionGenerator:
    def __init__(self) -> None:
        pass

    def show_time(self, key=None):  
        current_time = datetime.now()      
        if  getlocale()[0] == 'de_DE':
            print(current_time.strftime("%A, %d. %B %Y %H:%M:%S"))
        else:
            print(current_time.strftime("%A, %B %d, %Y %I:%M:%S %p"))
            
    def show_cwd(self, key=None):
        print(getcwd())

    def on_exit(self, key=None):
        exit()
    
    def set_locale_to(self, local):
        if 'e' == local:
            setlocale(LC_ALL, 'en_US')
        elif 'd' == local:
            setlocale(LC_ALL, 'de_DE')

    


if __name__ == '__main__':


    tp = Textparser(texts=texts_menue, answers=texts_answer)
    ag = ActionGenerator()

    menulines = [
        Menuline(key="1", callback_requests=tp.print_formatted_text, 
                callback_answers=[tp.print_answer_for_key, ag.show_time]),
        Menuline(key="2", callback_requests=tp.print_formatted_text,
                callback_answers=[tp.print_answer_for_key, ag.show_cwd]),
        Menuline(key="d", callback_requests=tp.print_formatted_text,
                callback_answers=[ag.set_locale_to, tp.refresh_longest_msg]),
        Menuline(key="e", callback_requests=tp.print_formatted_text,
                callback_answers=[ag.set_locale_to, tp.refresh_longest_msg]),   
        Menuline(key="x", callback_requests=tp.print_formatted_text,
                callback_answers=[tp.print_answer_for_key, ag.on_exit])
    ]
    ag.set_locale_to('d')
    tp.refresh_longest_msg()
    
    while True:
        for menuline in menulines:
            key = menuline.key()
            menuline.on_callback_request(key)

        menuline.on_callback_request('in')
        key = input().lower()
        for menuline in menulines:
            if key == menuline.key():
                menuline.on_callback_answer(key)
                break


