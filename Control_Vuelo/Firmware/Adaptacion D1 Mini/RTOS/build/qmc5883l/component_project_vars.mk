# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/qmc5883l
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/qmc5883l -lqmc5883l
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += qmc5883l
COMPONENT_LDFRAGMENTS += 
component-qmc5883l-build: component-i2cdev-build component-log-build
