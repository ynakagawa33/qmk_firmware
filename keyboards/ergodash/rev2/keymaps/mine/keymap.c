#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, LCAG(KC_NO), SGUI(KC_NO), KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO, KC_NO, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQL, MO(2), KC_A, KC_S, KC_D, KC_F, KC_G, KC_NO, KC_NO, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_LANG2, KC_SPC, MO(1), KC_BSPC, KC_ENT, KC_LANG1, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT),
	[1] = LAYOUT(KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_EJCT, KC_NO, KC_MSTP, KC__VOLUP, KC_MPLY, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_HOME, KC_UP, KC_END, KC_PSCR, KC_F12, KC_NO, KC_NO, KC_MRWD, KC__VOLDOWN, KC_MFFD, KC_NO, KC_NO, KC_NO, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PAUS, KC_NO, KC_LSFT, KC_NO, KC_NO, KC__MUTE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_LANG2, KC_NO, KC_TRNS, KC_DEL, KC_NO, KC_LANG1, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT),
	[2] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ACL0, KC_ACL1, KC_ACL2, KC_NO, KC_NO, KC_NO, KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_BTN2, KC_BTN3, KC_BTN1, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, KC_LSFT, KC_NO, KC_WBAK, KC_WHOM, KC_WFWD, KC_NO, KC_NO, KC_RALT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_LANG2, KC_SPC, KC_NO, KC_RSFT, KC_RCTL, KC_LANG1, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT)
};
