//
//	UI_SHAPES.CPP
//
//	coded by : Demiurg-HG
//	descr : all shapes that needed for drawing...
//

#include "demo_def.h"


void bar(int x, int y, int w, int h, const float *clr)
{
	glDisable(GL_TEXTURE_2D);

	glColor4fv(clr);	
	glBegin(GL_QUADS);
		glVertex3f(x+0, y+0, 0);	glVertex3f(x+w, y+0, 0);
		glVertex3f(x+w, y+h, 0);	glVertex3f(x+0, y+h, 0);
	glEnd();
	
	glColor4f(1,1,1,0.7);
	glBegin(GL_LINE_LOOP);
		glVertex3f(x+0, y+0, 0);	glVertex3f(x+w, y+0, 0);
		glVertex3f(x+w, y+h, 0);	glVertex3f(x+0, y+h, 0);
	glEnd();
	
	glColor4f(1,1,1,1);
}

void bar_flat(int x, int y, int w, int h, const float *clr)
{
	glDisable(GL_TEXTURE_2D);
	
	glColor4fv(clr);
	glBegin(GL_QUADS);
		glVertex3f(x+0, y+0, 0);	glVertex3f(x+w, y+0, 0);
		glVertex3f(x+w, y+h, 0);	glVertex3f(x+0, y+h, 0);
	glEnd();
	glColor4f(1,1,1,1);
}


void cursor(int shp, int x, int y)
{
	glPushMatrix();
	glTranslatef(x,y,0);
	glRotatef(0, 0.5, 1,0);
		glColor4f(1,1,1,0.33);;
		glBegin(GL_TRIANGLES);
			glVertex3f(  0,	  0,  0);			glVertex3f(  0,	 24,  0);
			glVertex3f(  8,	 16,  0);			glVertex3f(  0,	  0,  0);
			glVertex3f(  8,	 16,  0);			glVertex3f(  24, 24,  0);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(-640,0,0);
			glVertex3f(640,0,0);
			glVertex3f(0,480,0);
			glVertex3f(0,-480,0);
		glEnd();

		glColor4f(1,1,1,0.9);;
		glBegin(GL_LINE_LOOP);
			glVertex3f(  0,  0, 0);
			glVertex3f(  0, 24, 0);
			glVertex3f(  8, 16, 0);
			glVertex3f( 24, 24, 0);
		glEnd();

	glPopMatrix();
}