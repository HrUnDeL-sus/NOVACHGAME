#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "client.h"
#include "camera.h"
struct world_object {
    float xPosition;
    float yPosition;
    float zPosition;
    float xScale;
    float yScale;
    float zScale;
    float xRotate;
    float yRotate;
    float zRotate;
    float colorR;
    float colorG;
    float colorB;
    int UID;
    int type;
};
struct world_object* world_objects=NULL;
struct world_object* world_objects_save;
int count_world_objects=0;
int count=0;
void rendering_world() {


    for(int i=0; i<count_world_objects; i+=1) {
        glPushMatrix();
		GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
		  GLfloat high_shininess[]={100.0};
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glColor3f(world_objects[i].colorR,world_objects[i].colorG,world_objects[i].colorB);
         glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
          glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
        glTranslated(world_objects[i].xPosition,world_objects[i].yPosition,world_objects[i].zPosition);
        glScaled(world_objects[i].xScale,world_objects[i].yScale,world_objects[i].zScale);
        glRotated(world_objects[i].xRotate,1,0,0);
        glRotated(world_objects[i].yRotate,0,1,0);
        glRotated(world_objects[i].zRotate,0,0,1);
        if(world_objects[i].type==3){

				GLfloat light_position[]={world_objects[i].xPosition,world_objects[i].yPosition,world_objects[i].zPosition,1.0};
	 glLightfv(GL_LIGHT0,GL_POSITION, light_position);
			glutSolidSphere(1,15,15);

        }
		else
        glutSolidCube(1);
    //    if(world_objects[i].UID==client_UID){
		//	set_camera_position(world_objects[i].xPosition,world_objects[i].yPosition,world_objects[i].zPosition);
   //     }
        if(world_objects[i].type==0) {
            glPushMatrix();
            glColor3f(1,1,1);
            glTranslated(-0.3f,0,-0.5f);
            glScaled(0.1f,0.1f,0.1f);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
            glColor3f(1,1,1);
            glTranslated(0.3f,0,-0.5f);
            glScaled(0.1f,0.1f,0.1f);

            glutSolidCube(1);
            glPopMatrix();
        }
        glPopMatrix();
		glDisable(GL_COLOR_MATERIAL);
    }
}
void apply_data_to_object(float* data,struct world_object* obj) {
    obj->xPosition=data[1];
    obj->yPosition=data[2];
    obj->zPosition=data[3];
    obj->xScale=data[4];
    obj->yScale=data[5];
    obj->zScale=data[6];
    obj->xRotate=data[7];
    obj->yRotate=data[8];
    obj->zRotate=data[9];
    obj->colorR=data[10];
    obj->colorG=data[11];
    obj->colorB=data[12];
    obj->UID=(int)data[14];
    obj->type=data[13];
   // printf("\nPOSITION:%f %f %f\nSCALE: %f %f %f\n",data[1],data[2],data[3],data[4],data[5],data[6]);
}
void add_object(float* data) {
    if((int)data[0]==0) {

        count_world_objects+=1;
        world_objects_save=realloc(world_objects,count_world_objects*sizeof(struct world_object));
        world_objects_save[count_world_objects-1].xPosition=data[1];
        apply_data_to_object(data,&world_objects_save[count_world_objects-1]);
        world_objects=world_objects_save;

    } else if((int)data[0]==2) {
        for(int i=0; i<count_world_objects; i+=1) {
            if(world_objects[i].UID==data[14]) {

                apply_data_to_object(data,&world_objects[i]);


            }
        }
    } else if((int)data[0]==1) {
        for(int i=0; i<count_world_objects; i+=1) {
            if(world_objects[i].UID==data[14]) {

                for(int q=i; q<count_world_objects; q+=1) {
                    world_objects[q]=world_objects[q+1];
                }
                count_world_objects-=1;
                world_objects_save=realloc(world_objects,count_world_objects*sizeof(struct world_object));
                world_objects=world_objects_save;

            }

        }
    }
}

