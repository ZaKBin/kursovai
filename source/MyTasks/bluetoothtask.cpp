#include "bluetoothtask.h" // for BluetoothTask

void BluetoothTask::Execute()
{
  for(;;)
  {
    mTransmitDataUsart.WriteData(filtredValue);
    Sleep(1000ms);
  }
}

void BluetoothTask::FilteredValueUpdate(std::float_t value)
{
  filtredValue = value;
}