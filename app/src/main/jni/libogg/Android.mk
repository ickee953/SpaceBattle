TARGET_PLATFORM := android-3

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE     := ogg
LOCAL_ARM_MODE   := arm

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/include/ogg \
					
LOCAL_SRC_FILES  := src/bitwise.c 	\
					src/framing.c 	\

LOCAL_CFLAGS     := -DAL_BUILD_LIBRARY -DAL_ALEXT_PROTOTYPES
LOCAL_LDLIBS     := -llog -Wl,-s -ldl -lGLESv1_CM

include $(BUILD_SHARED_LIBRARY)