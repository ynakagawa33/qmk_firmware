/* Copyright 2020 yfuku
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  CK_KHKR = SAFE_RANGE,
  CK_EMHS
};

#define L_SPC LT(_LOWER, KC_SPC)
#define R_ENT LT(_RAISE, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        ALT_T(KC_TAB),  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    ALT_T(KC_EQL),
        SFT_T(KC_LBRC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  LCAG(KC_SPC),   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, SFT_T(KC_QUOT),
        CTL_T(KC_RBRC), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, CTL_T(KC_BSLS),
                            KC_LGUI,CK_EMHS,LT(_LOWER, KC_SPC),             LT(_ADJUST, KC_ENT),CK_KHKR,KC_BSPC,
                                            XXXXXXX, XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_LOWER] = LAYOUT(
        KC_LALT, XXXXXXX,  XXXXXXX,      LCAG(KC_UP),  XXXXXXX,      XXXXXXX,            KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_PSCR, XXXXXXX,
        KC_LSFT, XXXXXXX,  LCAG(KC_LEFT),LCAG(KC_DOWN),LCAG(KC_RGHT),XXXXXXX,  _______,  KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PAUS, KC_INS,
        KC_LCTL,LCAG(KC_1),LCAG(KC_2),   LCAG(KC_3),   LCAG(KC_4),   KC_BSPC,            XXXXXXX,LCAG(KC_M),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______,                           _______, _______, _______,
                                            _______, _______,                           _______, _______, _______
    ),
    [_RAISE] = LAYOUT(
        KC_LALT, XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX,          KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, XXXXXXX, XXXXXXX,
        KC_LSFT, XXXXXXX, KC_BTN2, KC_BTN3, KC_BTN1, XXXXXXX, _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
        KC_LCTL, _______, _______, _______, _______, KC_BSPC,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______,          _______, _______, _______,
                                            _______, _______,          _______, _______, _______
   ),
    [_ADJUST] = LAYOUT(
        ALT_T(KC_ESC), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        SFT_T(KC_GRV), KC_1,    KC_2,    KC_3,    KC_4,    KC_5, _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_LCTL, _______, _______, _______, _______, KC_BSPC,                XXXXXXX, XXXXXXX, XXXXXXX, KC_DOT,  XXXXXXX, KC_F12,
                                   _______, _______, _______,                _______, _______, _______,
                                            _______, _______,                _______, _______, _______
   )
};

static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;
static bool shift_pressed = false;
static uint16_t shift_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CK_KHKR:
      if (record->event.pressed) {
        raise_pressed = true;
        raise_pressed_time = record->event.time;
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);

        if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
          register_code(KC_LANG1);
          register_code(KC_HENK);
          unregister_code(KC_HENK);
          unregister_code(KC_LANG1);
        }

        raise_pressed = false;
      }
      return false;
      break;
    case CK_EMHS:
      if (record->event.pressed) {
        shift_pressed = true;
        shift_pressed_time = record->event.time;
        register_code(KC_LSFT);
      } else {
        unregister_code(KC_LSFT);
        
        if (shift_pressed && (TIMER_DIFF_16(record->event.time, shift_pressed_time) < TAPPING_TERM)) {
          register_code(KC_LANG2);
          register_code(KC_MHEN);
          unregister_code(KC_MHEN);
          unregister_code(KC_LANG2);
        }

        shift_pressed = false;
      }
      return false;
      break;
  }

  return true;
}
