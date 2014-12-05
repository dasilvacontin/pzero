
#include <pebble.h>
#include "Car.h"
#include "Race.h"
#include "Constants.h"

static Window *window;
Layer *window_layer;
Layer *map_layer;

Race *track;
Car *hero;

static GBitmap* spritesheet;
GBitmap* mapSprites[100];
int spritesw;
int spritesh;

int x = 0;
int y = 0;

//top left, top right, bottom left, bottom right
int cornerx[4] = {-1, 1, -1, 1};
int cornery[4] = {-1, -1, 1, 1};
int centerx[4] = {1, 0, 1, 0};
int centery[4] = {1, 1, 0, 0};

#define ROAD 13
#define FL0 26
#define FL1 27

#define TURBO_UP 6
#define TURBO_DOWN 18

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {

}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  car_change_dir(hero, -1);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  car_change_dir(hero, 1);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static bool valid_cell(int i, int j) {
  int cell_id = mapdata[i*map_w+j];
  return (cell_id == ROAD || cell_id == FL0 || cell_id == FL1 || cell_id == TURBO_UP || cell_id == TURBO_DOWN);
}

int d = 0;

void loop (void* callback_data){

  app_timer_register (INTERVAL, loop, NULL);

  int thrustx_power[2] = {0,0};
  int thrustx_votes[2] = {0,0};

  int thrusty_power[2] = {0,0};
  int thrusty_votes[2] = {0,0};

  int i = 0;
  for (i = 0; i < 4; ++i) {

    int cx = carpos.x + cornerx[i]*half_edge;
    int cy = carpos.y + cornery[i]*half_edge;

    int celli = cx/sprites_edge;
    int cellj = cy/sprites_edge;

    if (!valid_cell(celli,cellj)) {

      int offsetx = - (cx%sprites_edge);
      int offsety = - (cy%sprites_edge);

      if (centerx[i] == 1) offsetx += sprites_edge;
      if (centery[i] == 1) offsety += sprites_edge;

      int index_x = 0;
      if (offsetx > 0) index_x = 1;
      thrustx_power[index_x] = offsetx;
      ++thrustx_votes[index_x];

      int index_y = 0;
      if (offsety > 0) index_y = 1; 
      thrusty_power[index_y] = offsety;
      ++thrusty_votes[index_y];

    }

  }

  int index_x = thrustx_votes[1] - thrustx_votes[0];
  if (index_x != 0) {
    index_x = index_x > 0? 1 : 0;
    carpos.x += thrustx_power[index_x];
  }

  int index_y = thrusty_votes[1] - thrusty_votes[0];
  if (index_y != 0) {
    index_y = index_y > 0? 1 : 0;
    carpos.y += thrusty_power[index_y];
  }

  GRect map_frame = layer_get_frame(map_layer);
  map_frame.origin.x = SCREEN_WIDTH/2 - carpos.x;
  map_frame.origin.y = SCREEN_HEIGHT/2 - carpos.y;
  layer_set_frame(map_layer, map_frame);

  GRect car_frame = layer_get_frame((Layer *)car_layer);
  car_frame.origin.x = map_frame.origin.x + carpos.x - sprites_edge/2;
  car_frame.origin.y = map_frame.origin.y + carpos.y - sprites_edge/2;
  rot_bitmap_layer_set_angle(car_layer, TRIG_MAX_ANGLE*(dir*90)/360);
  layer_set_frame((Layer *)car_layer, car_frame);
  //layer_mark_dirty((Layer *)car_layer);

}

// We are trying to rotate this
static void car_draw(struct Layer *layer, GContext *ctx) {
  graphics_draw_bitmap_in_rect(ctx, mapSprites[CAR], (GRect) { .origin = { 0, 0 } , .size = { sprites_edge, sprites_edge } } );
  rot_bitmap_layer_set_angle(car_layer, TRIG_MAX_ANGLE*(dir*90)/360);

}

// Draws map_layer when marked as dirty in the initialization
static void map_draw(struct Layer *layer, GContext *ctx) {

  int i = 0, j = 0;
  for (i = 0; i < map_h; ++i) {
    for (j = 0; j < map_w; ++j) {
      graphics_draw_bitmap_in_rect(ctx, mapSprites[mapdata[i*map_w+j]-1], (GRect) { .origin = { j*sprites_edge, i*sprites_edge }, .size = { sprites_edge, sprites_edge } } );
    }
  }

}

void load_resources() {

  spritesheet = gbitmap_create_with_resource(RESOURCE_ID_SPRITESHEET);
  int i = 0, j = 0;
  spritesw = (int) spritesheet->bounds.size.w/sprites_edge + 1;
  spritesh = (int) spritesheet->bounds.size.h/sprites_edge + 1;

  // Generating sprites and saving them in mapSprites
  for (i = 0; i < spritesh; ++i) {
    for (j = 0; j < spritesw; ++j) {
      GBitmap* sprite = gbitmap_create_as_sub_bitmap (spritesheet, (GRect) { .origin = { j*sprites_edge, i*sprites_edge}, .size = { sprites_edge, sprites_edge} });
      mapSprites[i*spritesw + j] = sprite;
    }
  }

}

static void window_load(Window *window) {

  window_layer = window_get_root_layer(window);

  load_resources();

  // Draw whole map in a single layer
  map_layer = layer_create((GRect) { .origin = { -(int)SCREEN_WIDTH/2, -(int)SCREEN_HEIGHT/2 }, .size = { sprites_edge*map_w, sprites_edge*map_h} });
  layer_set_update_proc(map_layer, map_draw); 
  layer_mark_dirty(map_layer);
  layer_add_child(window_layer, map_layer);

  hero = car_create_with_type(0);
  layer_add_child(window_layer, car_get_layer(hero));
  car_set_position(hero, sprites_edge*2.5, sprites_edge*8);

}

static void window_unload(Window *window) {

}

static void init(void) {

  window = window_create();
  window_layer = window_get_root_layer (window);
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);

}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {

  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_timer_register(INTERVAL, loop, NULL);
  app_event_loop();
  deinit();

}
