package com.example.test;


import android.opengl.GLES30;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyGLRenderer implements GLSurfaceView.Renderer {

    @Override
    public void onSurfaceCreated(GL10 unused, EGLConfig config) {
        //GLES30.glClearColor(2.0f, 3.0f, 0.0f, 1.0f);
    }

    @Override
    public void onDrawFrame(GL10 unused) {
        // Здесь выполняется отрисовка кадра
        renderNative();
    }

    @Override
    public void onSurfaceChanged(GL10 unused, int width, int height) {
        // Здесь выполняется обработка изменения размеров окна отображения
        //GLES30.glViewport(0, 0, width, height);
    }
    private native void renderNative();
}