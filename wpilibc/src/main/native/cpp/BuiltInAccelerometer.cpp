// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/BuiltInAccelerometer.h"

#include <hal/Accelerometer.h>
#include <hal/FRCUsageReporting.h>

#include "frc/Errors.h"
#include "frc/smartdashboard/SendableBuilder.h"
#include "frc/smartdashboard/SendableRegistry.h"

using namespace frc;

BuiltInAccelerometer::BuiltInAccelerometer(Range range) {
  SetRange(range);

  HAL_Report(HALUsageReporting::kResourceType_Accelerometer, 0, 0,
             "Built-in accelerometer");
  SendableRegistry::GetInstance().AddLW(this, "BuiltInAccel");
}

void BuiltInAccelerometer::SetRange(Range range) {
  if (range == kRange_16G) {
    throw FRC_MakeError(err::ParameterOutOfRange,
                        "16G range not supported (use k2G, k4G, or k8G)");
  }

  HAL_SetAccelerometerActive(false);
  HAL_SetAccelerometerRange(static_cast<HAL_AccelerometerRange>(range));
  HAL_SetAccelerometerActive(true);
}

double BuiltInAccelerometer::GetX() {
  return HAL_GetAccelerometerX();
}

double BuiltInAccelerometer::GetY() {
  return HAL_GetAccelerometerY();
}

double BuiltInAccelerometer::GetZ() {
  return HAL_GetAccelerometerZ();
}

void BuiltInAccelerometer::InitSendable(SendableBuilder& builder) {
  builder.SetSmartDashboardType("3AxisAccelerometer");
  builder.AddDoubleProperty(
      "X", [=]() { return GetX(); }, nullptr);
  builder.AddDoubleProperty(
      "Y", [=]() { return GetY(); }, nullptr);
  builder.AddDoubleProperty(
      "Z", [=]() { return GetZ(); }, nullptr);
}
