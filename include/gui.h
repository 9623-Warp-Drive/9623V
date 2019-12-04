#ifndef GUI
#define GUI
extern uint8_t auton;
void gui(void);
void groot(void);
extern lv_res_t btn_click_action(lv_obj_t * btn);
extern lv_obj_t * createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, lv_obj_t * btn, uint8_t id, const char * title);
extern lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr, lv_color_t textColor, lv_obj_t * btn);
void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn);
extern lv_coord_t btn_width;
extern lv_coord_t btn_height;
extern lv_color_t RED;
extern lv_color_t BLUE;
extern lv_color_t SKILL;
extern lv_color_t TEXT_COLOR;
#endif /* ifndef GUI */
