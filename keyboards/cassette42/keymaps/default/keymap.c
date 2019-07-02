/* Copyright 2019 monksoffunk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
extern keymap_config_t keymap_config;
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
rgblight_config_t RGB_current_config;
#endif

#ifdef SSD1306OLED
  #include "ssd1306.h"
  #include <string.h>
  #include "print.h"
  #include "common/glcdfont.c"
  #include "sendchar.h"
  #include "common/oled_helper.h"
#endif

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  WRTROM,
};

enum layer_number {
    _AUDIO = 0,
    _HUE,
    _SAT,
    _VAL,
    _MODE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_AUDIO] = LAYOUT(
                 KC_MUTE, KC_ENT,
        LT(_HUE, KC_MPRV), LT(_SAT, KC_MPLY), LT(_VAL, KC_MNXT), LT(_MODE, KC_SPC)),
    [_HUE] = LAYOUT(
                 RGB_TOG, RGBRST,
        _______, _______, RGB_HUD, RGB_HUI),
    [_SAT] = LAYOUT(
                 _______, _______,
        _______, _______, RGB_SAD, RGB_SAI),
    [_VAL] = LAYOUT(
                 _______, _______,
        RGB_VAD, RGB_VAI, _______, RGB_VAI),
    [_MODE] = LAYOUT(
                 _______, WRTROM,
        RGB_RMOD, RGB_MOD, RGB_MOD, _______),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case WRTROM:
      #ifdef RGBLIGHT_ENABLE
      if (record->event.pressed) {
        eeconfig_update_rgblight(rgblight_config.raw);
      }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
      if (record->event.pressed) {
        eeconfig_update_rgblight_default();
        rgblight_enable();
        RGB_current_config.mode = rgblight_config.mode;
      }
      #endif
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
#ifdef SSD1306OLED
  iota_gfx_init(false);  // turns on the display
#endif
}

#define SSD1306OLED
// SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
  iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

// assign the right code to your layers for OLED display
#define L_AUDIO 0
#define L_HUE (1 << _HUE)
#define L_SAT (1 << _SAT)
#define L_VAL (1 << _VAL)
#define L_MODE (1 << _MODE)

void render_status(struct CharacterMatrix *matrix) {
  render_logo(matrix);
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf, sizeof(buf), "Undef-%ld", layer_state);
  switch (layer_state) {
     case L_AUDIO:
      matrix_write_P(matrix, PSTR("audio control\n"));
      break;
    case L_HUE:
      matrix_write_P(matrix, PSTR("rgb HUE control\n"));
      break;
    case L_SAT:
      matrix_write_P(matrix, PSTR("rgb SAT control\n"));
      break;
    case L_VAL:
      matrix_write_P(matrix, PSTR("rgb VAL control\n"));
      break;
    case L_MODE:
      matrix_write_P(matrix, PSTR("rgb MODE control\n"));
      break;
    default:
      break;
      matrix_write(matrix, buf);
  }
  UPDATE_LED_STATUS();
  RENDER_LED_STATUS(matrix);
  // Host Keyboard LED Status
  //char led[40];
  //snprintf(led, sizeof(led), "\n%s  %s  %s", (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ", (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) ? "CAPS" : "    ", (host_keyboard_leds() & (1 << USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  //matrix_write(matrix, led);
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

  #if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
  #endif

  bool is_master = true;

  matrix_clear(&matrix);
  if (is_master) {
    render_status(&matrix);
  } else {
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif

void led_set_user(uint8_t usb_led) {}

void encoder_update_user(uint8_t index, bool clockwise) {
  iota_gfx_force_dirty();
  if (index == 0) { /* left encoder */
    switch (layer_state) {
      case L_AUDIO:
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
      case L_HUE:
      #ifdef RGBLIGHT_ENABLE
        if (clockwise) {
          rgblight_increase_hue_noeeprom();
        } else {
          rgblight_decrease_hue_noeeprom();
          }
      #endif
        break;
      case L_SAT:
      #ifdef RGBLIGHT_ENABLE
        if (clockwise) {
          rgblight_increase_sat_noeeprom();
        } else {
          rgblight_decrease_sat_noeeprom();
          }
      #endif
        break;
      case L_VAL:
      #ifdef RGBLIGHT_ENABLE
        if (clockwise) {
          rgblight_increase_val_noeeprom();
        } else {
          rgblight_decrease_val_noeeprom();
          }
      #endif
        break;
      case L_MODE:
      #ifdef RGBLIGHT_ENABLE
        if (clockwise) {
          rgblight_step_noeeprom();
        } else {
          rgblight_step_reverse_noeeprom();
          }
      #endif
        break;
    }
  } else if (index == 1) { /* right encoder */
    if (!clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  }
}
