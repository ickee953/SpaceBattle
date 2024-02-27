/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

#include <irrlicht.h>
#include "event-receiver.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;

namespace SpaceBattle{

class Camera{
public:
	static const int MAX_DIST_TO_SPACECAR = 500;
	static const int MIN_DIST_TO_SPACECAR = 100;
	static const int X_OFFSET = -150;

	ICameraSceneNode* node;

	Camera(ISceneManager* smgr, ISceneNode* parent);
	~Camera();
};
}
