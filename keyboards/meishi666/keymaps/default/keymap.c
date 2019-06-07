/* Copyright 2019 %YOUR_NAME%
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
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
// Defines the keycodes used by our macros in process_record_user
//enum custom_keycodes {
//};

enum layer_number {
  _CTL = 0,
  _CURSOL,
  _MOUSE
};

#define CTL    TO(_CTL)
#define CURSOL TO(_CURSOL)
#define MOUSE  TO(_MOUSE)
#define CP     M(0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_CTL] = LAYOUT( \
    C(KC_Z), CURSOL,  C(KC_Y),      \
             C(KC_S),            \
    C(KC_C), RGB_MOD, C(KC_V) \
  ),

  [_CURSOL] = LAYOUT( \
    KC_ENT,  MOUSE,   KC_TAB,  \
             KC_UP,            \
    KC_LEFT, KC_DOWN, KC_RIGHT \
  ),

  [_MOUSE] = LAYOUT( \
    KC_MS_BTN1, CTL,        KC_MS_BTN2, \
                KC_MS_UP,               \
    KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT \
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
//float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
//float tone_plover[][2]     = SONG(PLOVER_SOUND);
//float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CTL:
      #ifdef AUDIO_ENABLE
        PLAY_SONG(tone_qwerty);
      #endif
      return true;
      break;
    case CURSOL:
      #ifdef AUDIO_ENABLE
        PLAY_SONG(tone_dvorak);
      #endif
      return true;
      break;
    case MOUSE:
      #ifdef AUDIO_ENABLE
        PLAY_SONG(music_scale);
      #endif
      return true;
      break;
    }
  return true;
}

void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
    startup_user();
  #endif

}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {

}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case 0: {
      if (record->event.pressed) {
        return MACRO( D(LCTL), T(C), U(LCTL), END  );
      } else {
        return MACRO( D(LCTL), T(V), U(LCTL), END  );
      }
      break;
    }
  }
  return MACRO_NONE;
};

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(50); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}
#endif
