#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace pct2075 {

#define PCT2075_REGISTER_TEMP 0x00   ///<  Temperature register (read-only)
#define PCT2075_REGISTER_CONFIG 0x01 ///<  Configuration register
#define PCT2075_REGISTER_THYST 0x02  ///<  Hysterisis register
#define PCT2075_REGISTER_TOS 0x03    ///<  OS register
#define PCT2075_REGISTER_TIDLE 0x04 ///< Measurement idle time register

class PCT2075Component : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void update() override;

  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { temperature_sensor_ = temperature_sensor; }

 protected:
  bool read_data_(uint16_t *data);

  sensor::Sensor *temperature_sensor_;
};

}  // namespace pct2075
}  // namespace esphome
