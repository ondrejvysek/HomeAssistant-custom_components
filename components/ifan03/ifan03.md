# IFan 03 External Component

External Component for SonOff ifan 03

This has been changed as the custom components were removed from HA

example YAML:
```
esphome:
  name: ifan03

external_components:
  - source:
      type: local
      path: components

esp8266:
  board: esp8285


# Enable Home Assistant API
api:
  encryption:
    key: "your key"

ota:
  - platform: esphome
    password: "password"

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

web_server:

remote_receiver:
  pin: GPIO3

binary_sensor:
  - platform: gpio
    id: button
    pin:
      number: GPIO0
    on_press:
      then:
        - light.toggle: ifan03_light

  - platform: remote_receiver
    name: "Fan 0"
    id: remote_0
    raw:
      code: [-207, 104, -103, 104, -104, 103, -104, 207, -104, 103, -104, 104, -103, 104, -104, 103, -104, 105, -102, 104, -725, 104, -311, 103, -518, 104, -933, 103, -104, 104, -725, 104, -932, 104, -207, 207, -519]
    on_release:
      then:
        - fan.turn_off: ifan03_fan
    internal: true
  - platform: remote_receiver
    id: remote_fan1
    raw:
      code: [-207, 104, -104, 103, -104, 104, -103, 207, -104, 104, -103, 104, -104, 103, -104, 104, -103, 104, -104, 103, -726, 103, -312, 103, -518, 104, -933, 103, -104, 104, -725, 104, -103, 104, -726, 103, -104, 311, -518]
    on_release:
      then:
        - fan.turn_on:
              id: ifan03_fan
              speed: 1
    internal: true
  - platform: remote_receiver
    id: remote_fan2
    raw:
      code: [-208, 103, -104, 104, -103, 104, -103, 208, -103, 104, -104, 103, -104, 104, -103, 104, -104, 103, -104, 103, -726, 104, -310, 104, -518, 104, -933, 103, -104, 104, -725, 104, -207, 104, -622, 103, -416, 102, -415]
    on_release:
      then:
        - fan.turn_on:
              id: ifan03_fan
              speed: 2
    internal: true
  - platform: remote_receiver
    id: remote_fan3
    raw:
      code: [-207, 104, -104, 103, -104, 104, -103, 208, -103, 104, -104, 103, -104, 104, -103, 104, -104, 103, -104, 103, -726, 104, -311, 104, -518, 103, -934, 103, -103, 104, -726, 103, -104, 207, -622, 104, -103, 104, -207, 104, -415]
    on_release:
      then:
        - fan.turn_on:
              id: ifan03_fan
              speed: 3
    internal: true

  - platform: remote_receiver
    id: remote_light
    raw:
      code: [-207, 104, -103, 104, -104, 103, -104, 207, -104, 103, -104, 104, -103, 104, -103, 104, -104, 103, -104, 104, -725, 104, -311, 103, -518, 104, -933, 103, -104, 103, -726, 103, -311, 104, -518, 104, -207, 104, -103, 104, -414]
    on_release:
      then:
        - light.toggle: ifan03_light


output:
  - platform: ifan03
    id: fanoutput
  - platform: gpio
    pin: GPIO9
    id: relay_light
    inverted: true

light:
  - platform: binary
    name: "iFan03 Light"
    output: relay_light
    id: ifan03_light

switch:
  - platform: template
    id: update_fan_speed
    optimistic: true
    turn_on_action:
      then:
        - delay: 200ms
        - if:
            condition:
              and:
                - switch.is_off: relay_fan1
                - switch.is_off: relay_fan2
                - switch.is_off: relay_fan3
            then:
              - fan.turn_off: ifan03_fan
        - if:
            condition:
              and:
                - switch.is_on: relay_fan1
                - switch.is_off: relay_fan2
                - switch.is_off: relay_fan3
            then:
              - fan.turn_on:
                  id: ifan03_fan
                  speed: 1
        - if:
            condition:
              and:
                - switch.is_off: relay_fan1
                - switch.is_on: relay_fan2
                - switch.is_off: relay_fan3
            then:
              - fan.turn_on:
                  id: ifan03_fan
                  speed: 2
        - if:
            condition:
              and:
                - switch.is_off: relay_fan1
                - switch.is_off: relay_fan2
                - switch.is_on: relay_fan3
            then:
              - fan.turn_on:
                  id: ifan03_fan
                  speed: 3
        - switch.turn_off: update_fan_speed

  - platform: gpio
    pin: GPIO14
    id: relay_fan1
  - platform: gpio
    pin: GPIO12
    id: relay_fan2
  - platform: gpio
    pin: GPIO15
    id: relay_fan3

fan:
  - platform: speed
    output: fanoutput
    id: ifan03_fan
    name: "iFan03"
    speed_count: 3
```
