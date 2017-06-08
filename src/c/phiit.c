#include <pebble.h>

static Window *window;
static TextLayer *text_layer;
static TextLayer *time_layer;
static GFont time_font;
static StatusBarLayer *s_status_bar;
static bool timer_active = false;
static double start_time = 0; 
static uint16_t start_time_ms = 0;
static time_t start_time_s = 0;
static AppTimer* timer;
static void timer_handler ();

static void window_load (Window *window) {
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
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
  text_layer_destroy(time_layer);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  int now_time_ms;
  if (timer_active) {
    timer_active = false;
    } else {
      timer_active = true;
      if (start_time == 0) {
        start_time_ms = time_ms(&start_time_s, NULL);
        start_time = (double)start_time_s + ((double)start_time_ms / 1000);
      }

      now_time_ms = time_ms(NULL, NULL);
      timer = app_timer_register((1000 + now_time_ms - start_time_ms) %100, timer_handler, NULL);
    };
  }

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void update_display() {
  time_t now_s;
  int now_time_ms;
  double now;
  double elapsed_time;
  now_time_ms = time_ms(&now_s, NULL);
  now = (double)now_s + ((double)now_time_ms / 1000);
  if (start_time == 0) {
    elapsed_time = 0;
  }
  else {
    elapsed_time = now - start_time;
  };
  int tenths = (int)(elapsed_time * 10) % 10;
  int seconds = (int)elapsed_time % 60;
  int minutes = (int)elapsed_time / 60 % 60; 
  static char display_time[] = "00:00.0";
  snprintf(display_time, 8, "%02d:%02d.%1d", minutes, seconds, tenths);
  text_layer_set_text (time_layer, display_time);
}

static void timer_handler () {
  if(timer_active) {
	timer = app_timer_register(100, timer_handler, NULL);
        update_display();
  }
}


static void init() {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  window_stack_push(window, true);
}

static void deinit() {
  window_destroy(window);
}

int main() {
   init();
   app_event_loop();
   deinit();
   return 0;
}
