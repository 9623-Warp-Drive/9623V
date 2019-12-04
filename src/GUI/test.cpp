#include "main.h"
void test() {
  // Set display styling
  lv_color_t BG = LV_COLOR_MAKE(29, 32, 33);
  static lv_style_t screen_style;
  lv_style_copy(&screen_style, &lv_style_plain);
  screen_style.body.main_color = BG;
  screen_style.body.grad_color = BG;
  lv_obj_set_style(lv_scr_act(), &screen_style);

  // Field outlines
  static lv_style_t style_line;
  lv_style_copy(&style_line, &lv_style_plain);
  style_line.line.color = LV_COLOR_MAKE(235, 219, 178);
  style_line.line.width = 8;
  style_line.line.rounded = 1;

  static lv_point_t center_separator[] = { {240,0}, {240,272} };
  lv_obj_t * color_separator = lv_line_create(lv_scr_act(), NULL);
  lv_line_set_points(color_separator, center_separator, 2);
  lv_line_set_style(color_separator, &style_line);

  static lv_point_t red_side[] = { {0,114}, {112,114}, {210,52}, {210,-10}, {106,-10}, {106,52}, {1,52} };
  lv_obj_t * red_outline = lv_line_create(lv_scr_act(), NULL);
  lv_line_set_points(red_outline, red_side, 7);
  lv_line_set_style(red_outline, &style_line);

  static lv_point_t blue_side[] = { {480,114}, {368,114}, {270,52}, {270,-10}, {374,-10}, {374,52}, {480,52} };
  lv_obj_t * blue_outline = lv_line_create(lv_scr_act(), NULL);
  lv_line_set_points(blue_outline, blue_side, 7);
  lv_line_set_style(blue_outline, &style_line);
}
