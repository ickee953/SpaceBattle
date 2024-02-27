LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := irrbullet
 
BULLET_PATH := $(LOCAL_PATH)/../bullet
LOCAL_C_INCLUDES := \
        $(BULLET_PATH)/ \
		$(BULLET_PATH)/BulletCollision \
		$(BULLET_PATH)/BulletCollision/BroadphaseCollision \
		$(BULLET_PATH)/BulletCollision/NarrowPhaseCollision \
		$(BULLET_PATH)/BulletCollision/CollisionDispatch \
		$(BULLET_PATH)/BulletCollision/CollisionShapes \
		$(BULLET_PATH)/BulletCollision/Gimpact \
		$(BULLET_PATH)/BulletSoftBody \
		$(BULLET_PATH)/BulletDynamics \
		$(BULLET_PATH)/BulletDynamics/Vehicle \
		$(BULLET_PATH)/BulletDynamics/ConstraintSolver \
		$(BULLET_PATH)/BulletDynamics/Dynamics \
		$(BULLET_PATH)/BulletDynamics/Character \
		$(BULLET_PATH)/LinearMath \
		$(IRRLICHT_PATH) \
		$(IRRLICHT_PATH)/aesGladman \
		$(IRRLICHT_PATH)/bzip2 \
		$(IRRLICHT_PATH)/jpeglib \
		$(IRRLICHT_PATH)/libpng \
		$(IRRLICHT_PATH)/lzma \
		$(IRRLICHT_PATH)/zlib \
		$(IRRLICHT_PATH)/include \
		$(LOCAL_PATH)
		
LOCAL_SRC_FILES := \
		boxshape.cpp \
		bulletworld.cpp \
		bvhtrianglemeshshape.cpp \
		collisioncallbackinformation.cpp \
		collisionobjectaffectorattract.cpp \
		collisionobjectaffector.cpp \
		collisionobjectaffectordelete.cpp \
		collisionobject.cpp \
		collisionshape.cpp \
		convexhullshape.cpp \
		gimpactmeshshape.cpp \
		irrbulletcommon.cpp \
		irrbullet.cpp \
		liquidbody.cpp \
		motionstate.cpp \
		physicsdebug.cpp \
		raycastvehicle.cpp \
		rigidbody.cpp \
		softbody.cpp \
		sphereshape.cpp \
		trianglemeshshape.cpp

LOCAL_SHARED_LIBRARIES := irrlicht bullet
LOCAL_ARM_MODE   := arm 
LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%) -O3 -DANDROID_NDK -DDISABLE_IMPORTGL 
LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)