# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/tca95x5
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/tca95x5 -ltca95x5
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += tca95x5
COMPONENT_LDFRAGMENTS += 
component-tca95x5-build: component-i2cdev-build component-log-build
