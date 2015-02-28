#include "common.h"

static Window *s_init_window;
static Window *s_trainers_window;
static TextLayer *s_load_layer;
extern char trainers[5][16];
extern int num_of_trainers;
MenuLayer* trainers_menu_layer;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_load_layer, "Select pressed!");
  window_stack_push(s_trainers_window, true);
}

static uint16_t menu_get_num_sections_callback(MenuLayer* menu_layer, void* data) {
  return 1;
}

static uint16_t menu_get_num_rows_callback(MenuLayer* menu_layer, uint16_t section_index, void* data) {
  return num_of_trainers;
}

static int16_t menu_get_header_height_callback(MenuLayer* menu_layer, uint16_t section_index, void* data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
    menu_cell_basic_header_draw(ctx, cell_layer, "Trainers");
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
    menu_cell_basic_draw(ctx, cell_layer, trainers[cell_index->row], NULL, NULL);
}

static void menu_select_callback(MenuLayer* menu_layer, MenuIndex* cell_index, void* data) {
    // TODO: SEND CONNECT
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void init_window_load(Window *window) {
  s_load_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(s_load_layer, GColorClear);
  text_layer_set_text_color(s_load_layer, GColorBlack);
  text_layer_set_text(s_load_layer, "Click to Connect");
  
   // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_load_layer));
}

static void init_window_unload(Window *window) {
  text_layer_destroy(s_load_layer);
}

static void trainers_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(s_trainers_window);
  GRect bounds = layer_get_frame(window_layer);
  
  trainers_menu_layer = menu_layer_create(bounds);
  
  menu_layer_set_callbacks(trainers_menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });
  
  menu_layer_set_click_config_onto_window(trainers_menu_layer, s_trainers_window);
  
  layer_add_child(window_layer, menu_layer_get_layer(trainers_menu_layer));
}

static void trainers_window_unload(Window *window) {
  menu_layer_destroy(trainers_menu_layer);
}
  
static void init(void) {
  // Create main Window element and assign to pointer
  s_init_window = window_create();
  
  // For initial select clicking
  window_set_click_config_provider(s_init_window, click_config_provider);
  
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_init_window, (WindowHandlers) {
    .load   = init_window_load,
    .unload = init_window_unload
  });
  
  s_trainers_window = window_create();
  window_set_window_handlers(s_trainers_window, (WindowHandlers) {
    .load   = trainers_window_load,
    .unload = trainers_window_unload,
  });
  
  // Set the window to be fullscreen
  window_set_fullscreen(s_init_window, true);
  
  // Show the Window on the watc, with animated=true
  window_stack_push(s_init_window, true);
}

static void deinit(void) {
  // Destroy Window
  window_destroy(s_trainers_window);
  window_destroy(s_init_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}

