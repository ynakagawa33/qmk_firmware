#include QMK_KEYBOARD_H
#include "app_ble_func.h"

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
  
extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
extern int RGB_current_mode;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
  BLE_DIS,              /* Disable BLE HID sending              */
  BLE_EN,               /* Enable BLE HID sending               */
  USB_DIS,              /* Disable USB HID sending              */
  USB_EN,               /* Enable USB HID sending               */
  DELBNDS,              /* Delete all bonding                   */
  ADV_ID0,              /* Start advertising to PeerID 0        */
  ADV_ID1,              /* Start advertising to PeerID 1        */
  ADV_ID2,              /* Start advertising to PeerID 2        */
  ADV_ID3,              /* Start advertising to PeerID 3        */
  ADV_ID4,              /* Start advertising to PeerID 4        */
  BATT_LV,              /* Display battery level in milli volts */
  DEL_ID0,              /* Delete bonding of PeerID 0           */
  DEL_ID1,              /* Delete bonding of PeerID 1           */
  DEL_ID2,              /* Delete bonding of PeerID 2           */
  DEL_ID3,              /* Delete bonding of PeerID 3           */
  DEL_ID4,              /* Delete bonding of PeerID 4           */
  ENT_DFU,              /* Start bootloader                     */
  ENT_SLP,              /* Deep sleep mode                      */
  QWERTY,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST
};

enum user_macro {
  UM_EMHL,
  UM_KHKR
};

#define M_EMHL MACROTAP(UM_EMHL)
#define M_KHKR MACROTAP(UM_KHKR)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                                  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                                  |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |                                  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------.-------.  ,---------------|   N  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/   [   /       /   \       \   ]   \----------------------------------------'
 *                          | LAlt | LOWER| /-------/  Del  /     \  Bksp \-------\  | RAISE| RGUI |
 *                          |      |      |/ Space /       /       \       \ Enter \ |      |      |
 *                          `-----------------------------'         '------------------------------'
 */
 [_QWERTY] = LAYOUT( \
  KC_GRV,   KC_1, KC_2, KC_3, KC_4,    KC_5,                                       KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_TAB,   KC_Q, KC_W, KC_E, KC_R,    KC_T,                                       KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_EQL,  \
  KC_LSFT,  KC_A, KC_S, KC_D, KC_F,    KC_G,                                       KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
  KC_LCTRL, KC_Z, KC_X, KC_C, KC_V,    KC_B,   KC_LBRC, KC_DEL, KC_BSPC, KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, \
                              KC_LALT, M_EMHL, KC_SPC,                     KC_ENT, M_KHKR,  KC_RGUI\
  ),

/* LOWER
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |                                  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * | Tab  |   /  |   -  |   7  |   8  |   9  |                                  |PageUP| Home |   ↑  | End  | PSCR |  F12 |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LShift|   *  |   +  |   4  |   5  |   6  |                                  |PageDN|   ←  |   ↓  |   →  | Pause|      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LCTRL |   .  |   0  |   1  |   2  |   3  |-------.-------.  ,---------------|      |      |      |      |      |      |
 * `-----------------------------------------/       /       /   \       \   ]  \----------------------------------------'
 *                          |AD_WOL| LOWER| /-------/       /     \ Bksp  \-------\  | RAlt | RGUI |
 *                          |      |      |/DELBNDS/       /       \       \ Enter \ |      |      |
 *                          `-----------------------------'         '------------------------------'
 */
 [_LOWER] = LAYOUT( \
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,                                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
  _______, KC_PSLS, KC_PMNS, KC_P7,   KC_P8,    KC_P9,                                        KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_PSCR, KC_F12, \
  _______, KC_PAST, KC_PPLS, KC_P4,   KC_P5,    KC_P6,                                        KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PAUS, XXXXXXX, \
  _______, KC_PDOT, KC_P0,   KC_P1,   KC_P2,    KC_P3,   XXXXXXX,  _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                      AD_WO_L,  _______, DELBNDS,                    _______, KC_RALT, KC_RGUI\

  ),

/* RAISE
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |                                  |   ^  |   &  |   *  |   (  |   )  |  _   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      | MACL0| MACL1| MACL2|      |                                  | MWHU | MWHL | MSU  | MWHR |      |  +   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LShift|      | MBTNR| MBTNM| MBTNL|      |                                  | MWHD | MSL  | MSD  | MSR  |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |      |-------.-------.  ,---------------| Bksp | Enter|      |      |      |      |
 * `-----------------------------------------/   [   /       /   \       \       \----------------------------------------'
 *                          | LAlt |      | /-------/  Del  /     \       \-------\  | RAISE| RGUI |
 *                          |      |      |/ Space /       /       \       \ Insert\ |      |      |
 *                          `-----------------------------'         '------------------------------'
 */
 [_RAISE] = LAYOUT( \
  XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,   KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, \
  XXXXXXX, XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2,  XXXXXXX,                                     KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, XXXXXXX, KC_PLUS, \
  _______, XXXXXXX, KC_BTN2, KC_BTN3, KC_BTN1,  XXXXXXX,                                     KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, \
  _______, _______, _______, _______, _______,  XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, KC_BSPC, KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                      _______,  XXXXXXX, _______,                   KC_INS,  _______, _______ \
  ),

/*   ADJUST
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |RESET |AD_WOL|ADVID1|ADVID2|ADVID3|ADVID4|                                  | Mute | Vol+ | Play |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |ENTSLP|USBDIS|BLEDIS| PSCR | SLCK | Pause|                                  | Prev | Vol- | Next |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |ENTDFU|USB_EN|BLE_EN|Insert| Home |PageUP|                                  |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |BATTLV|DELID1|      |  Del | End  |PageDN|-------.-------.  ,---------------|      |RGB Re| MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |ADJUST| /-------/       /     \       \-------\  |      |      |
 *                          |      |      |/       /       /       \       \       \ |      |      |
 *                          `-----------------------------'         '------------------------------'
 */
 [_ADJUST] = LAYOUT( \
  RESET,   AD_WO_L, ADV_ID1, ADV_ID2, ADV_ID3, ADV_ID4,                                     KC_MUTE, KC_VOLU, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, \
  ENT_SLP, USB_DIS, BLE_DIS, KC_PSCR, KC_SLCK, KC_PAUS,                                     KC_MPRV, KC_VOLD, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, \
  ENT_DFU, USB_EN,  BLE_EN,  KC_INS,  KC_HOME, KC_PGUP,                                     XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  BATT_LV, DEL_ID1, XXXXXXX, KC_DEL,  KC_END,  KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGBRST,  RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, \
                                      XXXXXXX, _______, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX \
  ) 
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

//assign the right code to your layers for OLED display
#define L_QWERTY 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

// When add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    static char indctr[2][20][5]=
    {
      // white icon
      {
        {0x80,0x81,0x82,0x83,0},
        {0x88,0x89,0x8A,0x8B,0},
        {0x90,0x91,0x92,0x93,0},
        {0x98,0x99,0x9A,0x9B,0},
        {0x01,0x02,0x03,0x04,0},
        {0xA0,0xA1,0xA2,0xA3,0},
        {0xA8,0xA9,0xAA,0xAB,0},
        {0xB0,0xB1,0xB2,0xB3,0},
        {0xB8,0xB9,0xBA,0xBB,0},
        {0x21,0x22,0x23,0x24,0},
        {0xC0,0xC1,0xC2,0xC3,0},
        {0xC8,0xC9,0xCA,0xCB,0},
        {0xD0,0xD1,0xD2,0xD3,0},
        {0xD8,0xD9,0xDA,0xDB,0},
        {0x41,0x42,0x43,0x44,0},
        {0xE0,0xE1,0xE2,0xE3,0},
        {0xE8,0xE9,0xEA,0xEB,0},
        {0xF0,0xF1,0xF2,0xF3,0},
        {0xF8,0xF9,0xFA,0xFB,0},
        {0x61,0x62,0x63,0x64,0}
      },
      // Black icon
      {
        {0x84,0x85,0x86,0x87,0},
        {0x8C,0x8D,0x8E,0x8F,0},
        {0x94,0x95,0x96,0x97,0},
        {0x9C,0x9D,0x9E,0x9F,0},
        {0x05,0x06,0x07,0x08,0},
        {0xA4,0xA5,0xA6,0xA7,0},
        {0xAC,0xAD,0xAE,0xAF,0},
        {0xB4,0xB5,0xB6,0xB7,0},
        {0xBC,0xBD,0xBE,0xBF,0},
        {0x25,0x26,0x27,0x28,0},
        {0xC4,0xC5,0xC6,0xC7,0},
        {0xCC,0xCD,0xCE,0xCF,0},
        {0xD4,0xD5,0xD6,0xD7,0},
        {0xDC,0xDD,0xDE,0xDF,0},
        {0x45,0x46,0x47,0x48,0},
        {0xE4,0xE5,0xE6,0xE7,0},
        {0xEC,0xED,0xEE,0xEF,0},
        {0xF4,0xF5,0xF6,0xF7,0},
        {0xFC,0xFD,0xFE,0xFF,0},
        {0x65,0x66,0x67,0x68,0}
      }
    };

    int rown = 0;
    int rowc = 0;
    int rowl = 0;
    int rowr = 0;
    int rowa = 0;

    //Set Indicator icon
    if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) { rown = 1; } else { rown = 0; }
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { rowc = 1; } else { rowc = 0; }
    if (layer_state == L_LOWER) { rowl = 1; }
    if (layer_state == L_RAISE) { rowr = 1; }
    if (layer_state == L_ADJUST) { rowa = 1; }

    matrix_write(matrix, indctr[rowl]  [0]);
    matrix_write(matrix, indctr[rowr]  [1]);
    matrix_write(matrix, indctr[rowa]  [2]);
    matrix_write(matrix, indctr[rowc]  [3]);
    matrix_write(matrix, indctr[rown]  [4]);
    matrix_write_char(matrix, 0x13);
    matrix_write(matrix, indctr[rowl]  [5]);
    matrix_write(matrix, indctr[rowr]  [6]);
    matrix_write(matrix, indctr[rowa]  [7]);
    matrix_write(matrix, indctr[rowc]  [8]);
    matrix_write(matrix, indctr[rown]  [9]);
    matrix_write_char(matrix, 0x13);
    matrix_write(matrix, indctr[rowl]  [10]);
    matrix_write(matrix, indctr[rowr]  [11]);
    matrix_write(matrix, indctr[rowa]  [12]);
    matrix_write(matrix, indctr[rowc]  [13]);
    matrix_write(matrix, indctr[rown]  [14]);
    matrix_write_char(matrix, 0x13);
    matrix_write(matrix, indctr[rowl]  [15]);
    matrix_write(matrix, indctr[rowr]  [16]);
    matrix_write(matrix, indctr[rowa]  [17]);
    matrix_write(matrix, indctr[rowc]  [18]);
    matrix_write(matrix, indctr[rown]  [19]);

  }else{
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];

  switch (keycode) {
    case DELBNDS:
      if (record->event.pressed) {
        delete_bonds();
      }
      return false;
    case AD_WO_L:
      if (record->event.pressed) {
        restart_advertising_wo_whitelist();
      }
      return false;
    case USB_EN:
      if (record->event.pressed) {
        set_usb_enabled(true);
      }

      return false;
      break;
    case USB_DIS:
      if (record->event.pressed) {
        set_usb_enabled(false);
      }
      return false;
      break;
    case BLE_EN:
      if (record->event.pressed) {
        set_ble_enabled(true);
      }
      return false;
      break;
    case BLE_DIS:
      if (record->event.pressed) {
        set_ble_enabled(false);
      }
      return false;
      break;
    case ADV_ID0:
      if (record->event.pressed) {
        restart_advertising_id(0);
      }
      return false;
    case ADV_ID1:
      if (record->event.pressed) {
        restart_advertising_id(1);
      }
      return false;
    case ADV_ID2:
      if (record->event.pressed) {
        restart_advertising_id(2);
      }

      return false;
    case ADV_ID3:
      if (record->event.pressed) {
        restart_advertising_id(3);
      }
      return false;
    case ADV_ID4:
      if (record->event.pressed) {
        restart_advertising_id(4);
      }
      return false;
    case DEL_ID0:
      if (record->event.pressed) {
        delete_bond_id(0);
      }
      return false;
    case DEL_ID1:
      if (record->event.pressed) {
        delete_bond_id(1);
      }
      return false;
    case DEL_ID2:
      if (record->event.pressed) {
        delete_bond_id(2);
      }
      return false;
    case DEL_ID3:
     if (record->event.pressed) {
        delete_bond_id(3);
      }
      return false;
    case DEL_ID4:
      if (record->event.pressed) {
        delete_bond_id(4);
      }
      return false;
    case BATT_LV:
      if (record->event.pressed) {
        sprintf(str, "%4dmV", get_vcc());
        send_string(str);
      }
      return false;
    case ENT_DFU:
     if (record->event.pressed) {
        bootloader_jump();
      }
      return false;
    case ENT_SLP:
      if (!record->event.pressed) {
        sleep_mode_enter();
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
      case UM_EMHL:
        return MACRO_TAP_HOLD_LAYER(record, MACRO(TYPE(KC_MHEN), TYPE(KC_LANG2), END), _LOWER);
      case UM_KHKR:
        return MACRO_TAP_HOLD_LAYER(record, MACRO(TYPE(KC_HENK), TYPE(KC_LANG1), END), _RAISE);
    }

    return MACRO_NONE;
}