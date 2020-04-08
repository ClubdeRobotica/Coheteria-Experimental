# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/dht
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/dht -ldht
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += dht
COMPONENT_LDFRAGMENTS += 
component-dht-build: component-esp8266-build component-freertos-build
