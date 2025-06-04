#include "bluetoothtask.h" // for BluetoothTask


void BluetoothTask::Execute()
{
  for(;;)
  {
   const char* message = mFormatter.FormatString(filtredValue, 2, " V ");
    mTransmitDataUsart.WriteData(message);
    Sleep(100ms);
  }
}

void BluetoothTask::FilteredValueUpdate(std::float_t value)
{
  filtredValue = value;
}