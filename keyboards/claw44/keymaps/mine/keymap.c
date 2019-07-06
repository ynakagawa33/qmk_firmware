#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  CK_KHKR,
  CK_EMHS,
  CK_SPCL,
  CK_ENTA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
  //,---------------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+---------------.
     ALT_T(KC_TAB),  KC_Q,    KC_W,     KC_E,    KC_R,     KC_T,        KC_Y,    KC_U,     KC_I,    KC_O,     KC_P,    ALT_T(KC_EQL), 
  //|---------------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+---------------|
     SFT_T(KC_LBRC), KC_A,    KC_S,     KC_D,    KC_F,     KC_G,        KC_H,    KC_J,     KC_K,    KC_L,     KC_SCLN, SFT_T(KC_QUOT),
  //|---------------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+---------------|
     CTL_T(KC_RBRC), KC_Z,    KC_X,     KC_C,    KC_V,     KC_B,        KC_N,    KC_M,     KC_COMM, KC_DOT,   KC_SLSH, CTL_T(KC_BSLS),
  //`---------------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+---------------'
                      XXXXXXX, KC_LGUI, CK_EMHS, LT(_LOWER, KC_SPC),  LT(_ADJUST, KC_ENT), CK_KHKR, KC_BSPC,  XXXXXXX
  //                `--------+---------+--------+------------------'   `------------------+---------+--------+--------'
  ),

  [_LOWER] = LAYOUT( \
  //,--------+-----------+--------------+--------------+--------------+---------.   ,--------+-----------+--------+--------+--------+--------.
     KC_LALT, XXXXXXX,    XXXXXXX,       LCAG(KC_UP),   XXXXXXX,       XXXXXXX,      KC_PGUP, KC_HOME,    KC_UP,   KC_END,  KC_PSCR, XXXXXXX,
  //|--------+-----------+--------------+--------------+--------------+---------|   |--------+-----------+--------+--------+--------+--------|
     KC_LSFT, XXXXXXX,    LCAG(KC_LEFT), LCAG(KC_DOWN), LCAG(KC_RGHT), XXXXXXX,      KC_PGDN, KC_LEFT,    KC_DOWN, KC_RGHT, KC_PAUS, KC_INS,
  //|--------+-----------+--------------+--------------+--------------+---------|   |--------+-----------+--------+--------+--------+--------|
     KC_LCTL, LCAG(KC_1), LCAG(KC_2),    LCAG(KC_3),    LCAG(KC_4),    KC_BSPC,      XXXXXXX, LCAG(KC_M), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //`--------+-----------+--------------+--------------+--------------+---------/   \--------+-----------+--------+--------+--------+--------'
                          _______,       _______,        _______,      _______,      _______, _______,    _______, _______
  //                     `--------------+--------------+--------------+--------'    `--------+-----------+--------+--------'
  ),

  [_RAISE] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     KC_LALT, XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX,     KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_LSFT, XXXXXXX, KC_BTN2, KC_BTN3, KC_BTN1, XXXXXXX,     KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_LCTL, _______, _______, _______, _______, KC_BSPC,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       _______, _______, _______, _______,     _______, _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_ADJUST] = LAYOUT( \
  //,--------------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     ALT_T(KC_ESC), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //|--------------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     SFT_T(KC_GRV), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  //|--------------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_LCTL,       _______, _______, _______, _______, KC_BSPC,     XXXXXXX, XXXXXXX, XXXXXXX, KC_DOT,  XXXXXXX, KC_F12,
  //`--------------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                             _______, _______, _______, _______,     _______, _______, _______, _______
  //                        `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),
};

void matrix_init_user(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
  iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;
static bool shift_pressed = false;
static uint16_t shift_pressed_time = 0;
static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool adjust_pressed = false;
static uint16_t adjust_pressed_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
   case ADJUST:
     if (record->event.pressed) {
       layer_on(_ADJUST);
     } else {
       layer_off(_ADJUST);
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
    case CK_SPCL:
    if (record->event.pressed) {
      lower_pressed = true;
      lower_pressed_time = record->event.time;
      layer_on(_LOWER);
    } else {
      layer_off(_LOWER);

      if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
        register_code(KC_SPC);
        unregister_code(KC_SPC);
      }

      lower_pressed = false;
    }
    return false;
    break;
    case CK_ENTA:
    if (record->event.pressed) {
      adjust_pressed = true;
      adjust_pressed_time = record->event.time;
      layer_on(_ADJUST);
    } else {
      layer_off(_ADJUST);

      if (adjust_pressed && (TIMER_DIFF_16(record->event.time, adjust_pressed_time) < TAPPING_TERM)) {
        register_code(KC_ENT);
        unregister_code(KC_ENT);
      }

      adjust_pressed = false;
    }
    return false;
    break;
  }
  return true;
}
