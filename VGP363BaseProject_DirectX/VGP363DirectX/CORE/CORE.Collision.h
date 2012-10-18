// CORE.Collision.h
/////////////////////////////////////////////////////////

#ifndef __CORE_COLLISION_H_
#define __CORE_COLLISION_H_

#include "CORE.Math.h"

namespace GameCore {

	class Collision {
	public:
		static bool _CheckCollision(int x, int y, int w, int h, int padleft, int padtop, int padright, int padbottom, double &vx, double &vy, int bx, int by, int bw, int bh);
	};

}

#endif