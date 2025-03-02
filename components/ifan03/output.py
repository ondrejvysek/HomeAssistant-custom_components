import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID

# Create a namespace for your component
ifan03_ns = cg.esphome_ns.namespace("ifan03")
IFan03Output = ifan03_ns.class_("IFan03Output", output.FloatOutput, cg.Component)

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(IFan03Output),
})

def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])
    cg.add(var)
