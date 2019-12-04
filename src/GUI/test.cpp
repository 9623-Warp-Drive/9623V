#include "main.h"
void test() {
  setBackgroundColor();
  createLine(lv_scr_act(), center_separator, 2);
  createLine(lv_scr_act(), red_side, 7);
  createLine(lv_scr_act(), blue_side, 7);
  createBtn(lv_scr_act(), 55, 40, btn_width, btn_height, 1, "TOP RED");
  createBtn(lv_scr_act(), 55, 235, btn_width, btn_height, 2, "BOT RED");
  createBtn(lv_scr_act(), 217, 40, btn_width, btn_height, 1, "TOP BLUE");
  createBtn(lv_scr_act(), 217, 235, btn_width, btn_height, 2, "BOT BLUE");
  createBtn(lv_scr_act(), 140, 136, btn_width, btn_height, 5, "SKILL");
}
