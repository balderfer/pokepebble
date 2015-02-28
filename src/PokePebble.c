#include "common.h"

static Window *window;
static TextLayer *s_load_layer;


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_load_layer, "Select pressed!");
  trainer_menu_init();
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void window_load(Window *window) {
  s_load_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(s_load_layer, GColorClear);
  text_layer_set_text_color(s_load_layer, GColorBlack);
  text_layer_set_text(s_load_layer, "Click to Connect");
  
   // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_load_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_load_layer);
}
  
static void init(void) {
  app_message_init();
  // Create main Window element and assign to pointer
  window = window_create();
  
  // For initial select clicking
  window_set_click_config_provider(window, click_config_provider);
  
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(window, (WindowHandlers) {
    .load   = window_load,
    .unload = window_unload
  });
  
  // Set the window to be fullscreen
  window_set_fullscreen(window, true);
  
  // Show the Window on the watc, with animated=true
  window_stack_push(window, true);
}

static void deinit(void) {
  // Destroy Window
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}

