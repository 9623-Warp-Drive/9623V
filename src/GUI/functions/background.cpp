#include "main.h"

void setBackgroundColor() {
  lv_style_t background_style;
  lv_style_copy(&background_style, &lv_style_plain);
  background_style.body.main_color = TEAL;
  background_style.body.grad_color = TEAL;
  lv_obj_set_style(lv_scr_act(), &background_style);
}
