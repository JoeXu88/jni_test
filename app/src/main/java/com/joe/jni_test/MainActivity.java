package com.joe.jni_test;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    final String TAG = "maincode";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private int val = 0;
    public static String str;
    private float fval = 3.2f;

    public float getFval() {
        return fval;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        setString("test java string");

        int a[] = getIntArray();
        for(int i=0; i<a.length; i++) {
            Log.d(TAG, "array elelem: "+a[i]);
        }

        float[] f = new float[3];
        for(int i=0; i<f.length; i++) {
            f[i] = (float)(i+1) + (float)0.5;
        }
        setFloatArray(f);

        setJavaVal();
        Log.d(TAG, "after set from native: "+val +" str:"+str);

        callMainFunc();

        callObjFunc();

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native void setString(String string);
    public native int[] getIntArray();
    public native void setFloatArray(float[] array);
    public native void setJavaVal();
    public native void callMainFunc();
    public native void callObjFunc();
}
