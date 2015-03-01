#include <pebble.h>

//initialize all the parts of the c - for me
// things used for all files

// battleWindow.c
void battle_window_init(void);
void count_game_text(void);

// appMsg.c
void app_message_init(void);
void send_challenge(char* trainer);
void send_connect(char* name);
// void fetch_battle_menu(int option);
void send_move(char* move);
void send_poke(char* poke);
void accept_request(char* name);
void set_offline(void);

// battleMenu.c
void battle_menu_init(void);

// dynamicMenu.c
void dynamic_menu_init(int option);

// trainerMenu.c
void trainer_menu_init(void);
void trainer_menu_update(void);

// incomingRequest.c
void incoming_request_init(void);
  
  
  
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
  KEY_TRAINER_1 = 0x13,
  KEY_TRAINER_2 = 0x14,
  KEY_TRAINER_3 = 0x15,
  KEY_TRAINER_4 = 0x16,
  KEY_TRAINER_5 = 0x17,
  KEY_NUM_OF_TRAINERS = 0x18,
  KEY_OP_CODE = 0x19,
  KEY_OP_DATA = 0x1A,
  KEY_R_INCOMING = 0x1B,
  KEY_VIEW_USERS = 0x1C,
  KEY_START_BATTLE = 0x1D
} MessageKey;