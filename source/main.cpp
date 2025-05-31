#include "rtos.hpp" // for Rtos
#include "mailbox.hpp" // for Mailbox
#include "event.hpp" // for Event
#include "rccregisters.hpp" // for RCC
#include "Application/Diagnostic/GlobalStatus.hpp"
#include "gpioaregisters.hpp" // for GPIOA
#include "gpiocregisters.hpp" // for GPIOC
#include "adc1registers.hpp" // for ADC1
#include "adccommonregisters.hpp" // for ADC
#include "tim3fieldvalues.hpp" // for TIM3 values
#include "tim3registers.hpp" // for TIM3 registers
#include "usart2fieldvalues.hpp" // for USART2
#include "usart2registers.hpp" // for USART2
#include "usart2data.h" // for usart2data
#include "transmitdatausart.h" // for TransmitDataUsart
#include "measurementtask.h"   // for MeasurementTask 
#include "bluetoothtask.h"  // for BluetoothTask
#include "voltage.h"  // for Voltage
#include "filter.h"   // for Filter
#include "luminance.h"   // for Luminance
#include "measurementadccode.h"   // for MeasurementADCCode
#include "pwm.h"   // for PWM

std::uint32_t SystemCoreClock = 16'000'000U;

extern "C" {
int __low_level_init(void)
{
//Switch on external 16 MHz oscillator
  RCC::CR::HSION::On::Set();
  // while (RCC::CR::HSIRDY::NotReady::IsSet())
  {

  }
  //Switch system clock on external oscillator
  RCC::CFGR::SW::Hsi::Set();
  // while (!RCC::CFGR::SWS::Hsi::IsSet())
  {

  }
  RCC::APB2ENR::SYSCFGEN::Enable::Set();
  RCC::APB1ENR::TIM3EN::Enable::Set();
  RCC::AHB1ENR::GPIOCEN::Enable::Set();
  RCC::APB2ENR::ADC1EN::Enable::Set();
  RCC::AHB1ENR::GPIOAEN::Enable::Set();
  RCC::APB1ENR::USART2EN::Enable::Set();

  GPIOC::MODER::MODER8::Alternate::Set();
  GPIOC::AFRH::AFRH8::Af2::Set();
  GPIOC::PUPDR::PUPDR8::NoPullUpNoPullDown::Set(); 
  GPIOC::OSPEEDR::OSPEEDR8::HighSpeed::Set();
  
  TIM3::CCMR2_Output::CC3S::Value0::Set();
  TIM3::CCMR2_Output::OC3M::Value6::Set();
  TIM3::CCMR2_Output::OC3PE::Value1::Set();
  TIM3::CR1::ARPE::Value1::Set();
  TIM3::ARR::ARR_H::Set(0U);
  TIM3::ARR::ARR_L::Set(2000U);
  TIM3::CCR3::CCR3_H::Set(0U);
  TIM3::CCR3::CCR3_L::Set(0U);
  TIM3::CCER::CC3P::Value0::Set();
  TIM3::CCER::CC3NP::Value0::Set();
  TIM3::CCER::CC3E::Value1::Set();
  TIM3::CR1::CEN::Value1::Set();
  
  ADC1::CR1::RES::Bits12::Set();
  ADC1::CR2::CONT::SingleConversion::Set();
  ADC1::CR2::EOCS::SingleConversion::Set();
  ADC1::SQR1::L::Conversions1::Set();
  ADC1::SQR3::SQ1::Channel0::Set();
  ADC1::SMPR2::SMP0::Cycles84::Set();
  GPIOA::MODER::MODER0::Analog::Set();
  ADC1::CR2::ADON::Enable::Set();
  
  GPIOA::MODER::MODER2::Alternate::Set(); 
  GPIOA::MODER::MODER3::Alternate::Set(); 
  GPIOA::OTYPER::OT2::OutputPushPull::Set();
  GPIOA::OTYPER::OT3::OutputPushPull::Set();
  GPIOA::PUPDR::PUPDR2::PullUp::Set(); 
  GPIOA::PUPDR::PUPDR3::PullUp::Set(); 
  
  GPIOA::AFRL::AFRL2::Af7::Set();
  GPIOA::AFRL::AFRL3::Af7::Set();
  
  USART2::BRR::DIV_Mantissa::Set(104);
  USART2::BRR::DIV_Fraction::Value2::Set();
  USART2::CR2::STOP::Value0::Set();
    
  USART2::CR1::OVER8::OversamplingBy16::Set(); 
  USART2::CR1::M::Data8bits::Set();
  
  USART2::CR1::TE::Enable::Set();
  USART2::CR1::UE::Enable::Set();
  USART2::SR::TC::TransmitionNotComplete::Set();
  
  return 1;
}
}

constexpr std::float_t dt = 0.1f ;
constexpr std::float_t rc = 10.0f;
constexpr std::float_t maxVoltageValue = 3.3f ;
constexpr std::float_t k = 0.000806f ;
constexpr std::float_t offset = 0.000806f ;

MeasurementADCCode mADCCode;
Pwm pwm;
Voltage<k, offset> voltage(mADCCode);
Usart2Data usart2Data;
TransmitDataUsart transmitDataUsart(usart2Data);
Filter<dt, rc> filter;
Luminance<maxVoltageValue> lumin(pwm);
BluetoothTask bluetoothTask(transmitDataUsart);
MeasurementTask measurementTask(filter, voltage, lumin, bluetoothTask);


int main()
{
  using namespace OsWrapper;
  Rtos::CreateThread(measurementTask, "MeasurementTask", ThreadPriority::priorityMax);
  Rtos::CreateThread(bluetoothTask, "BluetoothTask", ThreadPriority::lowest);
  Rtos::Start();
  return 0;
}
