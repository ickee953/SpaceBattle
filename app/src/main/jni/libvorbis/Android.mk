TARGET_PLATFORM := android-3

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := ogg
LOCAL_MODULE     := vorbis
LOCAL_ARM_MODE   := arm

LIBOGG_PATH := $(LOCAL_PATH)/../libogg
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/include/vorbis $(LOCAL_PATH)/src/books/coupled $(LOCAL_PATH)/src/books/floor $(LOCAL_PATH)/src/books/uncoupled $(LOCAL_PATH)/src/models \
					$(LIBOGG_PATH)/include \
					
					
LOCAL_SRC_FILES  := src/mdct.c	\
					src/smallft.c 	\
					src/block.c 	\
					src/envelope.c 	\
					src/window.c 	\
					src/lsp.c 		\
					src/lpc.c 		\
					src/analysis.c 	\
					src/synthesis.c \
					src/psy.c 		\
					src/info.c 		\
					src/floor1.c 	\
					src/floor0.c	\
					src/res0.c 		\
					src/mapping0.c 	\
					src/registry.c 	\
					src/codebook.c 	\
					src/sharedbook.c\
					src/lookup.c 	\
					src/bitrate.c	\
					src/envelope.h 	\
					src/lpc.h 		\
					src/lsp.h 		\
					src/codebook.h 	\
					src/misc.h 		\
					src/psy.h		\
					src/masking.h 	\
					src/os.h 		\
					src/mdct.h 		\
					src/smallft.h 	\
					src/highlevel.h	\
					src/registry.h 	\
					src/scales.h 	\
					src/window.h 	\
					src/lookup.h 	\
					src/lookup_data.h	\
					src/codec_internal.h \
					src/backends.h 		\
					src/bitrate.h	\
					src/vorbisfile.c	\ 
					

LOCAL_CFLAGS     := -DAL_BUILD_LIBRARY -DAL_ALEXT_PROTOTYPES
LOCAL_LDLIBS     := -llog -Wl,-s -ldl -lGLESv1_CM

include $(BUILD_SHARED_LIBRARY)