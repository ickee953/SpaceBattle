/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

package su.panov.irrlicht;

public class IrrlichtTouchEvent {
	/**
	 * ACTION_DOWN = 0
	 * ACTION_UP = 1
	 * ACTION_POINTER_DOWN = 5
	 * ACTION_POINTER_UP = 6
	*/

	public int activePid;
	public int pointerCount;

	public int action0;
	public int action1;
	public int pid0;
	public int pid1;
	//coordinates for first finger
	public int x0;
	public int y0;

	//coordinates for second finger
	public int x1;
	public int y1;
}
