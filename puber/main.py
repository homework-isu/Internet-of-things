import paho.mqtt.client as mqtt
import datetime
import time

def min():
    return datetime.datetime.now().minute

def hour():
    return datetime.datetime.now().hour

def sec():
    return datetime.datetime.now().second

broker_address = "broker.emqx.io" 
port = 1883 
topic = "esp8266_Danila/command" 

def send_message(client, message):
    client.publish(topic, message)


client = mqtt.Client("lamp_client")


client.connect(broker_address, port, 60)

duration = 20 
try:
    while True:
      
        time_to_start = 20
  
        minute = min()
        state = False

        while minute == min():

            second = sec()
            if second >= time_to_start and second <= time_to_start + duration and not state:
                state = True
                send_message(client, "u")
                print(f"отправлено 'u'; время: {hour()}:{minute}:{second}; duration: {duration}")
            elif (second < time_to_start or second > time_to_start + duration) and state:
                state = False
                send_message(client, "d")
                print(f"отправлено 'd'; время: {hour()}:{minute}:{second}")
    
            time.sleep(1)

        if duration == 10:
            duration = 20
        else:
            duration -= 1
            print(f"new duretion {duration}")

except KeyboardInterrupt:
    pass

finally:
    client.disconnect()
