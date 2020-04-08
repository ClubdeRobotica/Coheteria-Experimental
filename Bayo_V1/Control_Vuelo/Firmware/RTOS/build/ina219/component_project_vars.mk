# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/ina219
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/ina219 -lina219
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += ina219
COMPONENT_LDFRAGMENTS += 
component-ina219-build: component-i2cdev-build component-log-build
