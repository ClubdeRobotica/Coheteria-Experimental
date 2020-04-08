# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/mqtt/include $(IDF_PATH)/components/mqtt/ibm-mqtt/MQTTClient-C/src $(IDF_PATH)/components/mqtt/ibm-mqtt/MQTTClient-C/src/FreeRTOS $(IDF_PATH)/components/mqtt/ibm-mqtt/MQTTPacket/src
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/mqtt -lmqtt
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += mqtt
component-mqtt-build: 
