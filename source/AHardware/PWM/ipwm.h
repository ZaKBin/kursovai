#ifndef IPWM
#define IPWM

class IPwm
{
public:
  virtual void SetValue(float kz) = 0;
};

#endif