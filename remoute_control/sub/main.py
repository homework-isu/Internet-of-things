# import paho.mqtt.client as mqtt
# import time
# import serial

# mqtt_broker_host = "broker.emqx.io"
# mqtt_broker_port = 1883
# mqtt_topic = "fed-dan"

# ser = serial.Serial("COM7", baudrate=9600, timeout=1)

# def on_connect(client, userdata, flags, rc):
#     print(f"Connected with result code {rc}")
#     client.subscribe(mqtt_topic)

# def on_message(client, userdata, msg):
#     message = msg.payload.decode()
#     print(f"Received message: {message}")
#     ser.write(message.encode())

# client = mqtt.Client()
# client.on_connect = on_connect
# client.on_message = on_message

# client.connect(mqtt_broker_host, mqtt_broker_port, 60)

# while True:
#     client.loop_start()
#     time.sleep(1)

import time
import paho.mqtt.client as paho
import random

broker = "broker.emqx.io"

client = paho.Client("client-isu-741")

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()
print("Publishing")


state = "fce"
print(f'state is {state}')
client.publish("esp8266_Danila/command", state)
time.sleep(random.randint(4, 10))

client.disconnect()
client.loop_stop()