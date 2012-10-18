// CORE.Collision.cpp
/////////////////////////////////////////////////

#include "..\GameCore.h"

namespace GameCore {

	bool Collision::_CheckCollision(int x, int y, int w, int h, int padleft, int padtop, int padright, int padbottom, double &vx, double &vy, int bx, int by, int bw, int bh) {

		// Current bounding box of player
		int leftSrc = x - padleft;
		int topSrc = y - padtop;
		int rightSrc = x + w + padright;
		int bottomSrc = y + h + padbottom;
	
		// Destination bounding box of player after movement
		int leftDest = leftSrc + vx;
		int topDest = topSrc + vy;
		int rightDest = rightSrc + vx;
		int bottomDest = bottomSrc + vy;

		// Will the character intersect with the block?
		Rect r1(leftDest, topDest, rightDest, bottomDest),   // Rectangle for myself
			 r2(bx, by, bx+bw, by+bh);						 // Rectangle for the block
	
		if(GameCore::Math::_IsRectCollide(r1, r2)) {

			// Cap his vertical motion if he is colliding from above the box
			if(bottomSrc <= r2.top) {
				vy = r2.top - bottomSrc;
				return true;
			}

			// Cap his vertical motion if he is colliding from below the box
			if(topSrc >= r2.bottom) {
				vy = r2.bottom - topSrc;
				return false;
			}

			// Cap his horizontal motion if he is colliding from left of the box
			if(rightSrc <= r2.left) {
				vx = r2.left - rightSrc - 7;
				return false;
			}

			// Cap his horizontal motion if he is colliding from right of the box
			if(leftSrc >= r2.right) {
				vx = r2.right - leftSrc + 7;
				return false;
			}

		} else {
			// not standing on the block
			return false;
		}
	}

}