# Morse Code Example for ESP8266 using ESP8266_RTOS_SDK


Using `sdkconfig.defaults` to hold the config settings that match the current device.

## Building for flash

```shell
make defconfig flash
```

If the `defconfig` or `menuconfig` targets have been used at least once (since a clean), then you can just

```shell
make flash
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
    * builds the tests
    * runs the tests
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


