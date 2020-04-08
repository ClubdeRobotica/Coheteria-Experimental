# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/ds1302
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/ds1302 -lds1302
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += ds1302
COMPONENT_LDFRAGMENTS += 
component-ds1302-build: component-esp8266-build component-freertos-build component-esp_idf_lib_helpers-build
