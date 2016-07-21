/*
      This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
      Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
      Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
      You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>.
 */

#include "libs/Module.h"
#include "libs/Kernel.h"
#include "PanelDue.h"
#include "communication/SerialConsole.h"

#include "version.h"
#include "checksumm.h"
#include "ConfigValue.h"
#include "Config.h"

#include <string>
// for parse_pins in mbed
#include "pinmap.h"

#define panel_checksum       CHECKSUM("panel")
#define enable_checksum      CHECKSUM("enable")
#define tx_pin_checksum      CHECKSUM("tx_pin")
#define rx_pin_checksum      CHECKSUM("tx_pin")
#define baud_rate_checksum   CHECKSUM("baud_rate")

PanelDue::PanelDue(){
}

PanelDue::~PanelDue(){
  delete this->serial;
}

void PanelDue::on_module_loaded(){
  // Exit if this module is not enabled
  if ( !THEKERNEL->config->value( panel_checksum, enable_checksum )->by_default(false)->as_bool() ) {
      delete this;
      return;
  }
  string tx_pin = THEKERNEL->config->value( panel_checksum, tx_pin_checksum)->by_default("nc")->as_string();
  string rx_pin = THEKERNEL->config->value( panel_checksum, rx_pin_checksum)->by_default("nc")->as_string();
  int baud_rate = THEKERNEL->config->value( panel_checksum, baud_rate_checksum)->by_default(9600)->as_number();
  tx_pin= "P" + tx_pin; // Pinnames need to be Px_x
  rx_pin= "P" + rx_pin; // Pinnames need to be Px_x
  
  this->serial = new SerialConsole(parse_pins(tx_pin.c_str()), parse_pins(rx_pin.c_str()), baud_rate);
}
