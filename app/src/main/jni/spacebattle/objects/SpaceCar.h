/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

#ifndef SPACECAR_H
#define SPACECAR_H

#include "event-receiver.h"
#include <btBulletDynamicsCommon.h>
#include "../irrBullet/irrbullet.h"
#include "Gun.h"
//#include <cAudio.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
//using namespace cAudio;

namespace SpaceBattle{

class SpaceCar{

private:
	stringc modelFileName;
	stringc textureFileName;

	IrrlichtDevice* device;
	ISceneManager* sceneManager;
	IVideoDriver* driver;
	AndroidEventReceiver* receiver;

	irrBulletWorld* world;

	//stringc shootSound;
	//IAudioManager* audioManager;
	//IAudioSource* shootSound;
	//IListener* audioListener;

	int localCounter;

	static const f32 MOVEMENT_MAX_SPEED = 80.f;
	f32 maxSpeed;
	u32 mass;
	array<Bullet> bullets;
public:
	IRigidBody *rigidBody;
	IAnimatedMeshSceneNode* node;

	SpaceCar(IrrlichtDevice* device, irrBulletWorld* world, IVideoDriver* driver, ISceneManager* smgr);
	~SpaceCar();

	void init();
	void resize(float width, float height);
	//void pause();
	void setEventReceiver(AndroidEventReceiver* receiver);

	void iterate();
	ISceneNode* getNode();

	vector3df getPosition();
	void setPosition(vector3df position);

	vector3df getScale();
	void setScale(vector3df scale);

	void shoot();
	void move();
};

}
#endif
