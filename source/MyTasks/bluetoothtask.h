#ifndef BLUETOOTHTASK
#define BLUETOOTHTASK

#include "thread.hpp" //For OsWrapper::Thread
#include "transmitdatausart.h" // for TransmitDataUsart
#include "ifilternotifier.h" // for IFilterNotifier
#include "IFormatter.h"

using namespace OsWrapper;

class BluetoothTask : public OsWrapper::Thread<512U>, public IFilterNotifier
{
public:
  BluetoothTask(TransmitDataUsart& transmitDataUsart, IFormatter& formatter) : 
    mTransmitDataUsart(transmitDataUsart), mFormatter(formatter)
  {
    
  }
  
  virtual void Execute() override;
  virtual void FilteredValueUpdate(std::float_t value) override;
private:
  IFormatter& mFormatter;
  TransmitDataUsart& mTransmitDataUsart;
  std::float_t filtredValue;
};

#endif