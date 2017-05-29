#include <jni.h>
#include <string>
#include "fractals.h"

static FractalRender *fractalRender = NULL;

extern "C" {
JNIEXPORT jint JNICALL
Java_com_harsukh_fractaldisplay_SerpenskiCallbacks_loadFractal(JNIEnv *env, jobject instance);
};

JNIEXPORT jint JNICALL
Java_com_harsukh_fractaldisplay_SerpenskiCallbacks_loadFractal(JNIEnv *env, jobject instance) {
    if (fractalRender) {
        delete fractalRender;
        fractalRender = NULL;
    }
    vertex points_to_draw[MAX_POINTS];
    srand(time(NULL));
    drawTriangle(points_to_draw, MAX_POINTS);
    GLfloat pos[MAX_POINTS * POS_SIZE];
    int l = 0;
    for (int i = 0; i < MAX_POINTS; ++i) {
        for (int j = 0; j < POS_SIZE; ++j) {
            pos[l] = points_to_draw[i].pos[j];
            ++l;
        }
    }
    fractalRender = createRenderer();
    fractalRender->render(pos);
    return 0;
}