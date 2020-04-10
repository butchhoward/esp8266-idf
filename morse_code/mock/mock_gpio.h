#ifndef MOCK_GPIO_H
#define MOCK_GPIO_H

#include <esp_err.h>

#ifndef BIT
#define BIT(x) (1 << (x))
#endif

#define GPIO_Pin_0              (BIT(0))  /* Pin 0 selected */
#define GPIO_Pin_1              (BIT(1))  /* Pin 1 selected */
#define GPIO_Pin_2              (BIT(2))  /* Pin 2 selected */
#define GPIO_Pin_3              (BIT(3))  /* Pin 3 selected */
#define GPIO_Pin_4              (BIT(4))  /* Pin 4 selected */
#define GPIO_Pin_5              (BIT(5))  /* Pin 5 selected */
#define GPIO_Pin_6              (BIT(6))  /* Pin 6 selected */
#define GPIO_Pin_7              (BIT(7))  /* Pin 7 selected */
#define GPIO_Pin_8              (BIT(8))  /* Pin 8 selected */
#define GPIO_Pin_9              (BIT(9))  /* Pin 9 selected */
#define GPIO_Pin_10             (BIT(10)) /* Pin 10 selected */
#define GPIO_Pin_11             (BIT(11)) /* Pin 11 selected */
#define GPIO_Pin_12             (BIT(12)) /* Pin 12 selected */
#define GPIO_Pin_13             (BIT(13)) /* Pin 13 selected */
#define GPIO_Pin_14             (BIT(14)) /* Pin 14 selected */
#define GPIO_Pin_15             (BIT(15)) /* Pin 15 selected */
#define GPIO_Pin_16             (BIT(16)) /* Pin 16 selected */
#define GPIO_Pin_All            (0x1FFFF)  /* All pins selected */

#define GPIO_MODE_DEF_DISABLE         (0)
#define GPIO_MODE_DEF_INPUT           (BIT(0))
#define GPIO_MODE_DEF_OUTPUT          (BIT(1))
#define GPIO_MODE_DEF_OD              (BIT(2))

typedef enum {
    GPIO_MODE_DISABLE = GPIO_MODE_DEF_DISABLE,                          /*!< GPIO mode : disable input and output */
    GPIO_MODE_INPUT = GPIO_MODE_DEF_INPUT,                              /*!< GPIO mode : input only */
    GPIO_MODE_OUTPUT = GPIO_MODE_DEF_OUTPUT,                            /*!< GPIO mode : output only mode */
    GPIO_MODE_OUTPUT_OD = ((GPIO_MODE_DEF_OUTPUT) | (GPIO_MODE_DEF_OD)), /*!< GPIO mode : output only with open-drain mode */
} gpio_mode_t;


#endif
