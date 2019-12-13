#ifndef _GUI_
#define _GUI_

extern uint8_t auton;

/* DISPLAY FUNCTION */
extern void setBackgroundColor(void);
extern void setGroot(void);
extern void setBonsai(void);
extern void gui(void);
extern void test(void);

/* COLOR */
extern const lv_color_t TEAL;
extern const lv_color_t WHITE;
extern const lv_color_t RED;
extern const lv_color_t BLUE;
extern const lv_color_t ORANGE;

/* OBJECT */
extern lv_obj_t * label;
extern lv_obj_t * redOutline;
extern lv_obj_t * blueOutline;
extern lv_obj_t * centerOutline;
extern lv_obj_t * topRedBtn;
extern lv_obj_t * botRedBtn;
extern lv_obj_t * topBlueBtn;
extern lv_obj_t * botBlueBtn;
extern lv_obj_t * skillBtn;

/* OUTLINE */
extern const lv_point_t center_separator[];
extern const lv_point_t red_side[];
extern const lv_point_t blue_side[];
extern lv_obj_t * createLine(lv_obj_t * line, lv_obj_t * parent, const lv_point_t * pointArray, const uint8_t arrayNum);
extern void setLineStyle(lv_obj_t * line);

/* BUTTON */
extern const lv_coord_t btn_width;
extern const lv_coord_t btn_height;
extern lv_res_t btn_click_action(lv_obj_t * btn);
extern lv_obj_t * createBtn(lv_obj_t * btn, lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, uint8_t id, const char * title);
extern lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr, lv_color_t textColor, lv_obj_t * btn);
extern void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn);

#endif /* ifndef _GUI_ */
