#ifndef PWM
#define PWM

#include <ipwm.h> // for IPWM
#include "tim3fieldvalues.hpp" // for TIM3 values
#include "tim3registers.hpp" // for TIM3 registers

class Pwm : public IPwm
{
public:
  void SetValue(std::float_t kz) override
  {
    auto valueCCR = static_cast<std::float_t>(TIM3::ARR::ARR_L::Get()) * kz;
    TIM3::CCR3::CCR3_L::Set(static_cast<uint16_t>(valueCCR));
  }
};

#endif