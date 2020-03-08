#include "pros.h"

extern "C" {
#include "gui.h"
#include "vision.h"
#include "recorder.h"
}

void
initialize(void) {
  initRecorder();
  initVisionSensor();
  setVisionSig();
  gui();
}

void
disabled(void) {}

void
competition_initialize(void) {}
