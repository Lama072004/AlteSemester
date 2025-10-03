import random, time
from paho.mqtt import client as mqtt

class Thermometer(mqtt.Client):
    def __init__(self, client_id, mqtt_host, host_port=1883, username=None, password=None) -> None:
        super().__init__(client_id=client_id, clean_session=True)
        
        self.__id = client_id
        self.__reading = 0

        if None is not username and None is not password:
            self.username_pw_set(username=username, password=password)

        self.connect(host=mqtt_host, port=host_port)
        self.loop_start()
        time.sleep(0.001)

    def id(self):
        return self.__id
    
    def write_to_hardware(self):
        pass

    def read_from_hardware(self, topic_id=None):
        self.__reading = random.gauss(22,2)

        if topic_id is not None:
            self.publish(topic_id)

    def publish_to_TS_Field(self,topic_id, reporter=None):
        topic_data = self.__reading

        topic = "channels/2187162/publish/fields/field1"
        #print(type(topic))

        payload = str(topic_data)
        #print(type(payload))
        
        retVal =  super().publish(topic=topic, payload=payload, qos=0)
        if reporter:
            reporter("Publishing '%s' -> '%s'" % (topic, payload))
        if reporter:
            reporter("Published. return was: %s" % retVal)


    def value(self):
        return self.__reading
        

if __name__ == '__main__':

    secret_MQTT_username =  "ORQcJA4VLC43MAYLERcqIzI"
    secret_MQTT_client_id = "ORQcJA4VLC43MAYLERcqIzI"
    secret_MQTT_password = "D3CchbEhHqs4/FJiTF59N2/w"
    mqtt_host = "mqtt3.thingspeak.com"

    th = Thermometer(client_id=secret_MQTT_client_id, mqtt_host=mqtt_host, host_port=1883,
                     username=secret_MQTT_username, password=secret_MQTT_password)
    try:
        while True:
            th.write_to_hardware()
            th.read_from_hardware()
            #th.publish_to_TS(th.id(), print)
            th.publish_to_TS_Field(th.id(), print)
            #th.publish(th.id() + "/temperatur", print)
            time.sleep(1.0)

    except KeyboardInterrupt:
        exit()