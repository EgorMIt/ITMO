//
//	WIN_MAIN.CPP
//
//	descr : 
//

#include "demo_def.h"


ESystem		sys;
EWinGL		wgl;
EDemo		demo;
EArbExt		ext;
EUICore		uicore;
EFourierEngine	fe;

//
//	WinMain()
//
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPTSTR lpCmdLine, int nCmdShow)
{
	MSG	msg;

	PRINTF("Engine Demo\r\n");

	demo.Init();

	while(true)
	{
		if ( PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE) )
		{
			if ( GetMessage(&msg, 0, 0, 0) )
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}else break;
		}else
		{			
			demo.Frame();
		}
	}

	demo.Shutdown();

	return 0;
}








