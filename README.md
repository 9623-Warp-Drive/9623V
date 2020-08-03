# AUTONOMOUS SELECTOR

## CORTEX

[LVGL](https://github.com/littlevgl/lvgl) was used to create the graphical interface on the cortex.

**LVGL Auton Selector Demo**: https://youtu.be/p4ntxXrUGNo

## CONTROLLER

**Controller Auton Selector Demo**: https://youtu.be/eG3GMTe0Tv4
> Make sure to select autonomous routine before plugging the controller into the tower

## SETUP LVGL IN VEXCODE

To add LVGL library to your porject, follow the instruction [here](https://github.com/littlevgl/lvgl#add-littlevgl-to-your-project)

**Example Vexcode Program With LVGL**: https://github.com/jpearman/vexcode-lvgllib6_X


# MOTOR PORT CONFIGURATION

| Subsystem | Left Motor | Right Motor |
| --------- | ---------- | ----------- |
| `Chassis` |    `10`    |     `1`     |
| `Intake`  |    `9`     |     `2`     |
| `Lift`    |    `20`    |     `13`    |
| `Tray`    |    `15`    |     `16`    |


# KEYBINDING
|      Key       |    Function   |
| -------------  | ------------- |
| `Left Y Axis`  | Forward       |
| `Right X Axis` | Turn          |
| `R1`           | Intake Out    |
| `R2`           | Intake In     |
| `L1`           | Lift Up       |
| `L2`           | Lift Down     |
| `X`            | Tray Up       |
| `B`            | Tray Down     |
| `A + `        | Switch Layout |

# CONTROLLER LAYOUT SWITCHER

| Number |       Layout       |
| -------| -------------------|
| `0`    | `Macro Recorder`   |
| `1`    | `Autonmous Related`|
| `2`    | `Macro`            |

## MACRO RECORDER

|       Key      |            Function            |
| -------------- | ------------------------------ |
|     `Y + `    | `Switch Subsystem`             |
|     `Y + `    | `Recorder Checkpoint`          |
|     `Y + `    | `Print/Preview Recorded Value` |
|     `Y + `    | `Clear All Recorded Value`     |

## AUTONOMOUS RELATED

|       Key      |            Function             |
| -------------- | ------------------------------- |
|     `Y + `    | `Switch Autonomous Routines`    |
|     `Y + `    | `Run Autonomous`                |
|     `Y + `    | `Run Recorded Macro`            |
|     `Y + `    | `Run Recorded Macro in Reverse` |

## MACRO

|       Key      |            Function           |
| -------------- | ----------------------------- |
|     `Y + `    | `Stack Macro`                 |
|     `Y + `    | `Raise Lift to Medium Height` |
|     `Y + `    | `Raise Lift to Max Height`    |

# DISCLAIMER

I created project to test out different functionality, so the codebase is messy and not optimized. In addition, some functionalities are broken.
