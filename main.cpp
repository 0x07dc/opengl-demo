#include<Windows.h>    
// first include Windows.h header file which is required    
#include<stdio.h>    
//#include<gl/GL.h>   // GL.h header file    
//#include<gl/GLU.h> // GLU.h header file   
#define GLEW_STATIC
#include "glew/glew.h"
#include "freeglut/glut.h"  // glut.h header file from freeglut\include\GL folder    
#include<conio.h>    
#include<stdio.h>    
#include<math.h>    
#include<string.h>    
#include <iostream>
#include <WindowsNumerics.h>
#include <algorithm>
#include <memory>
#include <vector>
using namespace Windows::Foundation::Numerics;


#include "OpenGLShape.h"
#include "OpenGLShapes.h"

std::unique_ptr<OpenGLShape> shapeToDisplay;

// Init_OpenGL() function    
void Init_OpenGL()
{
    // set background color to Black    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // set shade model to Flat    
    glShadeModel(GL_FLAT);

}
struct VertexXYZColor
{
    float3 m_Pos;
    float3 m_Color;
};
double count = 0;
GLuint g_uiVerticesVBO = 0;
GLuint g_uiIndicesVBO = 0;

// Display_Objects() function    
void Display_Objects(void)
{
    // clearing the window or remove all drawn objects    
    glClear(GL_COLOR_BUFFER_BIT);
    /*glPushMatrix(), which copies the current matrix and adds
    the copy to the top of the stack, and
    glPopMatrix(), which discards the top matrix on the stack*/
    glPushMatrix();



    //you can draw many objects here like polygons,lines,triangles etc  
    shapeToDisplay->display();


    glPopMatrix();
    glutSwapBuffers();

}


void timer(int value)
{
    glutTimerFunc(16, timer, 0);
    glutPostRedisplay();
}

// Reshape() function    
void Reshape(int w, int h)
{
    //adjusts the pixel rectangle for drawing to be the entire new window    
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    //matrix specifies the projection transformation    
    glMatrixMode(GL_PROJECTION);
    // load the identity of matrix by clearing it.    
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    //matrix specifies the modelview transformation    
    glMatrixMode(GL_MODELVIEW);
    // again  load the identity of matrix    
    glLoadIdentity();
    // gluLookAt() this function is used to specify the eye.    
    // it is used to specify the coordinates to view objects from a specific position    
    gluLookAt(-0.3, 0.5, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}



// main function    
int main(int argc, char** argv)
{
    // initialize glut    
    glutInit(&argc, argv);
    //glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // set window size    
    glutInitWindowSize(700, 500);
    // set window location    
    glutInitWindowPosition(250, 50);
    // create window with window text    
    glutCreateWindow("OpenGL Demo");
    // call Init_OpenGL() function    
    Init_OpenGL();




    // Init GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW." << std::endl;
        exit(-1);
    }
    if (!glewIsSupported("GL_VERSION_1_5") && !glewIsSupported("GL_ARB_vertex_buffer_object"))
    {
        std::cerr << "ARB_vertex_buffer_object not supported!" << std::endl;
        exit(-2);
    }

    // Prepare scene/shapes
    // If rowLen is not evenly divisible into numVertices, the last (incomplete) row will be truncated
    shapeToDisplay = std::make_unique<openGLShapes::WaveForm>(30'000, 400);// First screenshots were with 50'000, 1'000


    // call glutDisplayFunc() function & pass parameter as Display_Objects() function  
    glutDisplayFunc(Display_Objects);
    // call glutReshapeFunc() function & pass parameter as Reshape() function    
    glutReshapeFunc(Reshape);

    glutTimerFunc(0, timer, 0);
    //glutMainLoop() is used to redisplay the objects   
    glutMainLoop();
    

    return 0;
}