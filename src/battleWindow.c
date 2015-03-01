#include "common.h"
  
#define leftTop ((GPoint){(5), (117)})
#define leftBottom ((GPoint){(5), (162)})
#define rightTop ((GPoint){(138), (117)})
#define rightBottom ((GPoint){(138), (162)})
  
static Window* window;
static int select_count;
static bool drawn = false;

extern char name_1[16];
extern char name_2[16];
extern char status_1[4];
extern char status_2[4];
extern int health_1;
extern int health_2;
extern char game_text[256];

static char game_text_buffer[8][32];
static int array_num;

Layer * canvas_layer;
TextLayer* name1_layer;
TextLayer* name2_layer;
TextLayer* status1_layer;
TextLayer* status2_layer;
TextLayer* battle_text_layer;

extern GBitmap *sprite_1_bitmap;
extern GBitmap *sprite_2_bitmap;
BitmapLayer *sprite1_layer;
BitmapLayer *sprite2_layer;

void count_game_text(void) {
  array_num = 0;
  int i = 0;
  int j = 0;
  char c = game_text[i];
  
  while(c != '\0') {
    if(c != '\n') {
      game_text_buffer[array_num][j++] = c;
    }
    else {
      game_text_buffer[array_num][j] = '\0';
      j = 0; array_num++;
    }
    c = game_text[++i];
  }
  game_text_buffer[array_num][j] = '\0';
  array_num++;
  select_count = 0;
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  // TODO: Parse game_text via \n, set that to count. Everything time select is clicked, count goes down until 0, where battle_menu_init() is called.
  if(drawn == true) {
    select_count++;
    drawn = false;
  }
  if(select_count < array_num) {
    text_layer_set_text(battle_text_layer, game_text_buffer[select_count]);
    APP_LOG(APP_LOG_LEVEL_INFO, "current buffer: %s", game_text_buffer[select_count]);
    drawn = true;
    Layer *root = window_get_root_layer(window);
    layer_mark_dirty(root);
  }
  else {
    battle_menu_init();
  }
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
//   GRect bounds = layer_get_bounds(this_layer);

  //p2 
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(9, 35, 2, 11), 0, GCornerNone);
  graphics_fill_rect(ctx, GRect(9, 46, 70, 2), 0, GCornerNone);
  graphics_fill_rect(ctx, GRect(13, 36, 66, 8), 0, GCornerNone);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(14, 37, 64, 6), 0, GCornerNone);
  graphics_context_set_fill_color(ctx, GColorBlack);
  //One after this is setting health bar, third element dictates health
  graphics_fill_rect(ctx, GRect(14, 37, ((int)((16.0/25.0)*health_2)), 6), 0, GCornerNone);



  //p1
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(135, 95, 2, 11), 0, GCornerNone);
  graphics_fill_rect(ctx, GRect(67, 106, 70, 2), 0, GCornerNone);
  graphics_fill_rect(ctx, GRect(67, 96, 66, 8), 0, GCornerNone);
  graphics_context_set_fill_color(ctx, GColorWhite);
  //For p1, heath bar decided by opposite width
  graphics_fill_rect(ctx, GRect(68, 97, ((int)(64-((16.0/25.0)*health_1))), 6), 0, GCornerNone);

  graphics_context_set_stroke_color(ctx, GColorWhite);

  // Main boxes
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(3, 115, 138, 51), 0, GCornerNone);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(4, 116, 136, 47), 0, GCornerNone);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(6, 118, 132, 43), 0, GCornerNone);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(7, 121, 130, 39), 0, GCornerNone);

  // Pokeballs
  // Top left
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_circle(ctx, leftTop, 4);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_circle(ctx, leftTop, 3);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(2, 114, 7, 3), 0, GCornerNone);
  // Bottom left
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_circle(ctx, leftBottom, 4);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_circle(ctx, leftBottom, 3);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(2, 159, 7, 3), 0, GCornerNone);
  // Top right
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_circle(ctx, rightTop, 4);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_circle(ctx, rightTop, 3);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(135, 114, 7, 3), 0, GCornerNone);
  // Bottom right
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_circle(ctx, rightBottom, 4);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_circle(ctx, rightBottom, 3);
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(135, 159, 7, 3), 0, GCornerNone);
  drawn = true;
}

static void window_load(Window* window) {
  
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);
  
  
  // Create Layer
  canvas_layer = layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  layer_add_child(window_layer, canvas_layer);
  
  //Main text
  battle_text_layer = text_layer_create(GRect(8, 120, 130, 42));
  text_layer_set_background_color(battle_text_layer, GColorClear);
  text_layer_set_text_color(battle_text_layer, GColorBlack);
  text_layer_set_font(battle_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(battle_text_layer, game_text_buffer[select_count]);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(battle_text_layer));
  
  
  name2_layer = text_layer_create(GRect(10, 3, 144, 14));
  text_layer_set_background_color(name2_layer, GColorClear);
  text_layer_set_text_color(name2_layer, GColorBlack);
  text_layer_set_font(name2_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(name2_layer, name_2);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(name2_layer));
  
  status2_layer = text_layer_create(GRect(13, 17, 144, 14));
  text_layer_set_background_color(status2_layer, GColorClear);
  text_layer_set_text_color(status2_layer, GColorBlack);
  text_layer_set_font(status2_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  text_layer_set_text(status2_layer, "LV. 50");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(status2_layer));
  
  name1_layer = text_layer_create(GRect(64, 64, 68, 14));
  text_layer_set_background_color(name1_layer, GColorClear);
  text_layer_set_text_color(name1_layer, GColorBlack);
  text_layer_set_font(name1_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(name1_layer, name_1);
  text_layer_set_text_alignment(name1_layer, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(name1_layer));
  
  status1_layer = text_layer_create(GRect(61, 78, 68, 14));
  text_layer_set_background_color(status1_layer, GColorClear);
  text_layer_set_text_color(status1_layer, GColorBlack);
  text_layer_set_font(status1_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  text_layer_set_text(status1_layer, "LV. 50");
  text_layer_set_text_alignment(status1_layer, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(status1_layer));
  
  sprite_1_bitmap = gbitmap_create_blank(GSize(32, 32));
  sprite1_layer = bitmap_layer_create(GRect(5, 55, 32, 32));
  bitmap_layer_set_bitmap(sprite1_layer, sprite_1_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(sprite1_layer));
  
  sprite_2_bitmap = gbitmap_create_blank(GSize(32, 32));
  sprite2_layer = bitmap_layer_create(GRect(80, 10, 32, 32));
  bitmap_layer_set_bitmap(sprite2_layer, sprite_2_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(sprite2_layer));
  
  

  // Set the update_proc
  layer_set_update_proc(canvas_layer, canvas_update_proc);
  
}

static void window_unload(Window* window) {
  layer_destroy(canvas_layer);
  text_layer_destroy(name1_layer);
  text_layer_destroy(status1_layer);
  text_layer_destroy(battle_text_layer);
  text_layer_destroy(name2_layer);
  text_layer_destroy(status2_layer);
  bitmap_layer_destroy(sprite1_layer);
  gbitmap_destroy(sprite_1_bitmap);
  bitmap_layer_destroy(sprite2_layer);
  gbitmap_destroy(sprite_2_bitmap);
  window_destroy(window);
}

void battle_window_init(void) {
  window_stack_pop_all(false);
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load   = window_load,
    .unload = window_unload,
  });
  window_set_fullscreen(window, true);
  window_stack_push(window, false);
  APP_LOG(APP_LOG_LEVEL_INFO, "Print HEAP %d", heap_bytes_free());
}