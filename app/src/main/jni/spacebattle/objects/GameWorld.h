/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <irrlicht.h>
#include "../irrBullet/irrbullet.h"
#include <GameObjectsManager.h>

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

namespace SpaceBattle{

class GameWorld{

private:
	u32 time;
	stringc path;

	GameObjectsManager* gameObjectsManager;
	ITexture* terrainMap;

public:
	int static const DEFAULT_SCREEN_WIDTH  = 480;
	int static const DEFAULT_SCREEN_HEIGHT = 320;
	int static const GROUND_WIDTH = 1000;
	int static const GROUND_HEIGHT = 1000;

	GameWorld(stringc path = "/sdcard/Irrlicht/");
	virtual ~GameWorld();

	bool init();
	bool initGraphics(dimension2d<u32> screenSize  = dimension2d<u32>(DEFAULT_SCREEN_WIDTH , DEFAULT_SCREEN_HEIGHT), E_DRIVER_TYPE driver = EDT_OGLES1 );
	bool initPhysics();
	void initLights();
	void graphicsResize(int w, int h);

	void createGround();
	void generateTerrain();
	void addPortal(vector3df pos, ISceneManager* sceneManager);
	void createMap();

	void iterate();
	void sendTouchEvent(int pointerCount, int activePid, int pid0, int pid1, int action0, int action1, int x0, int y0, int x1, int y1);
	//void sendAccelerometerEvent( float y, int direction );
	void sendAccelerometerEvent( float x, float y, float z );
	void pause();
	void resume();

	bool cleanupGraphics();
	bool cleanupPhysics();
	void destroy();

	void setPath(stringc path);
	stringc getPath();
protected:
	//Irrlicht engine
	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* smgr;
};
}
#endif
