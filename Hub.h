#ifndef __HUB_H__
#define __HUB_H__

#include <memory>
#include <list>
#include "Device.h"
#include "Frame.h"

class Device;

class Hub : public Device {
 public:
  Hub();
  virtual ~Hub();
  void receiveFrame(std::shared_ptr<Frame>);
  void sendFrame(std::shared_ptr<Frame>);
  std::list<std::shared_ptr<Device>> getNeighbours();
  void addNeighbour(std::shared_ptr<Device>);

 private:
  std::list<std::shared_ptr<Device>> neighbours;

};

#endif