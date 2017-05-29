//
// Created by Harsukh Singh on 5/26/17.
//

#include "fractals.h"

FractalRender::~FractalRender() {
    glDeleteBuffers(1, &mVB);
    glDeleteProgram(mProgram);
}

FractalRender::FractalRender() : mEglContext(eglGetCurrentContext()), mProgram(0),
                                 mVB(0), mPosAttrib(0) {}

const char VERTEX_SHADER[] =
        "attribute vec2 a_Position;     \n"     // Per-vertex position information
                "void main()                    \n"
                "{                               \n  "
                "   gl_PointSize= 3;            \n"
                "   gl_Position =vec4(a_Position, 0.0, 1.0); \n"
                "}                              \n";

const char FRAGMENT_SHADER[] =
        "precision mediump float;       \n"
                "void main()                    \n"
                "{                              \n"
                "   gl_FragColor = vec4(0.0, 1.0, 0.0, 0.5);     \n"
                "}                              \n";

bool FractalRender::init(GLfloat *points_to_draw) {
    mProgram = createProgram(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!mProgram) {
        return false;
    }
    glBindAttribLocation(mProgram, mPosAttrib, "pos");
//    glGenBuffers(1, &mVB);
//    glBindBuffer(GL_ARRAY_BUFFER, mVB);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(points_to_draw), &points_to_draw, GL_STATIC_DRAW);
    return true;
}

void FractalRender::draw(GLfloat pos[]) {
    glUseProgram(mProgram);
    //glBindBuffer(GL_ARRAY_BUFFER, mVB);
    glVertexAttribPointer(mPosAttrib, POS_SIZE, GL_FLOAT, GL_FALSE, 0, pos);
    glEnableVertexAttribArray(mPosAttrib);
    glEnable(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, MAX_POINTS);
}

FractalRender *createRenderer(GLfloat *points) {
    FractalRender *renderer = new FractalRender;
    if (!renderer->init(points)) {
        delete renderer;
        return NULL;
    }
    return renderer;
}

GLuint FractalRender::createShader(GLenum shaderType, const char *src) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader) {
        return 0;
    }
    glShaderSource(shader, 1, &src, NULL);
    GLint compiled = GL_FALSE;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    return shader;
}

GLuint FractalRender::createProgram(const char *vtxSrc, const char *fragSrc) {
    GLuint vtxShader = 0;
    GLuint fragShader = 0;
    GLuint program = 0;
    GLint linked = GL_FALSE;

    vtxShader = createShader(GL_VERTEX_SHADER, vtxSrc);
    if (!vtxShader) {
        glDeleteShader(vtxShader);
        return program;
    }

    fragShader = createShader(GL_FRAGMENT_SHADER, fragSrc);
    if (!fragShader) {
        glDeleteShader(fragShader);
        return program;
    }

    program = glCreateProgram();
    if (!program) {
        return program;
    }
    glAttachShader(program, vtxShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        glDeleteProgram(program);
        program = 0;
    }
    return program;
}


void FractalRender::render(GLfloat pos[]) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    draw(pos);
}