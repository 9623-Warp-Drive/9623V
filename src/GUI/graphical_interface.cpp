#include "main.h"

void gui() {
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

  // Add buttons to choose autnomous routines
  lv_color_t RED = LV_COLOR_MAKE(251, 73, 52);
  lv_color_t BLUE = LV_COLOR_MAKE(69, 113, 136);
  lv_color_t SKILL = LV_COLOR_MAKE(254, 128, 25);
  lv_color_t TEXT_COLOR = LV_COLOR_MAKE(251, 241, 199);

  // Button Style
  static lv_style_t red_button_rel;
  lv_style_copy(&red_button_rel, &lv_style_plain);
  red_button_rel.body.grad_color = RED;
  red_button_rel.body.main_color = RED;
  red_button_rel.text.color = TEXT_COLOR;

  static lv_style_t red_button_pr;
  lv_style_copy(&red_button_pr, &lv_style_plain);
  red_button_pr.body.grad_color = RED;
  red_button_pr.body.main_color = RED;
  red_button_pr.body.opa = LV_OPA_50;
  red_button_pr.text.color = TEXT_COLOR;

  static lv_style_t blue_button_rel;
  lv_style_copy(&blue_button_rel, &lv_style_plain);
  blue_button_rel.body.grad_color = BLUE;
  blue_button_rel.body.main_color = BLUE;
  blue_button_rel.text.color = TEXT_COLOR;

  static lv_style_t blue_button_pr;
  lv_style_copy(&blue_button_pr, &lv_style_plain);
  blue_button_pr.body.grad_color = BLUE;
  blue_button_pr.body.main_color = BLUE;
  blue_button_pr.body.opa = LV_OPA_50;
  blue_button_pr.text.color = TEXT_COLOR;

  static lv_style_t skill_button_rel;
  lv_style_copy(&skill_button_rel, &lv_style_plain);
  skill_button_rel.body.grad_color = SKILL;
  skill_button_rel.body.main_color = SKILL;
  skill_button_rel.text.color = TEXT_COLOR;

  static lv_style_t skill_button_pr;
  lv_style_copy(&skill_button_pr, &lv_style_plain);
  skill_button_pr.body.grad_color = SKILL;
  skill_button_pr.body.main_color = SKILL;
  skill_button_pr.body.opa = LV_OPA_50;
  skill_button_pr.text.color = TEXT_COLOR;

  lv_obj_t * label;
  lv_coord_t btn_width =  (lv_obj_get_width(lv_scr_act())/4)-10;
  lv_coord_t btn_height = btn_width/2;

  // Button for autonomous 1
  lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btn1, btn_width, btn_height);
  lv_obj_align(btn1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 56);
  lv_obj_set_free_num(btn1, 1);
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(btn1, LV_BTN_STYLE_REL, &red_button_rel);
  lv_btn_set_style(btn1, LV_BTN_STYLE_PR, &red_button_pr);

  label = lv_label_create(btn1, NULL);
  lv_label_set_text(label, "TOP RED");

  // Button for autonomous 2
  lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btn2, btn_width, btn_height);
  lv_obj_align(btn2, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, -30);
  lv_obj_set_free_num(btn2, 2);
  lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(btn2, LV_BTN_STYLE_REL, &red_button_rel);
  lv_btn_set_style(btn2, LV_BTN_STYLE_PR, &red_button_pr);

  label = lv_label_create(btn2, NULL);
  lv_label_set_text(label, "BOT RED");

  // Button for autonomous 3
  lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btn3, btn_width, btn_height);
  lv_obj_align(btn3, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 56);
  lv_obj_set_free_num(btn3, 3);
  lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(btn3, LV_BTN_STYLE_REL, &blue_button_rel);
  lv_btn_set_style(btn3, LV_BTN_STYLE_PR, &blue_button_pr);

  label = lv_label_create(btn3, NULL);
  lv_label_set_text(label, "TOP BLUE");

  // Button for autonomous 4
  lv_obj_t * btn4 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btn4, btn_width, btn_height);
  lv_obj_align(btn4, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, -30);
  lv_obj_set_free_num(btn4, 4);
  lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(btn4, LV_BTN_STYLE_REL, &blue_button_rel);
  lv_btn_set_style(btn4, LV_BTN_STYLE_PR, &blue_button_pr);

  label = lv_label_create(btn4, NULL);
  lv_label_set_text(label, "BOT BLUE");

  // Button for skill autonomous
  lv_obj_t * btn5 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btn5, btn_width, btn_height);
  lv_obj_align(btn5, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(btn5, 5);
  lv_btn_set_action(btn5, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(btn5, LV_BTN_STYLE_REL, &skill_button_rel);
  lv_btn_set_style(btn5, LV_BTN_STYLE_PR, &skill_button_pr);

  label = lv_label_create(btn5, NULL);
  lv_label_set_text(label, "SKILL");
}
