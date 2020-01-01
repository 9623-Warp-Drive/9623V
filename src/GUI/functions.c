#include "display/lvgl.h"
#include "gui.h"
#include <stdlib.h>

void
setBackgroundColor(void) {
  static lv_style_t background_style;
  lv_style_copy(&background_style, &lv_style_plain);
  background_style.body.main_color = TEAL;
  background_style.body.grad_color = TEAL;
  lv_obj_set_style(lv_scr_act(), &background_style);
}

lv_res_t btn_click_action(lv_obj_t * btn) {
  uint8_t id = lv_obj_get_free_num(btn);
  auton = id;
  lv_obj_clean(lv_scr_act());
}

lv_obj_t * createBtn(lv_obj_t * btn, lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, uint8_t id, const char * title) {
  btn = lv_btn_create(parent, NULL);
  lv_obj_set_pos(btn, x, y);
  lv_obj_set_size(btn, width, height);
  lv_obj_set_free_num(btn, id);

  lv_obj_t * label = lv_label_create(btn, NULL);
  lv_label_set_text(label, title);

  return btn;
}

lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr, lv_color_t textColor, lv_obj_t * btn) {
  lv_style_t * btnStyle = (lv_style_t *)malloc(sizeof(lv_style_t) * 4);

  for(int i = 0; i < 4; i++) lv_style_copy(&btnStyle[i], copy);

  btnStyle[0].body.main_color = rel;
  btnStyle[0].body.grad_color = rel;
  btnStyle[0].text.color = textColor;

  btnStyle[1].body.main_color = pr;
  btnStyle[1].body.grad_color = pr;
  btnStyle[1].body.opa = LV_OPA_50;
  btnStyle[1].text.color = WHITE;

  lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
  lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);

  return btnStyle;
}

void
setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn) {
  lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
  lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);
}

const lv_point_t center_separator[] = { {240,0}, {240,272} };
const lv_point_t red_side[] = { {0,114}, {112,114}, {210,52}, {210,-10}, {106,-10}, {106,52}, {1,52} };
const lv_point_t blue_side[] = { {480,114}, {368,114}, {270,52}, {270,-10}, {374,-10}, {374,52}, {480,52} };

lv_obj_t * createLine(lv_obj_t * line, lv_obj_t * parent, const lv_point_t * pointArray, const uint8_t arrayNum) {
  line = lv_line_create(parent, NULL);
  lv_line_set_points(line, pointArray, arrayNum);

  return line;
}

void
setLineStyle(lv_obj_t * line) {
  static lv_style_t lineStyle;
  lv_style_copy(&lineStyle, &lv_style_plain);
  lineStyle.line.color = WHITE;
  lineStyle.line.width = 8;
  lineStyle.line.rounded = 1;

  lv_line_set_style(line, &lineStyle);
}
