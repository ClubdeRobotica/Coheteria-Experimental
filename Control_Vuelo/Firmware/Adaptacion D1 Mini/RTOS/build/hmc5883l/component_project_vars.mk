# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/hmc5883l
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/hmc5883l -lhmc5883l
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += hmc5883l
COMPONENT_LDFRAGMENTS += 
component-hmc5883l-build: component-i2cdev-build component-log-build
