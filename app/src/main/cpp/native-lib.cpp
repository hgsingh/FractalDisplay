#include <jni.h>
#include <string>
#include "fractals.h"

static FractalRender *fractalRender = NULL;

extern "C" {
JNIEXPORT jint JNICALL
        Java_com_harsukh_fractaldisplay_SerpenskiCallbacks_loadFractal(JNIEnv *env,
                                                                       jobject instance),
        Java_com_harsukh_fractaldisplay_SerpenskiCallbacks_loadFractalFromSeek(JNIEnv *env,
                                                                               jobject instance,
                                                                               jint progress);
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

JNIEXPORT jint JNICALL
Java_com_harsukh_fractaldisplay_SerpenskiCallbacks_loadFractalFromSeek(JNIEnv *env,
                                                                       jobject instance,
                                                                       jint progress) {
    if (fractalRender) {
        delete fractalRender;
        fractalRender = NULL;
    }
    int addition_of_points = progress + MAX_POINTS;
    vertex points_to_draw[progress];
    srand(time(NULL));
    drawTriangle(points_to_draw, progress);
    GLfloat pos[(addition_of_points) * POS_SIZE];
    int l = 0;
    for (int i = 0; i < addition_of_points; ++i) {
        for (int j = 0; j < POS_SIZE; ++j) {
            pos[l] = points_to_draw[i].pos[j];
            ++l;
        }
    }
    fractalRender = createRenderer();
    fractalRender->render(pos);
    return 0;

}