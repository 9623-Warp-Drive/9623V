#ifndef DISPLAY
#define DISPLAY
extern lv_color_t BG;
void setBackgroundColor(void);
#endif /* ifndef DISPLAY */

#ifndef OUTLINE
#define OUTLINE
extern lv_color_t OUTLINE_COLOR;
extern lv_point_t center_separator[];
extern lv_point_t red_side[];
extern lv_point_t blue_side[];
extern lv_obj_t * createLine(lv_obj_t * parent, lv_point_t * pointArray, uint8_t arrayNum);
void setLineStyle(lv_obj_t * line);
#endif /* ifndef OUTLINE */

#ifndef BUTTON
#define BUTTON
extern uint8_t auton;
void gui(void);
void groot(void);
extern lv_res_t btn_click_action(lv_obj_t * btn);
extern lv_obj_t * createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, uint8_t id, const char * title);
extern lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr, lv_color_t textColor, lv_obj_t * btn);
void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn);
extern lv_coord_t btn_width;
extern lv_coord_t btn_height;
extern lv_color_t RED;
extern lv_color_t BLUE;
extern lv_color_t SKILL;
extern lv_color_t TEXT_COLOR;
#endif /* ifndef BUTTON */
