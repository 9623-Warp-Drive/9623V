#include <stdlib.h>

#include "gui.h"
#include "colorscheme/outrun-dark.h"

#define BTN_HEIGHT 55
#define BTN_WIDTH 110

uint8_t auton = 0;
static const lv_point_t center_separator[2] = { {240,0}, {240,272} };
static const lv_point_t red_side[7] = { {0,114}, {112,114}, {210,52}, {210,-10}, {106,-10}, {106,52}, {1,52} };
static const lv_point_t blue_side[7] = { {480,114}, {368,114}, {270,52}, {270,-10}, {374,-10}, {374,52}, {480,52} };

static void setBackgroundColor(void);
static lv_res_t btn_click_action(lv_obj_t *btn);
static lv_obj_t *createBtn(lv_obj_t *btn, lv_obj_t *parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, lv_color_t color, uint8_t id, const char *title);
static lv_obj_t *createLine(lv_obj_t *line, lv_obj_t *parent, const lv_point_t pointArray[], const uint8_t arrayNum);
void autonSelector(void);
void home(void);
void gui(void);

static lv_obj_t *redOutline;
static lv_obj_t *blueOutline;
static lv_obj_t *centerOutline;
static lv_obj_t *topRedBtn;
static lv_obj_t *botRedBtn;
static lv_obj_t *topBlueBtn;
static lv_obj_t *botBlueBtn;
static lv_obj_t *skillBtn;

void
setBackgroundColor(void) {
  static lv_style_t background_style;
  lv_style_copy(&background_style, &lv_style_plain);
  background_style.body.main_color = BACKGROUND_COLOR;
  background_style.body.grad_color = BACKGROUND_COLOR;
  lv_obj_set_style(lv_scr_act(), &background_style);
}

lv_obj_t
*createLine(lv_obj_t *line, lv_obj_t *parent, const lv_point_t pointArray[], const uint8_t arrayNum) {
  static lv_style_t style_line;
  lv_style_copy(&style_line, &lv_style_plain);
  style_line.line.color = LINE_COLOR;
  style_line.line.width = 8;
  style_line.line.rounded = 1;

  line = lv_line_create(parent, NULL);
  lv_line_set_points(line, pointArray, arrayNum);
  lv_line_set_style(line, &style_line);

  return line;
}

lv_res_t
btn_click_action(lv_obj_t *btn) {
  uint8_t id = lv_obj_get_free_num(btn);
  auton = id;
  lv_obj_clean(lv_scr_act());
  if (!id) {
    autonSelector();
  }
  else {
    home();
  }

  return LV_RES_OK;
}

lv_obj_t
*createBtn(lv_obj_t *btn, lv_obj_t *parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, lv_color_t color, uint8_t id, const char *title) {

  btn = lv_btn_create(parent, NULL);
  lv_obj_set_pos(btn, x, y);
  lv_obj_set_size(btn, width, height);
  lv_obj_set_free_num(btn, id);
  lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, btn_click_action);

  lv_obj_t *label = lv_label_create(btn, NULL);
  lv_label_set_text(label, title);

  lv_style_t *btnStyle = (lv_style_t *)malloc(sizeof(lv_style_t) * 2);

  for(int i = 0; i < 4; i++) lv_style_copy(&btnStyle[i], &lv_style_plain);

  btnStyle[0].body.main_color = color;
  btnStyle[0].body.grad_color = color;
  btnStyle[0].text.color = TEXT_COLOR;

  btnStyle[1].body.main_color = color;
  btnStyle[1].body.grad_color = color;
  btnStyle[1].body.opa = LV_OPA_50;
  btnStyle[1].text.color = TEXT_COLOR;

  lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
  lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);

  return btn;
}

void
autonSelector(void) {
  setBackgroundColor();

  createLine(centerOutline, lv_scr_act(), center_separator, 2);
  createLine(blueOutline, lv_scr_act(), blue_side, 7);
  createLine(redOutline, lv_scr_act(), red_side, 7);

  createBtn(topRedBtn, lv_scr_act(), 0, 55, BTN_WIDTH, BTN_HEIGHT, RED_BUTTON_COLOR, 1, "TOP RED");
  createBtn(botRedBtn, lv_scr_act(), 0, 170, BTN_WIDTH, BTN_HEIGHT, RED_BUTTON_COLOR, 2, "BOT RED");
  createBtn(topBlueBtn, lv_scr_act(), 370, 55, BTN_WIDTH, BTN_HEIGHT, BLUE_BUTTON_COLOR, 3, "TOP BLUE");
  createBtn(botBlueBtn, lv_scr_act(), 370, 170, BTN_WIDTH, BTN_HEIGHT, BLUE_BUTTON_COLOR , 4, "BOT BLUE");
  createBtn(skillBtn, lv_scr_act(), 185, 90, BTN_WIDTH, BTN_HEIGHT, SKILL_BUTTON_COLOR, 5, "SKILL");
}

void
home(void) {
  createBtn(topRedBtn, lv_scr_act(), 370, 182, BTN_WIDTH, BTN_HEIGHT, LV_COLOR_GRAY, 0, "Back");
}

void
gui(void) {
  autonSelector();
}
