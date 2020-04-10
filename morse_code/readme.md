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

* Still working on getting a good build target to put in the root make. For now these steps seem to get it built and run:
```shell
rm -rf build-test/
make BUILD_DIR_BASE="$(PWD)/build-test" defconfig
cd build-test 
cmake -DTDD=true .. 
make tdd
```
I have it making the test build in the folder `build-test/`. It is still using the manual commands and only CMake for now.

The TDD build is currently only CMake. It might end up staying that way. It is not yet clear to me whether the RTOS_SDK supports the full `idf.py` style building. The Makefile in the root does appear to invoke the `CMakeLists.txt`files and itself is running some of the `esp-idf` tools, so maybe it just runs `idf.py`.

