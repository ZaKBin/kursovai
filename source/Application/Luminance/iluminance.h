#ifndef ILUMINANCE
#define ILUMINANCE

class ILuminance
{
public:
  virtual void Update(std::float_t filtredValue) = 0;
};

#endif