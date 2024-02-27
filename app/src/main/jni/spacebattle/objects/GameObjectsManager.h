/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

#ifndef GAMEOBJECTSMANAGER_H
#define GAMEOBJECTSMANAGER_H

#include <irrlicht.h>
#include <event-receiver.h>
#include <SpaceCar.h>
#include <Camera.h>
#include <vector>
#include <Asteroid.h>

using namespace irr;
using namespace video;
using namespace std;
using namespace core;

namespace SpaceBattle {

class GameObjectsManager {
private:
	u32 timeStamp;
	u32 deltaTime;
	int counter;
	AndroidEventReceiver* receiver;
	SpaceCar* spaceCar;
	Camera* camera;

	//irrBullet
	irrBulletWorld* physicWorld;
	vector<Bullet> bullets;

	vector<Asteroid> asteroids;

public:
	GameObjectsManager(IVideoDriver* driver, IrrlichtDevice* device, ISceneManager* smgr, stringc path);
	~GameObjectsManager(){};

	void resize(int width, int height);
	void iterate(IrrlichtDevice* device, IVideoDriver* driver, ISceneManager* smgr);
	void move(ISceneNode* node, float speed);

	static bool shouldRemoveBullet(Bullet &b);
	void spaceCarTranslate();
	void asteroidsTranslate();

	bool collision(ISceneNode* one, ISceneNode* two);
};

}

#endif
