import random, time
from paho.mqtt import client as mqtt

class Thermometer(mqtt.Client):
    def __init__(self, mqtt_topic, mqtt_host, host_port=1883, username=None, password=None) -> None:
        super().__init__(client_id=username, clean_session=True)
        
        self.__mqtt_topic = mqtt_topic
        self.__reading = 0

        if None is not username:
            self.username_pw_set(username=username, password=password)

        self.connect(host=mqtt_host, port=host_port)
        self.loop_start()
        time.sleep(0.001)

    def topic(self):
        return self.__mqtt_topic
    
    def write_to_hardware(self):
        pass

    def read_from_hardware(self, topic_id=None):
        self.__reading = random.gauss(22,2)

        if topic_id is not None:
            self.publish(topic_id)

    def publish(self,topic_id, reporter=None):
        topic_data = self.__reading
        payload = str(topic_data)
        if reporter:
            reporter("Publishing '%s' -> '%s'" % (topic_id, payload))
        try:
            retVal =  super().publish(topic=topic_id, payload=payload, qos=0)
            if reporter:
                reporter("Published. return was: %s" % retVal)
        except Exception as e:
            if reporter:
                reporter ("Sending failed. Error was: %s" % e)

    def value(self):
        return self.__reading
        

if __name__ == '__main__':

    secret_MQTT_username =  "ORQcJA4VLC43MAYLERcqIzI"
    secret_MQTT_password = "D3CchbEhHqs4/FJiTF59N2/w"
    mqtt_host = "mqtt3.thingspeak.com"
    mqtt_topic = "channels/2187162/publish/fields/"
    th = Thermometer(mqtt_topic=mqtt_topic, mqtt_host=mqtt_host, host_port=1883,
                     username=secret_MQTT_username, password=secret_MQTT_password)
    try:
        while True:
            th.write_to_hardware()
            th.read_from_hardware()
            #th.publish_to_TS(th.id(), print)
            th.publish(th.topic() + "field1", print)
            #th.publish(th.id() + "/temperatur", print)
            time.sleep(1.0)

    except KeyboardInterrupt:
        exit()