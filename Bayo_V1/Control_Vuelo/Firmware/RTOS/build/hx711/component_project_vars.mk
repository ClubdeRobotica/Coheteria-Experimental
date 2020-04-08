# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/hx711
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/hx711 -lhx711
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += hx711
COMPONENT_LDFRAGMENTS += 
component-hx711-build: component-esp8266-build component-freertos-build
