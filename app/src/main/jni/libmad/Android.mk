#ifeq ($(strip $(BUILD_WITH_GST)),true)

include $(CLEAR_VARS)

LOCAL_PATH:= $(call my-dir)

LOCAL_MODULE:= mad
#LOCAL_ARM_MODE := arm

OPENAL_PATH := $(LOCAL_PATH)/../openal

LOCAL_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/android	\
					$(OPENAL_PATH)/include $(OPENAL_PATH)/include/AL $(OPENAL_PATH)/OpenAL32/Include	\ 

LOCAL_SRC_FILES	:=	version.c \
					fixed.c \
					bit.c \
					timer.c \
					stream.c \
					frame.c  \
					synth.c \
					decoder.c \
					layer12.c \
					layer3.c \
					huffman.c

#LOCAL_SHARED_LIBRARIES := 

LOCAL_CFLAGS := -DHAVE_CONFIG_H -DFPM_DEFAULT 

include $(BUILD_SHARED_LIBRARY)

#endif