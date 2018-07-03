#!/bin/sh
sudo apt-get install freeglut3
sudo apt-get install freeglut3-dev
sudo apt-get install binutils-gold
#sudo apt-get install g++ cmake
sudo apt-get install libglew-dev
#sudo apt-get install g++
sudo apt-get install mesa-common-dev
sudo apt-get install build-essential
sudo apt-get install libglew1.5-dev libglm-dev
sudo apt-get install libfreeimage3 libfreeimage-dev
glxinfo | grep OpenGL
mkdir Sample-OpenGL-Programs
cd Sample-OpenGL-Programs 
echo "#include <GL/freeglut.h> 
#include <GL/gl.h>
void renderFunction() { glClearColor(0.0, 0.0, 0.0, 0.0); glClear(GL_COLOR_BUFFER_BIT); glColor3f(1.0, 1.0, 1.0); glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); glBegin(GL_POLYGON); glVertex2f(-0.5, -0.5); glVertex2f(-0.5, 0.5); glVertex2f(0.5, 0.5); glVertex2f(0.5, -0.5); glEnd(); glFlush(); } int main(int argc, char** argv) { glutInit(&argc, argv); glutInitDisplayMode(GLUT_SINGLE); glutInitWindowSize(500,500); glutInitWindowPosition(100,100); glutCreateWindow(\"OpenGL - First window demo\"); glutDisplayFunc(renderFunction); glutMainLoop(); return 0; }
" > main.c
gcc main.c -lglut -lGL -lGLEW -lGLU -o OpenGLExample
./OpenGLExample
