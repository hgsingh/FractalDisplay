#include <iostream>
#include <cstdlib>
#include <ctime>
#include <GLES2/gl2.h>
#include "EGL/egl.h"

#define MAX_POINTS 1000 //modify this to render more points
#define POS_SIZE 2
typedef struct vertex_points {
    GLfloat pos[POS_SIZE];
} vertex;
extern vertex triangle[3]; //initial points_to_draw

void drawTriangle(vertex points_to_draw[], int size_of_points);

int
recurse_triangles(GLfloat point[], GLfloat a[], GLfloat b[], GLfloat c[],
                  int iteration, int size_of_points, vertex points_to_draw[]);

int half_way(GLfloat point[], GLfloat a[], GLfloat new_point[]);


class FractalRender {
public:
    FractalRender();

    virtual ~FractalRender();

    bool init();

    void render(GLfloat pos[]);

protected:
    void draw(GLfloat pos[]);

private:
    GLuint createProgram(const char *vertexSrc, const char *fragmentSrc);

    GLuint createShader(GLenum shaderType, const char *src);

    const EGLContext mEglContext;
    GLuint mProgram;
    GLuint mPosAttrib;
};

extern FractalRender *createRenderer();