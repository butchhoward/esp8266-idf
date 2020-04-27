#include "unity_fixture.h"

static void run_all_tests(void) {
  RUN_TEST_GROUP(gpio_assistant);
  RUN_TEST_GROUP(relay);
  RUN_TEST_GROUP(button_server);
}

int main(int argc, const char **argv) {
  return UnityMain(argc, argv, run_all_tests);
}
