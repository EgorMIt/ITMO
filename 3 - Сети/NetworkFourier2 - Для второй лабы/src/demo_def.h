//
//	ECL_DEF.H
//

#pragma once

// required libs:
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")


/*-----------------------------------------------------------------------------
	Tune compilator
-----------------------------------------------------------------------------*/
#pragma warning (1 : 4710)		// "not inlined" - warning of 1-th level

#pragma warning (disable : 4267) 
#pragma warning (disable : 4710) 
#pragma warning (disable : 4244) 

#define inline __forceinline

/*-----------------------------------------------------------------------------
	MESSAGE MACROS & DEFINITION
-----------------------------------------------------------------------------*/
#define ERR_FATAL		0x0001
#define ERR_SERVER		0x0002
#define ERR_CLIENT		0x0004


#define WARNING(s)		sys.Printf("\r\nWARNING : %s\r\n\r\n", s)
#define FATAL(s)		sys.Fatalf("%s", s)
#define PRINTF			sys.Printf
#define ASSERT(expr)	sys.FailAssert(#expr, __FUNCTION__, __FILE__, __LINE__);


#define BIT(n)	(1<<(n))

/*-----------------------------------------------------------------------------
	INCLUDING OF REQUIRED MODULES
-----------------------------------------------------------------------------*/
// std modules :
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "opengl\gl.h"
#include "opengl\glu.h"
#include "opengl\glext.h"

#include <float.h>

// basic types :
typedef unsigned char		uchar;
typedef unsigned long int	uint;
typedef unsigned short int	word;

typedef unsigned long int	vhandle;


// shared :
#include "shared\string2.h"

// custom modules :
#include "system.h"
#include "file.h"
#include "wingl.h"
#include "tga_image.h"
#include "demo.h"
#include "arb_ext.h"
#include "ui.h"
#include "ui_new.h"
#include "fourier.h"

extern	ESystem		sys;
extern	EWinGL		wgl;
extern	EDemo		demo;
extern	EArbExt		ext;
extern	EUICore		uicore;
extern	EFourierEngine	fe;










