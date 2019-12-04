#include "main.h"

lv_color_t BG = LV_COLOR_MAKE(29, 32, 33);

void setBackgroundColor() {
  lv_style_t background_style;
  lv_style_copy(&background_style, &lv_style_plain);
  background_style.body.main_color = BG;
  background_style.body.grad_color = BG;
  lv_obj_set_style(lv_scr_act(), &background_style);
}
