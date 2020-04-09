# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/pcf8574
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/pcf8574 -lpcf8574
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += pcf8574
COMPONENT_LDFRAGMENTS += 
component-pcf8574-build: component-i2cdev-build component-log-build
