#include "main.h"

void gui() {
  setBackgroundColor();

  /* Field outlines */
  static lv_style_t style_line;
  lv_style_copy(&style_line, &lv_style_plain);
  style_line.line.color = OUTLINE_COLOR;
  style_line.line.width = 8;
  style_line.line.rounded = 1;

  /* field outlines */
  lv_obj_t * color_separator = lv_line_create(lv_scr_act(), NULL);
  lv_line_set_points(color_separator, center_separator, 2);
  lv_line_set_style(color_separator, &style_line);

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

  lv_obj_t * topRedBtn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(topRedBtn, btn_width, btn_height);
  lv_obj_align(topRedBtn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 56);
  lv_obj_set_free_num(topRedBtn, 1);
  lv_btn_set_action(topRedBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(topRedBtn, LV_BTN_STYLE_REL, &red_button_rel);
  lv_btn_set_style(topRedBtn, LV_BTN_STYLE_PR, &red_button_pr);

  label = lv_label_create(topRedBtn, NULL);
  lv_label_set_text(label, "TOP RED");

  lv_obj_t * botRedBtn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(botRedBtn, btn_width, btn_height);
  lv_obj_align(botRedBtn, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, -30);
  lv_obj_set_free_num(botRedBtn, 2);
  lv_btn_set_action(botRedBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(botRedBtn, LV_BTN_STYLE_REL, &red_button_rel);
  lv_btn_set_style(botRedBtn, LV_BTN_STYLE_PR, &red_button_pr);

  label = lv_label_create(botRedBtn, NULL);
  lv_label_set_text(label, "BOT RED");

  lv_obj_t * topBlueBtn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(topBlueBtn, btn_width, btn_height);
  lv_obj_align(topBlueBtn, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 56);
  lv_obj_set_free_num(topBlueBtn, 3);
  lv_btn_set_action(topBlueBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(topBlueBtn, LV_BTN_STYLE_REL, &blue_button_rel);
  lv_btn_set_style(topBlueBtn, LV_BTN_STYLE_PR, &blue_button_pr);

  label = lv_label_create(topBlueBtn, NULL);
  lv_label_set_text(label, "TOP BLUE");

  lv_obj_t * botBlueBtn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(botBlueBtn, btn_width, btn_height);
  lv_obj_align(botBlueBtn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, -30);
  lv_obj_set_free_num(botBlueBtn, 4);
  lv_btn_set_action(botBlueBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(botBlueBtn, LV_BTN_STYLE_REL, &blue_button_rel);
  lv_btn_set_style(botBlueBtn, LV_BTN_STYLE_PR, &blue_button_pr);

  label = lv_label_create(botBlueBtn, NULL);
  lv_label_set_text(label, "BOT BLUE");

  lv_obj_t * skillBtn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(skillBtn, btn_width, btn_height);
  lv_obj_align(skillBtn, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_free_num(skillBtn, 5);
  lv_btn_set_action(skillBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(skillBtn, LV_BTN_STYLE_REL, &skill_button_rel);
  lv_btn_set_style(skillBtn, LV_BTN_STYLE_PR, &skill_button_pr);

  label = lv_label_create(skillBtn, NULL);
  lv_label_set_text(label, "SKILL");
}
