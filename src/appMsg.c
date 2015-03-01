// All communication between the c and javascript
#include "common.h"

int num_of_party = 0;
char moves[4][16];
char party[5][16];
char trainers[5][16];
int num_of_trainers = 0;

char name_1[16];
char name_2[16];
char status_1[4];
char status_2[4];
char game_text[256];
int health_1;
int health_2;
char incoming_request[16];

extern Layer * canvas_layer;
extern TextLayer* name1_layer;
extern TextLayer* name2_layer;
extern TextLayer* status1_layer;
extern TextLayer* status2_layer;


  
//declare the stuff to see the text layers and the buffers? / arrays?
  
static void inbox_recieved_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG  (APP_LOG_LEVEL_INFO, "Message recieved!");
  
  Tuple *t = dict_read_first(iterator);
  
  while (t != NULL) {
      
    switch(t->key) {
      case KEY_NAME_1:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        strcpy(name_1, t->value->cstring);
        text_layer_set_text(name1_layer, name_1);
        break;
      case KEY_NAME_2:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        strcpy(name_2, t->value->cstring);
        text_layer_set_text(name2_layer, name_2);
        break;
      case KEY_HEALTH_1:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %d", t->value->int16);
        health_1 = t->value->int16;
        break;
      case KEY_HEALTH_2:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %d", t->value->int16);
        health_2 = t->value->int16;
        break;
      case KEY_STATUS_1:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        strcpy(status_1, t->value->cstring);
        text_layer_set_text(status1_layer, status_1);
        break;
      case KEY_STATUS_2:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        strcpy(status_2, t->value->cstring);
        text_layer_set_text(status2_layer, status_2);
        break;
        // TODO: Sprites
//       case KEY_SPRITE_1:
//         APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
//         snprintf(apps[6], sizeof(apps[6]), t->value->cstring);
//         break;
//       case KEY_SPRITE_2:
//         APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
//         snprintf(apps[7], sizeof(apps[7]), t->value->cstring);
//         break;
      case KEY_IN_GAME_TEXT:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        strcpy(game_text, t->value->cstring);
        count_game_text();
        break;
      case KEY_MOVE_1:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(moves[0], sizeof(moves[0]), t->value->cstring);
        break;
      case KEY_MOVE_2:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(moves[1], sizeof(moves[1]), t->value->cstring);
        break;
      case KEY_MOVE_3:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(moves[2], sizeof(moves[2]), t->value->cstring);
        break;
      case KEY_MOVE_4:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(moves[3], sizeof(moves[3]), t->value->cstring);
        break;
      case KEY_POKE_1:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(party[0], sizeof(party[0]), t->value->cstring);
        break;
      case KEY_POKE_2:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(party[1], sizeof(party[1]), t->value->cstring);
        break;
      case KEY_POKE_3:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(party[2], sizeof(party[2]), t->value->cstring);
        break;
      case KEY_POKE_4:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(party[3], sizeof(party[3]), t->value->cstring);
        break;
      case KEY_POKE_5:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(party[4], sizeof(party[4]), t->value->cstring);
        break;
      case KEY_NUM_OF_PARTY:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %d", t->value->int16);
        num_of_party = t->value->int16;
        // TODO: CREATE RELOAD PROTOCOL
        layer_mark_dirty(canvas_layer);
        break;
      case KEY_TRAINER_1:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(trainers[0], sizeof(trainers[0]), t->value->cstring);
        break;
      case KEY_TRAINER_2:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(trainers[1], sizeof(trainers[1]), t->value->cstring);
        break;
      case KEY_TRAINER_3:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(trainers[2], sizeof(trainers[2]), t->value->cstring);
        break;
      case KEY_TRAINER_4:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(trainers[3], sizeof(trainers[3]), t->value->cstring);
        break;
      case KEY_TRAINER_5:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(trainers[4], sizeof(trainers[4]), t->value->cstring);
        break;
      case KEY_NUM_OF_TRAINERS:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %d", t->value->int16);
        num_of_trainers = t->value->int16;
        break;
      case KEY_R_INCOMING:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        strcpy(incoming_request, t->value->cstring);
        incoming_request_init();
        break;
      case KEY_VIEW_USERS:
        APP_LOG(APP_LOG_LEVEL_INFO, "View Users Message received! %d", t->value->int16);
        if(t->value->int16 == 1)
          trainer_menu_init();
        else
          trainer_menu_update();
        break;
      case KEY_START_BATTLE:
        APP_LOG(APP_LOG_LEVEL_INFO, "Start battle Message received! %d", t->value->int16);
        battle_window_init();
        break;
    }
    
    
      t = dict_read_next(iterator);
    
  }
  
}
  
static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator * iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}  
  
// see about doing the equivalent of the wrist control           **************send_command ()
//check if it is screen dependent or screen independent
// and then implement it
  
  
//  *********************from here below is dependent on send command*********************
//copied from wrist control, dont know what outbox is

void send_challenge(char* trainer) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Trainer Name: %s", trainer);
  DictionaryIterator* outbox_iter;
  
  if(app_message_outbox_begin(&outbox_iter) != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "opening outbox failed\n");
    return;
  }
  
  dict_write_uint8(outbox_iter, KEY_OP_CODE, 1);
  
  dict_write_cstring(outbox_iter, KEY_OP_DATA, trainer);
  
  if(outbox_iter == NULL) {
    return;
  }
  
  if (dict_write_end(outbox_iter) == 0) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "the parameters for writing were invalid");
  }
  app_message_outbox_send();
}

void send_move(char* move) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Trainer Name: %s", move);
  DictionaryIterator* outbox_iter;
  
  if(app_message_outbox_begin(&outbox_iter) != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "opening outbox failed\n");
    return;
  }
  
  dict_write_uint8(outbox_iter, KEY_OP_CODE, 2);
  
  dict_write_cstring(outbox_iter, KEY_OP_DATA, move);
  
  if(outbox_iter == NULL) {
    return;
  }
  
  if (dict_write_end(outbox_iter) == 0) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "the parameters for writing were invalid");
  }
  app_message_outbox_send();
}

void send_poke(char* poke) {
  DictionaryIterator* outbox_iter;
  
  if(app_message_outbox_begin(&outbox_iter) != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "opening outbox failed\n");
    return;
  }
  
  dict_write_uint8(outbox_iter, KEY_OP_CODE, 3);
  
  dict_write_cstring(outbox_iter, KEY_OP_DATA, poke);
  
  if(outbox_iter == NULL) {
    return;
  }
  
  if (dict_write_end(outbox_iter) == 0) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "the parameters for writing were invalid");
  }
  app_message_outbox_send();
}

void send_connect(char* name) {
  DictionaryIterator* outbox_iter;
  
  if(app_message_outbox_begin(&outbox_iter) != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "opening outbox failed\n");
    return;
  }
  
  dict_write_uint8(outbox_iter, KEY_OP_CODE, 0);
  if(name != NULL)
    dict_write_cstring(outbox_iter, KEY_OP_DATA, name);
  else
    dict_write_cstring(outbox_iter, KEY_OP_DATA, NULL);
  
  if(outbox_iter == NULL) {
    return;
  }
  
  if (dict_write_end(outbox_iter) == 0) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "the parameters for writing were invalid");
  }
  app_message_outbox_send();
}

void set_offline(void) {
  DictionaryIterator* outbox_iter;
  
  if(app_message_outbox_begin(&outbox_iter) != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "opening outbox failed\n");
    return;
  }
  
  dict_write_uint8(outbox_iter, KEY_OP_CODE, 4);
  
  dict_write_cstring(outbox_iter, KEY_OP_DATA, "offline");
  
  if(outbox_iter == NULL) {
    return;
  }
  
  if (dict_write_end(outbox_iter) == 0) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "the parameters for writing were invalid");
  }
  app_message_outbox_send();
}


void app_message_init() {
  app_message_register_inbox_received(inbox_recieved_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  APP_LOG  (APP_LOG_LEVEL_INFO, "INIT APP MESSAGES");
  
}