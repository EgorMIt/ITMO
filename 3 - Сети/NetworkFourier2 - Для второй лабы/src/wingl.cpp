//
//	GL_WINGL.H
//	
//	descr : OS specific part of OpenGL
//

#include "demo_def.h"


EWinGL::EWinGL(void)
{ 
	colorbpp		= 32;
	depthbpp		= 24;
	stencilbpp		= 8;
	mode	= 4;
	fullscr	= 0;
	pos[0]	= 100;
	pos[1]	= 50;
}

EWinGL::~EWinGL(void){ /* do nothing */ }



/*
**	EWinGL::InitDisplay()
*/
void EWinGL::InitDisplay(void)
{
	PRINTF("Display initialization:\r\n");
	DEVMODE		devmode;
	WNDCLASSEX	wc;
	int		w = mode_list[mode&0x7][0];
	int		h = mode_list[mode&0x7][1];

	// setting display mode :
	PRINTF("...setting display mode : ");

		memset(&devmode, 0, sizeof(devmode));
		devmode.dmSize			= sizeof(DEVMODE);
		devmode.dmPelsWidth		= w;
		devmode.dmPelsHeight	= h;
		devmode.dmFields		= DM_PELSWIDTH | DM_PELSHEIGHT;

		PRINTF("%dx%d ", w,h);
		if (fullscr) PRINTF("FS "); else PRINTF("W ");

		if ( fullscr )
			if (ChangeDisplaySettings(&devmode, CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
			{
				FATAL(va("EWinGL::InitDisplay() : Mode %dx%d is not supported in fullscreen\r\n", w,h));
			}
		PRINTF("ok\r\n");

	//	creation window :
	PRINTF("...registering class : ");
		memset(&wc, 0, sizeof(WNDCLASSEX));
		wc.cbSize			= sizeof (WNDCLASSEX);
		wc.lpfnWndProc		= WndProc;	
		wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.hInstance		= GetModuleHandle(NULL);
		wc.hbrBackground	= (HBRUSH)(4);
		wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName	= WGL_CLASSNAME;

		if (!RegisterClassEx (&wc))	FATAL( "EWinGL::InitDisplay() : RegisterClassEx() failed.");
		else PRINTF("ok\r\n");

	PRINTF("...creating window : ");
		if (fullscr)
			hWnd = CreateWindow(WGL_CLASSNAME, WGL_WNDNAME, WS_FULLSCR, 
								0,0, w,h, 
								NULL, NULL, GetModuleHandle(NULL), 0);
		else
			hWnd = CreateWindow(WGL_CLASSNAME, WGL_WNDNAME, WS_WINDOW, 
								pos[0], pos[1],
								w + WBORDER, h + HBORDER, 
								NULL, NULL, GetModuleHandle(NULL), 0);

		if (!hWnd) FATAL( "EWinGL::InitDisplay() : CreateWindow() failed.");
		else PRINTF("ok\r\n");

		ShowWindow(hWnd, SW_NORMAL);
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);
		UpdateWindow(hWnd);
}

/*
**	EWinGL::ShutdownDisplay(void)
*/
void EWinGL::ShutdownDisplay(void)
{
	PRINTF("...window destroying : ");
	if ( DestroyWindow(hWnd) )	PRINTF("ok\r\n");
						else	PRINTF("failed\r\n");

	PRINTF("...unregistering class : ");
	if ( UnregisterClass(WGL_CLASSNAME, GetModuleHandle(NULL)) ) 
		PRINTF("ok\r\n"); else
		PRINTF("failed\r\n");

	PRINTF("...restoring display mode : ");
	ChangeDisplaySettings(0, 0);
	PRINTF("ok\r\n");
}


LRESULT	EWinGL::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	uicore.TransferMessage( uMsg, (uint)wParam, (uint)lParam );
	switch( uMsg )
	{ 
	case WM_MOVE :		break;
    case WM_CREATE :	break;
    case WM_KEYDOWN :	break;
    case WM_CHAR :		break;
    case WM_CLOSE :	 
			PostQuitMessage(0);
			return 0;
			break;
    case WM_DESTROY :	break;
	default :	return DefWindowProc( hWnd, uMsg, wParam, lParam ) ;
	} 
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



/*
**	EWinGL::InitOpenGL()
*/
void EWinGL::InitOpenGL(void)
{
	PRINTF("OpenGL initialization:\r\n");
	static PIXELFORMATDESCRIPTOR	pfd;

	PRINTF("...getting dc : ");
	hDC = GetDC(hWnd);
	if (!hDC) FATAL( "WGL_InitOpenGL() : GetDC() failed.");
	else PRINTF("ok\r\n");

		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.cColorBits		= (uchar)colorbpp;
		pfd.cDepthBits		= (uchar)depthbpp;
		pfd.cStencilBits	= (uchar)stencilbpp;
		pfd.dwFlags			= PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.nSize			= sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion		= 1;
		pfd.iLayerType		= PFD_MAIN_PLANE;

	int iPixelFormat		= 0;

	PRINTF("...choosing pixel format : ");
	iPixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (!iPixelFormat) FATAL( "EWinGL::InitOpenGL() : ChoosePixelFormat() failed");
	else PRINTF("ok\r\n");
	
	PRINTF("...setting pixel format : ");
	if ( !SetPixelFormat(hDC, iPixelFormat, &pfd) ) FATAL( "EWinGL::InitOpenGL() : SetPixelFormat() failed");
	else PRINTF("ok\r\n");

	PRINTF("...context creation : ");
	hRC = wglCreateContext(hDC);
	if ( !hRC ) FATAL( "EWinGL::InitOpenGL() : wglCreateContext() failed");
	else PRINTF("ok\r\n");

	PRINTF("...making context current : ");
	if( !wglMakeCurrent(hDC, hRC) ) FATAL( "EWinGL::InitOpenGL() : wglMakeCurrent() failed");
	else PRINTF("ok\r\n");
}

/*
**	EWinGL::ShutdownOpenGL()
*/
void EWinGL::ShutdownOpenGL()
{
	if (hRC)
	{
		PRINTF("...making current NULL : ");
		if ( !wglMakeCurrent(NULL, NULL) ) PRINTF("failed\r\n");
		else PRINTF("ok\r\n");

		PRINTF("...deleting context : ");
		if ( !wglDeleteContext(hRC) ) PRINTF("failed\r\n");
		else PRINTF("ok\r\n");
	}

	PRINTF("...releasing dc : ");
	if (hDC){
		if ( !ReleaseDC(hWnd, hDC) ) PRINTF("failed\r\n");
		else PRINTF("ok\r\n");
	}
}


/*
**	EWinGL::FinalizeFrame();
*/
void EWinGL::FinalizeFrame(void)
{
	const int NUM = 64;
	static uint last_time = sys.Milliseconds();
	static uint num = 0;
	static uint frame_time[NUM] ;
	uint	time;
	float	average = 0;

	frame_time[(num++)&(NUM-1)] = sys.Milliseconds()-last_time;
	time = sys.Milliseconds()-last_time;
	last_time = sys.Milliseconds();

	char str[512];
	for (int i=0; i<NUM; i++) average += frame_time[i];
	average/=(float)NUM;
	
	Sleep(1);

	sprintf(str, "%s : frame time = %6.2f", WGL_WNDNAME, average);

		SetWindowText(hWnd, str);	

	// swap buffers :
	if ( !SwapBuffers(hDC) ) 
		FATAL( "EWinGL::FinalizeFrame() : SwapBuffers() failed");
}


/*
**	EWinGL::GetViewport()
*/
void EWinGL::GetViewport(int *x, int *y, int *w, int *h)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);
	*x = rect.left;
	*y = rect.top;
	*w = mode_list[mode&0x7][0];
	*h = mode_list[mode&0x7][1];
}



void EWinGL::ListDispModes_f(void)
{
	PRINTF("Display modes :\r\n");
	for (int i=0; i<8; i++)
		PRINTF(" %2d : %4dx%d\r\n", i, mode_list[i][0], mode_list[i][1]);
}








