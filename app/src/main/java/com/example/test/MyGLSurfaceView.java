package com.example.test;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class MyGLSurfaceView extends GLSurfaceView {

    private final MyGLRenderer renderer;

    public MyGLSurfaceView(Context context) {
        super(context);
        setEGLContextClientVersion(3);
        // Создаем экземпляр класса MyGLRenderer
        renderer = new MyGLRenderer();
        // Устанавливаем рендерер для этой GLSurfaceView
        setRenderer(renderer);
    }
}