## GRAPHICAL INTERFACE

LVGL was used for creating an autonomous selector. Demo video: https://www.youtube.com/watch?v=p4ntxXrUGNo

If you are using VexCode, you can add LVGL to your project by following the directions here: https://github.com/littlevgl/lvgl#add-littlevgl-to-your-project

Example LVGL project format in VexCode: https://github.com/jpearman/vexcode-lvgllib6_2

## PORT

| Subsystem | Left Motor | Right Motor |
| ------------- | ------------- | ------------- |
| Chassis | 10 | 1 |
| Intake | 9 | 2 |
| Lift | 20 | 13 |
| Tray | 15 | 16 |

## KEYBINDING

* `Drive Chassis` = Split Arcade

* `R1`: Intake Out
* `R2`: Intake In

* `L1`: Lift Up
* `L2`: Lift Down

* `X`: Tray Up
* `B`: Tray Down

## CONTROLLER LAYOUT SWITCHER

| Number  | Layout |
| ------------- | ------------- |
| 0  | Autonmous Recorder  |
| 1  | Autonmous Related  |
| 2  | Macro  |

* `Prefix A + Down Arrow`: Switch Layout

### AUTONOMOUS RECORDER

* `Prefix Y + Down Arrow`: Switch Subsystem
* `Prefix Y + Left Arrow`: Recorder Checkpoint
* `Prefix Y + Up Arrow`: Print/Preview Recorded Value
* `Prefix Y + Right Arrow`: Clear All Recorded Value

### AUTONOMOUS RELATED

* `Prefix Y + Down Arrow`: Switch Autonomous Routines
* `Prefix Y + Right Arrow`: Run Autonomous

### MACRO

* `Prefix Y + Up Arrow`: Stack Macro
* `Prefix Y + Left Arrow`: Raise Lift to Medium Height
* `Prefix Y + Right Arrow`: Raise Lift to Max Height

## REMINDER

I created project to test out different functionality so the project is kind of messy and not optimized. In addition, some functionality might be broken as well. Please not try to copy everything in the project. Feel free to contribute or fork this repo. Thank you!
