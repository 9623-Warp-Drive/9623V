#include "display/lvgl.h"
#include "gui.h"

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
