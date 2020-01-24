#ifndef _PORT_CONFIG_
#define _PORT_CONFIG_

#include "okapi/api.hpp"
#include "pros/motors.hpp"

using namespace okapi;

static inline auto Drive = ChassisControllerBuilder()
  .withMotors(1, -10)
  .withGains(
    {0.001, 0, 0.0001}, // Distance
    {0.001, 0, 0.0001}, // Turn
    {0.001, 0, 0.0001} ) // Angle Controller
  .withDerivativeFilters(
    std::make_unique<AverageFilter<3>>(),
    std::make_unique<AverageFilter<3>>(),
    std::make_unique<AverageFilter<3>>() )
  .withDimensions(AbstractMotor::gearset::green, {{4.0_in, 16.0_in}, imev5GreenTPR})
  .withLogger(
    std::make_shared<Logger>(
      TimeUtilFactory::createDefault().getTimer(),
      "/usd/log.txt",
      Logger::LogLevel::debug
    )
  )
  .withOdometry()
  .buildOdometry();

#endif /* ifndef _PORT_CONFIG_ */
