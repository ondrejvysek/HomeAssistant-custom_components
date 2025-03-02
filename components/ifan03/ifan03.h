#pragma once
#include "esphome.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
namespace ifan03 {

class IFan03Output : public Component, public output::FloatOutput {
 public:
  void setup() override {
    // Initialize the GPIO pins
    pinMode(14, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(15, OUTPUT);
  }

  void write_state(float state) override {
    if (state < 0.3) {
      // OFF
      digitalWrite(14, LOW);
      digitalWrite(12, LOW);
      digitalWrite(15, LOW);
    } else if (state < 0.6) {
      // low speed
      digitalWrite(14, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(15, LOW);
    } else if (state < 0.9) {
      // medium speed
      digitalWrite(14, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(15, LOW);
    } else {
      // high speed
      digitalWrite(14, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(15, HIGH);
    }
  }
};

}  // namespace ifan03
}  // namespace esphome
