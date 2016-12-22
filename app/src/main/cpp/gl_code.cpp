/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// OpenGL ES 2.0 code

#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Sprite.h"




auto gVertexShader =
    "attribute vec2 vPosition;\n"
            "uniform vec2 translate; \n"
    "void main() {\n"
    "  gl_Position = vec4( vPosition.x + translate.x , vPosition.y + translate.y, 0.0, 1.0);\n"
    "}\n";

auto gFragmentShader =
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";

Sprite* sprite;
Sprite* sprite1;


GLuint gProgram;


bool setupGraphics(int w, int h) {
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return false;
    }

    sprite = new Sprite(gProgram);
    sprite1 = new Sprite(gProgram);

    checkGlError("glGetAttribLocation");


    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    return true;
}


auto x =0.0;
auto y= 0.0;
void renderFrame() {



    glClearColor(0.1, 0.25, 0.75, 1.0f);

    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    sprite->draw();
    sprite1->draw();
}

void touch(int e,int a , int b){

    switch (e){
        case touchEvent::down :
            sprite->move(0.2,0.0);
            break;
        case touchEvent::up :
           y += 0.1;
            break;
        case touchEvent::move :
           x=0, y=0;
            break;

    }
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_touch(JNIEnv * env, jobject obj,jint e,  jint x , jint y);
};

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}
JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_touch(JNIEnv * env, jobject obj,jint e, jint x , jint y)
{
    touch(e,x,y);
}