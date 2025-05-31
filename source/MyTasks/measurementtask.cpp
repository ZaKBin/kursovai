#include "measurementtask.h" // for MeasurementTask
#include "tim3fieldvalues.hpp" // for TIM3 values
#include "tim3registers.hpp" // for TIM3 registers

void MeasurementTask::Execute()
{
  for(;;)
  {
    Sleep(50ms);
    auto measurementVariable1 = mMeasuredValue.Measure();
    Sleep(50ms);
    auto measurementVariable2 = mMeasuredValue.Measure();
    auto measurementVariableSum = (measurementVariable1 + measurementVariable2)/2.0f;
    auto filteredVoltage = mFilteredValue.FilterValue(measurementVariableSum);
    mLuminance.Update(filteredVoltage);
    mFilterNotifier.FilteredValueUpdate(filteredVoltage);
  }
} ;