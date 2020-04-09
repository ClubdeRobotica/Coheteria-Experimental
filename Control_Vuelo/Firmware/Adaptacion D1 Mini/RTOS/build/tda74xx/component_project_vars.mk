# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/tda74xx
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/tda74xx -ltda74xx
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += tda74xx
COMPONENT_LDFRAGMENTS += 
component-tda74xx-build: component-i2cdev-build component-log-build
