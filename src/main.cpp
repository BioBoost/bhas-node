#include "mbed_events.h"
#include "mbed.h"
#include "four_switch_node.h"
#include "local_echo_channel.h"

using BHAS::Nodes::FourSwitchNode;
using BHAS::Communication::Channels::LocalEchoChannel;

// using BHAS::Communication::Channels::CANChannel;
// CAN _canBus(D15, D14);
// CANChannel _canChannel(_canBus);

LocalEchoChannel localEchoChannel;
FourSwitchNode node(88, 1, localEchoChannel);       // TODO: Can we use sille's command thingy to configure for example this ID and gateway ID

int main() {
  ThisThread::sleep_for(2s);
  printf("... Booting BHAS node firmware ...\r\n");
  ThisThread::sleep_for(2s);

  node.take_over();
}