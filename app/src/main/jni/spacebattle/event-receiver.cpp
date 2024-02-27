/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

#include "event-receiver.h"
#include <android/log.h>

bool AndroidEventReceiver::OnEvent(const SEvent& event)
{
	if( event.EventType == EET_ANDROID_TOUCH_EVENT ){
		int x = event.AndroidTouchEvent.x;

		__android_log_print(ANDROID_LOG_INFO, "TouchEvent", "x = %d", x);
		if( event.AndroidTouchEvent.action == E_ANDROID_TOUCH_DOWN ){
			if( x>this->screenWidth/2 ){
				__android_log_print(ANDROID_LOG_INFO, "TouchEvent", "space car fire start");
				spaceCarTouchEvent.fire = true;
			} else if ( x<this->screenWidth/2 ) {
				__android_log_print(ANDROID_LOG_INFO, "TouchEvent", "space car speed start");
				spaceCarTouchEvent.move = true;
			}
		} else if( event.AndroidTouchEvent.action == E_ANDROID_TOUCH_UP ){
			if( x>this->screenWidth/2 ){
				__android_log_print(ANDROID_LOG_INFO, "TouchEvent", "space car fire stop");
				spaceCarTouchEvent.fire = false;
			} else if ( x<this->screenWidth/2 ) {
				__android_log_print(ANDROID_LOG_INFO, "TouchEvent", "space car speed stop");
				spaceCarTouchEvent.move = false;
			}
		}
	}
	if( event.EventType == EET_ANDROID_ACCELEROMETER_EVENT ){
		float x = event.AndroidAccelerometerEvent.x;
		float y = event.AndroidAccelerometerEvent.y;
		float z = event.AndroidAccelerometerEvent.z;

		__android_log_print(ANDROID_LOG_INFO, "AccelerometerEvent", "y = %f", y);

		spaceCarRotationEvent.changeRotation = true;
		spaceCarRotationEvent.rotationValueX = x;
		spaceCarRotationEvent.rotationValueY = y;
		spaceCarRotationEvent.rotationValueZ = z;
	}
    return false;
}

void AndroidEventReceiver::resize(float width, float height){
	this->screenWidth = width;
	this->screenHeight = height;
}
