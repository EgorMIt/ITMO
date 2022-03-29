//
//	DEMO_MAIN.CPP
//


#include "demo_def.h"


EDemo::EDemo(void)
{  
	cam.ang[0] = cam.ang[1] = cam.ang[2] = 0;
	cam.pos[0] = 0;	 cam.pos[1] = -15;	cam.pos[2] = 5;
	cam.ang[0] = -18.0f;
}

EDemo::~EDemo(void){ /*...*/ }

/*
**	GENERAL	STUFF
*/
/*
**	EDemo::Init()
*/
void EDemo::Init(void)
{
	PRINTF("\r\n---- Demo Initialization ----------------\r\n");

	wgl.InitDisplay();
	wgl.InitOpenGL();
	//ext.Init();

	PRINTF("Loading :\r\n");
	glGenTextures(256, &texobj[0]);

	uicore.Init();	
	
	fe.Init();
	
	_control87(_PC_53, _MCW_PC);
	//_control87(_DN_FLUSH, _MCW_DN);

	PRINTF("-----------------------------------------\r\n");
}


/*
**	EDemo::Shutdown()
*/
void EDemo::Shutdown(void)
{
	PRINTF("\r\n---- Demo Shutting down -----------------\r\n");
	
	fe.Shutdown();
	
	uicore.Shutdown();

	glDeleteTextures(256, &texobj[0]);

	wgl.ShutdownOpenGL();
	wgl.ShutdownDisplay();

	PRINTF("-----------------------------------------\r\n");
}


/*
**	EDemo::Frame()
*/
void EDemo::Frame(void)
{
	int x,y,w,h;
	wgl.GetViewport(&x, &y, &w, &h);
	glViewport(0,0, w,h);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	uicore.Process();
	fe.UpdateControls();
	
	//Sleep(5);

	wgl.FinalizeFrame();
	Control();
}


/*
**	EDemo::MakeViewTexture()
*/
void EDemo::MakeViewTexture(void) {
	// do nothing
}


/*
**	EDemo::DrawScene()
*/
void EDemo::DrawScene(void)
{
	//-------------------------------------------------
	// Draw Grid
	glEnable(GL_TEXTURE_2D);
	this->BindTexture(0);

	glBegin(GL_QUADS);
		glTexCoord2f(1,1); glVertex3f( 5, 5, 1);
		glTexCoord2f(0,1); glVertex3f(-5, 5, 1);
		glTexCoord2f(0,0); glVertex3f(-5,-5, 1);
		glTexCoord2f(1,0); glVertex3f( 5,-5, 1);
	glEnd();
	
	//-------------------------------------------------
	// Draw Grid
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	Grid(32);
}


/*
===============================================================================

	MISC.

===============================================================================
*/
/*
**	EDemo::SetCamera()
*/
void EDemo::SetCamera(float fov, float nearf, float farf, float *ang, float *pos)
{
	float A = 0.75f, W = tanf(fov/57.29f/2.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-nearf*W, nearf*W, -nearf*A*W, nearf*A*W, nearf, farf);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(-90, 1,0,0);
	glRotatef(-ang[0], 1,0,0);
	glRotatef(-ang[2], 0,0,1);
	glTranslatef(-pos[0], -pos[1], -pos[2]);

}


/*
**	EDemo::Control()
*/
void EDemo::Control(void)
{
	static int last = sys.Milliseconds();
	float	delta = (sys.Milliseconds() - last)*0.001f;
	last = sys.Milliseconds();

	if (sys.ScanKey('1')) texbase = 0*4;
	if (sys.ScanKey('2')) texbase = 1*4;
	if (sys.ScanKey('3')) texbase = 2*4;
	if (sys.ScanKey('4')) texbase = 3*4;

	if (sys.ScanKey(0x25))	cam.ang[2]+=	180*delta;
	if (sys.ScanKey(0x27))	cam.ang[2]-=	180*delta;
	if (sys.ScanKey(0x26))	cam.ang[0]-=	90*delta;
	if (sys.ScanKey(0x28))	cam.ang[0]+=	90*delta;

	if (sys.ScanKey('S')){	// forward
		cam.pos[0]+= cosf((cam.ang[2] + 90)/57.29f) *delta*10.0f;
		cam.pos[1]+= sinf((cam.ang[2] + 90)/57.29f) *delta*10.0f;
	}
	if (sys.ScanKey('Z')){	// backward
		cam.pos[0]-= cosf((cam.ang[2] + 90)/57.29f) *delta*10.0f;
		cam.pos[1]-= sinf((cam.ang[2] + 90)/57.29f) *delta*10.0f;
	}
	if (sys.ScanKey('X')){	// strafe right
		cam.pos[0]+= cosf((cam.ang[2] +  0)/57.29f) *delta*10.0f;
		cam.pos[1]+= sinf((cam.ang[2] +  0)/57.29f) *delta*10.0f;
	}
	if (sys.ScanKey('A')){	// strafe left
		cam.pos[0]-= cosf((cam.ang[2] +  0)/57.29f) *delta*10.0f;
		cam.pos[1]-= sinf((cam.ang[2] +  0)/57.29f) *delta*10.0f;
	}

	if (sys.ScanKey(' '))	cam.pos[2]+=	delta*5.0f;
	if (sys.ScanKey('C'))	cam.pos[2]-=	delta*5.0f;
}


/*
**
*/
vhandle	EDemo::RegisterImage(const char *name)
{
	LoadTexture( image_count, name );
	PRINTF("...image registered %3d : %s\r\n", image_count, name);
	image_count++;
	return (image_count-1);	
}


/*
**	EDemo::LoadTexture()
*/	
void EDemo::LoadTexture(int n, const char *name)
{
	BindTexture(n);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	ETgaImage	img;
	img.Load(name);

	int format = GL_RGB;
	if (img.GetColorBpp()==32) format = GL_RGBA;

	gluBuild2DMipmaps(	GL_TEXTURE_2D, 
						img.GetColorBpp()/8,	
						img.GetWidth(), 
						img.GetHeight(), 
						format, GL_UNSIGNED_BYTE, img.GetImageData());
	img.Free();	
}


void EDemo::BindTexture(int n){
	glBindTexture(GL_TEXTURE_2D, texobj[n]);
}


/*
**	EDemo::Grid()
*/
void EDemo::Grid(int size)
{
	glPushMatrix();
		glTranslatef(0,0,1);
		glBegin(GL_LINES);
			glColor3f(1,0,0);	glVertex3f(0,0,0);	glVertex3f(1,0,0);
			glColor3f(0,1,0);	glVertex3f(0,0,0);	glVertex3f(0,1,0);
			glColor3f(0,0,1);	glVertex3f(0,0,0);	glVertex3f(0,0,1);
		glEnd();
	glPopMatrix();

	glBegin(GL_LINES);
		for (int i=-size; i<size; i++)		{
			if (!(i&0x7)) glColor3f(0.4f,0.4f,0.4f);
					else  glColor3f(0.2f,0.2f,0.2f);
			glVertex3i(i, size, 0);
			glVertex3i(i, -size, 0);
			glVertex3i(size, i, 0);
			glVertex3i(-size, i, 0);
		}
	glEnd();

	glColor3f(1,1,1);
}








