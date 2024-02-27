LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := spacebattle

LOCAL_SHARED_LIBRARIES := irrlicht bullet irrbullet openal

IRRLICHT_PATH := $(LOCAL_PATH)/../irrlicht
BULLET_PATH := $(LOCAL_PATH)/../bullet
SPACEBATTLE_PATH := $(LOCAL_PATH)/../spacebattle
SPACEBATTLEAUDIO_PATH := $(LOCAL_PATH)/audio
OPENAL_PATH := $(LOCAL_PATH)/../openal
VORBIS_PATH := $(LOCAL_PATH)/../libvorbis
OGG_PATH := $(LOCAL_PATH)/../libogg
MAD_PATH := $(LOCAL_PATH)/../libmad

LOCAL_C_INCLUDES := $(SPACEBATTLE_PATH) \
				$(SPACEBATTLE_PATH)/objects \
				$(SPACEBATTLE_PATH)/audio \
				$(IRRLICHT_PATH)/include \
				$(BULLET_PATH) \
				$(BULLET_PATH)/BulletCollision/BroadphaseCollision \
				$(BULLET_PATH)/BulletCollision/CollisionDispatch \
				$(BULLET_PATH)/BulletCollision/CollisionShapes \
				$(BULLET_PATH)/BulletCollision/NarrowPhaseCollision \
				$(BULLET_PATH)/BulletDynamics/ConstraintSolver \
				$(BULLET_PATH)/BulletDynamics/Dynamics \
				$(BULLET_PATH)/BulletDynamics/Vehicle \
				$(BULLET_PATH)/LinearMath \
				$(BULLET_PATH) \
				/Users/vetalpanov/development/android/android-ndk-r8b/platforms/android-5/arch-arm/usr/include \
				$(OPENAL_PATH)/include $(OPENAL_PATH)/include/AL $(OPENAL_PATH)/OpenAL32/Include \
				$(VORBIS_PATH)/include \
				$(OGG_PATH)/include \
				$(MAD_PATH) \

LOCAL_SRC_FILES := android-activity.cpp event-receiver.cpp objects/Camera.cpp objects/SpaceCar.cpp objects/GameWorld.cpp objects/Gun.cpp objects/GameObjectsManager.cpp	\
					#soundutil.cpp \
					#xzaudio/Data.cpp audio/OpenAlContext.cpp audio/Sound.cpp audio/SoundData.cpp audio/Vector3D.cpp \

LOCAL_CFLAGS := ${LOCAL_C_INCLUDES:%=-I%} -O3 -DANDROID_NDK -DDISABLE_IMPORTGL
LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog -lGLESv2 -Wl,-s

include $(BUILD_SHARED_LIBRARY)