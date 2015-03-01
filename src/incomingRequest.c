#include "common.h"

static Window* window;
static TextLayer* name_layer;
static TextLayer* text_layer;
static ActionBarLayer* action_bar;
static GBitmap *check_icon, *cross_icon;

extern char incoming_request[16];

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_connect(1);
  window_stack_pop(true);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_connect(0);
  window_stack_pop(true);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) down_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler) up_click_handler);
}

static void window_load(Window *window) {
  
  check_icon = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CHECK_ICON);
  cross_icon = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CROSS_ICON);
  
  action_bar = action_bar_layer_create();
  action_bar_layer_add_to_window(action_bar, window);
  action_bar_layer_set_click_config_provider(action_bar, click_config_provider);
  
  action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, check_icon);
  action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, cross_icon);

  name_layer = text_layer_create(GRect(0, 40, 144, 50));
  text_layer_set_background_color(name_layer, GColorClear);
  text_layer_set_text_color(name_layer, GColorBlack);
  text_layer_set_font(name_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text(name_layer, incoming_request);
  
  text_layer = text_layer_create(GRect(0, 65, 144, 50));
  text_layer_set_background_color(text_layer, GColorClear);
  text_layer_set_text_color(text_layer, GColorBlack);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(text_layer, "wants to battle!");
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(name_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(name_layer);
  text_layer_destroy(text_layer);
  action_bar_layer_destroy(action_bar);
  gbitmap_destroy(check_icon);
  gbitmap_destroy(cross_icon);
  window_destroy(window);
}

void incoming_request_init(void) {
  window = window_create();

  // For initial select clicking
  window_set_click_config_provider(window, click_config_provider);

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  const bool animated = true;
  window_stack_push(window, animated);
}