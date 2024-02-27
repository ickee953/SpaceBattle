TARGET_PLATFORM := android-3

ROOT_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE     := openal
LOCAL_ARM_MODE   := arm
LOCAL_PATH       := $(ROOT_PATH)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/include/AL $(LOCAL_PATH)/OpenAL32/Include \
					/Users/vetalpanov/development/android/android-ndk-r8b/sources/cxx-stl/stlport/stlport	\
					$(LOCAL_PATH)/ALUT	\
					
LOCAL_SRC_FILES  := OpenAL32/alAuxEffectSlot.c \
                    OpenAL32/alBuffer.c        \
                    OpenAL32/alDatabuffer.c    \
                    OpenAL32/alEffect.c        \
                    OpenAL32/alError.c         \
                    OpenAL32/alExtension.c     \
                    OpenAL32/alFilter.c        \
                    OpenAL32/alListener.c      \
                    OpenAL32/alSource.c        \
                    OpenAL32/alState.c         \
                    OpenAL32/alThunk.c         \
                    Alc/ALc.c                  \
                    Alc/alcConfig.c            \
                    Alc/alcEcho.c              \
                    Alc/alcModulator.c         \
                    Alc/alcReverb.c            \
                    Alc/alcRing.c              \
                    Alc/alcThread.c            \
                    Alc/ALu.c                  \
                    Alc/android.c              \
                    Alc/bs2b.c                 \
                    Alc/null.c                 \
                    ALUT/alutBufferData.c		\
                    ALUT/alutCodec.c			\
                    ALUT/alutError.c			\
                    ALUT/alutInit.c				\
                    ALUT/alutInputStream.c		\
                    ALUT/alutLoader.c			\
                    ALUT/alutOutputStream.c		\
                    ALUT/alutUtil.c				\
                    ALUT/alutVersion.c			\
                    ALUT/alutWaveform.c			\

LOCAL_CFLAGS     := -DAL_BUILD_LIBRARY -DAL_ALEXT_PROTOTYPES -Wno-psabi
LOCAL_LDLIBS     := -llog -Wl,-s

include $(BUILD_SHARED_LIBRARY)