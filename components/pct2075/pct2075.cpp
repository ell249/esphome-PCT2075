// Implementation based on:
//  - ESPHome DHT12: https://github.com/esphome/esphome/tree/dev/esphome/components/dht12

#include "pct2075.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pct2075 {

static const char *const TAG = "pct2075";

void PCT2075Component::update() {
  uint16_t data[2];
  if (!this->read_data_(data)) {
    this->status_set_warning();
    return;
  }

  int16_t raw_temp = data[0];
  float temperature = (float)((raw_temp >> 5) * 0.125);


  ESP_LOGD(TAG, "Got temperature=%.2f°C ", temperature);
  if (this->temperature_sensor_ != nullptr)
    this->temperature_sensor_->publish_state(temperature);
  this->status_clear_warning();
}
void PCT2075Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up PCT2075...");
  uint16_t data[2];
  if (!this->read_data_(data)) {
    this->mark_failed();
    return;
  }
}
void PCT2075Component::dump_config() {
  ESP_LOGD(TAG, "PCT2075:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with PCT2075 failed!");
  }
  LOG_SENSOR("  ", "Temperature", this->temperature_sensor_);
}

float PCT2075Component::get_setup_priority() const { return setup_priority::DATA; }

bool PCT2075Component::read_data_(uint16_t *data) {
  if (!this->read_bytes_16(0, data, 1)) {
    ESP_LOGW(TAG, "Updating PCT2075 failed!");
    return false;
  }

  return true;
}

}  // namespace pct2075
}  // namespace esphome
