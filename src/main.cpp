#include "mbed_events.h"
#include "mbed.h"
#include "four_switch_node.h"
#include "relay_node.h"
#include "local_echo_channel.h"
#include "version.h"
#include "mbed_trace.h"
#include "configuration_manager.h"
#include "command_manager.h"

#if defined(TARGET_NUCLEO_L476RG) || defined(TARGET_LPC1768)
#include "can_channel.h"
using BHAS::Communication::Channels::CANChannel;
#endif

#define TRACE_GROUP "BHAS Node main"

using BHAS::Nodes::FourSwitchNode;
using BHAS::Nodes::RelayNode;
using BHAS::Communication::Channels::LocalEchoChannel;
using BHAS::ConfigurationManager;
using BHAS::CommandManager;

int main() {
  mbed_trace_init();

  tr_info("Booting BHAS node firmware");
  tr_info("Firmware version: %s", BHAS_FIRMWARE_VERSION);
  tr_info("Target: %s", MBED_STRINGIFY(TARGET_NAME));

#ifdef MBED_CONF_RTOS_PRESENT
  const char* profile = "rtos";
#else
  const char* profile = "bare-metal";
#endif
  tr_info("Mbed OS version: %d.%d.%d (profile: %s)", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION, profile);
    
  ConfigurationManager config;
  config.init();
  tr_info("This device has booted %lu times", config.boot_count());

  bool startCommandManager = config.double_reset();
  if (startCommandManager) tr_info("Detected double reset");

  config.set_double_reset();
  ThisThread::sleep_for(2s);    // Basically if we reset within this time window, command manager is started
  config.clear_double_reset();

  if(startCommandManager) {
    LowPowerTimer consoleTimeout;
    consoleTimeout.start();
    CommandManager commandManager(config);
    commandManager.on_command([&consoleTimeout] () { consoleTimeout.reset(); });

    while(consoleTimeout.elapsed_time() < std::chrono::seconds(MBED_CONF_APP_COMMAND_CONSOLE_TIMEOUT)) {
      commandManager.dispatch();
    }
  }

#if defined(TARGET_NUCLEO_L476RG)
  CAN canBus(D15, D14);
  CANChannel channel(canBus);
#elif defined(TARGET_LPC1768)
  CAN canBus(p30, p29);
  CANChannel channel(canBus);
#else
  LocalEchoChannel channel;
#endif

  FourSwitchNode node(config.node_id(), config.gateway_id(), channel);
  // RelayNode node(config.node_id(), config.gateway_id(), localEchoChannel);

  tr_info("Passing control to node");
  node.dispatch_forever();
}