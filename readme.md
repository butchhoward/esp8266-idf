# Explorations with ESP8266 

## Configurations

### Resolve MacOS Python issues

Python has [environment issues](https://xkcd.com/1987/)

MacOS makes those worse by still installing Python 2.7.

Pyenv helps in most cases ([there are details](https://opensource.com/article/19/5/python-3-default-mac)):
```
pyenv install 3.7.2
pyenv global 3.7.2
```


### Install ESP8266_RTOS_SDK (IDF Style)

* Follow the steps EXACTLY: [Get Started](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html)


### Hello World

Getting the hello world example to build took some sleuthing:

* Be sure Python is right (see above)

* Make sure all the environment variables from the setup doc are set (`PATH` and `IDF_PATH`)

* Make sure those environment variables do not have conflicting settings from where you were exploring the ESP32-IDF tools earlier (they use the same variables!)

* Make sure you do not have any compiler or linker flags set globally (I had `LDFLAGS` and `CPPFLAGS` settings from a zlib config in my `.bash_profile`)

  This presented as linker errors when building the hello_world app:
  
  ```../../xtensa-esp32-elf/bin/ld: cannot find crt1-sim.o: No such file or directory```






