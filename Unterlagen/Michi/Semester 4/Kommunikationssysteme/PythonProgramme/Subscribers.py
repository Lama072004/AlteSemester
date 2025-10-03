import random, time

from paho.mqtt import client as mqtt

class Dashboard(mqtt.Client):
    def __init__(self, id, brokeraddress, brokerportnumber=1883) -> None:
        super().__init__(client_id=id)
        
        self.__id = id

        self.connect(brokeraddress, brokerportnumber)
        self.loop_start()
        time.sleep(0.001)

    def id(self):
        return self.__id
    
    def on_message(self, client, userdata, message):
        topicid= message.topic
        topicdata = message.payload

        print("Got message '%s': '%s'" % (topicid, str(topicdata, "utf-8")))

    def subscribe(self, topicid):
        super().subscribe(topic=topicid)


if __name__=='__main__':
    db = Dashboard("dashboard", "localhost")
    db.subscribe("wohnzimmerthermometer/#")
    try:
        while True:
            print("Waiting for  data")
            time.sleep(0.5)
    except KeyboardInterrupt:
        print("\nFinished")
    

    