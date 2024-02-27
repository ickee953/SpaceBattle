/**
 * © Panov Vitaly 2023 - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Panov Vitaly <vetalpanov@gmail.com>, June 2017
 */

package su.panov.irrlicht;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;

public class IrrlichtGLView extends GLSurfaceView implements SensorEventListener{

    private NativeIrrlichtActivity mActivity;
    private IrrlichtTouchEvent irrTouchEvent;
    private IrrlichtAccelerometerRotationEvent irrAccelEvent;
    private IrrlichtRenderer mRenderer;

    //accelerometer
    private boolean sensorInicialized;
    private SensorManager sensorManager;
    private Sensor accelerometer;
    private final float ACCELEROMETER_NOISE = (float)0.05;
    private float accelerometerLastX;
    private float accelerometerLastY;
    //private float accelerometerLasZ;

    public IrrlichtGLView(NativeIrrlichtActivity activity) {
        super(activity);
        mActivity = activity;
        mRenderer = new IrrlichtRenderer(activity);
        setRenderer(mRenderer);
        irrTouchEvent = new IrrlichtTouchEvent();

        sensorInicialized = false;
        sensorManager = (SensorManager) mActivity.getSystemService(mActivity.getApplicationContext().SENSOR_SERVICE);
        accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_NORMAL);
        irrAccelEvent = new IrrlichtAccelerometerRotationEvent();
    }

    @Override
    public void onPause() {
    	super.onPause();
    	sensorManager.unregisterListener(this);
    }

    @Override
    public void onResume() {
	super.onResume();
	sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_NORMAL);
    }

    private void dumpEvent(MotionEvent event) {
    	   String names[] = { "DOWN" , "UP" , "MOVE" , "CANCEL" , "OUTSIDE" ,
    	      "POINTER_DOWN" , "POINTER_UP" , "7?" , "8?" , "9?" };
    	   StringBuilder sb = new StringBuilder();
    	   int action = event.getAction();
    	   int actionCode = action & MotionEvent.ACTION_MASK;
    	   sb.append("event ACTION_" ).append(names[actionCode]);
    	   if (actionCode == MotionEvent.ACTION_POINTER_DOWN
    	         || actionCode == MotionEvent.ACTION_POINTER_UP) {
    	      sb.append("(pid " );//.append(action >> MotionEvent.ACTION_POINTER_ID_SHIFT);
    	      sb.append(")" );
    	   }
    	   sb.append("[" );
    	   for (int i = 0; i < event.getPointerCount(); i++) {
    	      sb.append("#" ).append(i);
    	      sb.append("(pid " ).append(event.getPointerId(i));
    	      sb.append(")=" ).append((int) event.getX(i));
    	      sb.append("," ).append((int) event.getY(i));
    	      if (i + 1 < event.getPointerCount())
    	         sb.append(";" );
    	   }
    	   sb.append("]" );
    	   Log.d("MultitouchExample", sb.toString());
    	}

    public boolean onTouchEvent(final MotionEvent event) {
    	 super.onTouchEvent(event);
    	 dumpEvent(event);
    	 irrTouchEvent.pointerCount = event.getPointerCount();
    	 int action = event.getAction();
  	   	 int actionCode = action & MotionEvent.ACTION_MASK;
    	 if( actionCode == MotionEvent.ACTION_POINTER_DOWN 
    			 || actionCode == MotionEvent.ACTION_POINTER_UP ){
    		 irrTouchEvent.activePid = action >> MotionEvent.ACTION_POINTER_ID_SHIFT;
    	 } else if( actionCode == MotionEvent.ACTION_DOWN 
    			 || actionCode == MotionEvent.ACTION_UP ){
    		 irrTouchEvent.activePid = 0;
    	 }
    	 if(irrTouchEvent.activePid == 0){
    		 irrTouchEvent.action0 = actionCode;
    	 } else if( irrTouchEvent.activePid == 1 ){
    		 irrTouchEvent.action1 = actionCode;
    	 }
    	 for( int i = 0; i < event.getPointerCount(); i++ ){
    		 if( i == 0 ){
    			 irrTouchEvent.pid0 = event.getPointerId(i);
    			 irrTouchEvent.x0 = (int)event.getX(i);
    			 irrTouchEvent.y0 = (int)event.getY(i);
    		 } else if( i == 1 ){
    			 irrTouchEvent.pid1 = event.getPointerId(i);
    			 irrTouchEvent.x1 = (int) event.getX(i);
    			 irrTouchEvent.y1 = (int) event.getY(i);
    		 }
    	 }
    	 if( mActivity!= null ){
    		 mActivity.nativeSendTouchEvent(irrTouchEvent);
    	 }
        return true;
    }

	public void onAccuracyChanged(Sensor arg0, int arg1) {
	}

	public void onSensorChanged(SensorEvent event) {
		float xRotation = event.values[0];
		float yRotation = event.values[1];
		float zRotation = event.values[2];
		
		IrrlichtAccelerometerRotationEvent nativeEvent = new IrrlichtAccelerometerRotationEvent();
		/*nativeEvent.setXRotation(xRotation);
		nativeEvent.setYRotation(yRotation);
		nativeEvent.setZRotation(zRotation);
		*/

		if(!sensorInicialized){
			accelerometerLastY = yRotation;
			irrAccelEvent.xRotation = (float)0.0;
			irrAccelEvent.yRotation = (float)0.0;
			irrAccelEvent.zRotation = (float)0.0;

			sensorInicialized = true;
		} else {
			float deltaX = Math.abs(accelerometerLastX - xRotation);
			float deltaY = Math.abs(accelerometerLastY - yRotation);
			//get changeDirection
			if(	xRotation < ACCELEROMETER_NOISE && xRotation > -ACCELEROMETER_NOISE ){
				accelerometerLastX = (float)0.0;
				irrAccelEvent.xRotation = accelerometerLastX;
				//mActivity.nativeSendAccelerometerEvent(irrAccelEvent);
			} else if( deltaX > ACCELEROMETER_NOISE ){
				accelerometerLastX = xRotation;
				irrAccelEvent.xRotation = accelerometerLastX;
				Log.d("Accelerometer", "accel X value = "+irrAccelEvent.xRotation);
				//mActivity.nativeSendAccelerometerEvent(irrAccelEvent);
			}
			if(  yRotation < ACCELEROMETER_NOISE && yRotation > -ACCELEROMETER_NOISE ){
				accelerometerLastY = (float)0.0;
				irrAccelEvent.yRotation = accelerometerLastY;
				//mActivity.nativeSendAccelerometerEvent(irrAccelEvent);
			} else if( deltaY > ACCELEROMETER_NOISE ){
				accelerometerLastY = yRotation;
				irrAccelEvent.yRotation = accelerometerLastY;
				Log.d("Accelerometer", "accel Y value = "+irrAccelEvent.yRotation);
				//mActivity.nativeSendAccelerometerEvent(irrAccelEvent);
			} 
			mActivity.nativeSendAccelerometerEvent(irrAccelEvent);
		}
		
		/*final float alpha = (float)0.8;
		gravityY = alpha * gravityY + (1 - alpha) * event.values[0];		
		float linearAcceleration = event.values[0] - gravityY;
		Log.d("Accelerometer",linearAcceleration+"");
		if(linearAcceleration<0){
			irrAccelEvent.changeDirection = true;			
		} else {
			irrAccelEvent.changeDirection = false;
		}*/
	}
}
