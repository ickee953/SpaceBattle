#APP_MODULES := irrlicht bullet irrbullet openal ogg vorbis mad spacebattle
APP_MODULES := irrlicht bullet irrbullet openal spacebattle
APP_STL := stlport_static
#APP_OPTIM := release
APP_OPTIM := debug
APP_CFLAGS := -DDEBUG
APP_CPPFLAGS += -frtti # -fexceptions
APP_ABI := armeabi
LOCAL_ARM_MODE := thumb