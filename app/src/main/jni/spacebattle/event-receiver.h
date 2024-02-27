/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

#ifndef _event-receiver_h_included_
#define _event-receiver_h_included_
#include <irrlicht.h>

using namespace irr;

struct SAppContext{
	float width;
	float height;
};

struct SSpaceCarTouchEvent{
	bool fire;
	bool move;
};

struct SSpaceCarRotationEvent{
	float rotationValueX;
	float rotationValueY;
	float rotationValueZ;

	bool changeRotation;
};

class AndroidEventReceiver : public IEventReceiver
{
public:
	SSpaceCarTouchEvent spaceCarTouchEvent;
	SSpaceCarRotationEvent spaceCarRotationEvent;

	AndroidEventReceiver(const SAppContext& context){
		spaceCarTouchEvent.fire = false;
		spaceCarTouchEvent.move = false;
		spaceCarRotationEvent.changeRotation = false;
		spaceCarRotationEvent.rotationValueX = 0.0;
		spaceCarRotationEvent.rotationValueY = 0.0;
		spaceCarRotationEvent.rotationValueZ = 0.0;

		this->screenWidth = context.width;
		this->screenHeight = context.height;
	}

	AndroidEventReceiver(float width, float height){
		spaceCarTouchEvent.fire = false;
		spaceCarTouchEvent.move = false;
		spaceCarRotationEvent.changeRotation = false;
		spaceCarRotationEvent.rotationValueX = 0.0;
		spaceCarRotationEvent.rotationValueY = 0.0;
		spaceCarRotationEvent.rotationValueZ = 0.0;

		this->screenWidth = width;
		this->screenHeight = height;
	}

	void resize(float width, float height);
	virtual bool OnEvent(const SEvent& event);
	private:
		float screenWidth;
		float screenHeight;
};
#endif
