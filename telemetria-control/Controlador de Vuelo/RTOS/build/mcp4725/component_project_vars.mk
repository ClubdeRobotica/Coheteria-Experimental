# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/mcp4725
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/mcp4725 -lmcp4725
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += mcp4725
COMPONENT_LDFRAGMENTS += 
component-mcp4725-build: component-i2cdev-build component-log-build
