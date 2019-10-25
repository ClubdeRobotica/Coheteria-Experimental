# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/ds18x20
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/ds18x20 -lds18x20
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += ds18x20
COMPONENT_LDFRAGMENTS += 
component-ds18x20-build: component-onewire-build component-freertos-build component-log-build
