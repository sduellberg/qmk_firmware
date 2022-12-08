/* Copyright 2022 @ S. Duellberg
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

/*
 *   Keycodes: https://docs.qmk.fm/#/keycodes
 *
 *   Git tagging (last used version will be in this comment):
 *       (LISTING)
 *       git tag -n3 -l 'sduellberg-v*'
 *
 *       (CREATION)
 *       git tag sduellberg-v2.0 HEAD -m "*MESSAGE*"
 *       git push origin sduellberg-v2.0
 *
 *       (DELETION)
 *       git tag -d sduellberg-vx.x
 *       git push origin :sduellberg-vx.x
 *
 *    Console logging:
 *      (All messages need to end wit a newline or they will not be displayed!)
 *      qmk console -t
 *
 *   TODOs:
 *       - LED override for FN and macro layers
 *       - Map additional layers to numbers and use indicators
 *       - Custom key for "KeepMeAlive" using deferred execution + indicator
 *           (https://docs.qmk.fm/#/custom_quantum_functions?id=deferred-execution)
 *           (https://docs.qmk.fm/#/feature_rgb_matrix?id=indicators)
 *           (https://docs.qmk.fm/#/feature_macros?id=advanced-macros)
 *           (https://docs.qmk.fm/#/feature_macros?id=super-alt%e2%86%aftab)
 *       - Clean up unwanted RGB effects.
 *       - Increase the "cooldown" time of the rgb effect.
 *       - Check out the console feature.
 *           (https://docs.qmk.fm/#/cli_commands?id=qmk-console)
 *       - Check if there is an rgb effect for the keyboard going to sleep.
 *           (https://docs.qmk.fm/#/custom_quantum_functions?id=keyboard-idlingwake-code)
 *       - Add functionality for rectangle and cross in default layer.
 *           (https://docs.qmk.fm/#/feature_send_string?id=send_stringstring)
 *           (https://docs.qmk.fm/#/feature_macros?id=using-macros-in-c-keymaps)
 *       - RAW HID companion for additional functionality?
 *           (https://docs.qmk.fm/#/feature_rawhid)
 *       - Indicators and effects for dynamic macros?
 *       - Is it possible to cancel all currently locked keys (QK_LOCK)?
 *
 */

#include QMK_KEYBOARD_H
#include "print.h"

#define LYR_FN MO(LAYER_FUNCTIONS)
#define LYR_MCR MO(LAYER_MACROS)
#define KEEP_AWAKE_INTERVAL_MS 60000

// clang-format off

deferred_token keep_awake_token = '\0';

enum my_keycodes {
  SD_WAKE = SAFE_RANGE,
};

enum layers{
  LAYER_BASE,
  LAYER_SPECIAL,
  LAYER_FUNCTIONS,
  LAYER_MACROS
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_iso_110(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,    KC_MUTE,    KC_PSCR,  KC_LSCR,  KC_PAUS,    DM_PLY1,  DM_PLY2,  XXXXXXX,  XXXXXXX,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,    KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,    KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,               KC_DEL,   KC_END,   KC_PGDN,    KC_P7,    KC_P8,    KC_P9,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,   KC_ENT,                                     KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,        KC_RSFT,                   KC_UP,                KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  LYR_FN,   LYR_MCR,   KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,            KC_P0,        KC_PDOT,  KC_PENT),
    [LAYER_SPECIAL] = LAYOUT_iso_110(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,    _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,    _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,               _______,  _______,  _______,    _______,  _______,  _______,
        XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,                                    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,                   _______,              _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,   _______,    _______,  _______,  _______,         _______,       _______,  _______),
    [LAYER_FUNCTIONS] = LAYOUT_iso_110(
        QK_BOOT,  KC_BRID,  KC_BRIU,  KC_CPNL,  KC_CALC,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,   RGB_TOG,    KC_SLEP,  XXXXXXX,  RGB_MOD,    DM_REC1,  DM_REC2,  QK_LOCK,  SD_WAKE,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,  XXXXXXX,  KC_WH_U,    XXXXXXX,  RGB_RMOD, RGB_MOD,  RGB_SPD,
        RGB_TOG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,               XXXXXXX,  XXXXXXX,  KC_WH_D,    XXXXXXX,  RGB_HUI,  XXXXXXX,
        CW_TOGG,  XXXXXXX,  XXXXXXX,  DB_TOGG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_BTN1,                                    RGB_SAD,  XXXXXXX,  RGB_SAI,  RGB_SPI,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  NK_TOGG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,        KC_BTN2,                   KC_MS_U,              XXXXXXX,  RGB_HUD,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,    KC_MS_L,  KC_MS_D,  KC_MS_R,         XXXXXXX,       RGB_TOG,  XXXXXXX),
    [LAYER_MACROS] = LAYOUT_iso_110(
        DM_RSTP,  KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_F24,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,               XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,                                    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,        XXXXXXX,                   XXXXXXX,              XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,         XXXXXXX,       XXXXXXX,  XXXXXXX),
};

const uint16_t PROGMEM encoder_map[][1][2] = {
    [LAYER_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LAYER_SPECIAL] = {ENCODER_CCW_CW(_______, _______) },
    [LAYER_FUNCTIONS] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [LAYER_MACROS] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
};


/// @brief Keep the computer awake by sending a key event every minute
uint32_t keep_awake(uint32_t trigger_time, void *cb_arg) {
    dprint("keep_awake: Sending keycode.\n");
    tap_code(KC_BRIU);

    // setup next execution
    return keep_awake_token != '\0' ? KEEP_AWAKE_INTERVAL_MS : 0;
}


bool dip_switch_update_user(uint8_t index, bool active) {
    if(active)
    {
      dprint("DIP event: Switching to SPECIAL layer.\n");
      set_single_persistent_default_layer(LAYER_SPECIAL);
    }
    else
    {
      dprint("DIP event: Switching to BASE layer.\n");
      set_single_persistent_default_layer(LAYER_BASE);
    }
    return false; // always skip default handling
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SD_WAKE:
      if (record->event.pressed)
      {
        if(keep_awake_token != '\0'){
          // deactivate deferred execution
          dprint("Ending keep_awake.\n");
          cancel_deferred_exec(keep_awake_token);
          keep_awake_token = '\0';
        }
        else{
          // activate keep awake deferred execution
          dprint("Starting keep_awake.\n");
          keep_awake_token = defer_exec(KEEP_AWAKE_INTERVAL_MS, keep_awake, NULL);
        }
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}
