/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

#include <SpaceCar.h>
#include <android/log.h>
#include <vector>

using namespace SpaceBattle;
using namespace std;

SpaceCar::SpaceCar(IrrlichtDevice* device, irrBulletWorld* world, IVideoDriver* driver, ISceneManager* smgr){
	this->modelFileName = "/Feisar_Ship.3DS";
	this->textureFileName = "/diffuse.jpg";

	this->maxSpeed = 30;
	this->mass = 100;
	this->world = world;
	this->sceneManager = smgr;
	this->driver = driver;
	this->device = device;

	IAnimatedMesh* mesh = this->sceneManager->getMesh( (device->getFileSystem()->getWorkingDirectory()+modelFileName).c_str() );
	if (!mesh){
		__android_log_print(ANDROID_LOG_INFO, "SpaceCar", "cannot getMesh");
		return;
	}
	this->node = this->sceneManager->addAnimatedMeshSceneNode( mesh );
	if (this->node){
		node->setMaterialFlag(EMF_LIGHTING, true);
		this->node->setMaterialTexture( 0, this->driver->getTexture((device->getFileSystem()->getWorkingDirectory()+textureFileName ).c_str()) );
		this->node->setPosition(vector3df(0, 100, 0));
		this->node->setScale(vector3df(0.2, 0.2, 0.2));
		this->node->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
		__android_log_print(ANDROID_LOG_INFO, "SpaceCar", "add texture");

		ICollisionShape *shape = new IBoxShape(this->node, this->mass, true);
		this->rigidBody = this->world->addRigidBody(shape);
		this->rigidBody->setDamping(0.2,0.2);
	}
}

void SpaceCar::move(){
	vector3df rot = this->node->getRotation();
	matrix4 mat;
	mat.setRotationDegrees(rot);
	vector3df forwardDir(vector3df(mat[8], mat[9], mat[10]) * 200);
	this->rigidBody->setLinearVelocity(forwardDir);
	__android_log_print(ANDROID_LOG_INFO, "SpaceCar", "move");
}
