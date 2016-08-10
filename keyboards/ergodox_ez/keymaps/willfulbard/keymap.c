// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "timer.h"

LEADER_EXTERNS();


// Layer Definitions
#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define NUMS 3 // number keys

// Macro Definitions
#define MAC_SHIFT M(0) // default 
#define MAC_VIMSV M(1) // Vim Save

// For full keymap see 
// https://docs.google.com/spreadsheets/d/1D1bO-_haUM3atuROX6FVWUTrJUPxv3q4HyD5qT-1bIQ/edit#gid=1391997722
//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,    KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_GRV,
        KC_TAB,    KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_EQUAL,
        KC_LCTL,   KC_A,    KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,   KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_LEAD,
          LCTL(KC_LEFT), LCTL(KC_RIGHT), KC_LCTL, KC_LALT, KC_LGUI,
                                       ALT_T(KC_APP), KC_LGUI,
                                                      KC_HOME,
                                  MO(SYMB), MO(MDIA), MO(NUMS),
        // right hand
        KC_BSPC,  KC_6,  KC_7,  KC_8,    KC_9,   KC_0,       KC_BSPC,
        KC_ENTER, KC_Y,  KC_U,  KC_I,    KC_O,   KC_P,       KC_BSLS,
                  KC_H,  KC_J,  KC_K,    KC_L,   KC_SCLN,    KC_QUOTE,
        KC_ENTER, KC_N,  KC_M,  KC_COMM, KC_DOT, KC_SLSH,    KC_RSFT,
          KC_LEAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                       MAC_VIMSV, CTL_T(KC_ESC),
                       LGUI(KC_TAB),
                       S(KC_SCLN), CTL_T(KC_ENTER), KC_SPACE 
),
[SYMB] = KEYMAP( // SYMBOLS
       // left hand
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_TRNS,
       KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, S(KC_SLSH),  KC_TRNS,
       KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, S(KC_SCLN),
       KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, S(KC_MINUS), KC_TRNS,
         KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
       KC_TRNS, KC_EXLM,  KC_AMPR, KC_PLUS, KC_ASTR, KC_TRNS, KC_TRNS,
                KC_EQUAL, KC_PIPE, KC_MINS, KC_SLSH, KC_TRNS, S(KC_QUOTE),
       KC_TRNS, KC_TILD,  KC_TRNS, KC_LABK, KC_RABK, KC_TRNS, KC_TRNS,
         KC_LEAD, LCTL(LSFT(KC_TAB)), LCTL(KC_TAB), LCTL(KC_LEFT), LCTL(KC_RIGHT),
                         KC_TRNS, KC_TRNS,
                         KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_ENTER
),
[MDIA] = KEYMAP( // MEDIA AND MOUSE
    // left hand
       KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_R, KC_MS_D, KC_MS_U, KC_MS_L,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS,
       KC_TRNS,  LCTL(S(KC_TAB)),KC_PGDN, KC_PGUP, LCTL(KC_TAB),  KC_TRNS, KC_TRNS,
                 KC_LEFT,        KC_DOWN, KC_UP,   KC_RIGHT,       KC_TRNS, KC_MPLY,
       KC_TRNS,  LCTL(KC_LEFT), KC_END,  KC_HOME, LCTL(KC_RIGHT), KC_TRNS, KC_TRNS,
         KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS,
                          KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS
),
[NUMS] = KEYMAP( // NUMBERS
    // left hand
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
    KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, S(KC_SLSH), KC_TRNS,
    KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, S(KC_SCLN),
    KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, S(KC_MINUS), KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LSHIFT,
                        KC_TRNS,KC_TRNS,
                                KC_TRNS,
                KC_TRNS,KC_TRNS,KC_TRNS,
    // right hand
    KC_TRNS, KC_TRNS, KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_7,    KC_8,    KC_9,    KC_PPLS,  KC_TRNS,
             KC_TRNS, KC_4,    KC_5,    KC_6,    KC_PPLS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_1,    KC_2,    KC_3,    KC_ENTER, KC_TRNS,
                      KC_0,    KC_0,    KC_DOT,  KC_ENTER, KC_TRNS,
               KC_TRNS, KC_TRNS,
               KC_TRNS,
               KC_TRNS, KC_TRNS, KC_ENTER
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
          break;
        case 1:
          // Vim Save
          if (record->event.pressed) {
            return MACRO(I(10), T(ESC), D(LSFT), T(SCLN), U(LSFT), T(W), T(ENTER), END);
          } 
          break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

bool copy_whole_line = false;
void WB_select_line(void) {
  register_code(KC_HOME);
  unregister_code(KC_HOME);

  register_code(KC_LSFT);
  register_code(KC_END);
  unregister_code(KC_END);
  register_code(KC_RIGHT);
  unregister_code(KC_RIGHT);
  unregister_code(KC_LSFT);
}

void WB_copy(void) {
  register_code(KC_LGUI);
  register_code(KC_C);
  unregister_code(KC_C);
  unregister_code(KC_LGUI);
  register_code(KC_LEFT);
  unregister_code(KC_LEFT);
}

void WB_copy_line(void) {
  WB_select_line();
  WB_copy();
  copy_whole_line = true;
}

void WB_cut_line(void) {
  WB_select_line();
  register_code(KC_LGUI);
  register_code(KC_X);
  unregister_code(KC_X);
  unregister_code(KC_LGUI);
}


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
      leading = false;
      leader_end();

      SEQ_ONE_KEY(KC_P) {
        // Paste Line
        if (copy_whole_line) {
          register_code(KC_END);
          unregister_code(KC_END);
          register_code(KC_ENTER);
          unregister_code(KC_ENTER);
        }

        register_code(KC_LGUI);
        register_code(KC_V);
        unregister_code(KC_V);
        unregister_code(KC_LGUI);
        register_code(KC_BSPC);
        unregister_code(KC_BSPC);
        copy_whole_line = false;
      }
 
      // Cut Line
      SEQ_TWO_KEYS(KC_D, KC_D) {
        WB_cut_line();
      }
      SEQ_TWO_KEYS(KC_LSFT, KC_D) {
        WB_cut_line();
      }

      // Copy selection 
      SEQ_ONE_KEY(KC_Y) {
        WB_copy();
      }

      // Copy Line
      SEQ_TWO_KEYS(KC_Y, KC_Y) {
        WB_copy_line();
      }
      SEQ_TWO_KEYS(KC_LSFT, KC_Y) {
        WB_copy_line();
      }

      // Find
      SEQ_ONE_KEY(KC_SLSH) {
        register_code(KC_LGUI);
        register_code(KC_F);
        unregister_code(KC_F);
        unregister_code(KC_LGUI);
      }

      // Undo 
      SEQ_ONE_KEY(KC_U) {
        register_code(KC_LGUI);
        register_code(KC_Z);
        unregister_code(KC_Z);
        unregister_code(KC_LGUI);
      }
    }

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
