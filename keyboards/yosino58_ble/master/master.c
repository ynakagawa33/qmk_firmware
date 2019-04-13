#include QMK_KEYBOARD_H
#include "app_ble_func.h"

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

void matrix_init_user(void) {
  set_usb_enabled(true);
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
  // SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    #ifdef SSD1306_128X64
      iota_gfx_init(false);   // turns on the display
    #else
      iota_gfx_init(!has_usb());   // turns on the display
    #endif
  #endif
}