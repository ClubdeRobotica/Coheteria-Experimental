# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/ds3231
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/ds3231 -lds3231
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += ds3231
COMPONENT_LDFRAGMENTS += 
component-ds3231-build: component-i2cdev-build component-log-build
