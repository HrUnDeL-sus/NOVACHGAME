#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
float camera_position_y=1;
float camera_position_x=-10;
float camera_position_z=-10;
float add_y=20;
float add_x=0;
float add_z=-10;
void invert_camera(){
add_z=-add_z;
}
int is_invert_camera(){
return add_z>0?1:0;
}
void set_camera_position(float x,float y,float z){
camera_position_y=y;

camera_position_x=x;
camera_position_z=z;
}
void add_camera_position_add(float x,float y,float z){
add_y+=y;

add_x+=x;
add_z+=z;
}
void enable_camera(){

	gluLookAt(camera_position_x+add_x,camera_position_y+add_y,camera_position_z+add_z,camera_position_x,camera_position_y,camera_position_z,0,1,0);
}
