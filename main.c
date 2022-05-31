#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "camera.h"
int keys[256];
void reshare(int w,int h) {
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float r=1.0*w/h;
    gluPerspective(70,r,1,700);

    glMatrixMode(GL_MODELVIEW);
}

void key_test() {
    for (int i = 0; i < 256; i++) {

        if (!keys[i]) {
            continue;
        }


        if(i=='+'||i=='=')
			add_camera_position_add(0,1,0);
		if(i=='-')
			add_camera_position_add(0,-1,0);
		if(i=='e')
			send_state(8);
		if(i=='1')
			send_state(7);
		if(i=='2')
			send_state(12);
			if(i=='q')
			send_state(9);
        if(i=='w')
           send_state(is_invert_camera()?6:5);
        if(i=='s')
            send_state(is_invert_camera()?5:6);
        if(i=='d')
            send_state(is_invert_camera()?2:1);
        if(i=='a')
            send_state(is_invert_camera()?1:2);
		if(i==32)
			 send_state(11);

    }
}

float r=0;
void display() {
    glLoadIdentity();

	send_state(0);
    glClearColor(0.4f,0.6f,1,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	rendering_world();
    glutSwapBuffers();
	 key_test();
}
void idle() {
   // display();
}
void timer() {
    glutPostRedisplay();
    glutTimerFunc(1000/30, timer, 0);
}
void key(char key,int x,int y) {

    keys[key]=1;
}
void key_up(char key,int x,int y) {
if(key=='3')
	invert_camera();
keys[key]=0;
}
void change_light0(){
	GLfloat light_ambient[]= {1,1,1,1.0};
	GLfloat light_specular[]= {1,0,0,1.0};
    GLfloat light_diffuse[]= {0.3f,0.3f,0.3f,1.0};

    glShadeModel(GL_SMOOTH);
   // glLightfv(GL_LIGHT0,GL_AMBIENT, light_ambient);
 //   glLightfv(GL_LIGHT0,GL_DIFFUSE, light_diffuse);
  //  glLightfv(GL_LIGHT0,GL_SPECULAR, light_specular);

glLightfv(GL_LIGHT0,GL_EMISSION, light_diffuse);
}
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    printf("Connect to server...");
    if(connect_to_server()<0) {
        printf("ERROR!!!");
        return 0;
    } else
        printf("Connected");
   int handle = glutCreateWindow("Red square example");

    glutIgnoreKeyRepeat(1);
    glutReshapeFunc(reshare);
    glutDisplayFunc(display);

    glutIdleFunc(idle);
    glEnable(GL_DEPTH_TEST);
    glutKeyboardFunc(key);
    glutKeyboardUpFunc(key_up);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    change_light0();
    timer();
    glutMainLoop();
	printf("QQQQ");
    return EXIT_SUCCESS;
}
