//
//	ABOUT_BOX.H
//


void	cube(float x, float y, float z);
void	cone(float r_up, float r_dn, float height, int side);
void	tube(float r_in, float r_out, float h, int side);
void	gear(float r_in, float r_out, float width, float tooth_height, float count);



class EUIAbout: public	EUIFrame {
	private:
		
	public:
		virtual	void	FMPaint		( void );	
		virtual void	FMMouseUp		( int btn, int x, int y ) 
						{ 
							EUIFrame::FMMouseUp(btn,x,y); 
							visible = false; 
						}
	};
	
const char	*about_text = 
	"Network Fourier 2.0\r\n"
	"\r\n"
			"coded by : Alexey Bezgodov\r\n"
			"also known as Demiurg-HG\r\n"
			//"coded by : Demiurg-HG\r\n"
	"\r\n"
	"write to : demiurg-hg@yandex.ru\r\n"
	"\r\n"
	"CS Department\r\n"
	"IFMO\r\n"
	"2005\r\n"
	"\r\n"
	"click...\r\n";



void EUIAbout::FMPaint(void)
{
	EUIFrame::FMPaint();
	
	float black[4] = {0,0,0.0,0.5f};
	
	if (!this->visible) return;
	
	GLUquadricObj	*quadric = gluNewQuadric();
	
	int x,y,w,h, i;

	uirect_t	r = GetAbsoluteRect();

	glPushMatrix();
	glTranslatef(rect.x, rect.y, 0);
	
		x = 4;			y = 16;
		w = rect.w-8;	h = rect.h-4-16;

		bar(x-1, y-1, w+2, h+2,  black);

		glEnable(GL_SCISSOR_TEST);
		glScissor(r.x+4,	UI_DESKTOP_HEIGHT-(r.y+r.h-4), r.w+1-8, r.h+1-4-16);
		glViewport(r.x+4,	UI_DESKTOP_HEIGHT-(r.y+r.h-4), r.w+1-8, r.h+1-4-16);
		//------------------------------------------------------
		
		glPushMatrix();
		glLoadIdentity();
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		
		glLoadIdentity();
		glFrustum(-0.04f, 0.04f, -0.025f, 0.025f, 0.03f, 100.0f);
		//glOrtho( -4.0f, 4.0f,  -2.5f, 2.5f,  -0,80);
		
			//--------------------------------------------------
			// scene :
			glMatrixMode(GL_MODELVIEW);
			//glPushMatrix();
			
			glRotatef(90.0f, -1, 0, 0);		// <-- now Z looks up...
			glTranslatef(0, 5, 0);
			
			glBlendFunc(GL_ONE, GL_ONE);
			glEnable(GL_DEPTH_TEST);
				{
					glEnable(GL_LIGHTING);
					glEnable(GL_LIGHT0);
					glEnable(GL_LIGHT1);
					glEnable(GL_LIGHT2);

					
					float amb[4]	= {0.2, 0.2, 0.2, 1.0};
					float dif[4]	= {0.1, 0.1, 0.1, 1.0};
					float spc[4]	= {1.0, 1.0, 1.0, 1.0};

					float pos0[4]	= {-7, -5, 3, 1};
					float clr0[4]	= { 1, 1, 1, 1};

					float pos1[4]	= { 5, 2, 3, 1};
					float clr1[4]	= { 1, 1, 1, 1};

					float pos2[4]	= { 1,-5,-3, 1};
					float clr2[4]	= { 1, 1, 1, 1};
					int	shine		= 16;

					glLightfv(GL_LIGHT0, GL_DIFFUSE, clr0);
					glLightfv(GL_LIGHT0, GL_SPECULAR, clr0);
					glLightfv(GL_LIGHT0, GL_POSITION, pos0);

					glLightfv(GL_LIGHT1, GL_DIFFUSE, clr1);
					glLightfv(GL_LIGHT1, GL_SPECULAR, clr1);
					glLightfv(GL_LIGHT1, GL_POSITION, pos1);

					glLightfv(GL_LIGHT2, GL_DIFFUSE, clr2);
					glLightfv(GL_LIGHT2, GL_SPECULAR, clr2);
					glLightfv(GL_LIGHT2, GL_POSITION, pos2);

					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,	amb);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,	dif);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spc);
					glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shine);

				 }
			float time = sys.Milliseconds();
			glRotatef(time/100.0f, 1,0,0);
			glRotatef(time/200.0f, 0,1,0);
			glRotatef(time/300.0f, 0,0,1);
			
			glDisable(GL_BLEND);	

			for (i=0; i<64; i++)
			{
				glPushMatrix();
				glTranslatef(i/16-1.5, (i/4)%4-1.5, i%4-1.5);
				if (sinf(i*i)>0) cube(0.9,0.9,0.9); else	gluSphere(quadric, 0.5, 32, 16);
				glPopMatrix();//*/
				
			} 
			//gear(3.0f, 3.2f, 0.5f, 0.4f, 16);
			
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);
			
			glEnable(GL_BLEND);	
			

			//--------------------------------------------------
			
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();		
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();	

		//------------------------------------------------------
		glScissor( 0, 0, UI_DESKTOP_WIDTH, UI_DESKTOP_HEIGHT);
		glViewport( 0, 0, UI_DESKTOP_WIDTH, UI_DESKTOP_HEIGHT);
		glDisable(GL_SCISSOR_TEST);


		glColor4f(0,0,0,0.9);
		uicore.DrawString(21,31,8,8, about_text);
		glColor4f(1,1,1,0.9);
		uicore.DrawString(20,30,8,8, about_text);
		
		glColor4f(1,1,1,1);
		
	glPopMatrix();
	
	gluDeleteQuadric(quadric);
}



/*
===============================================================================

	PRIMITIVES

===============================================================================
*/
void cube(float x, float y, float z)
{
	x/=2.0;
	y/=2.0;
	z/=2.0;
	glBegin(GL_QUADS);
		glNormal3f(0,1,0);
		glVertex3f( x, y, z);		glVertex3f( x, y,-z);
		glVertex3f(-x, y,-z);		glVertex3f(-x, y, z);

		glNormal3f(0,-1,0);
		glVertex3f(-x,-y, z);		glVertex3f(-x,-y,-z);
		glVertex3f( x,-y,-z);		glVertex3f( x,-y, z);

		glNormal3f(1,0,0);
		glVertex3f( x,-y, z);		glVertex3f( x,-y,-z);
		glVertex3f( x, y,-z);		glVertex3f( x, y, z);

		glNormal3f(-1,0,0);
		glVertex3f(-x, y, z);		glVertex3f(-x, y,-z);
		glVertex3f(-x,-y,-z);		glVertex3f(-x,-y, z);

		glNormal3f(0,0,1);
		glVertex3f(-x,-y, z);		glVertex3f( x,-y, z);
		glVertex3f( x, y, z);		glVertex3f(-x, y, z);

		glNormal3f(0,0,-1);
		glVertex3f(-x, y,-z);		glVertex3f( x, y,-z);
		glVertex3f( x,-y,-z);		glVertex3f(-x,-y,-z);
	glEnd();
}

/*
**	cone()
*/
void cone(float r_up, float r_dn, float height, int side)
{
	float	a = 0;
	int		i = 0;
	float	h = height/2.0f;
	float	n[3], l;

	l = (float)sqrt( (r_up-r_dn)*(r_up-r_dn) + height*height );
	if (l*l<=0.001) return;

	n[0] = height/l;
	n[1] = height/l;
	n[2] = -(r_up-r_dn)/l;

	if (!side) side = 3;

	glBegin(GL_QUAD_STRIP);
		for (i=0; i<side+1; i++)
		{
			a = 6.2832f*i/(float)side;
			glNormal3f(n[0]*cos(a), n[1]*sin(a), n[2]);
			glVertex3f(r_up*cos(a), r_up*sin(a), h);
			glVertex3f(r_dn*cos(a), r_dn*sin(a), -h);
		}
	glEnd();
}

void tube(float r_in, float r_out, float h, int side)
{
	glPushMatrix();	glTranslatef(0,0,h/2.0);
		cone(r_in, r_out, 0, side);
	glPopMatrix();

	glPushMatrix();	glTranslatef(0,0,-h/2.0);
		cone(r_out, r_in, 0, side);
	glPopMatrix();

	cone(r_out, r_out, h, side);
	cone(r_in, r_in,  -h, side);
}

/*
**	gear();
*/
void gear(float r_in, float r_out, float width, float tooth_height, float count)
{
	float w = width/2.0;
	int i,j;

	glPushMatrix();	glTranslatef(0,0,w);
		cone(r_in, r_out, 0, count);
	glPopMatrix();
	
	glPushMatrix();	glTranslatef(0,0,-w);
		cone(r_out, r_in, 0, count);
	glPopMatrix();

	cone(r_out, r_out, width, count);
	cone(r_in, r_in, -width, count);

	
	for (i=0; i<count; i++)
	{
		//if (i&1) continue;
		glPushMatrix();
			glRotatef(360.0*i/count+0.0/count/2.0,0,0,1);
			glTranslatef(0, r_in+tooth_height/2.0, 0);

			cube(6.28*r_out/count/2.0, tooth_height, width);
		glPopMatrix();
	}
	
}

