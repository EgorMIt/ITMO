//
//	WINGL.H
//

#ifndef _WINGL_H_
#define _WINGL_H_

#define	WGL_WNDNAME		"Network Fourier 2.0"
#define	WGL_CLASSNAME	"OpenGL Display"
#define WS_WINDOW		WS_CLIPCHILDREN | WS_CLIPSIBLINGS
#define WS_FULLSCR		WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP
#define WBORDER			2*GetSystemMetrics(SM_CXFIXEDFRAME)
#define HBORDER			2*GetSystemMetrics(SM_CYFIXEDFRAME)+GetSystemMetrics(SM_CYCAPTION)

const	int	mode_list[8][2]	= {
			320, 240,		400, 300,
			512, 384,		640, 480,
			800, 600,		1024, 768,
			1280, 1024,		1600, 1280	};

class EWinGL
	{
	private:
		HWND	hWnd;
		HDC		hDC;
		HGLRC	hRC;

		uint	mode;
		uint	fullscr;
		uint	pos[2];
		uint	colorbpp;
		uint	depthbpp;
		uint	stencilbpp;

	public:
					EWinGL(void);
					~EWinGL(void);

		void		InitDisplay(void);		// creates window and changes display mode
		void		ShutdownDisplay(void);	// destoys window and set default disp mode

		void		InitOpenGL(void);		// creates GL context
		void		ShutdownOpenGL(void);	// kills GL context

		void		FinalizeFrame(void);	// swaps buffers.

		void		GetViewport(int *x, int *y, int *w, int *h);

	static	LRESULT	__stdcall WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	static	void	ListDispModes_f(void);
	};



#endif //_WINGL_H_