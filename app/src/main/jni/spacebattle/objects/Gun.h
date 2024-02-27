/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, July 2017
 */

#ifndef GUN_H
#define GUN_H

#include <irrlicht.h>
#include "../irrBullet/irrbullet.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;

namespace SpaceBattle{

class Bullet{
public:
	ISceneNode *node;
	vector3df pos, vel;
	bool active;

	Bullet(stringc dataDir, ISceneManager* smgr, IVideoDriver* driver){
		node = smgr->addLightSceneNode(0, pos, SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);
		node = smgr->addBillboardSceneNode(node, core::dimension2d<f32>(50, 50));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
		node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		node->setMaterialTexture(0, driver->getTexture((dataDir+"/portal2.bmp").c_str()));
		active = false;
	}
	~Bullet(){
		active = false;
	}

	void update(){
		pos += vel;
		//vel *= 0.99; // slowdown in a long time

		node->setPosition(pos);
	}
};

/*class Gun{
private:
	stringc dataDir;
	irrBulletWorld* world;
	ISceneManager* sceneManager;
	IVideoDriver* driver;
	IAnimatedMeshSceneNode* parent;

public:
	ISceneNode* node;

	Gun(stringc dataDir, irrBulletWorld* world, ISceneManager* smgr, IVideoDriver* driver, IAnimatedMeshSceneNode* parent);
	~Gun();

	ISceneNode* getNode();

	void createBullets();
	void move(ISceneNode* node, float speed);
	//Bullet shoot();
	void shoot();
};
*/

}
#endif
