/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

#include <android/log.h>
#include <GameObjectsManager.h>
#include <math.h>
#include <utils.h>
#include <GameWorld.h>

using namespace SpaceBattle;

const int MAX_BULLET_COUNT = 10;
const int MAX_ASTEROIDS_COUNT = 7;

void GameObjectsManager::resize(int width, int height){
	receiver->resize(width, height);
}

GameObjectsManager::GameObjectsManager(IVideoDriver* driver, IrrlichtDevice* device, ISceneManager* smgr, stringc path){
	timeStamp = device->getTimer()->getTime();
	deltaTime = 0;
	counter = 0;

	// add event reciever to engine
	float w = device->getVideoDriver()->getScreenSize().Width;
	float h = device->getVideoDriver()->getScreenSize().Height;

	receiver = new AndroidEventReceiver(w, h);
	device->setEventReceiver(receiver);

	//create physic world
	physicWorld = createIrrBulletWorld(device, true, false);
	physicWorld->setGravity(vector3df(0, 0, 0));

	//TODO OpenAL init

	//create game objects
	spaceCar = new SpaceCar(device, physicWorld, driver, smgr);
	camera = new Camera(smgr, spaceCar->node);

	// add some random asteroids for the bugs to come out
    for(int i=0; i<MAX_ASTEROIDS_COUNT; i++) {
    	vector3df pos;
    	pos.X = rand() % GameWorld::GROUND_WIDTH - GameWorld::GROUND_WIDTH / 2;
    	pos.Y = 100;
    	pos.Z = rand() % GameWorld::GROUND_HEIGHT - GameWorld::GROUND_HEIGHT / 2;

    	Asteroid asteroid;
    	asteroid.node = smgr->addCubeSceneNode(50);
    	asteroid.node->setPosition(pos);
    	asteroid.node->setMaterialTexture(0, driver->getTexture(device->getFileSystem()->getWorkingDirectory()+"/crate.jpg"));
    	asteroid.node->setMaterialFlag(video::EMF_LIGHTING, true);

    	ICollisionShape *shape = new IBoxShape(asteroid.node, 100, true);
    	asteroid.rigidBody = physicWorld->addRigidBody(shape);

    	vector3df vel;
    	vel.X = rand() % 200;
    	vel.Y = 0;
    	vel.Z = rand() % 200;

    	asteroid.rigidBody->setLinearVelocity(vel);

    	vector3df rot;
    	rot.X = rand() % 2;
    	rot.Y = rand() % 2;
    	rot.Z = rand() % 2;

    	asteroid.rigidBody->setAngularVelocity(rot, ERBTS_LOCAL);
    	//asteroid.node->setDebugDataVisible(EDS_BBOX);

    	asteroids.push_back(asteroid);
    }
}

bool GameObjectsManager::shouldRemoveBullet(Bullet &b) {
    if(!b.active) return true;

    bool bRemove = false;
    if( b.pos.X >= GameWorld::GROUND_WIDTH / 2 ||
    	b.pos.Z >= GameWorld::GROUND_HEIGHT / 2 ||
    	b.pos.X <= -GameWorld::GROUND_WIDTH / 2 ||
    	b.pos.Z <= -GameWorld::GROUND_HEIGHT / 2 ){
    	bRemove = true;
    	//TODO some thing wrong in that logic?!
    	b.node->setVisible(false);
    }

    return bRemove;
}

/*
* direction = 0 - X translation
* direction = 1 - Y translation
* direction = 2 - Z translation
*/
void GameObjectsManager::spaceCarTranslate(){
	vector3df pos = spaceCar->node->getPosition();
	if(	pos.X >= GameWorld::GROUND_WIDTH / 2 ){
		pos.X = -GameWorld::GROUND_WIDTH / 2;
		__android_log_print(ANDROID_LOG_INFO, "Aircraft", "position [%f %f %f]", pos.X, pos.Y, pos.Z);

		matrix4 mat;
		mat.setTranslation(pos);
		mat.setRotationDegrees(spaceCar->node->getRotation());
		spaceCar->rigidBody->setWorldTransform(mat);
	} else {
		if(	pos.X <= -GameWorld::GROUND_WIDTH / 2 ){
			pos.X = GameWorld::GROUND_WIDTH / 2;
			__android_log_print(ANDROID_LOG_INFO, "Aircraft", "position [%f %f %f]", pos.X, pos.Y, pos.Z);

			matrix4 mat;
			mat.setTranslation(pos);
			mat.setRotationDegrees(spaceCar->node->getRotation());
			spaceCar->rigidBody->setWorldTransform(mat);
		}
	}
	if(	pos.Y <= 100 ){
		pos.Y = 100;

		matrix4 mat;
		mat.setTranslation(pos);
		mat.setRotationDegrees(spaceCar->node->getRotation());
		spaceCar->rigidBody->setWorldTransform(mat);
	} else if(pos.Y >= 100) {
		pos.Y = 100;

		matrix4 mat;
		mat.setTranslation(pos);
		mat.setRotationDegrees(spaceCar->node->getRotation());
		spaceCar->rigidBody->setWorldTransform(mat);
	}

	if(	pos.Z >= GameWorld::GROUND_HEIGHT/2 ){
		pos.Z = -GameWorld::GROUND_HEIGHT / 2;
		__android_log_print(ANDROID_LOG_INFO, "Aircraft", "position [%f %f %f]", pos.X, pos.Y, pos.Z);

		matrix4 mat;
		mat.setTranslation(pos);
		mat.setRotationDegrees(spaceCar->node->getRotation());
		spaceCar->rigidBody->setWorldTransform(mat);
	} else {
		if(	pos.Z <= -GameWorld::GROUND_HEIGHT/2 ){
			pos.Z = GameWorld::GROUND_HEIGHT / 2;
			__android_log_print(ANDROID_LOG_INFO, "Aircraft", "position [%f %f %f]", pos.X, pos.Y, pos.Z);

			matrix4 mat;
			mat.setTranslation(pos);
			mat.setRotationDegrees(spaceCar->node->getRotation());
			spaceCar->rigidBody->setWorldTransform(mat);
		}
	}
}

void GameObjectsManager::asteroidsTranslate(){
	for(int i = 0; i<asteroids.size(); i++){
		vector3df pos = asteroids[i].node->getPosition();
		if(	pos.X >= GameWorld::GROUND_WIDTH / 2 ){
			pos.X = -GameWorld::GROUND_WIDTH / 2;
			__android_log_print(ANDROID_LOG_INFO, "Aircraft", "position [%f %f %f]", pos.X, pos.Y, pos.Z);

			matrix4 mat;
			mat.setTranslation(pos);
			mat.setRotationDegrees(asteroids[i].node->getRotation());
			asteroids[i].rigidBody->setWorldTransform(mat);
		} else {
			if(	pos.X <= -GameWorld::GROUND_WIDTH / 2 ){
				pos.X = GameWorld::GROUND_WIDTH / 2;
				__android_log_print(ANDROID_LOG_INFO, "Aircraft", "position [%f %f %f]", pos.X, pos.Y, pos.Z);

				matrix4 mat;
				mat.setTranslation(pos);
				mat.setRotationDegrees(asteroids[i].node->getRotation());
				asteroids[i].rigidBody->setWorldTransform(mat);
			}
		}

		if(	pos.Y <= 100 ){
			pos.Y = 100;

			matrix4 mat;
			mat.setTranslation(pos);
			mat.setRotationDegrees(asteroids[i].node->getRotation());
			asteroids[i].rigidBody->setWorldTransform(mat);
		} else if(pos.Y >= 100) {
				pos.Y = 100;

			matrix4 mat;
			mat.setTranslation(pos);
			mat.setRotationDegrees(asteroids[i].node->getRotation());
			asteroids[i].rigidBody->setWorldTransform(mat);
		}

		if(	pos.Z >= GameWorld::GROUND_HEIGHT/2 ){
			pos.Z = -GameWorld::GROUND_HEIGHT / 2;
			__android_log_print(ANDROID_LOG_INFO, "Aircraft", "position [%f %f %f]", pos.X, pos.Y, pos.Z);

			matrix4 mat;
			mat.setTranslation(pos);
			mat.setRotationDegrees(asteroids[i].node->getRotation());
			asteroids[i].rigidBody->setWorldTransform(mat);
		} else {
			if(	pos.Z <= -GameWorld::GROUND_HEIGHT/2 ){
				pos.Z = GameWorld::GROUND_HEIGHT / 2;
				__android_log_print(ANDROID_LOG_INFO, "Aircraft", "position [%f %f %f]", pos.X, pos.Y, pos.Z);

				matrix4 mat;
				mat.setTranslation(pos);
				mat.setRotationDegrees(asteroids[i].node->getRotation());
				asteroids[i].rigidBody->setWorldTransform(mat);
			}
		}
	}
}

bool GameObjectsManager::collision(ISceneNode* one, ISceneNode* two){
	aabbox3d<f32> b1, b2;

	b1 = one->getBoundingBox();
	b2 = two->getBoundingBox();

	one->getRelativeTransformation().transformBoxEx( b1 );
	two->getRelativeTransformation().transformBoxEx( b2 );

	return b1.intersectsWithBox( b2 );


	//if(one->getTransformedBoundingBox().intersectsWithBox(two->getTransformedBoundingBox())){
	//	return (one->getTransformedBoundingBox().intersectsWithBox(two->getTransformedBoundingBox()));
	//}
	return false;
}

vector3df cameraPos(0, 200, 0);

void GameObjectsManager::iterate(IrrlichtDevice* device, IVideoDriver* driver, ISceneManager* smgr){
	deltaTime = device->getTimer()->getTime() - timeStamp;
	timeStamp = device->getTimer()->getTime();

	device->run();

	//iterate space car
	if(spaceCar){
		if(receiver && receiver->spaceCarTouchEvent.fire){
			//shoot
			if(bullets.size() < MAX_BULLET_COUNT){
				Bullet b((device->getFileSystem()->getWorkingDirectory()).c_str(), smgr, driver);

				vector3df rotation = spaceCar->node->getRotation();
				matrix4 mat;
				mat.setRotationDegrees(rotation);
				vector3df vec(vector3df(mat[8], mat[9], mat[10]));
				vec.normalize();
				vector3df bulletPos(spaceCar->node->getPosition());

				__android_log_print(ANDROID_LOG_INFO, "Bullet", "position [%f %f %f]", bulletPos.X, bulletPos.Y, bulletPos.Z);
				__android_log_print(ANDROID_LOG_INFO, "Bullet", "vector [%f %f %f]", vec.X, vec.Y, vec.Z);

				//b.node->setDebugDataVisible(EDS_BBOX);

				b.pos = bulletPos;
				b.vel = vec * 9;
				b.active = true;

				bullets.push_back(b);
			}
			receiver->spaceCarTouchEvent.fire = !receiver->spaceCarTouchEvent.fire;
		}

		//translate objects x & z dimensions
		spaceCarTranslate();
		asteroidsTranslate();

		if(receiver && receiver->spaceCarTouchEvent.move){
			//matrix4 mat;
			//mat.setRotationDegrees(vector3df(0,spaceCar->node->getRotation().Y,0));
			//mat.setTranslation(spaceCar->node->getPosition());
			//spaceCar->rigidBody->setWorldTransform(mat);
			spaceCar->move();
		}

		if(receiver && receiver->spaceCarRotationEvent.changeRotation){
			float rotX = receiver->spaceCarRotationEvent.rotationValueX;
			float rotY = receiver->spaceCarRotationEvent.rotationValueY;

			vector3df rotVect;
			//rotVect.X = -rotX*0.02;
			rotVect.X = 0;
			rotVect.Y = rotY*1.3f;
			rotVect.Z = 0;

			spaceCar->rigidBody->setAngularVelocity(rotVect, ERBTS_LOCAL);
		}
		//if(camera){
		//	cameraPos = camera->node->getPosition();
		//}
		cameraPos.Z = spaceCar->node->getPosition().Z + camera->X_OFFSET;
		cameraPos.X = spaceCar->node->getPosition().X;
	}

	//update bullets
	for(int i = 0; i < bullets.size(); i++){
		//intersections
		for(int aCnt=0;aCnt<asteroids.size();aCnt++){
			if(	asteroids[aCnt].node->isVisible() &&
				asteroids[aCnt].node->getTransformedBoundingBox().isPointInside(bullets[i].node->getPosition())){
				//then bullet in asteroid
				bullets[i].active = false;
				bullets[i].node->setVisible(false);

				asteroids[aCnt].node->setVisible(false);
			}
		}
		bullets[i].update();
	}
	//remove bullets[i] if shouldRemoveBullet(bullets[i])
    ofRemove(bullets, shouldRemoveBullet);

	//iterate camera
	if(camera){
		if(receiver->spaceCarTouchEvent.move){
			if( cameraPos.Y <= camera->MAX_DIST_TO_SPACECAR ){
				cameraPos.Y += 1;
			}
		} else {
			if( cameraPos.Y > camera->MIN_DIST_TO_SPACECAR ){
				cameraPos.Y -= 2;
			}
		}
		camera->node->setPosition(cameraPos);
		camera->node->setTarget(spaceCar->node->getPosition());
	}

	physicWorld->stepSimulation(deltaTime * 0.001f, 120);

	driver->beginScene(true, true, SColor(255,50,50,50));
	smgr->drawAll();
	driver->endScene();

	counter++;
}
