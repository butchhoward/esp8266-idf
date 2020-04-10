# Morse Code Example for ESP8266 using ESP8266_RTOS_SDK


To make some of the config things easier, I have changed the `$(IDF_PATH)/components/esptool_py/Kconfig.projbuild` file have defaults matching the device I am using:

```diff
diff --git a/components/esptool_py/Kconfig.projbuild b/components/esptool_py/Kconfig.projbuild
index 46230a81..f869ada4 100644
--- a/components/esptool_py/Kconfig.projbuild
+++ b/components/esptool_py/Kconfig.projbuild
@@ -2,7 +2,7 @@ menu "Serial flasher config"

 config ESPTOOLPY_PORT
        string "Default serial port"
-       default "/dev/ttyUSB0"
+       default "/dev/cu.SLAB_USBtoUART"
        help
                The serial port that's connected to the ESP chip. This can be overridden by setting the ESPPORT
                environment variable.
@@ -84,7 +84,7 @@ config SPI_FLASH_MODE

 choice ESPTOOLPY_FLASHFREQ
        prompt "Flash SPI speed"
-       default ESPTOOLPY_FLASHFREQ_40M
+       default ESPTOOLPY_FLASHFREQ_80M
        help
                The SPI flash frequency to be used.

@@ -114,7 +114,7 @@ config SPI_FLASH_FREQ

 choice ESPTOOLPY_FLASHSIZE
        prompt "Flash size"
-       default ESPTOOLPY_FLASHSIZE_2MB
+       default ESPTOOLPY_FLASHSIZE_4MB
```



## Adding Tests

Cribbed much from Clay Dowlings [`holidaylights`](https://gitlab.com/ClayDowling/holidaylights) project which is based on the ESP32 using `esp-idf` (which the ESP8266_RTOS_SDK is based on). 

* Added folders for tests, mocks, the `unity` test framework.  
* Added `CMakeLists.txt` for `unity` which builds it as a static library. 
* Added `CMakeLists.txt` for `test` which builds `test/*.c`, `mock/*.c`, `main/*.c`, sets up the RTOS_SDK components, and makes an an executable based on the project name (`morse-code-test`. 
  `test_main.c` sets up and executes the unity tests that are written in the other source files in the folder.
* Added just enough mocks (actually mostly cribbed from Clay) to support testing for the modules that exist. (I will not entertain any bickering about mocks vs. fakes vs stubs; they are all test doubles of one kind or another.)
* The root `CMakeLists.txt` is changed to have conditonals around the TDD verses flash build.

* Create `Makefile.tdd` to be able to use `make` for both the flash and the TDD. `make` seems to be the preferred tool for the RTOS_SDK, even though it uses some of the IDF tools underneath. I'm still looking into whether using `idf.py` does the right thing for the flash builds and, if so, how to get it to do the TDD builds.

## `Makefile.tdd`

```shell
make -f Makefile.tdd
```

Provides these targets using the `build-test` folder as the output location:
* all
    * Generates the default config
* CMakes the `build-test`
    * Builds and Runs the tests
* tdd
    * Builds and Runs the tests
* do_cmake
    * regenerates the cmake files (useful when you add or remove a file from the tests)
* defconfig
    * Generates the default config
* menuconfig
    * Generates the full menu config (should the defaults not be good)
* clean
    * Cleans (removes) the `build-test` folder


