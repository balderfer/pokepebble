#include "common.h"
  
static Window* window;
static Window* menuWindow;

extern char names[2][16];
extern char statuses[2][4];
extern int health1;
extern int health2;
extern char moves[4][16];
extern char party[5][16];
extern int num_of_party;

int battle_menu_index = 0;

MenuLayer* battle_menu_layer;
TextLayer* name1_layer;
TextLayer* name2_layer;
TextLayer* status1_layer;
TextLayer* status2_layer;
TextLayer* battle_text_layer;

static char *battle_menu[] = {
  "FIGHT",
  "SWITCH",
  "RUN"
};

static uint16_t menu_get_num_sections_callback(MenuLayer* menu_layer, void* data) {
  return 1;
}

static uint16_t menu_get_num_rows_callback(MenuLayer* menu_layer, uint16_t section_index, void* data) {
  if(battle_menu_index == 0)
    return 4;
  else
    return num_of_party;
}

static int16_t menu_get_header_height_callback(MenuLayer* menu_layer, uint16_t section_index, void* data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  if(battle_menu_index == 0)
    menu_cell_basic_header_draw(ctx, cell_layer, "Moves");
  else
    menu_cell_basic_header_draw(ctx, cell_layer, "Party");
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  if(battle_menu_index == 0)
    menu_cell_basic_draw(ctx, cell_layer, moves[cell_index->row], NULL, NULL);
  else
    menu_cell_basic_draw(ctx, cell_layer, party[cell_index->row], NULL, NULL);
}

static void menu_select_callback(MenuLayer* menu_layer, MenuIndex* cell_index, void* data) {
//   if(battle_menu_index == 0) 
    // TODO: SEND SELECTION
//   else
    // TODO: SEND SELECTION
}


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_push(menuWindow, true);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_push(menuWindow, true);
  battle_menu_index--;
  if(battle_menu_index == -1)
    battle_menu_index = 2;
  text_layer_set_text(battle_text_layer, battle_menu[battle_menu_index]);
  
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_push(menuWindow, true);
  battle_menu_index++;
  if(battle_menu_index == 3)
    battle_menu_index = 0;
  text_layer_set_text(battle_text_layer, battle_menu[battle_menu_index]);
  
}
static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void menu_window_load(Window* window) {
  Layer *window_layer = window_get_root_layer(menuWindow);
  GRect bounds = layer_get_frame(window_layer);
  
  battle_menu_layer = menu_layer_create(bounds);
  
  menu_layer_set_callbacks(battle_menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });
  
  menu_layer_set_click_config_onto_window(battle_menu_layer, menuWindow);
  
  layer_add_child(window_layer, menu_layer_get_layer(battle_menu_layer));
}

static void menu_window_unload(Window* window) {
  menu_layer_destroy(battle_menu_layer);
}

static void window_load(Window* window) {
  // TODO: ADD UI STUFF HERE
  
}

static void window_unload(Window* window) {
  // TODO: ADD UI STUFF HERE
  
  window_destroy(menuWindow);
  window_destroy(window);
}

void battle_window_init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load   = window_load,
    .unload = window_unload,
  });
  menuWindow = window_create();
  window_set_window_handlers(menuWindow, (WindowHandlers) {
    .load   = menu_window_load,
    .unload = menu_window_unload,
  });
  window_stack_push(window, true);
}