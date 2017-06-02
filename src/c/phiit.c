#include <pebble.h>

Window *window;
TextLayer *text_layer;

void init() {
  window = window_create();
  Layer *parent_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(parent_layer);
  TextLayer *s_text_layer = text_layer_create(bounds);
  text_layer_set_text(text_layer, "PHIIT");
  layer_add_child(window_get_root_layer(window),
         text_layer_get_layer(text_layer));
  window_stack_push(window, true);
}

void deinit() {
  text_layer_destroy(text_layer);
  window_destroy(window);
}

int main() {
   init();
   app_event_loop();
   deinit();
   return 0;
}
