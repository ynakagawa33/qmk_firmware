/* Copyright 2019 SwanMatch
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

// Defines the keycodes used by our macros in process_record_user
//enum custom_keycodes {
//  QMKBEST = SAFE_RANGE,
//  QMKURL
//};

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  ADJUST,
  RGBRST,
  KC_00,
  ALTAB,
  CK_KHKR,
  CK_EMHS
};
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |                                  |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |   [  |   A  |   S  |   D  |   F  |   G  |                                  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |   ]  |   Z  |   X  |   C  |   V  |   B  |-------.-------.  ,---------------|   N  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/       /       /   \       \      \----------------------------------------'
 *                          |      | LGUI | / Eisu  / Space /     \ Enter \ Kana \  | Bksp |      |
 *                          |      |      |/ Shift / Lower /       \ Adjust\ Raise\ |      |      |
 *                          `-----------------------------'         '-----------------------------'
 */
 [_QWERTY] = LAYOUT( \
    ALT_T(KC_TAB),    KC_Q, KC_W, KC_E, KC_R, KC_T,                KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    ALT_T(KC_EQL),  \
    SFT_T(KC_LBRC),   KC_A, KC_S, KC_D, KC_F, KC_G,                KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, SFT_T(KC_QUOT), \
    CTL_T(KC_RBRC),  KC_Z, KC_X, KC_C, KC_V, KC_B,                KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, CTL_T(KC_BSLS), \
    XXXXXXX, KC_LGUI, CK_EMHS, LT(_LOWER, KC_SPC), LT(_ADJUST, KC_ENT), CK_KHKR, KC_BSPC, XXXXXXX \
  ),

/* LOWER
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * | LAlt |      |      | G(↑) |      |      |                                  |PageUP| Home |   ↑  | End  | PSCR |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LShift|      | G(←) | G(↓) | G(→) |      |                                  |PageDN|   ←  |   ↓  |   →  | Pause|Insert|
 * |------+------+------+------+------+------+                                  +------+------+------+------+------+------|
 * |LCtrl |      |      |      |      | Bksp |-------.-------.  ,---------------|      |      |      |      |      |      |
 * `-----------------------------------------/       /       /   \       \      \----------------------------------------'
 *                          |      | LGUI | / Eisu  / Space /     \ Enter \ Kana \  | Bksp |      |
 *                          |      |      |/ Shift / Lower /       \ Adjust\ Raise\ |      |      |
 *                          `-----------------------------'         '-----------------------------'
 */
 [_LOWER] = LAYOUT( \
  KC_LALT, XXXXXXX,XXXXXXX,      LGUI(KC_UP),  XXXXXXX,            XXXXXXX,                      KC_PGUP, KC_HOME,    KC_UP,   KC_END,  KC_PSCR, XXXXXXX,  \
  KC_LSFT, XXXXXXX,LGUI(KC_LEFT),LGUI(KC_DOWN),LGUI(KC_RGHT),     XXXXXXX,                      KC_PGDN, KC_LEFT,    KC_DOWN, KC_RGHT, KC_PAUS, KC_INS, \
  KC_LCTL, XXXXXXX,XXXXXXX,      XXXXXXX,      XXXXXXX,           KC_BSPC,                      XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, \
                                 XXXXXXX, _______, _______, _______,    _______, _______, _______, XXXXXXX \
  ),

/* RAISE
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |LAlt  |      | MACL0| MACL1| MACL2|      |                                  | MWHU | MWHL | MSU  | MWHR |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LShift|      | MBTNR| MBTNM| MBTNL|      |                                  | MWHD | MSL  | MSD  | MSR  |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LCtrl |   Z  |   X  |   C  |   V  | Bksp |-------.-------.  ,---------------|      |      |      |      |      |      |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      | LGUI | / Eisu  / Space /     \ Enter \ Kana  \  | Bksp |      |
 *                          |      |      |/ Shift / Lower /       \ Adjust\ Raise \ |      |      |
 *                          `-----------------------------'         '------------------------------'
 */
 [_RAISE] = LAYOUT( \
  KC_LALT, XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2,  XXXXXXX,                     KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, XXXXXXX, XXXXXXX, \
  KC_LSFT, XXXXXXX, KC_BTN2, KC_BTN3, KC_BTN1,  XXXXXXX,                     KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, \
  KC_LCTL, _______, _______, _______, _______,  KC_BSPC,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                             XXXXXXX, _______, _______, _______,    _______, _______, _______, XXXXXXX \
  ),

/*   ADJUST
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |                                  |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                                  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LCtrl |   Z  |   X  |   C  |   V  | Bksp |-------.-------.  ,---------------|RGB ON| MODE |      |   .  |      | F12  |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      | LGUI | / Eisu  / Space /     \ Enter \ Kana  \  | Bksp |      |
 *                          |      |      |/ Shift / Lower /       \ Adjust\ Raise \ |      |      |
 *                          `-----------------------------'         '------------------------------'
*/

 [_ADJUST] = LAYOUT( \
  ALT_T(KC_ESC),  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                 KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
  SFT_T(KC_GRV),  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
  KC_LCTL,        _______, _______, _______, _______, KC_BSPC,               RGB_TOG, RGB_MOD, XXXXXXX, KC_DOT,  XXXXXXX, KC_F12, \
                             XXXXXXX, _______, _______, _______,    _______, _______, _______, XXXXXXX \
  )
};


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

int RGB_current_mode;
bool alt_pressed = false;

static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;
static bool shift_pressed = false;
static uint16_t shift_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case KC_00:
      if (record->event.pressed) {
        SEND_STRING("00");
      }
      return false;
      break;
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
    case S(ALTAB):
    case ALTAB:
      if (record->event.pressed) {
        if (!alt_pressed) {
          alt_pressed = true;
          register_code(KC_LALT);
        }
        if (keycode == S(ALTAB)) {
          register_code(KC_LSFT);
        }
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
        if (keycode == S(ALTAB)) {
          unregister_code(KC_LSFT);
        }
      }
      return false;
      break;
    default:
      if (alt_pressed) {
        alt_pressed = false;
        unregister_code(KC_LALT);
        if (record->event.pressed) {
          return false;
        }
      }
    break;
  }
  return true;
}

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
