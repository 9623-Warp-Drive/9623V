#include "display/lvgl.h"
#include "gui.h"

const lv_point_t center_separator[] = { {240,0}, {240,272} };
const lv_point_t red_side[] = { {0,114}, {112,114}, {210,52}, {210,-10}, {106,-10}, {106,52}, {1,52} };
const lv_point_t blue_side[] = { {480,114}, {368,114}, {270,52}, {270,-10}, {374,-10}, {374,52}, {480,52} };

lv_obj_t * createLine(lv_obj_t * line, lv_obj_t * parent, const lv_point_t * pointArray, const uint8_t arrayNum) {
  line = lv_line_create(parent, NULL);
  lv_line_set_points(line, pointArray, arrayNum);

  return line;
}

void setLineStyle(lv_obj_t * line) {
  static lv_style_t lineStyle;
  lv_style_copy(&lineStyle, &lv_style_plain);
  lineStyle.line.color = WHITE;
  lineStyle.line.width = 8;
  lineStyle.line.rounded = 1;

  lv_line_set_style(line, &lineStyle);
}
