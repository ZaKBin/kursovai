#ifndef IINTDATAPROVIDER
#define IINTDATAPROVIDER

class IIntDataProvider
{
public:
  virtual std::uint16_t ReadData() const = 0;
};

#endif