#include "common.h"
  
static Window* window;
static MenuLayer* menu_layer;

extern char moves[4][16];
extern char party[5][16];
extern int num_of_party;

static bool attack;

static uint16_t menu_get_num_sections_callback(MenuLayer* menu_layer, void* data) {
  return 1;
}

static uint16_t menu_get_num_rows_callback(MenuLayer* menu_layer, uint16_t section_index, void* data) {
  if(attack)
    return 4;
  else
    return num_of_party;
}

static int16_t menu_get_header_height_callback(MenuLayer* menu_layer, uint16_t section_index, void* data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  if(attack)
    menu_cell_basic_header_draw(ctx, cell_layer, "Moves");
  else
    menu_cell_basic_header_draw(ctx, cell_layer, "Party");
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  if(attack)
    menu_cell_basic_draw(ctx, cell_layer, moves[cell_index->row], NULL, NULL);
  else
    menu_cell_basic_draw(ctx, cell_layer, party[cell_index->row], NULL, NULL);
}

static void menu_select_callback(MenuLayer* menu_layer, MenuIndex* cell_index, void* data) {
  APP_LOG  (APP_LOG_LEVEL_INFO, "MENU ITEM NUMBER: %d", cell_index->row);
  if(attack)
    send_move(moves[cell_index->row]);
  else
    send_poke(party[cell_index->row]);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  menu_layer = menu_layer_create(bounds);
  // Set all the callbacks for the menu layer
  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback
  });
  
  menu_layer_set_click_config_onto_window(menu_layer, window);
  
  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
}

static void window_unload(Window *window) {
  menu_layer_destroy(menu_layer);
  window_destroy(window);
}

void dynamic_menu_init(int option) {
  if(option == 0)
    attack = true;
  else
    attack = false;
    
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  
  const bool animated = true;
  window_stack_push(window, animated);
}
