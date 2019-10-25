# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/max7219
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/max7219 -lmax7219
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += max7219
COMPONENT_LDFRAGMENTS += 
component-max7219-build: component-esp8266-build component-log-build
