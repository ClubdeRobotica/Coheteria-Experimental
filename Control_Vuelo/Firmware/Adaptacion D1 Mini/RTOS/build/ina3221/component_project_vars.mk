# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/ina3221
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/ina3221 -lina3221
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += ina3221
COMPONENT_LDFRAGMENTS += 
component-ina3221-build: component-i2cdev-build component-log-build
