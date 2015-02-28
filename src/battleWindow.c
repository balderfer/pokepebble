#include "common.h"
  
static Window* window;

extern char names[2][16];
extern char statuses[2][4];
extern int health1;
extern int health2;
extern char game_text[256];

int battle_menu_index = 0;

TextLayer* name1_layer;
TextLayer* name2_layer;
TextLayer* status1_layer;
TextLayer* status2_layer;
TextLayer* battle_text_layer;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  // TODO: Parse game_text via \n, set that to count. Everything time select is clicked, count goes down until 0, where battle_menu_init() is called.
  battle_menu_init();
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void window_load(Window* window) {
  // TODO: ADD UI STUFF HERE
  
}

static void window_unload(Window* window) {
  // TODO: ADD UI STUFF HERE
  window_destroy(window);
}

void battle_window_init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load   = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);
}