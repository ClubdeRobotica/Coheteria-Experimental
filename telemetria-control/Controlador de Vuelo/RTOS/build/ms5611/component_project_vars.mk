# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/ms5611
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/ms5611 -lms5611
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += ms5611
COMPONENT_LDFRAGMENTS += 
component-ms5611-build: component-i2cdev-build component-log-build
