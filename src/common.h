#include <pebble.h>

//initialize all the parts of the c - for me
// things used for all files

// battleWindow.c
void battle_window_init(void);

// appMsg.c
void app_message_init(void);

  
  
  
  
typedef enum {
  KEY_NAME_1 = 0x00,
  KEY_NAME_2 = 0x01,
  KEY_HEALTH_1 = 0x02,
  KEY_HEALTH_2 = 0x03,
  KEY_STATUS_1 = 0x04,
  KEY_STATUS_2 = 0x05,
  KEY_SPRITE_1 = 0x06,
  KEY_SPRITE_2 = 0x07,
  KEY_IN_GAME_TEXT = 0x08,
  KEY_MOVE_1 = 0x09,
  KEY_MOVE_2 = 0x0A,
  KEY_MOVE_3 = 0x0B,
  KEY_MOVE_4 = 0x0C,
  KEY_POKE_1 = 0x0D,
  KEY_POKE_2 = 0x0E,
  KEY_POKE_3 = 0x0F,
  KEY_POKE_4 = 0x10,
  KEY_POKE_5 = 0x11,
  KEY_NUM_OF_PARTY = 0x12,
} MessageKey;