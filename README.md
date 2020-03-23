# Autonomous Selector

### Vexcode

To add LVGL library to your porject, follow the instruction here: https://github.com/littlevgl/lvgl#add-littlevgl-to-your-project

- Example Vexcode Program With LVGL: https://github.com/jpearman/vexcode-lvgllib6_X

### Cortex

LVGL (https://github.com/littlevgl/lvgl) was used to create the graphical interface on the cortex.

- LVGL Auton Selector Demo: https://youtu.be/p4ntxXrUGNo


### Controller

- Controller Auton Selector Demo: https://youtu.be/eG3GMTe0Tv4

# Port

| Subsystem | Left Motor | Right Motor |
| ------------- | ------------- | ------------- |
| Chassis | 10 | 1 |
| Intake | 9 | 2 |
| Lift | 20 | 13 |
| Tray | 15 | 16 |

# Keybinding

* `Drive Chassis` = Split Arcade

* `R1`: Intake Out
* `R2`: Intake In

* `L1`: Lift Up
* `L2`: Lift Down

* `X`: Tray Up
* `B`: Tray Down

# Controller Layout Switcher

| Number  | Layout |
| ------------- | ------------- |
| 0  | Autonmous Recorder  |
| 1  | Autonmous Related  |
| 2  | Macro  |

* `Prefix A + Down Arrow`: Switch Layout

### Autonomous Recorder

* `Prefix Y + Down Arrow`: Switch Subsystem
* `Prefix Y + Left Arrow`: Recorder Checkpoint
* `Prefix Y + Up Arrow`: Print/Preview Recorded Value
* `Prefix Y + Right Arrow`: Clear All Recorded Value

### Autonomous Related

* `Prefix Y + Down Arrow`: Switch Autonomous Routines
* `Prefix Y + Right Arrow`: Run Autonomous

### Macro

* `Prefix Y + Up Arrow`: Stack Macro
* `Prefix Y + Left Arrow`: Raise Lift to Medium Height
* `Prefix Y + Right Arrow`: Raise Lift to Max Height

# Reminder

I created project to test out different functionality so the project is kind of messy and not optimized. In addition, some functionality might be broken as well. Please not try to copy everything in the project. Feel free to contribute or fork this repo. Thank you!
