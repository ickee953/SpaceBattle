LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE     := caudio

LOCAL_SHARED_LIBRARIES := openal vorbis mp3Decoder 

OPENAL_PATH := $(LOCAL_PATH)/../openal
LIBOGG_PATH := $(LOCAL_PATH)/../libogg
LIBVORBIS_PATH:= $(LOCAL_PATH)/../libvorbis
MP3DECODER_PATH := $(LOCAL_PATH)/../mp3Decoder

LOCAL_C_INCLUDES := $(OPENAL_PATH)/include $(OPENAL_PATH)/include/AL $(OPENAL_PATH)/OpenAL32/Include \
					$(LOCAL_PATH)/include $(LOCAL_PATH)/Headers \
					$(LIBOGG_PATH)/include \
					$(LIBVORBIS_PATH)/include $(LIBVORBIS_PATH)/src/books/coupled $(LIBVORBIS_PATH)/src/books/floor $(LIBVORBIS_PATH)/src/books/uncoupled $(LIBVORBIS_PATH)/src/models \
					$(MP3DECODER_PATH)/include $(MP3DECODER_PATH)/mpaudec \
					/Users/vetalpanov/development/android/android-ndk-r8b/sources/cxx-stl/stlport/stlport	\
					
LOCAL_SRC_FILES  := src/cAudio.cpp	\
					src/cAudioCapture.cpp	\
					src/cAudioEffects.cpp	\
					src/cAudioManager.cpp	\
					src/cAudioMemory.cpp	\
					src/cAudioSleep.cpp		\
					src/cAudioSource.cpp	\
					src/cConsoleLogReceiver.cpp	\
					src/cEffect.cpp			\
					src/cFileLogReceiver.cpp	\
					src/cFileSource.cpp		\
					src/cFilter.cpp			\
					src/cListener.cpp		\
					src/cLogger.cpp			\
					src/cMemorySource.cpp	\
					src/cMemoryTracker.cpp	\
					src/cMutex.cpp			\
					src/cOggAudioDecoderFactory.cpp	\
					src/cOggDecoder.cpp		\
					src/cOpenALAudioDeviceList.cpp	\
					src/cOpenALDeviceContext.cpp	\
					src/cPluginManager.cpp	\
					src/cRawDecoder.cpp		\
					src/cStandardMemoryProvider.cpp	\
					src/cThread.cpp			\
					src/cWavAudioDecoderFactory.cpp	\
					src/cWavDecoder.cpp	\

LOCAL_CFLAGS     := ${LOCAL_C_INCLUDES:%=-I%} -O3 -DANDROID_NDK -DDISABLE_IMPORTGL -DAL_BUILD_LIBRARY -DAL_ALEXT_PROTOTYPES
#LOCAL_CFLAGS     := ${LOCAL_C_INCLUDES:%=-I%}
LOCAL_LDLIBS     := -llog -Wl,-s -ldl 

include $(BUILD_SHARED_LIBRARY)