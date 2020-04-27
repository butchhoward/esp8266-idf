# Internet Button Example for ESP8266 using ESP8266_RTOS_SDK

**Cloned from morse_code example**

Added a [Progress](./doc/progress.md) doc.

# The Button

Create a button that can be controlled via the (local LAN only) internet to switch power to an outlet so that a lamp can be turned on or off remotely.

Use:
* Adafruit Feather Huzzah ESP8266
* Adafruit Featherwing Power Relay (unlatched)
* Espressif ESP8266_RTOS_SDK


# Slices:

## Activate using a browser on an iPhone
* ~~Configure the device with a Static IP address on the local LAN~~
* ~~Use the RTOS_SDK http component to make a ReST Server on the ESP8266~~
* ~~Have 2 [HTTP GET URIs][1]~~
  * ~~http://10.10.1.252/lamp/on~~
  *  ~~http://10.10.1.252/lamp/off~~


## Activate using a (simple) custom iPhone app
* Change the 2 URIs to HTTP POST:
  * http://10.10.1.252/lamp/on
  * http://10.10.1.252/lamp/off
* Create a simple iPhone app with two buttons that POST those URIs.
* Continue to use the Static IP

## Use UDP to Discover the device

* Figure out how WeMo and FauxMo do it, and do something similar.
* Remove the Static IP

## Create and Alexa Skill and command set to control the device.

## Make a nice container to hold the wires and parts
So it does not look a tangled mess shove in a bin.



# Footnotes

[1]:  This is bad, but it allows the light to be controlled with any browser.
I made an attempt at using POST, but from a browser `<form>` the esp_http_server choked on the headers being sent. POST from `curl` worked fine. I'll sort that out in the next release or so, maybe
