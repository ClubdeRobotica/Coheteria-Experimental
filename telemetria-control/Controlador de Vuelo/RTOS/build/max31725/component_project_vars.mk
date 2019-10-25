# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/max31725
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/max31725 -lmax31725
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += max31725
COMPONENT_LDFRAGMENTS += 
component-max31725-build: component-i2cdev-build component-log-build
