import random, time
from paho.mqtt import client as mqtt
#from paho.mqtt.client import _OnPublish

class Thermometer(mqtt.Client):
    def __init__(self, client_id, mqtt_host, mqtt_portnumber=1883) -> None:
        super().__init__(client_id=client_id, clean_session=True)

        self.__id = client_id
        self.__reading = 0
        self.__mqtt_host=mqtt_host
        self.__mqtt_portnumber=mqtt_portnumber


    def start_connection(self):
        self.connect(self.__mqtt_host, self.__mqtt_portnumber)
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
    
    def publish(self, topic, payload=None, reporter=None, qos=0):
        if None is payload:
            payload = self.__reading
        if reporter:
            reporter("Publish '%s' -> '%s'" % (topic, payload))
        
        return super().publish(topic=topic, payload=payload, qos=0)

    def value(self):
        return self.__reading
    
    def username_pw_set(self, username: str, password: str | bytes | bytearray | None = None) -> None:
        return super().username_pw_set(username, password)
        

class TS_Thermometer(Thermometer):
    def __init__(self, client_id, mqtt_host, username=None, password=None, mqtt_portnumber=1883) -> None:
        super().__init__(client_id, mqtt_host, mqtt_portnumber)

        #if None is not username:
         #   super().username_pw_set(username=username, password=password)

    def start_connection(self):
        return super().start_connection()

    def publish(self, topic_id, reporter=None):
        topic = topic_id        

        retVal =  super().publish(topic=topic, qos=0)

        if reporter:
            reporter("Published. return was: %s" % retVal)
    

if __name__ == '__main__':
#    th = Thermometer("wohnzimmerthermometer","localhost")
#    th.start_connection()


    secret_MQTT_username =  "ORQcJA4VLC43MAYLERcqIzI"
    secret_MQTT_client_id = "ORQcJA4VLC43MAYLERcqIzI"
    secret_MQTT_password = "D3CchbEhHqs4/FJiTF59N2/w"

    mqtt_host = "mqtt3.thingspeak.com"

    ts_th = TS_Thermometer("channels/2187162/publish/fields/", mqtt_host=mqtt_host,
                           username=secret_MQTT_username, password=secret_MQTT_password)
    ts_th.username_pw_set(secret_MQTT_client_id, secret_MQTT_password)
    ts_th.start_connection()

    try:
        while True:
            ts_th.write_to_hardware()
            ts_th.write_to_hardware()
            ts_th.read_from_hardware()
            ts_th.publish(ts_th.id() + "field1", print)

            # th.write_to_hardware()
            # th.read_from_hardware()
            # th.publish(th.id() + "/temperatur", print)
            time.sleep(1.0)

    except KeyboardInterrupt:
        exit()