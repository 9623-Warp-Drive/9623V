#ifndef COLOR
#define COLOR
extern lv_color_t TEAL;
extern lv_color_t WHITE;
extern lv_color_t RED;
extern lv_color_t BLUE;
extern lv_color_t ORANGE;
#endif /* ifndef COLOR */

#ifndef OBJECT
#define OBJECT
extern lv_obj_t * label;
extern lv_obj_t * redOutline;
extern lv_obj_t * blueOutline;
extern lv_obj_t * centerOutline;
extern lv_obj_t * topRedBtn;
extern lv_obj_t * botRedBtn;
extern lv_obj_t * topBlueBtn;
extern lv_obj_t * botBlueBtn;
extern lv_obj_t * skillBtn;
#endif /* ifndef OBJECT */

#ifndef DISPLAY
#define DISPLAY
void setBackgroundColor(void);
#endif /* ifndef DISPLAY */

#ifndef OUTLINE
#define OUTLINE
extern lv_point_t center_separator[];
extern lv_point_t red_side[];
extern lv_point_t blue_side[];
extern lv_obj_t * createLine(lv_obj_t * line, lv_obj_t * parent, lv_point_t * pointArray, uint8_t arrayNum);
void setLineStyle(lv_obj_t * line);
#endif /* ifndef OUTLINE */

#ifndef BUTTON
#define BUTTON
extern uint8_t auton;
extern lv_coord_t btn_width;
extern lv_coord_t btn_height;
void gui(void);
void groot(void);
extern lv_res_t btn_click_action(lv_obj_t * btn);
extern lv_obj_t * createBtn(lv_obj_t * btn, lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, uint8_t id, const char * title);
extern lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr, lv_color_t textColor, lv_obj_t * btn);
void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn);
#endif /* ifndef BUTTON */
