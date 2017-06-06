#include <pebble.h>

static Window *window;
static TextLayer *text_layer;
static StatusBarLayer *s_status_bar;

static void init() {
  window = window_create();
  Layer *parent_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(parent_layer);

  s_status_bar = status_bar_layer_create();

  status_bar_layer_set_colors(s_status_bar, GColorBlack, GColorBlueMoon);
  layer_add_child(window_get_root_layer(window), status_bar_layer_get_layer(s_status_bar));
  
  text_layer = text_layer_create(bounds);
  text_layer_set_background_color(text_layer, GColorRed);
  text_layer_set_text(text_layer, "PHIIT");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);

  layer_add_child(window_get_root_layer(window),
         text_layer_get_layer(text_layer));

  text_layer_enable_screen_text_flow_and_paging(text_layer, 30);

  window_stack_push(window, true);
}

static void deinit() {
  text_layer_destroy(text_layer);
  window_destroy(window);
}

int main() {
   init();
   app_event_loop();
   deinit();
   return 0;
}
