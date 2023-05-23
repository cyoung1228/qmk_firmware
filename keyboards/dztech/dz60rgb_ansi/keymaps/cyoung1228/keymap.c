#include QMK_KEYBOARD_H

enum custom_keycodes {
    LGT_OFF = SAFE_RANGE
};

enum rgb_matrix_effects previous_effect = RGB_MATRIX_GRADIENT_LEFT_RIGHT;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi(
        KC_ESC,         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,         KC_EQL,          KC_BSPC,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,         KC_RBRC,         KC_BSLS,
        LT(2,KC_CAPS),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                          KC_ENT,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                          RSFT_T(KC_UP),
        KC_LCTL,        KC_LALT, KC_LGUI,                            KC_SPC,                             MO(1),   RGUI_T(KC_LEFT), RALT_T(KC_DOWN), RCTL_T(KC_RGHT)
    ),
    [1] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_VOLU,
        _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,          KC_MPLY,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          KC_UP,
        _______, _______, _______,                            _______,                            _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [2] = LAYOUT_60_ansi(
        KC_GRV , KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, LGT_OFF, KC_UP,   RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_MOD, _______, _______, _______, QK_BOOT,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, RGB_SPI, RGB_SPD, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          KC_UP,
        _______, _______, _______,                            _______,                            _______, KC_LEFT, KC_DOWN, KC_RGHT
    )
};

void no_light_mode(void) {
    switch(rgb_matrix_get_mode()) {
        case RGB_MATRIX_CUSTOM_no_light:
            rgb_matrix_mode(previous_effect);
            break;
        default:
            previous_effect = rgb_matrix_get_mode();
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_no_light);
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGT_OFF:
            if (record->event.pressed) {
                no_light_mode();
            }
            return false; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}
