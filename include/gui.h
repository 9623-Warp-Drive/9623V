#ifndef _GUI_
#define _GUI_

#include "display/lvgl.h"

extern uint8_t auton;

extern const lv_point_t center_separator[];
extern const lv_point_t red_side[];
extern const lv_point_t blue_side[];

extern lv_obj_t *createBtn(lv_obj_t *btn, lv_obj_t *parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, lv_color_t, uint8_t id, const char *title);
extern lv_obj_t *createLine(lv_obj_t *line, lv_obj_t *parent, const lv_point_t pointArray[], const uint8_t arrayNum);

void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn);
void setLineStyle(lv_obj_t * line);
void setBackgroundColor(void);
void gui(void);
void test(void);


#endif /* ifndef _GUI_ */
