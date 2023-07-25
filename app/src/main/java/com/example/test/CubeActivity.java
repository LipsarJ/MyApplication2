package com.example.test;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Surface;
import android.view.SurfaceHolder;



public class CubeActivity extends AppCompatActivity implements SurfaceHolder.Callback {
    private long nativeRenderer;

    // Загружаем библиотеку с нативным кодом
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        MyGLSurfaceView surfaceView = new MyGLSurfaceView(this);
        setContentView(surfaceView);
        surfaceView.getHolder().addCallback(this);
    }

    @Override
    protected void onDestroy() {
        // Освобождаем ресурсы нативного кода при уничтожении активности
        super.onDestroy();
        if (nativeRenderer != 0) {
            releaseNativeRenderer(nativeRenderer);
            nativeRenderer = 0;
        }
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        // Создаем и инициализируем рендерер при создании SurfaceView
        if (nativeRenderer == 0) {
            nativeRenderer = createNativeRenderer();
            initNativeRenderer(nativeRenderer, holder.getSurface());
        }
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        // При изменении размера SurfaceView обновляем размеры рендерера
        if (nativeRenderer != 0) {
            resizeNativeRenderer(nativeRenderer, width, height);
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        // Освобождаем ресурсы нативного кода при уничтожении SurfaceView
        if (nativeRenderer != 0) {
            releaseNativeRenderer(nativeRenderer);
            nativeRenderer = 0;
        }
    }

    // Методы для взаимодействия с нативным кодом
    private native long createNativeRenderer();
    private native void initNativeRenderer(long rendererPtr, Surface surface);
    private native void resizeNativeRenderer(long rendererPtr, int width, int height);
    private native void releaseNativeRenderer(long rendererPtr);
}