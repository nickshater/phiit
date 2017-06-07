#include <pebble.h>

static Window *window;
static TextLayer *text_layer;
static TextLayer *time_layer;
static GFont time_font;
static StatusBarLayer *s_status_bar;

static void init() {
  window = window_create();
  Layer *parent_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(parent_layer);

  text_layer = text_layer_create(bounds);
  text_layer_set_background_color(text_layer, GColorRed);
  text_layer_set_text(text_layer, "PHIIT");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);

  layer_add_child(window_get_root_layer(window),
         text_layer_get_layer(text_layer));

  text_layer_enable_screen_text_flow_and_paging(text_layer, 30);

  time_layer = text_layer_create((GRect) { .origin = { 0, 70 }, .size = { bounds.size.w -1, 50 } });
  time_font = fonts_get_system_font (FONT_KEY_LECO_36_BOLD_NUMBERS);
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  text_layer_set_font (time_layer, time_font);
  text_layer_set_text (time_layer, "00:00.0");
  layer_add_child(window_get_root_layer(window),
       text_layer_get_layer(time_layer));
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
