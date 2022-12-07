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
*   Git tagging:
*       (LISTING)
*       git tag -l 'sduellberg-v*'
*
*       (CREATION)
*       git tag sduellberg-v1.1 HEAD -m "*MESSAGE*"
*       git push origin sduellberg-v1.1
*
*       (DELETION)
*       git tag -d sduellberg-v1.0
*       git push origin :sduellberg-v1.0
*
*   TODOS:
*       - LED override for FN and macro layers
*       - Map RGB effects to numbers and use indicators
*       - Custom key for "KeepMeAlive" using deferred execution + indicator
*       - Move keymaps for rgb control to the numpad
*
*/

#include QMK_KEYBOARD_H
#define ___ KC_NO
#define LYR_FN MO(LAYER_FUNCTIONS)
#define LYR_MCR MO(LAYER_MACROS)
#define CAPS

// clang-format off

enum layers{
  LAYER_BASE,
  LAYER_SPECIAL,
  LAYER_FUNCTIONS,
  LAYER_MACROS
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT_iso_110(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,    KC_MUTE,    KC_PSCR,  KC_LSCR,  KC_PAUS,    DM_PLY1,  DM_PLY2,  _______,  _______,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,    KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,    KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,               KC_DEL,   KC_END,   KC_PGDN,    KC_P7,    KC_P8,    KC_P9,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,   KC_ENT,                                     KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,        KC_RSFT,                   KC_UP,                KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  LYR_FN,   LYR_MCR,   KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,            KC_P0,        KC_PDOT,  KC_PENT),
    [LAYER_SPECIAL] = LAYOUT_iso_110(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,    _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,    _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,               _______,  _______,  _______,    _______,  _______,  _______,
        KC_NO,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,                                    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,        _______,                   _______,              _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,   _______,    _______,  _______,  _______,         _______,       _______,  _______),
    [LAYER_FUNCTIONS] = LAYOUT_iso_110(
        XXXXXXX,  KC_BRID,  KC_BRIU,  KC_CPNL,  KC_CALC,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,   RGB_TOG,    KC_SLEP,  XXXXXXX,  RGB_MOD,    DM_REC1,  DM_REC2,  XXXXXXX,  QK_LOCK,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,  XXXXXXX,  KC_WH_U,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        RGB_TOG,  XXXXXXX,  XXXXXXX,  RGB_HUI,  RGB_SAI,  RGB_SPI,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,               XXXXXXX,  XXXXXXX,  KC_WH_D,    XXXXXXX,  XXXXXXX,  XXXXXXX,
        CW_TOGG,  XXXXXXX,  XXXXXXX,  RGB_HUD,  RGB_SAD,  RGB_SPD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_BTN1,                                    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  NK_TOGG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,        KC_BTN2,                   KC_MS_U,              XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,    KC_MS_L,  KC_MS_D,  KC_MS_R,         XXXXXXX,       XXXXXXX,  XXXXXXX),
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

bool dip_switch_update_user(uint8_t index, bool active) {
    if(active)
    {
        set_single_persistent_default_layer(LAYER_SPECIAL);
    }
    else
    {
        set_single_persistent_default_layer(LAYER_BASE);
    }
    return false; // always skip default handling
}
