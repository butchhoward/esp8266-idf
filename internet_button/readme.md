# Internet Button Example for ESP8266 using ESP8266_RTOS_SDK

**Cloned from morse_code example**


# The Button

Create a button that can be controlled via the (local LAN only) internet to switch power to an outlet so that a lamp can be turned on or off remotely.

Use:
* Adafruit Feather Huzzah ESP8266
* Adafruit Featherwing Power Relay (unlatched)
* Espressif ESP8266_RTOS_SDK


# Slices:

## Activate using a browser on an iPhone
* Configure the device with a Static IP address on the local LAN
* Use the RTOS_SDK http component to make a ReST Server on the ESP8266
* Have 2 URIs:
    http://10.10.1.252/on
    http://10.10.1.252/off
that are HTTP GET URIs (this is bad, but it allows the light to be controlled with any browser.)

## Activate using a (simple) custom iPhone app
* Change the 2 URIs to HTTP POST:
    http://10.10.1.252/on
    http://10.10.1.252/off

* Create a simple iPhone app with two buttons that POST those URIs.
* Continue to use the Static IP

## Use UDP to Discover the device

* Figure out how WeMo and FauxMo do it, and do something similar.
* Remove the Static IP

## Create and Alexa Skill and command set to control the device.

