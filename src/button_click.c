#include <pebble.h>

static Window *window;
static TextLayer *text_layer;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;
static TextLayer *phone_number_layer;
static char* phoneNum="650-555-0197";
static char* contactName="Dr. Gordon";
static const uint32_t const segments[] = { 200, 100, 200, 100, 200,100 };


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(text_layer, "Select");
	s_background_layer=bitmap_layer_create(GRect(124, 6, 20, 146));
	s_background_bitmap=gbitmap_create_with_resource(RESOURCE_ID_call_accept_cancel);
	bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
	layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));
	GRect bounds=layer_get_bounds(window_get_root_layer(window));//GRect bounds = layer_get_bounds(window);

  text_layer = text_layer_create((GRect) { .origin = { 0, 60 }, .size = { bounds.size.w-24, 20 } });
  text_layer_set_text(text_layer, contactName);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
	
	phone_number_layer =text_layer_create(GRect(4, 120, 120, 16));
	text_layer_set_text(phone_number_layer, phoneNum);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(phone_number_layer));
	VibePattern pat = {
  .durations = segments,
  .num_segments = ARRAY_LENGTH(segments),
};
	for(int i=0;i<3;i++){
		
		vibes_enqueue_custom_pattern(pat);
	}


	
	
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(text_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(text_layer, "Down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
 /* Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));*/
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
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
  app_event_loop();
  deinit();
}