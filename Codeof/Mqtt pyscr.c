import paho.mqtt.client as mqtt
import time

# MQTT broker information
broker_address = "broker.hivemq.com"  # Example MQTT broker
topic = "led/control"

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

client = mqtt.Client()
client.on_connect = on_connect

client.connect(broker_address)

client.loop_start()

try:
    while True:
        # Automatically publish messages to control LEDs
        client.publish(topic, "LED 1 ON")
        time.sleep(5)  # Wait for 5 seconds
        client.publish(topic, "LED 2 ON")
        time.sleep(5)  # Wait for 5 seconds
        client.publish(topic, "LED 3 ON")
        time.sleep(5)  # Wait for 5 seconds
        client.publish(topic, "LED 1 OFF")
        time.sleep(5)  # Wait for 5 seconds
        client.publish(topic, "LED 2 OFF")
        time.sleep(5)  # Wait for 5 seconds
        client.publish(topic, "LED 3 OFF")
        time.sleep(5)  # Wait for 5 seconds

except KeyboardInterrupt:
    print("Exiting...")

finally:
    client.loop_stop()
    client.disconnect()
