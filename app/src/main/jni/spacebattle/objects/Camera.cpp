/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

#include "Camera.h"

using namespace SpaceBattle;

ISceneNode* parent;

Camera::Camera(ISceneManager* smgr, ISceneNode* parentParam){
	parent = parentParam;
	this->node = smgr->addCameraSceneNodeFPS();
	this->node->setPosition(vector3df(0, MIN_DIST_TO_SPACECAR, 0));
	this->node->setTarget(parent->getPosition());
}

