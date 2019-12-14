#include "display/lvgl.h"
#include "gui.h"

void setGroot() {
  LV_IMG_DECLARE(groot);
  lv_obj_t * image = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(image, &groot);
  lv_obj_align(image, NULL, LV_ALIGN_CENTER, 30, 0);
}

void setBonsai() {
  LV_IMG_DECLARE(bonsai);
  lv_obj_t * image = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(image, &bonsai);
  lv_obj_align(image, NULL, LV_ALIGN_CENTER, 0, 0);
}
