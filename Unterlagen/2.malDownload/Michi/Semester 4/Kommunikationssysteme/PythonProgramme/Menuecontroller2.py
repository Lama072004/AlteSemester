from os import getcwd
from locale import setlocale, LC_ALL
from datetime import datetime
from MenueTexts import texts_answer, texts_menue

class Menuline:
    def __init__(self, key: str, callback: callable):
        #TODO: add multiple callbacks for each action
        self.__key = key
        self.__callback = callback

    def key(self):
        return self.__key
    
    def callback(self):
        self.__callback()

class Textparser:
    def __init__(self, texts: dict, lang: str = "de", answers: dict = None):
        #TODO:  keys (in, cwd and time) are fully bound to this function. 
        #       Could be separated by defining a function and add keys as member variables.
        #TODO:  Change binding to request answer keying. key 1 bound to answer 1 and so on.
        #       Additionally, add callbacks for each answer.       
        self.__lang = lang
        self.__texts = texts
        self.__answers = answers
        self.__longest_msg = 0

        #Get longest message to define layout of text
        for message_key in self.__texts.keys():
            for language_key in self.__texts[message_key]:
                message = self.__texts[message_key][language_key]
                if len(message) > self.__longest_msg:
                    self.__longest_msg = len(message)

    def change_language(self, lang: str):
        self.__lang = lang

    def get_text(self, val):
        return self.__texts[val][self.__lang]
    
    def get_formatted_text(self, val):
        retVal = self.get_text(val)
        filling_space = self.__longest_msg + 3 #3 spaces after the message
        retVal = retVal.ljust(filling_space, '.' if val != 'in' else ' ') #do not add dots to input line
        retVal = retVal + (val if val != 'in' else '')#do not add key to input line
        return retVal

    def change_to_de(self):
        self.change_language('de')   

    def change_to_en(self):
        self.change_language('en')
    
    def show_time(self):
        print(self.__answers['1'][self.__lang])
        
        if 'de' == self.__lang:
            setlocale(LC_ALL, 'de_DE')
            current_time = datetime.now()
            retVal = current_time.strftime("%A, %B %d, %Y %I:%M:%S %p")
        else:
            setlocale(LC_ALL, 'en_US')
            current_time = datetime.now()
            retVal = current_time.strftime("%A, %d. %B %Y %H:%M:%S")
        print(retVal)
        
    def show_cwd(self):
        print(self.__answers['2'][self.__lang])
        print(getcwd())

    def get_answer_for_key(self, key):
        return self.__answers[key][self.__lang]

    def on_exit(self):
        exit()

text_parser = Textparser(texts=texts_menue, answers=texts_answer)

menulines = [
    Menuline(key="1", callback=text_parser.show_time),
    Menuline(key="2", callback=text_parser.show_cwd),
    Menuline(key="d", callback=text_parser.change_to_de),
    Menuline(key="e", callback=text_parser.change_to_en),   
    Menuline(key="x", callback=text_parser.on_exit)
]

if __name__ == '__main__':
    while True:
        for menuline in menulines:
            key = menuline.key()
            print(text_parser.get_formatted_text(key))

        key = input(text_parser.get_formatted_text('in')).lower()
        for menuline in menulines:
            if key == menuline.key():
                menuline.callback()
                break


