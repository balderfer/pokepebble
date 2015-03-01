#include "common.h"

static Window *window;
static TextLayer *s_load_layer;
static Layer *s_canvas_layer;
static TextLayer *start_text;
static TextLayer *header_text;


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  // text_layer_set_text(s_load_layer, "Select pressed!");
  // trainer_menu_init();
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}
static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(this_layer);
  GPoint center = GPoint(bounds.size.w / 2, (bounds.size.h / 2));


  /* This is for color
  #ifdef PBL_COLOR
  graphics_context_set_fill_color(ctx, GColorRed);
#else
  graphics_context_set_fill_color(ctx, GColorBlack);
#endif*/
  
  graphics_context_set_fill_color(ctx, GColorBlack);
  
  graphics_fill_circle(ctx, center, 40);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(30, 85, 90, 45), 0, GCornerNone);
  graphics_draw_circle(ctx, center, 40);
  graphics_draw_circle(ctx, center, 41);
  graphics_draw_circle(ctx, center, 42);
  graphics_draw_circle(ctx, center, 43);
  graphics_draw_line(ctx, GPoint(30, 85), GPoint(112, 85));
  graphics_draw_line(ctx, GPoint(30, 86), GPoint(112, 86));
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_circle(ctx, center, 10);
  graphics_draw_circle(ctx, center, 11);
  graphics_draw_circle(ctx, center, 12);
  graphics_draw_circle(ctx, center, 5);
  
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);
  
   s_canvas_layer = layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  layer_add_child(window_layer, s_canvas_layer);
  
  //Main text
  start_text = text_layer_create(GRect(0, 130, 144, 30));
  text_layer_set_background_color(start_text, GColorClear);
  text_layer_set_text_color(start_text, GColorBlack);
  text_layer_set_text_alignment(start_text, GTextAlignmentCenter);
  text_layer_set_font(start_text, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(start_text, "Logon to begin your adventure");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(start_text));
  
  //Header text
  header_text = text_layer_create(GRect(0, 7, 144, 24));
  text_layer_set_background_color(header_text, GColorClear);
  text_layer_set_text_color(header_text, GColorBlack);
  text_layer_set_text_alignment(header_text, GTextAlignmentCenter);
  text_layer_set_font(header_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text(header_text, "PokéPebble");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(header_text));

  // Set the update_proc
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);
}

static void window_unload(Window *window) {
  text_layer_destroy(s_load_layer);
  layer_destroy(s_canvas_layer);
  text_layer_destroy(start_text);
  text_layer_destroy(header_text);
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

