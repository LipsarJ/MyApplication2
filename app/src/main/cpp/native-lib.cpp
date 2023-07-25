#include <jni.h>
#include <android/log.h>
#include "MyGLRenderer.h"


extern "C" {
JNIEXPORT jlong JNICALL Java_com_example_test_CubeActivity_createNativeRenderer(JNIEnv* env, jobject /* this */) {
    MyGLRenderer* renderer = new MyGLRenderer();
    renderer->setRotationSpeed(2.0f);
    renderer->onSurfaceCreated();
    return reinterpret_cast<jlong>(renderer);
}
JNIEXPORT void JNICALL Java_com_example_test_CubeActivity_initNativeRenderer(JNIEnv* env, jobject /* this */, jlong renderer_ptr, jobject surface) {
    MyGLRenderer* renderer = reinterpret_cast<MyGLRenderer*>(renderer_ptr);
    renderer->onSurfaceCreated();

}

JNIEXPORT void JNICALL Java_com_example_test_CubeActivity_resizeNativeRenderer(JNIEnv* env, jobject /* this */, jlong renderer_ptr, jint width, jint height) {
    MyGLRenderer* renderer = reinterpret_cast<MyGLRenderer*>(renderer_ptr);
    renderer->onSurfaceChanged(static_cast<int>(width), static_cast<int>(height));
}

JNIEXPORT void JNICALL Java_com_example_test_CubeActivity_releaseNativeRenderer(JNIEnv* env, jobject /* this */, jlong renderer_ptr) {
    MyGLRenderer* renderer = reinterpret_cast<MyGLRenderer*>(renderer_ptr);
    delete renderer;
}

JNIEXPORT void JNICALL Java_com_example_test_MyGLRenderer_renderNative(JNIEnv* env, jobject /* this */) {
    auto renderer = new MyGLRenderer;
    renderer->onDrawFrame();
}
}