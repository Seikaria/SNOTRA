#include "Switch.h"

Switch::Switch() {
  macTable = MacTable(DEFAULT_NUMBER_OF_INTERFACE);
}

Switch::Switch(int numberOfInterface) {
  macTable = MacTable(numberOfInterface);
}

Switch::~Switch() {
}

MacTable Switch::getMacTable() const {
  return macTable;
}

void Switch::setMacTable(MacTable macTable_) {
  macTable = macTable_;
}

void Switch::receiveFrame(std::shared_ptr<Frame> frame, int interfaceId) {
  Device::receiveFrame(frame, interfaceId);
  std::shared_ptr<DataLinkHeader> header = std::dynamic_pointer_cast<DataLinkHeader>(frame->getHeader());
  
  macTable.saveMac(header->getSource(), interfaceId);
  sendFrame(frame);
}

void Switch::sendFrame(std::shared_ptr<Frame> frame) {
  std::shared_ptr<DataLinkHeader> header = std::dynamic_pointer_cast<DataLinkHeader>(frame->getHeader());
  int temp = macTable.containsMac(header->getDestination());

  if(temp == 0) {
    Device::sendFrameBroadcast(frame, frame->getInterfaceId());
  }
  else {
    Device::sendFrameUnicast(frame, temp);
  }
}
