#ifndef BLUETOOTHTASK
#define BLUETOOTHTASK

#include "thread.hpp" //For OsWrapper::Thread
#include "transmitdatausart.h" // for TransmitDataUsart
#include "ifilternotifier.h" // for IFilterNotifier

using namespace OsWrapper;

class BluetoothTask : public OsWrapper::Thread<512U>, public IFilterNotifier
{
public:
  BluetoothTask(TransmitDataUsart& transmitDataUsart) : 
    mTransmitDataUsart(transmitDataUsart)
  {
    
  }
  
  virtual void Execute() override;
  virtual void FilteredValueUpdate(std::float_t value) override;
private:
  TransmitDataUsart& mTransmitDataUsart;
  std::float_t filtredValue;
};

#endif