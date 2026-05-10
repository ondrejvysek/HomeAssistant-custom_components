#pragma once

#include "esphome/core/component.h"
#include "esphome/components/output/float_output.h"
#include <Arduino.h>

namespace esphome {
namespace ifan03 {

class IFan03Output : public output::FloatOutput, public Component {
 public:
  void setup() override {
    pinMode(14, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(15, OUTPUT);

    digitalWrite(14, LOW);
    digitalWrite(12, LOW);
    digitalWrite(15, LOW);
  }

 protected:
  void write_state(float state) override {
    if (state < 0.3f) {
      digitalWrite(14, LOW);
      digitalWrite(12, LOW);
      digitalWrite(15, LOW);
    } else if (state < 0.6f) {
      digitalWrite(14, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(15, LOW);
    } else if (state < 0.9f) {
      digitalWrite(14, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(15, LOW);
    } else {
      digitalWrite(14, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(15, HIGH);
    }
  }
};

}  // namespace ifan03
}  // namespace esphome
