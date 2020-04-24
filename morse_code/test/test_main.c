#include "unity_fixture.h"

static void run_all_tests(void) {
  RUN_TEST_GROUP(leds);
  RUN_TEST_GROUP(morse);
  RUN_TEST_GROUP(gpio_assistant);
}

int main(int argc, const char **argv) {
  return UnityMain(argc, argv, run_all_tests);
}
