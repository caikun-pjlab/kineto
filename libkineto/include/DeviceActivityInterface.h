#pragma once

#include <atomic>
#include <functional>
#include <set>
#include <stdint.h>

#include "ActivityType.h"
#include "ITraceActivity.h"

namespace libkineto {

class ActivityLogger;

class DeviceActivityInterface {
 public:
  enum CorrelationFlowType {
    Default,
    User,
    End,
  };

  virtual ~DeviceActivityInterface() {}

  virtual void pushCorrelationID(uint64_t id, CorrelationFlowType type) = 0;
  virtual void popCorrelationID(CorrelationFlowType type) = 0;

  virtual void enableActivities(const std::set<ActivityType>& selectedActivities) = 0;
  virtual void disableActivities(const std::set<ActivityType>& selectedActivities) = 0;
  virtual void clearActivities() = 0;

  virtual void startTrace(const std::set<ActivityType>& selectedActivities) = 0;
  virtual void stopTrace(const std::set<ActivityType>& selectedActivities) = 0;
  virtual void teardownContext() = 0;
  virtual void setMaxBufferSize(int32_t size) = 0;

  virtual int32_t processActivities(ActivityLogger& logger,
                                    std::function<const ITraceActivity*(int32_t)> linkedActivity,
                                    int64_t startTime, int64_t endTime) = 0;

 public:
  std::atomic_bool stopCollection{false};
};

extern DeviceActivityInterface* device_activity_singleton;

} // namespace libkineto