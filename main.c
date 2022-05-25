#include <stdio.h>
#include <GL/glut.h>

static int win(0);

int main(int argc, char* argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);

    //step 2. Open a window named "GLUT DEMO"
    win = glutCreateWindow("GLUT DEMO");
    glClearColor(0.0,0.0,0.0,0.0); //set background

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    glutMainLoop();
}