/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

package su.panov.irrlicht;

public class IrrlichtAccelerometerRotationEvent {
	float xRotation;
	float yRotation;
	float zRotation;
	
	public float getXRotation() {
		return xRotation;
	}
	public float getYRotation() {
		return yRotation;
	}
	public float getZRotation() {
		return zRotation;
	}
	public void setXRotation(int xRotation) {
		this.xRotation = xRotation;
	}
	public void setYRotation(int yRotation) {
		this.yRotation = yRotation;
	}
	public void setZRotation(int zRotation) {
		this.zRotation = zRotation;
	}
}
