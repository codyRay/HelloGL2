//
// Created by Dc on 12/21/2016.
//

#include "Sprite.h"

Sprite::Sprite(GLuint program){

    _program = program;
    vPositionHandle = glGetAttribLocation(program, "vPosition");
    vtranslateHandle = glGetUniformLocation(program, "translate");
}

Sprite::~Sprite() {


}

void Sprite::draw() {

    glUseProgram(_program);

    glVertexAttribPointer(vPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    glUniform2f(vtranslateHandle, _x, _y);
    glEnableVertexAttribArray(vPositionHandle);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
void Sprite::move(float x, float y) {
    _x += x;
    _y += y;
}