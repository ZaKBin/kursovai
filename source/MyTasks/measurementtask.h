#ifndef MEASUREMENTTASK
#define MEASUREMENTTASK

#include "thread.hpp" //For OsWrapper::Thread
#include "ifilter.h" // for IFilter
#include "iparametr.h" // for IParametr
#include "iluminance.h" // for ILuminance
#include "ifilternotifier.h" // for IFilterNotifier

using namespace OsWrapper;

class MeasurementTask : public OsWrapper::Thread<512U>
{
public:
  MeasurementTask(IFilter& filteredValue, IParametr& measuredValue, ILuminance& luminance, IFilterNotifier& filterNotifier) : 
    mFilteredValue(filteredValue), mMeasuredValue(measuredValue), mLuminance(luminance), mFilterNotifier(filterNotifier)
  {
    
  }
  
  virtual void Execute() override;
private:
  IFilter& mFilteredValue;
  IParametr& mMeasuredValue;
  ILuminance& mLuminance;
  IFilterNotifier& mFilterNotifier;
};

#endif