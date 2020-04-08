# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/pcf8575
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/pcf8575 -lpcf8575
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += pcf8575
COMPONENT_LDFRAGMENTS += 
component-pcf8575-build: component-i2cdev-build component-log-build
