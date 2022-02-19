# esphome-PCT2075

Very basic component for esphome to fetch temperature in celcius from a PCT2075.

Based off the official dht12 temp/humidity sensor library.

## Installation

Add the pct2075 folder to your esphome components directory to install.

Add to your esphome yaml sensor block:
```
sensor:
  - platform: pct2075
    temperature:
      name: "PCT2075 Temperature"
    update_interval: 30s
```
