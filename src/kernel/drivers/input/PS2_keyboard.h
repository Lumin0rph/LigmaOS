#pragma once
#include <library/types.h>
#include <architecture/x86/32/isr.h>

union keycode
{
	struct {
		u8 row : 3;
		u8 column : 5;
	};
	u8 code;
};

enum : u8
{
	KEY_NMEMB = 86,
};

enum key : u8
{
	// these correspond to ascii
	KEY_BACKSPACE = 8,
	KEY_TAB,
	KEY_ESCAPE = 27,
	KEY_SPACE = 32,

	KEY_APOSTROPHE = 39,
	KEY_KEYPAD_ASTERISK = 42,
	KEY_KEYPAD_PLUS,
	KEY_COMMA,
	KEY_MINUS,
	KEY_DOT,
	KEY_SLASH,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,

	KEY_SEMICOLON = 59,
	KEY_EQUALS = 61,

	KEY_LEFT_BRACKET = 91,
	KEY_BACKSLASH,
	KEY_RIGHT_BRACKET,

	KEY_BACKTICK = 96,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	// end of ascii

	KEY_F1 = 128,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_PRINT_SCREEN,
	KEY_SCROLL_LOCK,
	KEY_PAUSE,

	KEY_KEYPAD_NUM_LOCK,
	KEY_KEYPAD_SLASH,
	KEY_KEYPAD_MINUS,
	KEY_KEYPAD_DOT,
	KEY_KEYPAD_ENTER,
	KEY_KEYPAD_0,
	KEY_KEYPAD_1,
	KEY_KEYPAD_2,
	KEY_KEYPAD_3,
	KEY_KEYPAD_4,
	KEY_KEYPAD_5,
	KEY_KEYPAD_6,
	KEY_KEYPAD_7,
	KEY_KEYPAD_8,
	KEY_KEYPAD_9,

	KEY_INSERT,
	KEY_HOME,
	KEY_PAGE_UP,
	KEY_DELETE,
	KEY_END,
	KEY_PAGE_DOWN,

	KEY_CURSOR_UP,
	KEY_CURSOR_LEFT, KEY_CURSOR_DOWN, KEY_CURSOR_RIGHT,

	KEY_CAPS_LOCK,
	KEY_ENTER,

	KEY_LEFT_SHIFT,
	KEY_RIGHT_SHIFT,
	KEY_LEFT_CONTROL,
	KEY_RIGHT_CONTROL,
	KEY_LEFT_ALT,
	KEY_RIGHT_ALT,
	KEY_LEFT_GUI,
	KEY_RIGHT_GUI,

};

// corresponds to full size model m
enum : u8
{
	KEYMAP_ROWS = 6,
	KEYMAP_COLUMNS = 21,
};

constexpr enum key const keycode_to_key[KEYMAP_ROWS][KEYMAP_COLUMNS] = {
	{ KEY_ESCAPE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PRINT_SCREEN, KEY_SCROLL_LOCK, KEY_PAUSE },

	{ KEY_BACKTICK, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUALS, KEY_BACKSPACE, KEY_INSERT, KEY_HOME, KEY_PAGE_UP, KEY_KEYPAD_NUM_LOCK, KEY_KEYPAD_SLASH, KEY_KEYPAD_ASTERISK, KEY_KEYPAD_MINUS, },

	{ KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACKET, KEY_RIGHT_BRACKET, KEY_BACKSLASH, KEY_DELETE, KEY_END, KEY_PAGE_DOWN, KEY_KEYPAD_7, KEY_KEYPAD_8, KEY_KEYPAD_9, KEY_KEYPAD_PLUS, },

	{ KEY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_APOSTROPHE, KEY_ENTER, KEY_KEYPAD_4, KEY_KEYPAD_5, KEY_KEYPAD_6, },

	{ KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_DOT, KEY_SLASH, KEY_RIGHT_SHIFT, KEY_CURSOR_UP, KEY_KEYPAD_1, KEY_KEYPAD_2, KEY_KEYPAD_3, KEY_KEYPAD_ENTER },

	{ KEY_LEFT_CONTROL, KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_SPACE, KEY_RIGHT_ALT, KEY_RIGHT_GUI, KEY_RIGHT_CONTROL, KEY_CURSOR_LEFT, KEY_CURSOR_DOWN, KEY_CURSOR_RIGHT, KEY_KEYPAD_0, KEY_KEYPAD_DOT, },
};

void PS2_keyboard_IRQ_1_handler(struct ISR_parameters const *p);
