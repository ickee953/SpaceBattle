/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

package su.panov.irrlicht;

import java.io.IOException;
import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;

public abstract class NativeIrrlichtActivity extends Activity{
	private IrrlichtGLView mGLView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//set full screen
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		try {
			Utils.unpackOnSdCard(getAssets());
		} catch (IOException e) {
			Log.i("Irrlicht", "Error in unpack");
		}
		nativeEnvJ2C(Environment.getExternalStorageDirectory().getAbsolutePath());
		mGLView = new IrrlichtGLView(this);
		setContentView(mGLView);
		nativeOnCreate();
	}

	@Override
	protected void onPause() {
		super.onPause();
		mGLView.onPause();
		nativeOnPause();
	}

	@Override
	protected void onResume() {
		super.onResume();
		mGLView.onResume();
		nativeOnResume();
	}

	@Override
	public void onDestroy() {
		nativeOnDestroy();
		super.onDestroy();
	}

	/** load irrlicht.so */
	static {
		System.loadLibrary("irrlicht");
		System.loadLibrary("bullet");
		System.loadLibrary("irrbullet");
		System.loadLibrary("openal");
		//System.loadLibrary("ogg");
		//System.loadLibrary("vorbis");
		//System.loadLibrary("mad");
		//System.loadLibrary("mp3Decoder");
		//System.loadLibrary("caudio");
		System.loadLibrary("spacebattle");
	}

	public native void nativeOnCreate();
	public native void nativeOnPause();
	public native void nativeOnResume();
	public native void nativeOnDestroy();
	public native void nativeInitGL();
	public native void nativeResize(int w, int h);
	public native void nativeGetStatus(IrrlichtStatus status);
	public native void nativeSendTouchEvent(IrrlichtTouchEvent event);
	//public native void nativeSendAccelerometerEvent(IrrlichtAccelerometerEvent event);
	public native void nativeSendAccelerometerEvent(IrrlichtAccelerometerRotationEvent event);
	public native void nativeEnvJ2C(String sdcardPath);

	public static native void nativeDrawIteration();
}
