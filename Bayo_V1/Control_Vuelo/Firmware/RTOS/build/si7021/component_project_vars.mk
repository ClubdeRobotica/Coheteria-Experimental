# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/si7021
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/si7021 -lsi7021
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += si7021
COMPONENT_LDFRAGMENTS += 
component-si7021-build: component-i2cdev-build component-log-build
