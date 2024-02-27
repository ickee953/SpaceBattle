/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, August 2017
 */

#ifndef ASTEROID_H
#define ASTEROID_H

#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace std;
using namespace core;

namespace SpaceBattle{

class Asteroid{
public:
	ISceneNode *node;
	IRigidBody *rigidBody;
};

}

#endif
