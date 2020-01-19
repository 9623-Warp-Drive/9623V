#include <stdlib.h>

#include "gui.h"

#define BLUE LV_COLOR_MAKE(69, 113, 136);
#define ORANGE LV_COLOR_MAKE(254, 128, 25);
#define RED LV_COLOR_MAKE(251, 73, 52);
#define TEAL LV_COLOR_MAKE(29, 32, 33)
#define WHITE LV_COLOR_MAKE(251, 241, 199);

#define BTN_HEIGHT 55
#define BTN_WIDTH 110

uint8_t auton = 0;
const lv_point_t center_separator[] = { {240,0}, {240,272} };
const lv_point_t red_side[] = { {0,114}, {112,114}, {210,52}, {210,-10}, {106,-10}, {106,52}, {1,52} };
const lv_point_t blue_side[] = { {480,114}, {368,114}, {270,52}, {270,-10}, {374,-10}, {374,52}, {480,52} };


void
setBackgroundColor(void) {
  static lv_style_t background_style;
  lv_style_copy(&background_style, &lv_style_plain);
  background_style.body.main_color = TEAL;
  background_style.body.grad_color = TEAL;
  lv_obj_set_style(lv_scr_act(), &background_style);
}

lv_res_t
btn_click_action(lv_obj_t * btn) {
  uint8_t id = lv_obj_get_free_num(btn);
  auton = id;
  lv_obj_clean(lv_scr_act());
}

lv_obj_t
*createBtn(lv_obj_t * btn, lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, uint8_t id, const char * title) {
  btn = lv_btn_create(parent, NULL);
  lv_obj_set_pos(btn, x, y);
  lv_obj_set_size(btn, width, height);
  lv_obj_set_free_num(btn, id);

  lv_obj_t * label = lv_label_create(btn, NULL);
  lv_label_set_text(label, title);

  return btn;
}

lv_style_t
*createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr, lv_color_t textColor, lv_obj_t * btn) {
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

lv_obj_t
*createLine(lv_obj_t * line, lv_obj_t * parent, const lv_point_t * pointArray, const uint8_t arrayNum) {
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

void
test(void) {
  setBackgroundColor();

  createLine(centerOutline, lv_scr_act(), center_separator, 2);
  createLine(redOutline, lv_scr_act(), red_side, 7);
  createLine(blueOutline, lv_scr_act(), blue_side, 7);

  setLineStyle(centerOutline);
  setLineStyle(redOutline);
  setLineStyle(blueOutline);

  createBtn(topRedBtn, lv_scr_act(), 55, 40, BTN_WIDTH, BTN_HEIGHT, 1, "TOP RED");
  createBtn(botRedBtn, lv_scr_act(), 55, 235, BTN_WIDTH, BTN_HEIGHT, 2, "BOT RED");
  createBtn(topBlueBtn, lv_scr_act(), 217, 40, BTN_WIDTH, BTN_HEIGHT, 1, "TOP BLUE");
  createBtn(botBlueBtn, lv_scr_act(), 217, 235, BTN_WIDTH, BTN_HEIGHT, 2, "BOT BLUE");
  createBtn(skillBtn, lv_scr_act(), 140, 136, BTN_WIDTH, BTN_HEIGHT, 5, "SKILL");
}

void
gui(void) {
  /* Set Background Color */
  static lv_style_t background_style;
  lv_style_copy(&background_style, &lv_style_plain);
  background_style.body.main_color = TEAL;
  background_style.body.grad_color = TEAL;
  lv_obj_set_style(lv_scr_act(), &background_style);

  /* Field outlines */
  static lv_style_t style_line;
  lv_style_copy(&style_line, &lv_style_plain);
  style_line.line.color = WHITE;
  style_line.line.width = 8;
  style_line.line.rounded = 1;

  lv_obj_t * centerOutline = lv_line_create(lv_scr_act(), NULL);
  lv_line_set_points(centerOutline, center_separator, 2);
  lv_line_set_style(centerOutline, &style_line);

  lv_obj_t * red_outline = lv_line_create(lv_scr_act(), NULL);
  lv_line_set_points(red_outline, red_side, 7);
  lv_line_set_style(red_outline, &style_line);

  lv_obj_t * blue_outline = lv_line_create(lv_scr_act(), NULL);
  lv_line_set_points(blue_outline, blue_side, 7);
  lv_line_set_style(blue_outline, &style_line);

  /* Add buttons to choose autnomous routines */
  static lv_style_t red_button_rel;
  lv_style_copy(&red_button_rel, &lv_style_plain);
  red_button_rel.body.grad_color = RED;
  red_button_rel.body.main_color = RED;
  red_button_rel.text.color = WHITE;

  static lv_style_t red_button_pr;
  lv_style_copy(&red_button_pr, &lv_style_plain);
  red_button_pr.body.grad_color = RED;
  red_button_pr.body.main_color = RED;
  red_button_pr.body.opa = LV_OPA_50;
  red_button_pr.text.color = WHITE;

  static lv_style_t blue_button_rel;
  lv_style_copy(&blue_button_rel, &lv_style_plain);
  blue_button_rel.body.grad_color = BLUE;
  blue_button_rel.body.main_color = BLUE;
  blue_button_rel.text.color = WHITE;

  static lv_style_t blue_button_pr;
  lv_style_copy(&blue_button_pr, &lv_style_plain);
  blue_button_pr.body.grad_color = BLUE;
  blue_button_pr.body.main_color = BLUE;
  blue_button_pr.body.opa = LV_OPA_50;
  blue_button_pr.text.color = WHITE;

  static lv_style_t skill_button_rel;
  lv_style_copy(&skill_button_rel, &lv_style_plain);
  skill_button_rel.body.grad_color = ORANGE;
  skill_button_rel.body.main_color = ORANGE;
  skill_button_rel.text.color = WHITE;

  static lv_style_t skill_button_pr;
  lv_style_copy(&skill_button_pr, &lv_style_plain);
  skill_button_pr.body.grad_color = ORANGE;
  skill_button_pr.body.main_color = ORANGE;
  skill_button_pr.body.opa = LV_OPA_50;
  skill_button_pr.text.color = WHITE;

  lv_obj_t * label;

  lv_obj_t * topRedBtn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(topRedBtn, BTN_WIDTH, BTN_HEIGHT);
  lv_obj_align(topRedBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 56);
  lv_obj_set_free_num(topRedBtn, 1);
  lv_btn_set_action(topRedBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(topRedBtn, LV_BTN_STYLE_REL, &red_button_rel);
  lv_btn_set_style(topRedBtn, LV_BTN_STYLE_PR, &red_button_pr);

  label = lv_label_create(topRedBtn, NULL);
  lv_label_set_text(label, "TOP RED");

  lv_obj_t * botRedBtn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(botRedBtn, BTN_WIDTH, BTN_HEIGHT);
  lv_obj_align(botRedBtn, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, -30);
  lv_obj_set_free_num(botRedBtn, 2);
  lv_btn_set_action(botRedBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(botRedBtn, LV_BTN_STYLE_REL, &red_button_rel);
  lv_btn_set_style(botRedBtn, LV_BTN_STYLE_PR, &red_button_pr);

  label = lv_label_create(botRedBtn, NULL);
  lv_label_set_text(label, "BOT RED");

  lv_obj_t * topBlueBtn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(topBlueBtn, BTN_WIDTH, BTN_HEIGHT);
  lv_obj_align(topBlueBtn, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 56);
  lv_obj_set_free_num(topBlueBtn, 3);
  lv_btn_set_action(topBlueBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(topBlueBtn, LV_BTN_STYLE_REL, &blue_button_rel);
  lv_btn_set_style(topBlueBtn, LV_BTN_STYLE_PR, &blue_button_pr);

  label = lv_label_create(topBlueBtn, NULL);
  lv_label_set_text(label, "TOP BLUE");

  lv_obj_t * botBlueBtn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(botBlueBtn, BTN_WIDTH, BTN_HEIGHT);
  lv_obj_align(botBlueBtn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, -30);
  lv_obj_set_free_num(botBlueBtn, 4);
  lv_btn_set_action(botBlueBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(botBlueBtn, LV_BTN_STYLE_REL, &blue_button_rel);
  lv_btn_set_style(botBlueBtn, LV_BTN_STYLE_PR, &blue_button_pr);

  label = lv_label_create(botBlueBtn, NULL);
  lv_label_set_text(label, "BOT BLUE");

  lv_obj_t * skillBtn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(skillBtn, BTN_WIDTH, BTN_HEIGHT);
  lv_obj_align(skillBtn, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(skillBtn, 5);
  lv_btn_set_action(skillBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(skillBtn, LV_BTN_STYLE_REL, &skill_button_rel);
  lv_btn_set_style(skillBtn, LV_BTN_STYLE_PR, &skill_button_pr);

  label = lv_label_create(skillBtn, NULL);
  lv_label_set_text(label, "SKILL");
}
