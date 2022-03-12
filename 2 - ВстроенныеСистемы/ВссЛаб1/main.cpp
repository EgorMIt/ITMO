#include "hal.h"

const int DELAY = 500;

void readStates(unsigned int swNum[], GPIO_PinState swStates[]) {
    for (int i = 0; i < 4; ++i) {
        swStates[i] = HAL_GPIO_ReadPin(GPIOE, swNum[i]);
    }
}

bool checkN(GPIO_PinState swStates[]) {
    return swStates[0] == GPIO_PIN_RESET &&
           swStates[1] == GPIO_PIN_SET &&
           swStates[2] == GPIO_PIN_RESET &&
           swStates[3] == GPIO_PIN_RESET;
}

void waitForButton(GPIO_PinState *swStates, unsigned int *swNum) {
    if ((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_RESET)) {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);

        GPIO_PinState status = GPIO_PIN_RESET;

        while (status == GPIO_PIN_RESET) {
            status = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
        }
        HAL_Delay(200);

        while (status == GPIO_PIN_SET && checkN(swStates)) {
            status = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
            readStates(swNum, swStates);
        }
        HAL_Delay(200);

        while (status == GPIO_PIN_RESET) {
            status = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
        }

        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
    }
}

void offAll(unsigned int ledsNum[]) {
    for (int i = 0; i < 8; ++i) {
        HAL_GPIO_WritePin(GPIOD, ledsNum[i], GPIO_PIN_RESET);
    }
}

void animate(unsigned int ledsNum[], unsigned int swNum[], GPIO_PinState swStates[]) {
    offAll(ledsNum);

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);

    for (int i = 1; checkN(swStates); i++) {
        waitForButton(swStates, swNum);
        if (i > 12)
            i = 0;

        offAll(ledsNum);

        if (i <= 6) {
            HAL_GPIO_WritePin(GPIOD, ledsNum[i - 1], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, ledsNum[i], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, ledsNum[i + 1], GPIO_PIN_SET);
        } else if (i >= 7 && i <= 10) {
            HAL_GPIO_WritePin(GPIOD, ledsNum[11 - i], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, ledsNum[11 - i + 1], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, ledsNum[11 - i + 1], GPIO_PIN_SET);
        }

        if (i < 7) {
            if (i == 0) {
                HAL_GPIO_WritePin(GPIOD, ledsNum[5], GPIO_PIN_RESET);
            } else {
                HAL_GPIO_WritePin(GPIOD, ledsNum[8 - i], GPIO_PIN_RESET);
            }
            HAL_GPIO_WritePin(GPIOD, ledsNum[7 - i], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, ledsNum[6 - i], GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOD, ledsNum[i - 7], GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, ledsNum[i - 6], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, ledsNum[i - 5], GPIO_PIN_SET);
        }
        HAL_Delay(DELAY);

        readStates(swNum, swStates);
    }
    offAll(ledsNum);

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
}

int umain() {

    unsigned int ledsNum[] = {GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6,
                              GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_11, GPIO_PIN_12};

    unsigned int swNum[] = {GPIO_PIN_4, GPIO_PIN_8, GPIO_PIN_10, GPIO_PIN_12};

    GPIO_PinState swStates[] = {GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET};

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);

    while (true) {
        readStates(swNum, swStates);

        if (checkN(swStates)) {
            animate(ledsNum, swNum, swStates);
        } else {
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
            for (int i = 0; i < 4; ++i) {
                HAL_GPIO_WritePin(GPIOD, ledsNum[i], swStates[i]);
            }
        }
    }

    return 0;
}
