#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

#include "midi.h"
#include "qmk_midi.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST,
  KC_00,
  RGB_RIPPLE
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                register_code(KC_LSFT);
                register_code(KC_SCLN);
                unregister_code(KC_9);
                register_code(KC_SCLN);
            case 1:
                return MACRO(T(CAPS), T(QUOT), T(CAPS));
        }
    }
    return MACRO_NONE;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  =   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Set  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |  /   |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctr  |  OS  | F12  | Alt  | Bksp |Space | Calc |Cursol|Enter | Del  |  Up  | Left | Down |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,          KC_3,    KC_4,           KC_5, \
    KC_TAB,  KC_Q,    KC_W,          KC_E,    KC_R,           KC_T, \
    ADJUST,  KC_A,    KC_S,          KC_D,    KC_F,           KC_G, \
    KC_LSFT, KC_Z,    KC_X,          KC_C,    KC_V,           KC_B, \
    KC_LCTL, KC_LGUI, LALT_T(KC_F5), KC_BSPC, RSFT_T(KC_SPC), TT(2) \
  ),
  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  | F10  |PrtSc |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | NmLk | ScLk | PgUp |Pouse |      |             |      |      |  Up  |      |      | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Ins  | Home | PgDw | End  |      |             |      | Left | Down |Right |      | F11  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | Undo | Cut  | Copy |Paste |      |      |      |      | OSL  | OSDw | OSR  |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   \
    _______, KC_NLCK, KC_SLCK, KC_PGUP, KC_PAUS, _______, \
    _______, KC_INS,  KC_HOME, KC_PGDN, KC_END,  KC_LT,   \
    _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_LPRN, \
    KC_LCTL, _______, _______, _______, _______, _______  \
  ),
  /* Raise
   * 
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |  1   |  2   |  3   |  4   |  5   |             |   6  |  7   |  8   |  9   |  +   |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |MusLft|MusDw |MusRgt|      |             |      |  4   |  5   |  6   |  ,   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |  1   |  2   |  3   |  =   |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |  0   |  0   |  .   |Enter |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
    KC_TILD, _______, _______,  _______,  _______, _______,\
    _______, KC_1,    KC_2,     KC_3,     KC_4,    KC_5,   \
    _______, KC_AT,   KC_HASH,  KC_DLR,   KC_PERC, KC_LCBR,\
    _______, KC_CIRC, KC_AMPR,  KC_ASTR,  KC_EXLM, KC_LBRC,\
    _______, _______, _______,  _______,  _______, _______ \
  ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  | F10  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |HueUp |      |      |             |      |SpdDw |BriUp |SpdUp |      | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |SadUp |HueDw |SadDw |      |             |      |ModeDw|BriDw |ModeUp|      | F11  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Ripple|      |      |      |      |      |Reset |LEDTgl|      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
    RESET,   _______, _______, _______, _______, _______,\
    RGBRST,  _______, _______, RGB_HUI, _______, _______,\
    RGB_MOD, _______, RGB_SAD, RGB_HUD, RGB_SAI, _______,\
    RGB_MOD, _______, _______, _______, _______, _______,\
    _______, RGBRST,  _______, _______, _______,  RGBRST \
  )
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}


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
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          rgblight_mode(14);
        }
      #endif
      break;
    case RGB_RIPPLE:
//      if (record->event.pressed) {
//        ripple = true;
//      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}


