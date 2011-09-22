/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_TAOS_SENSOR_H
#define ANDROID_TAOS_SENSOR_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "nusensors.h"
#include "SensorBase.h"
#include "InputEventReader.h"

/*****************************************************************************/

#define PROX_FILE      "/data/misc/prox_data.txt"

struct input_event;

class TaosSensor : public SensorBase {
  const static uint DEBUG = 0;
  uint mEnabled;
  InputEventCircularReader mInputReader;
  uint32_t mPendingMask;
  
  float mPreviousLight;
  float mPreviousDistance;

  int mInitialised;
  
  int initialise();
  int setInitialState();
  float indexToValue(size_t index) const;

public:
  TaosSensor();
  virtual ~TaosSensor();
  virtual int readEvents(sensors_event_t* data, int count);
  virtual bool hasPendingEvents() const;
  virtual int enable(int32_t handle, int enabled);
  const static uint     Proximity   = 0;
  const static uint        Light       = 1;
  const static uint        numSensors = 2;
  sensors_event_t mPendingEvents[numSensors];
};

/*****************************************************************************/

#endif  // ANDROID_TAOS_SENSOR_H
