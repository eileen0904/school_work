// keypad input 4 digits and display on 7-segment LEDs

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "MCU_init.h"
#include "NUC100Series.h"
#include "SYS_init.h"
#include "Scankey.h"
#include "Seven_Segment.h"

// display an integer on four 7-segment LEDs
void Display_7seg(uint16_t value) {
    uint8_t digit;
    digit = value / 1000;
    CloseSevenSegment();
    ShowSevenSegment(3, digit);
    CLK_SysTickDelay(5000);
    value = value - digit * 1000;
    digit = value / 100;
    CloseSevenSegment();
    ShowSevenSegment(2, digit);
    CLK_SysTickDelay(5000);
    value = value - digit * 100;
    digit = value / 10;
    CloseSevenSegment();
    ShowSevenSegment(1, digit);
    CLK_SysTickDelay(5000);
    value = value - digit * 10;
    digit = value;
    CloseSevenSegment();
    ShowSevenSegment(0, digit);
    CLK_SysTickDelay(5000);
}

void displayRound(uint16_t round) {
    uint8_t digit;
    uint16_t tmp = round;
    digit = round / 1000;
    CloseSevenSegment();

    if (digit != 0)
        ShowSevenSegment(3, digit);
    CLK_SysTickDelay(500000);
    round = round - digit * 1000;
    digit = round / 100;
    CloseSevenSegment();

    if (digit != 0)
        ShowSevenSegment(2, digit);
    CLK_SysTickDelay(500000);
    round = round - digit * 100;
    digit = round / 10;
    CloseSevenSegment();

    if (digit != 0)
        ShowSevenSegment(1, digit);
    CLK_SysTickDelay(500000);
    round = round - digit * 10;
    digit = round;
    CloseSevenSegment();

    if (digit != 0)
        ShowSevenSegment(0, digit);
    CLK_SysTickDelay(500000);

    displayRound((tmp * 10) % 10000);
}

void Buzz(uint16_t number) {
    int i;
    for (i = 0; i < number; i++) {
        PB11 = 0;  // PB11 = 0 to turn on Buzzer
        CLK_SysTickDelay(100000);  // Delay
        PB11 = 1;  // PB11 = 1 to turn off Buzzer
        CLK_SysTickDelay(100000);  // Delay
    }
}

int main(void) {
    int passcode;
    int tmppass = 1314;
    int i = 3;
    int j = 0;
    int k = 0;
    int s = 0;
    int p = 0;
    int code, tmpcode, number[10];
    int round = 0;

    for (j = 0; j < 50; j++)
        Display_7seg(s);

    memset(number, 0, sizeof(number));
    SYS_Init();
    OpenSevenSegment();  // for 7-segment
    OpenKeyPad();  // for keypad
    GPIO_SetMode(PB, BIT11, GPIO_MODE_OUTPUT);  // for Buzzer
    GPIO_SetMode(PC, BIT12, GPIO_MODE_OUTPUT);  // for Buzzer

    while (1) {
        k = ScanKey();
        if (k != 0) {
            s = s * 10 + k;
            printf("key=%d i=%d s=%d\n", k, i, s);
            i--;
            if (i < 0) {
                i = 3;
                code = s;
                s = 0;
                for (j = 0; j < 50; j++)
                    Display_7seg(code);
                tmppass = code;
                Buzz(1);
                break;
            }
        }
        for (j = 0; j < 10; j++)
            Display_7seg(s);
    }

    while (1) {
        k = ScanKey();
        if (k != 0) {
            s = s * 10 + k;
            printf("key=%d i=%d s=%d\n", k, i, s);
            i--;
            if (i < 0) {
                i = 3;
                tmpcode = s;
                s = 0;
                round++;
                if (tmpcode == tmppass) {
                    Buzz(4);
                    PC12 = 0;
                    PC13 = 0;
                    PC14 = 0;
                    PC15 = 0;
                    CLK_SysTickDelay(100000);
                    PC12 = 1;
                    PC13 = 1;
                    PC14 = 1;
                    PC15 = 1;
                    displayRound(round);
                    break;
                }
                else {
                    int count = 0, B = 0;
                    code = tmpcode;
                    passcode = tmppass;
                    for (p = 0; p < 4; p++) {
                        number[passcode % 10]++;
                        if (code % 10 == passcode % 10) {
                            count++;
                            number[passcode % 10]--;
                        }
                        code = code / 10;
                        passcode = passcode / 10;
                    }
                    code = tmpcode;
                    passcode = tmppass;
                    for (p = 0; p < 4; p++) {
                        if (number[code % 10]) {
                            B++;
                            number[code % 10]--;
                        }
                        code = code / 10;
                        passcode = passcode / 10;
                    }
                    switch (count) {
                        case 1:
                            Buzz(1);
                            break;
                        case 2:
                            Buzz(2);
                            break;
                        case 3:
                            Buzz(3);
                            break;
                    }
                    switch (B) {
                        case 1:
                            PC12 = 0;
                            break;
                        case 2:
                            PC12 = 0;
                            PC13 = 0;
                            break;
                        case 3:
                            PC12 = 0;
                            PC13 = 0;
                            PC14 = 0;
                            break;
                        case 4:
                            PC12 = 0;
                            PC13 = 0;
                            PC14 = 0;
                            PC15 = 0;
                            break;
                    }
                }
                for (j = 0; j < 50; j++)
                    Display_7seg(tmpcode);
            }
        }
        for (j = 0; j < 10; j++)
            Display_7seg(s);
        PC12 = 1;
        PC13 = 1;
        PC14 = 1;
        PC15 = 1;
        memset(number, 0, sizeof(number));
    }
}