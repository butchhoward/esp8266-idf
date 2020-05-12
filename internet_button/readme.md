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
* ~~Have 2 HTTP GET URIs<sup id="a1">[1](#f1)</sup>~~
  * ~~http://10.10.1.252/lamp/on~~
  * ~~http://10.10.1.252/lamp/off~~
* ~~Change the 2 URIs to HTTP POST:~~
  * ~~http://lamp.local/lamp/on~~
  * ~~http://lamp.local/lamp/off~~
* ~~Remove the Static IP (now using mDNS with a name of lamp.local)~~


## Activate using a (simple) custom iPhone app
* Create a simple iPhone app with two buttons that POST those URIs.

## Use UDP to Discover the device
* Figure out how WeMo and FauxMo do it, and do something similar.

## Create an Alexa Skill and command set to control the device.

## Make a nice container to hold the wires and parts
So it does not look a tangled mess shoved in a bin.


---

# Footnotes

[<b id="f1">1</b>](#a1) :
This is bad, but it allows the light to be controlled with any browser.
I made an attempt at using POST, but from a browser `<form>` the esp_http_server choked on the headers being sent. POST from `curl` worked fine. ~~I'll sort that out in the next release or so, maybe.~~ Turned out to be the size of the buffers the RTOS code allocates for reading and writing HTTP requests. There is a config setting to make it bigger.
