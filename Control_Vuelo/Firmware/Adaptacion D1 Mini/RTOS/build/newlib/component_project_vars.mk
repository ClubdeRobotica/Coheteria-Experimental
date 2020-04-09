# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(IDF_PATH)/components/newlib/include $(IDF_PATH)/components/newlib/newlib/port/include $(IDF_PATH)/components/newlib/newlib/include
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/newlib $(IDF_PATH)/components/newlib/newlib/lib/libc_fnano.a $(IDF_PATH)/components/newlib/newlib/lib/libm.a -lnewlib -u _printf_float -u _scanf_float
COMPONENT_LINKER_DEPS += $(IDF_PATH)/components/newlib/newlib/lib/libc_fnano.a $(IDF_PATH)/components/newlib/newlib/lib/libm.a
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += newlib
COMPONENT_LDFRAGMENTS += 
component-newlib-build: 
