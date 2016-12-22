//
// Created by Dc on 12/21/2016.
//

#ifndef HELLOGL2_SPRITE_H
#define HELLOGL2_SPRITE_H
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class Sprite {
    GLuint _program;
    GLuint vPositionHandle;
    GLuint vtranslateHandle;
    float _x = 0.0;
    float _y = 0.0;
    GLfloat gTriangleVertices[6] = { 0.0f, 0.5f, -0.5f, -0.5f,
                                  0.5f, -0.5f };
public:
    void draw();
    Sprite(GLuint program);
    ~Sprite();
    void move(float x, float y);
};


#endif //HELLOGL2_SPRITE_H
