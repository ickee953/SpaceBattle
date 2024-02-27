TARGET_PLATFORM := android-3

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE     := mp3Decoder
LOCAL_ARM_MODE   := arm

CAUDIO_PATH := $(LOCAL_PATH)/../cAudio

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/mpaudec \
					$(CAUDIO_PATH)/include \
					
LOCAL_SRC_FILES  := mpaudec/bits.c	\
					mpaudec/mpaudec.c	\
					src/cMP3Decoder.cpp	\
					src/main.cpp	\
					
LOCAL_CFLAGS     := -DAL_BUILD_LIBRARY -DAL_ALEXT_PROTOTYPES
LOCAL_LDLIBS     := -llog -Wl,-s -ldl -lGLESv1_CM

include $(BUILD_SHARED_LIBRARY)