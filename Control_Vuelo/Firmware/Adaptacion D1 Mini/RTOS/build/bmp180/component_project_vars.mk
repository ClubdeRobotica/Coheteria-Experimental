# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/bmp180
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/bmp180 -lbmp180
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += bmp180
COMPONENT_LDFRAGMENTS += 
component-bmp180-build: component-i2cdev-build component-log-build
