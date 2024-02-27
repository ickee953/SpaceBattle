/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

#include <jni.h>
#include <android/log.h>
#include <GameWorld.h>

using namespace io;
using namespace SpaceBattle;

int  gAppAlive   = 1;
GameWorld* gameWorld = NULL;

/* For JNI: C++ compiler need this */
extern "C" {

/** Activity onCreate */
void Java_su_panov_irrlicht_NativeIrrlichtActivity_nativeOnCreate( JNIEnv*  env )
{
	gameWorld = new GameWorld();
}

/** Activity onPause */
void Java_su_panov_irrlicht_NativeIrrlichtActivity_nativeOnPause( JNIEnv*  env )
{
	gameWorld->pause();
}

/** Activity onResume */
void Java_su_panov_irrlicht_NativeIrrlichtActivity_nativeOnResume( JNIEnv*  env )
{
	gameWorld->resume();
}

/** Activity onDestroy */
void Java_su_panov_irrlicht_NativeIrrlichtActivity_nativeOnDestroy( JNIEnv*  env )
{
	gameWorld->destroy();
}

void Java_com_alesdi_irrlicht_NativeIrrlichtActivity_nativeInitGL( JNIEnv*  env )
{
	gameWorld->init();
}

void Java_su_panov_irrlicht_NativeIrrlichtActivity_nativeResize( JNIEnv*  env, jobject  thiz, jint w, jint h )
{
	gameWorld->graphicsResize(w, h);
}

void Java_su_panov_irrlicht_NativeIrrlichtActivity_nativeSendTouchEvent( JNIEnv*  env, jobject defaultObj, jobject event)
{
    jclass classEvent = env->GetObjectClass(event);
    jfieldID fieldPointerCount = env->GetFieldID(classEvent, "pointerCount", "I");
    jfieldID fieldActivePid = env->GetFieldID(classEvent, "activePid", "I");
    jfieldID fieldAction0 = env->GetFieldID(classEvent, "action0", "I");
    jfieldID fieldAction1 = env->GetFieldID(classEvent, "action1", "I");
    jfieldID fieldPid0 = env->GetFieldID(classEvent, "pid0", "I");
    jfieldID fieldPid1 = env->GetFieldID(classEvent, "pid1", "I");
    jfieldID fieldX0 = env->GetFieldID(classEvent, "x0", "I");
    jfieldID fieldY0 = env->GetFieldID(classEvent, "y0", "I");
    jfieldID fieldX1 = env->GetFieldID(classEvent, "x1", "I");
    jfieldID fieldY1 = env->GetFieldID(classEvent, "y1", "I");

    int pointerCount = env->GetIntField(event, fieldPointerCount);
    int activePid = env->GetIntField(event, fieldActivePid);
    int action0 = env->GetIntField(event, fieldAction0);
    int action1 = env->GetIntField(event, fieldAction1);
    int pid0 = env->GetIntField(event, fieldPid0);
    int pid1 = env->GetIntField(event, fieldPid1);
    int x0 = env->GetIntField(event, fieldX0);
    int y0 = env->GetIntField(event, fieldY0);
    int x1 = env->GetIntField(event, fieldX1);
    int y1 = env->GetIntField(event, fieldY1);

    gameWorld->sendTouchEvent(pointerCount, activePid, pid0, pid1, action0, action1, x0, y0, x1, y1);
}

void Java_su_panov_irrlicht_NativeIrrlichtActivity_nativeSendAccelerometerEvent( JNIEnv*  env, jobject defaultObj, jobject event){
	jclass classEvent = env->GetObjectClass(event);

	jfieldID fieldX = env->GetFieldID(classEvent, "xRotation", "F");
	jfieldID fieldY = env->GetFieldID(classEvent, "yRotation", "F");

	float x = env->GetFloatField(event, fieldX);
	float y = env->GetFloatField(event, fieldY);
	float z = 0;

	gameWorld->sendAccelerometerEvent( x, y, z );
}

void Java_su_panov_irrlicht_NativeIrrlichtActivity_nativeGetStatus(JNIEnv*  env, jobject defaultObj, jobject status)
{
    if (gAppAlive==0) {
        jclass classStatus = env->GetObjectClass(status);
        jfieldID fieldStatus = env->GetFieldID(classStatus, "mQuit", "Z");
        env->SetBooleanField(status, fieldStatus, true);
    }
}

void Java_su_panov_irrlicht_NativeIrrlichtActivity_nativeEnvJ2C(JNIEnv*  env, jobject defaultObj, jstring jsdcardPath)
{
    char ligne[1024+1];
    const char *msg = env->GetStringUTFChars(jsdcardPath,0);
    stringc path = msg;
    //gameWorld->setPath(path);
    //__android_log_print(ANDROID_LOG_INFO, "Irrlicht", "not handled %s", (gameWorld->getPath()).c_str());
    env->ReleaseStringUTFChars(jsdcardPath,msg);
}

void Java_su_panov_irrlicht_NativeIrrlichtActivity_nativeDrawIteration( JNIEnv*  env )
{
	gameWorld->iterate();
}

}
