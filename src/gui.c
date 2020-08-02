#include <stdlib.h>

#include "display/lvgl.h"
#include "switcher.hpp"

#include "gui.h"

enum button_dimension {
	BTN_HEIGHT = 55,
	BTN_WIDTH = 110
};

enum auton_routine {
	NULL_AUTON,
	TOP_RED,
	BOT_RED,
	TOP_BLUE,
	BOT_BLUE,
	SKILL_AUTON,
};

static const lv_point_t center_separator[2] = {
	{240,0}, {240,272}
};

static const lv_point_t red_side[7] = {
	{0,114}, {112,114}, {210,52}, {210,-10},
	{106,-10}, {106,52}, {1,52}
};

static const lv_point_t blue_side[7] = {
	{480,114}, {368,114}, {270,52}, {270,-10},
	{374,-10}, {374,52}, {480,52}
};

static lv_obj_t *red_outline;
static lv_obj_t *blue_outline;
static lv_obj_t *center_outline;

static lv_obj_t *top_red_btn;
static lv_obj_t *bot_red_btn;
static lv_obj_t *top_blue_btn;
static lv_obj_t *bot_blue_btn;
static lv_obj_t *skill_btn;

static void auton_selector(void);
static void home(void);

static void
set_background_color(void)
{
	static lv_style_t background_style;
	lv_style_copy(&background_style, &lv_style_plain);
	background_style.body.main_color = LV_COLOR_BLACK;
	background_style.body.grad_color = LV_COLOR_BLACK;
	lv_obj_set_style(lv_scr_act(), &background_style);
}

static lv_obj_t *
create_line(lv_obj_t *line, lv_obj_t *parent,
            const lv_point_t point_array[], const int array_num)
{
	static lv_style_t line_style;
	lv_style_copy(&line_style, &lv_style_plain);
	line_style.line.color = LV_COLOR_WHITE;
	line_style.line.width = 8;
	line_style.line.rounded = 1;

	line = lv_line_create(parent, NULL);
	lv_line_set_points(line, point_array, array_num);
	lv_line_set_style(line, &line_style);

	return line;
}

static lv_res_t
btn_click_action(lv_obj_t *btn)
{
	unsigned char id = lv_obj_get_free_num(btn);
	current_auton = id;

	lv_obj_clean(lv_scr_act());

	if (!id)
		auton_selector();
	else
		home();

	return LV_RES_OK;
}

static lv_obj_t *
create_btn(lv_obj_t *btn, lv_obj_t *parent, lv_coord_t x, lv_coord_t y, lv_coord_t width,
           lv_coord_t height, lv_color_t color, int id, const char *title)
{
	lv_style_t *btnStyle = (lv_style_t *)malloc(sizeof(lv_style_t) * 2);

	for (int i = 0; i < 4; i++)
		lv_style_copy(&btnStyle[i], &lv_style_plain);

	btnStyle[0].body.main_color = color;
	btnStyle[0].body.grad_color = color;
	btnStyle[0].text.color = LV_COLOR_WHITE;

	btnStyle[1].body.main_color = color;
	btnStyle[1].body.grad_color = color;
	btnStyle[1].body.opa = LV_OPA_50;
	btnStyle[1].text.color = LV_COLOR_WHITE;

	btn = lv_btn_create(parent, NULL);
	lv_obj_set_pos(btn, x, y);
	lv_obj_set_size(btn, width, height);
	lv_obj_set_free_num(btn, id);
	lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, btn_click_action);
	lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
	lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);

	lv_obj_t *label = lv_label_create(btn, NULL);
	lv_label_set_text(label, title);

	return btn;
}

static void
auton_selector(void)
{
	create_line(center_outline, lv_scr_act(), center_separator, 2);
	create_line(blue_outline, lv_scr_act(), blue_side, 7);
	create_line(red_outline, lv_scr_act(), red_side, 7);

	create_btn(top_red_btn, lv_scr_act(), 0, 55, BTN_WIDTH,
	           BTN_HEIGHT, LV_COLOR_RED, TOP_RED, "TOP RED");
	create_btn(bot_red_btn, lv_scr_act(), 0, 170, BTN_WIDTH,
	           BTN_HEIGHT, LV_COLOR_RED, BOT_RED, "BOT RED");
	create_btn(top_blue_btn, lv_scr_act(), 370, 55, BTN_WIDTH,
	           BTN_HEIGHT, LV_COLOR_BLUE, TOP_BLUE, "TOP BLUE");
	create_btn(bot_blue_btn, lv_scr_act(), 370, 170, BTN_WIDTH,
	           BTN_HEIGHT, LV_COLOR_BLUE , BOT_BLUE, "BOT BLUE");
	create_btn(skill_btn, lv_scr_act(), 185, 90, BTN_WIDTH,
	           BTN_HEIGHT, LV_COLOR_ORANGE, SKILL_AUTON, "SKILL");
}

static void
home(void)
{
	create_btn(top_red_btn, lv_scr_act(), 370, 182,
	           BTN_WIDTH, BTN_HEIGHT, LV_COLOR_GRAY, NULL_AUTON, "BACK");
}

void
xinit(void)
{
	set_background_color();
	auton_selector();
}
