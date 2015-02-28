// All communication between the c and javascript
#include "common.h"
  
//declare the stuff to see the text layers and the buffers? / arrays?
  
static void inbox_recieved_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG  (APP_LOG_LEVEL_INFO, "Message recieved!");
  
  Tuple *t = dict_read_first(iterator);
  
  while (t != NULL) {
    /*if it is get info for the pick battelor screen
            then there is a switch statement and the values are the number and name of the person    
        
            additonally the key text header thing 
    */
    
    
    
    /* if it is get info for the battle options
          then there is something different that will take the strings from the js with the current action/options and print it
   
              ??? additonally the key text header thing -see if applicable for that type

   */
    
    
    
    /* if the person is picking moves
    
      switch statement to get the list of actions for the menu and the action name is what is in the array (t->value->blah)
      
                additonally the key text header thing 

    */
    
    
    
      /* if the person wants to switch pokemon
          switch statement to get the list of the pokemon names for js
    
                 additonally the key text header thing 

      */
    
    
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