#include "common.h"

static Window* window;
static TextLayer* s_text_layer;

extern char incoming_request[16];

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  s_text_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(s_text_layer, GColorClear);
  text_layer_set_text_color(s_text_layer, GColorBlack);
  text_layer_set_text(s_text_layer, incoming_request);

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_text_layer);
  window_destroy(window);
}

void incoming_request_init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  const bool animated = true;
  window_stack_push(window, animated);
}