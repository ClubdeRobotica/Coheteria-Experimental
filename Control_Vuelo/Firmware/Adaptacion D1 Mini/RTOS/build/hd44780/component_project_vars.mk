# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/hd44780
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/hd44780 -lhd44780
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += hd44780
COMPONENT_LDFRAGMENTS += 
component-hd44780-build: component-esp8266-build component-freertos-build
