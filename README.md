# AUTONOMOUS SELECTOR

## CORTEX

LVGL (https://github.com/littlevgl/lvgl) was used to create the graphical interface on the cortex.

`LVGL Auton Selector Demo`: https://youtu.be/p4ntxXrUGNo

## CONTROLLER

`Controller Auton Selector Demo`: https://youtu.be/eG3GMTe0Tv4
> Make sure to select autonomous routine before plugging the controller into the tower

## SETUP LVGL IN VEXCODE

To add LVGL library to your porject, follow the instruction here: https://github.com/littlevgl/lvgl#add-littlevgl-to-your-project

`Example Vexcode Program With LVGL`: https://github.com/jpearman/vexcode-lvgllib6_X


# MOTOR PORT CONFIGURATION

| Subsystem | Left Motor | Right Motor |
| ------------- | ------------- | ------------- |
| Chassis | 10 | 1 |
| Intake | 9 | 2 |
| Lift | 20 | 13 |
| Tray | 15 | 16 |


# KEYBINDING

* `Drive Chassis` = Split Arcade

* `R1`: Intake Out
* `R2`: Intake In

* `L1`: Lift Up
* `L2`: Lift Down

* `X`: Tray Up
* `B`: Tray Down


# CONTROLLER LAYOUT SWITCHER

| Number  | Layout |
| ------------- | ------------- |
| 0  | Macro Recorder  |
| 1  | Autonmous Related  |
| 2  | Macro  |

* `Prefix A + Down Arrow`: Switch Layout

## MACRO RECORDER
* `Prefix Y + Down Arrow`: Switch Subsystem
* `Prefix Y + Left Arrow`: Recorder Checkpoint
* `Prefix Y + Up Arrow`: Print/Preview Recorded Value
* `Prefix Y + Right Arrow`: Clear All Recorded Value

## AUTONOMOUS RELATED
* `Prefix Y + Down Arrow`: Switch Autonomous Routines
* `Prefix Y + Right Arrow`: Run Autonomous
* `Prefix Y + Left Arrow`: Run Recorded Macro
* `Prefix Y + Up Arrow`: Run Recorded Macro in Reverse

## MACRO
* `Prefix Y + Up Arrow`: Stack Macro
* `Prefix Y + Left Arrow`: Raise Lift to Medium Height
* `Prefix Y + Right Arrow`: Raise Lift to Max Height


# DISCLAIMER

I created project to test out different functionality so the project is kind of messy and not optimized. In addition, some functionality might be broken as well. Please not try to copy everything in the project. Feel free to contribute or fork this repo. Thank you!
