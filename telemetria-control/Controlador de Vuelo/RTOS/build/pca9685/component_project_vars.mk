# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/pca9685
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/pca9685 -lpca9685
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += pca9685
COMPONENT_LDFRAGMENTS += 
component-pca9685-build: component-i2cdev-build component-log-build
