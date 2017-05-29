package com.harsukh.fractaldisplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Debug;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by harsukh on 5/25/17.
 */

public class CustomJNIView extends GLSurfaceView {
    private static final int GL_VERSION = 2;

    public CustomJNIView(Context context) {
        super(context);
        setEGLContextClientVersion(GL_VERSION);
        setRenderer(new CustomRenderer(new SerpenskiCallbacks()));
    }

    private static final class CustomRenderer implements GLSurfaceView.Renderer {

        private SerpenskiCallbacks serpenskiCallbacks;

        public CustomRenderer(SerpenskiCallbacks serpenskiCallbacks) {
            this.serpenskiCallbacks = serpenskiCallbacks;
        }

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            serpenskiCallbacks.loadFractal();
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            serpenskiCallbacks.loadFractal();
        }

        @Override
        public void onDrawFrame(GL10 gl) {
        }
    }
}
