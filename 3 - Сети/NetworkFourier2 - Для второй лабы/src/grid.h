/* gird.h */

	#define GRID_SIZE 100
	glBegin(GL_LINES);
	glColor3f(0.4f,0.4f,0.4f);
	for (i=-GRID_SIZE;i<=GRID_SIZE;i++)
	{
		
		if(!(i%10))glColor3f(0.4f,0.4f,0.4f);else glColor3f(0.2f,0.2f,0.2f);
		glVertex3f((float)i,	-0.0,	GRID_SIZE);
		glVertex3f((float)i,	-0.0,	-GRID_SIZE);
		glVertex3f(-GRID_SIZE,			-0.0,	(float)i);
		glVertex3f( GRID_SIZE,			-0.0,	(float)i);
	}					
/*		glColor3f(1,0,0);	glVertex3f(5,1,0);	glVertex3f(0,1,0) ;
		glColor3f(0,1,0);	glVertex3f(0,6,0);	glVertex3f(0,1,0) ;
		glColor3f(0,0,1);	glVertex3f(0,1,5);	glVertex3f(0,1,0) ;*/
	glEnd();
	glColor4f(1,1,1,1);
