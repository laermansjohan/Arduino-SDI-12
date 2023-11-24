/**
 * @file SDI12_boards.cpp
 * @copyright (c) 2013-2020 Stroud Water Research Center (SWRC)
 *                          and the EnviroDIY Development Team
 * @author Sara Geleskie Damiano (sdamiano@stroudcenter.org)
 *
 * @brief This file implements the setting and unsetting of the proper prescalers for
 * the timers for SDI-12.
 *
 */

/* ======================== Arduino SDI-12 =================================
An Arduino library for SDI-12 communication with a wide variety of environmental
sensors. This library provides a general software solution, without requiring
   ======================== Arduino SDI-12 =================================*/

#include "SDI12_boards.h"

SDI12Timer::SDI12Timer() {}

// Most 'standard' AVR boards
//
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || \
  defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) ||  \
  defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__) ||   \
  defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega1284__)

/**
 * @brief The value of timer control register 2A prior to being set for SDI-12.
 */
static uint8_t preSDI12_TCCR2A;
/**
 * @brief The value of timer control register 2B prior to being set for SDI-12.
 */
static uint8_t preSDI12_TCCR2B;

#if F_CPU == 16000000L

void SDI12Timer::configSDI12TimerPrescale(void) {
  preSDI12_TCCR2A = TCCR2A;
  preSDI12_TCCR2B = TCCR2B;
  TCCR2A = 0x00;  // TCCR2A = 0x00 = "normal" operation - Normal port operation, OC2A &
                  // OC2B disconnected
  TCCR2B = 0x07;  // TCCR2B = 0x07 = 0b00000111 - Clock Select bits 22, 21, & 20 on -
                  // prescaler set to CK/1024
}
void SDI12Timer::resetSDI12TimerPrescale(void) {
  TCCR2A = preSDI12_TCCR2A;
  TCCR2B = preSDI12_TCCR2B;
}

#elif F_CPU == 12000000L

void SDI12Timer::configSDI12TimerPrescale(void) {
  preSDI12_TCCR2A = TCCR2A;
  preSDI12_TCCR2B = TCCR2B;
  TCCR2A = 0x00;  // TCCR2A = 0x00 = "normal" operation - Normal port operation, OC2A &
                  // OC2B disconnected
  TCCR2B = 0x07;  // TCCR2B = 0x07 = 0b00000111 - Clock Select bits 22, 21, & 20 on -
                  // prescaler set to CK/1024
}
void SDI12Timer::resetSDI12TimerPrescale(void) {
  TCCR2A = preSDI12_TCCR2A;
  TCCR2B = preSDI12_TCCR2B;
}

#elif F_CPU == 8000000L

void SDI12Timer::configSDI12TimerPrescale(void) {
  preSDI12_TCCR2A = TCCR2A;
  preSDI12_TCCR2B = TCCR2B;
  TCCR2A = 0x00;  // TCCR2A = 0x00 = "normal" operation - Normal port operation, OC2A &
                  // OC2B disconnected
  TCCR2B = 0x06;  // TCCR2B = 0x06 = 0b00000110 - Clock Select bits 22 & 20 on -
                  // prescaler set to CK/256
}
void SDI12Timer::resetSDI12TimerPrescale(void) {
  TCCR2A = preSDI12_TCCR2A;
  TCCR2B = preSDI12_TCCR2B;
}

// void SDI12Timer::configSDI12TimerPrescale(void)
// {
//     preSDI12_TCCR2A = TCCR2A;
//     preSDI12_TCCR2B = TCCR2B;
//     TCCR2A = 0x00;  // TCCR2A = 0x00 = "normal" operation - Normal port operation,
//     OC2A & OC2B disconnected TCCR2B = 0x07;  // TCCR2B = 0x07 = 0b00000111 - Clock
//     Select bits 22, 21, & 20 on - prescaler set to CK/1024
// }
// void SDI12Timer::resetSDI12TimerPrescale(void)
// {
//     TCCR2A = preSDI12_TCCR2A;
//     TCCR2B = preSDI12_TCCR2B;
// }
#endif


// ATtiny boards (ie, adafruit trinket)
//
#elif defined(__AVR_ATtiny25__) | defined(__AVR_ATtiny45__) | defined(__AVR_ATtiny85__)

/**
 * @brief The value of timer control register 1A prior to being set for SDI-12.
 */
static uint8_t preSDI12_TCCR1A;

#if F_CPU == 16000000L

void SDI12Timer::configSDI12TimerPrescale(void) {
  preSDI12_TCCR1A = TCCR1;
  TCCR1 = 0b00001011;  // Set the prescaler to 1024
}
void SDI12Timer::resetSDI12TimerPrescale(void) {
  TCCR1 = preSDI12_TCCR1A;
}


#elif F_CPU == 8000000L

void SDI12Timer::configSDI12TimerPrescale(void) {
  preSDI12_TCCR1A = TCCR1;
  TCCR1 = 0b00001010;  // Set the prescaler to 512
}
void SDI12Timer::resetSDI12TimerPrescale(void) {
  TCCR1 = preSDI12_TCCR1A;
}
#endif


// Arduino Leonardo & Yun and other 32U4 boards
//
#elif defined(ARDUINO_AVR_YUN) || defined(ARDUINO_AVR_LEONARDO) || \
  defined(__AVR_ATmega32U4__)

/**
 * @brief The value of timer control register 4A prior to being set for SDI-12.
 */
static uint8_t preSDI12_TCCR4A;
/**
 * @brief The value of timer control register 4B prior to being set for SDI-12.
 */
static uint8_t preSDI12_TCCR4B;
/**
 * @brief The value of timer control register 4C prior to being set for SDI-12.
 */
static uint8_t preSDI12_TCCR4C;
/**
 * @brief The value of timer control register 4D prior to being set for SDI-12.
 */
static uint8_t preSDI12_TCCR4D;
/**
 * @brief The value of timer control register 4E prior to being set for SDI-12.
 */
static uint8_t preSDI12_TCCR4E;

#if F_CPU == 16000000L

void SDI12Timer::configSDI12TimerPrescale(void) {
  preSDI12_TCCR4A = TCCR4A;
  preSDI12_TCCR4B = TCCR4B;
  preSDI12_TCCR4C = TCCR4C;
  preSDI12_TCCR4D = TCCR4D;
  preSDI12_TCCR4E = TCCR4E;
  TCCR4A = 0x00;  // TCCR4A = 0x00 = "normal" operation - Normal port operation, OC4A &
                  // OC4B disconnected
  TCCR4B = 0x0B;  // TCCR4B = 0x0B = 0b00001011 - Clock Select bits 43, 41, & 40 on -
                  // prescaler set to CK/1024
  TCCR4C = 0x00;  // TCCR4C = 0x00 = "normal" operation - Normal port operation, OC4D0
                  // disconnected
  TCCR4D = 0x00;  // TCCR4D = 0x00 = No fault protection
  TCCR4E = 0x00;  // TCCR4E = 0x00 = No register locks or overrides
}
void SDI12Timer::resetSDI12TimerPrescale(void) {
  TCCR4A = preSDI12_TCCR4A;
  TCCR4B = preSDI12_TCCR4B;
  TCCR4C = preSDI12_TCCR4C;
  TCCR4D = preSDI12_TCCR4D;
  TCCR4E = preSDI12_TCCR4E;
}

#elif F_CPU == 8000000L
void SDI12Timer::configSDI12TimerPrescale(void) {
  preSDI12_TCCR4A = TCCR4A;
  preSDI12_TCCR4B = TCCR4B;
  preSDI12_TCCR4C = TCCR4C;
  preSDI12_TCCR4D = TCCR4D;
  preSDI12_TCCR4E = TCCR4E;
  TCCR4A = 0x00;  // TCCR4A = 0x00 = "normal" operation - Normal port operation, OC4A &
                  // OC4B disconnected
  TCCR4B = 0x0A;  // TCCR4B = 0x0A = 0b00001010 - Clock Select bits 43 & 41 on -
                  // prescaler set to CK/512
  TCCR4C = 0x00;  // TCCR4C = 0x00 = "normal" operation - Normal port operation, OC4D0
                  // disconnected
  TCCR4D = 0x00;  // TCCR4D = 0x00 = No fault protection
  TCCR4E = 0x00;  // TCCR4E = 0x00 = No register locks or overrides
}
void SDI12Timer::resetSDI12TimerPrescale(void) {
  TCCR4A = preSDI12_TCCR4A;
  TCCR4B = preSDI12_TCCR4B;
  TCCR4C = preSDI12_TCCR4C;
  TCCR4D = preSDI12_TCCR4D;
  TCCR4E = preSDI12_TCCR4E;
}
#endif


// Arduino Zero other SAMD21 boards
//
#elif defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_ARCH_SAMD) || \
  defined(__SAMD21G18A__) || defined(__SAMD21J18A__) || defined(__SAMD21E18A__)

void SDI12Timer::configSDI12TimerPrescale(void) {
  // Select generic clock generator 5 (Arduino core uses 0, 1, and 3.  RTCZero uses 2)
  // Many examples use clock generator 4.. consider yourself warned!
  // I would use a higher clock number, but some of the cores don't include them for
  // some reason
  REG_GCLK_GENDIV = GCLK_GENDIV_ID(5) |  // Select Generic Clock Generator 5
    GCLK_GENDIV_DIV(3);                  // Divide the clock source by divisor 3
  while (GCLK->STATUS.bit.SYNCBUSY) {}   // Wait for synchronization


  // Write the generic clock generator 2 configuration
  REG_GCLK_GENCTRL = (GCLK_GENCTRL_ID(5) |        // Select GCLK5
                      GCLK_GENCTRL_SRC_DFLL48M |  // Select the 48MHz clock source
                      GCLK_GENCTRL_IDC |     // Set the duty cycle to 50/50 HIGH/LOW
                      GCLK_GENCTRL_GENEN) &  // Enable the generic clock clontrol
    ~GCLK_GENCTRL_RUNSTDBY &                 // Do NOT run in stand by
    ~GCLK_GENCTRL_DIVSEL;  // Divide clock source by GENDIV.DIV: 48MHz/3=16MHz
                           // ^^ & ~ for DIVSEL because not not divided
  while (GCLK->STATUS.bit.SYNCBUSY) {}  // Wait for synchronization

  // Feed GCLK1 to TC4 and TC5
  // TC6 and TC7 are not available on all boards
  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_GEN_GCLK5 |  // Select Generic Clock Generator 5
    GCLK_CLKCTRL_CLKEN |                       // Enable the generic clock generator
    GCLK_CLKCTRL_ID_TC4_TC5;  // Feed the Generic Clock Generator 1 to TC4 and TC5
  while (GCLK->STATUS.bit.SYNCBUSY) {}  // Wait for synchronization

  REG_TC4_CTRLA |=
    TC_CTRLA_PRESCALER_DIV1024 |  // Set prescaler to 1024, 16MHz/1024 = 15.625kHz
    TC_CTRLA_WAVEGEN_NFRQ |       // Put the timer TC4 into normal frequency (NFRQ) mode
    TC_CTRLA_MODE_COUNT8 |        // Put the timer TC4 into 8-bit mode
    TC_CTRLA_ENABLE;              // Enable TC4
  while (TC4->COUNT16.STATUS.bit.SYNCBUSY) {}  // Wait for synchronization
}

// NOT resetting the SAMD timer settings
void SDI12Timer::resetSDI12TimerPrescale(void) {
  // Disable TCx
  TC4->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
  while (TC4->COUNT16.STATUS.bit.SYNCBUSY) {}

  // Reset TCx
  TC4->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
  while (TC4->COUNT16.STATUS.bit.SYNCBUSY) {}
  while (TC4->COUNT16.CTRLA.bit.SWRST) {}

  // Disable generic clock generator
  REG_GCLK_GENCTRL = GCLK_GENCTRL_ID(5) &  // Select GCLK2
    ~GCLK_GENCTRL_GENEN;                   // Disable the generic clock control
  while (GCLK->STATUS.bit.SYNCBUSY) {}     // Wait for synchronization
}

// Espressif ESP32/ESP8266 boards
//
#elif defined(ESP32) || defined(ESP8266)

void         SDI12Timer::configSDI12TimerPrescale(void) {}
void         SDI12Timer::resetSDI12TimerPrescale(void) {}
sdi12timer_t SDI12Timer::SDI12TimerRead(void) {
  // Its a one microsecond clock but we want 64uS ticks so divide by 64 i.e. right shift
  // 6
  return ((sdi12timer_t)(micros() >> 6));
}
// Unknown board
#else
#error "Please define your board timer and pins"
#endif
