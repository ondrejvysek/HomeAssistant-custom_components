#include "esphome/core/defines.h"
#include "esphome/core/component.h"
#include "esphome/components/output/float_output.h"
#include "ifan03.h"

namespace esphome {
namespace ifan03 {

output::FloatOutput *ifan03_output_new() {
  auto *out = new IFan03Output();
  App.register_component(out);
  return out;
}

}  // namespace ifan03
}  // namespace esphome
