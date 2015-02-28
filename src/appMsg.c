// All communication between the c and javascript
#include "common.h"

int num_of_party = 0;
char moves[4][16];
char party[5][16];
char names[2][16];
char statuses[2][4];
char game_text[256];
int health1;
int health2;

extern MenuLayer* battle_menu_layer;
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
        snprintf(names[0], sizeof(names[0]), t->value->cstring);
        break;
      case KEY_NAME_2:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(names[1], sizeof(names[1]), t->value->cstring);
        break;
      case KEY_HEALTH_1:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %d", t->value->int16);
        health1 = t->value->int16;
        break;
      case KEY_HEALTH_2:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %d", t->value->int16);
        health2 = t->value->int16;
        break;
      case KEY_STATUS_1:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(statuses[0], sizeof(statuses[0]), t->value->cstring);
        break;
      case KEY_STATUS_2:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received! %s", t->value->cstring);
        snprintf(statuses[1], sizeof(statuses[1]), t->value->cstring);
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
        snprintf(game_text, sizeof(game_text), t->value->cstring);
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
void temp_send_command(char* option, char* button) {
  
  DictionaryIterator* outbox_iter;
  
  if(app_message_outbox_begin(&outbox_iter) != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "opening outbox failed\n");
    return;
  }
  
  if(outbox_iter == NULL) {
    return;
  }
    
    
  // figure out what this is and modify/ removed to fit our app for all below code
//   dict_write_cstring(outbox_iter, KEY_COMMAND_APP, option);
//   if (button != NULL) {
//     dict_write_cstring(outbox_iter, KEY_COMMAND_BUTTON, button);
//   }
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
  
}