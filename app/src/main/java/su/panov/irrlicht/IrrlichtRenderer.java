/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

package su.panov.irrlicht;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.opengl.GLSurfaceView;
import android.util.Log;

public class IrrlichtRenderer implements GLSurfaceView.Renderer {
	private NativeIrrlichtActivity mActivity;
    private int mWindowWidth;
    private int mWindowHeight;
    private IrrlichtStatus mStatus;

    public IrrlichtRenderer(NativeIrrlichtActivity activity) {
        mActivity = activity;
        mStatus = new IrrlichtStatus();
        mStatus.mQuit = false;
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        mActivity.nativeInitGL();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mWindowWidth = width;
        mWindowHeight = height;
        mActivity.nativeResize(width, height);
    }

    public void onDrawFrame(GL10 gl) {
        // render a frame
        mActivity.nativeDrawIteration();
        // get status
        mActivity.nativeGetStatus(mStatus);
        if (mStatus.mQuit) {
            Log.e("MESSAGE", "QUIT");
            mActivity.finish();
        }
    }
}
