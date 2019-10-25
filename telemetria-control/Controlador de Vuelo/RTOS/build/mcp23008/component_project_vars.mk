# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/mcp23008
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/mcp23008 -lmcp23008
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += mcp23008
COMPONENT_LDFRAGMENTS += 
component-mcp23008-build: component-i2cdev-build component-log-build
