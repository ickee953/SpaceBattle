/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

#include "GameWorld.h"
#include <android/log.h>
#include <noise.h>

using namespace SpaceBattle;

/* engine manager methoods*/
int importGLInit();
void importGLDeinit();

GameWorld::GameWorld(stringc path):device(0), driver(0), smgr(0){
	setPath(path);
}

GameWorld::~GameWorld(){
	cleanupGraphics();
}

bool GameWorld::initGraphics(dimension2d<u32> screenSize, E_DRIVER_TYPE driver){
	importGLInit();

	this->device = createDevice( driver, screenSize, 16, false, true);
	__android_log_print(ANDROID_LOG_INFO, "Irrlicht", "createDevice r=%d w=%d h=%d", device, screenSize.Width, screenSize.Height);

	this->driver = device->getVideoDriver();
	__android_log_print(ANDROID_LOG_INFO, "Irrlicht", "getVideoDriver r=%d", driver);

	if (!device){
		__android_log_print(ANDROID_LOG_INFO, "Irrlicht", "No device");
		return false;
	}
	if (!driver){
		__android_log_print(ANDROID_LOG_INFO, "Irrlicht", "No driver");
		return false;
	}

	smgr = device->getSceneManager();
	device->getFileSystem()->changeWorkingDirectoryTo(path.c_str());

	return true;
}

bool GameWorld::cleanupGraphics(){
	smgr = NULL;
	device->drop();
	/*if(spaceCar){
		spaceCar->pause();
	}*/
	return true;
}
/* end engine manager */

/* game manager */
void GameWorld::initLights(){
	//add lights;
	smgr->addLightSceneNode(0, vector3df(20, 500, -50), SColorf(1.0f, 1.0f, 1.0f), 4000.0f);
	smgr->addLightSceneNode(0, vector3df(-20, 300, 800), SColorf(1.0f, 1.0f, 1.0f), 4000.0f);
	smgr->addLightSceneNode(0, vector3df(20, 70, -500), SColorf(1.0f, 1.0f, 1.0f), 4000.0f);
}

void GameWorld::createGround(){
	//create ground
	ISceneNode *ground = smgr->addCubeSceneNode(1.0);
	ground->setScale(vector3df(GROUND_WIDTH, 3, GROUND_HEIGHT));
	ground->setPosition(vector3df(0, 0, 0));
	ground->setMaterialFlag(video::EMF_LIGHTING, true);
	ground->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
	ground->setMaterialTexture(0, driver->getTexture(device->getFileSystem()->getWorkingDirectory()+"/batleplacecool.jpeg"));
}

void GameWorld::createMap(){
	device->getFileSystem()->addFileArchive(this->path+"/flash.pk3");
	IAnimatedMesh* mesh = smgr->getMesh("flash.bsp");
	ISceneNode* node = 0;
	if (mesh)
		node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	 if (node)
		 node->setPosition(core::vector3df(0,0,0));
}

void GameWorld::generateTerrain(){
	/*int NoiseSize = 512;
	int NoiseZoom = 40;
	int Octaves = 5;
	double Persistance = .60;
	bool Colored = 0;
	int SeedNumber = 60493;

	Noise::Render_Clouds(SeedNumber,Colored,NoiseSize,NoiseSize,NoiseZoom,Octaves,Persistance, 0, 0, 0,driver);
	*/
	//terrainMap = driver->getTexture("NoiseMaps/noise.bmp");

	__android_log_print(ANDROID_LOG_INFO, "Terrain", "path = %s", device->getFileSystem()->getWorkingDirectory().c_str());
	ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
			device->getFileSystem()->getWorkingDirectory()+"/heightmap.bmp",
			0,
			-1,
			vector3df(-GROUND_WIDTH/2,-100,-GROUND_HEIGHT/2),
			//vector3df(,-100,0),
			vector3df(0,0,0),
			vector3df(5, 1, 5),
			SColor(255,255,255,255),
			5,
			ETPS_17,
			4) ;
	terrain->setMaterialFlag(video::EMF_LIGHTING, false);
	terrain->setMaterialTexture(0, driver->getTexture(device->getFileSystem()->getWorkingDirectory()+"/batleplacecool.jpeg"));
	terrain->setMaterialType(EMT_DETAIL_MAP);
	terrain->scaleTexture(1.0f, 20.0f);
	//terrain->setDebugDataVisible(true);
	//terrain->setMaterialFlag(EMF_WIREFRAME, !terrain->getMaterial(0).Wireframe);
	//terrain->setMaterialFlag(EMF_POINTCLOUD, true);
	//CDynamicMeshBuffer* buffer = new CDynamicMeshBuffer(EVT_2TCOORDS, EIT_16BIT);
	//terrain->getMeshBufferForLOD(*buffer, 0);
	//S3DVertex2TCoords* data = (S3DVertex2TCoords*)buffer->getVertexBuffer().getData();
	//buffer->drop();
}

void GameWorld::addPortal(vector3df pos, ISceneManager* sceneManager){
	ISceneNode *portalNode = sceneManager->addVolumeLightSceneNode(0, -1, 32, 32, SColor(0, 255, 255, 255), SColor(0, 0, 0, 0));
	if( portalNode ){
		portalNode->setScale(vector3df(250, 50, 250));
		portalNode->setPosition(pos);
		array<ITexture*> textures;
		for( s32 g = 7; g > 0; --g ){
			stringc tmp;
			tmp = this->path+"/portal";
			tmp += g;
			tmp += ".bmp";
			ITexture* t = driver->getTexture( tmp.c_str() );
				textures.push_back( t );
		}
		ISceneNodeAnimator* glow = smgr->createTextureAnimator( textures, 150 );
		portalNode->addAnimator(glow);
		glow->drop();
	}
}

/* end game manager */

/* events */
void GameWorld::sendTouchEvent( int pointerCount, int activePid, int pid0, int pid1, int action0, int action1, int x0, int y0, int x1, int y1 ){
	SEvent irrevent;
	irrevent.EventType = EET_ANDROID_TOUCH_EVENT;
	if( pointerCount >= 2 ){
		if( activePid == 0 ){
			if( action0 == 5 ){
				irrevent.AndroidTouchEvent.action = E_ANDROID_TOUCH_DOWN;
				irrevent.AndroidTouchEvent.x = x0;
				irrevent.AndroidTouchEvent.y = y0;
				this->device->postEventFromUser(irrevent);
			}else if( action0 == 6 ){
				irrevent.AndroidTouchEvent.action = E_ANDROID_TOUCH_UP;
				irrevent.AndroidTouchEvent.x = x0;
				irrevent.AndroidTouchEvent.y = y0;
				this->device->postEventFromUser(irrevent);
			}
		}else if( activePid == 1 ){
			if( action1 == 5 ){
				irrevent.AndroidTouchEvent.action = E_ANDROID_TOUCH_DOWN;
				irrevent.AndroidTouchEvent.x = x1;
				irrevent.AndroidTouchEvent.y = y1;
				this->device->postEventFromUser(irrevent);
			}else if( action1 == 6 ){
				irrevent.AndroidTouchEvent.action = E_ANDROID_TOUCH_UP;
				irrevent.AndroidTouchEvent.x = x1;
				irrevent.AndroidTouchEvent.y = y1;
				this->device->postEventFromUser(irrevent);
			}
		}
	}else if( pointerCount == 1 ){
		if( activePid == 0 ){
			if( action0 == 0 ){
				irrevent.AndroidTouchEvent.action = E_ANDROID_TOUCH_DOWN;
				irrevent.AndroidTouchEvent.x = x0;
				irrevent.AndroidTouchEvent.y = y0;
				this->device->postEventFromUser(irrevent);
			}else if( action0 == 1 ){
				irrevent.AndroidTouchEvent.action = E_ANDROID_TOUCH_UP;
				irrevent.AndroidTouchEvent.x = x0;
				irrevent.AndroidTouchEvent.y = y0;
				this->device->postEventFromUser(irrevent);
			}
		}
	}else {
		__android_log_print(ANDROID_LOG_INFO, "TouchEvent", "not handled");
	}
}

void GameWorld::sendAccelerometerEvent(  float x, float y, float z){
	SEvent irrevent;
	irrevent.EventType = EET_ANDROID_ACCELEROMETER_EVENT;
	irrevent.AndroidAccelerometerEvent.y = y;
	irrevent.AndroidAccelerometerEvent.x = x;
	irrevent.AndroidAccelerometerEvent.z = z;

	__android_log_print(ANDROID_LOG_INFO, "AccelerometerEvent", "x = %f, y = %f, z = %f", irrevent.AndroidAccelerometerEvent.x, irrevent.AndroidAccelerometerEvent.y, irrevent.AndroidAccelerometerEvent.z);
	if( this->device ) this->device->postEventFromUser(irrevent);
}
/* end events*/

bool GameWorld::init(){
	initGraphics();
	initLights();
	//createGround();
	generateTerrain();
	//addPortal(vector3df(0, 0, 0), smgr);
	//createMap();

	//create game objects manager and add event reciever to gameObjectsManager(device)
	gameObjectsManager = new GameObjectsManager(driver, device, smgr, this->path);

	return true;
}

void GameWorld::graphicsResize(int w, int h){
	dimension2d<unsigned int> size;
	size.Width = w;
	size.Height = h;
	device->getVideoDriver()->OnResize(size);
	__android_log_print(ANDROID_LOG_INFO, "Irrlicht", "resize w=%d h=%d", w, h);

	if(gameObjectsManager) gameObjectsManager->resize(w, h);
}

void GameWorld::iterate(){
	gameObjectsManager->iterate(device, driver, smgr);
}

void GameWorld::pause(){
}

void GameWorld::resume(){
}

void GameWorld::destroy(){
	importGLDeinit();
}

void GameWorld::setPath(stringc path){
	this->path = path;
}

stringc GameWorld::getPath(){
	return this->path;
}
