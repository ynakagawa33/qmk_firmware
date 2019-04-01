#ifndef REV2_H
#define REV2_CONFIG_H

#include "../cardkeyboardmidi.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
//rgb led driver
#include "ws2812.h"
#endif

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif
#endif

//void promicro_bootloader_jmp(bool program);

#define LAYOUT( \
  L00, L01, L02, L03, L04, L05,\
  L10, L11, L12, L13, L14, L15,\
  L20, L21, L22, L23, L24, L25,\
  L30, L31, L32, L33, L34, L35,\
  L40, L41, L42, L43, L44, L45 \
  ) \
  { \
    { L00, L01, L02, L03, L04, L05 },\
    { L10, L11, L12, L13, L14, L15 },\
    { L20, L21, L22, L23, L24, L25 },\
    { L30, L31, L32, L33, L34, L35 },\
    { L40, L41, L42, L43, L44, L45 } \
  }

// Used to create a keymap using only KC_ prefixed keys

// Used to create a keymap using only KC_ prefixed keys
#define LAYOUT_kc( \
  L40, L41, L42, L43, L44, L45,\
  L00, L01, L02, L03, L04, L05,\
  L10, L11, L12, L13, L14, L15,\
  L20, L21, L22, L23, L24, L25,\
  L30, L31, L32, L33, L34, L35 \
  ) \
  LAYOUT( \
    KC_##L40, KC_##L41, KC_##L42, KC_##L43, KC_##L44, KC_##L45,\
    KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05,\
    KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15,\
    KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25,\
    KC_##L30, KC_##L31, KC_##L32, KC_##L33, KC_##L34, KC_##L35 \
  )

#endif
