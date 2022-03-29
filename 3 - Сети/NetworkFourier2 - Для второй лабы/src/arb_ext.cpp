//
//	ARB_EXT.CPP
//

#include "demo_def.h"


PROC EArbExt::GetProcAddr(const char *str)
{
	PROC proc = wglGetProcAddress(str);
	if (!proc) FATAL(va("R_GetProcAddress() : ext function %s() not found", str));
	return proc;
}


void EArbExt::Init(void)
{
	PRINTF("GL Extension initialzing:\r\n");
	PRINTF("...allowing fragment shaders\r\n");
	// FRAGMENT SHADERS :
	glProgramStringARB				 =(PFNGLPROGRAMSTRINGARBPROC				)GetProcAddr("glProgramStringARB");
	glBindProgramARB				 =(PFNGLBINDPROGRAMARBPROC					)GetProcAddr("glBindProgramARB");
	glDeleteProgramsARB              =(PFNGLDELETEPROGRAMSARBPROC				)GetProcAddr("glDeleteProgramsARB");
	glGenProgramsARB                 =(PFNGLGENPROGRAMSARBPROC					)GetProcAddr("glGenProgramsARB");
	glProgramEnvParameter4dARB       =(PFNGLPROGRAMENVPARAMETER4DARBPROC		)GetProcAddr("glProgramEnvParameter4dARB");
	glProgramEnvParameter4dvARB      =(PFNGLPROGRAMENVPARAMETER4DVARBPROC		)GetProcAddr("glProgramEnvParameter4dvARB");
	glProgramEnvParameter4fARB       =(PFNGLPROGRAMENVPARAMETER4FARBPROC		)GetProcAddr("glProgramEnvParameter4fARB");
	glProgramEnvParameter4fvARB      =(PFNGLPROGRAMENVPARAMETER4FVARBPROC		)GetProcAddr("glProgramEnvParameter4fvARB");
	glProgramLocalParameter4dARB     =(PFNGLPROGRAMLOCALPARAMETER4DARBPROC		)GetProcAddr("glProgramLocalParameter4dARB");
	glProgramLocalParameter4dvARB    =(PFNGLPROGRAMLOCALPARAMETER4DVARBPROC		)GetProcAddr("glProgramLocalParameter4dvARB");
	glProgramLocalParameter4fARB     =(PFNGLPROGRAMLOCALPARAMETER4FARBPROC		)GetProcAddr("glProgramLocalParameter4fARB");
	glProgramLocalParameter4fvARB    =(PFNGLPROGRAMLOCALPARAMETER4FVARBPROC		)GetProcAddr("glProgramLocalParameter4fvARB");
	glGetProgramEnvParameterdvARB    =(PFNGLGETPROGRAMENVPARAMETERDVARBPROC		)GetProcAddr("glGetProgramEnvParameterdvARB");
	glGetProgramEnvParameterfvARB    =(PFNGLGETPROGRAMENVPARAMETERFVARBPROC		)GetProcAddr("glGetProgramEnvParameterfvARB");
	glGetProgramLocalParameterdvARB  =(PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC	)GetProcAddr("glGetProgramLocalParameterdvARB");
	glGetProgramLocalParameterfvARB  =(PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC	)GetProcAddr("glGetProgramLocalParameterfvARB");
	glGetProgramivARB                =(PFNGLGETPROGRAMIVARBPROC					)GetProcAddr("glGetProgramivARB");
	glGetProgramStringARB            =(PFNGLGETPROGRAMSTRINGARBPROC				)GetProcAddr("glGetProgramStringARB");
	glIsProgramARB                   =(PFNGLISPROGRAMARBPROC					)GetProcAddr("glIsProgramARB");

	PRINTF("...allowing vertex shaders\r\n");
	// VERTEX SHADERS :	
	glVertexAttrib1sARB           = (PFNGLVERTEXATTRIB1SARBPROC				)GetProcAddr("glVertexAttrib1sARB");
	glVertexAttrib1fARB           = (PFNGLVERTEXATTRIB1FARBPROC				)GetProcAddr("glVertexAttrib1fARB");
	glVertexAttrib1dARB           = (PFNGLVERTEXATTRIB1DARBPROC				)GetProcAddr("glVertexAttrib1dARB");
	glVertexAttrib2sARB           = (PFNGLVERTEXATTRIB2SARBPROC				)GetProcAddr("glVertexAttrib2sARB");
	glVertexAttrib2fARB           = (PFNGLVERTEXATTRIB2FARBPROC				)GetProcAddr("glVertexAttrib2fARB");
	glVertexAttrib2dARB           = (PFNGLVERTEXATTRIB2DARBPROC				)GetProcAddr("glVertexAttrib2dARB");
	glVertexAttrib3sARB           = (PFNGLVERTEXATTRIB3SARBPROC				)GetProcAddr("glVertexAttrib3sARB");
	glVertexAttrib3fARB           = (PFNGLVERTEXATTRIB3FARBPROC				)GetProcAddr("glVertexAttrib3fARB");
	glVertexAttrib3dARB           = (PFNGLVERTEXATTRIB3DARBPROC				)GetProcAddr("glVertexAttrib3dARB");
	glVertexAttrib4sARB           = (PFNGLVERTEXATTRIB4SARBPROC				)GetProcAddr("glVertexAttrib4sARB");
	glVertexAttrib4fARB           = (PFNGLVERTEXATTRIB4FARBPROC				)GetProcAddr("glVertexAttrib4fARB");
	glVertexAttrib4dARB           = (PFNGLVERTEXATTRIB4DARBPROC				)GetProcAddr("glVertexAttrib4dARB");
	glVertexAttrib4NubARB         = (PFNGLVERTEXATTRIB4NUBARBPROC			)GetProcAddr("glVertexAttrib4NubARB");
	glVertexAttrib1svARB          = (PFNGLVERTEXATTRIB1SVARBPROC			)GetProcAddr("glVertexAttrib1svARB");
	glVertexAttrib1fvARB          = (PFNGLVERTEXATTRIB1FVARBPROC			)GetProcAddr("glVertexAttrib1fvARB");
	glVertexAttrib1dvARB          = (PFNGLVERTEXATTRIB1DVARBPROC			)GetProcAddr("glVertexAttrib1dvARB");
	glVertexAttrib2svARB          = (PFNGLVERTEXATTRIB2SVARBPROC			)GetProcAddr("glVertexAttrib2svARB");
	glVertexAttrib2fvARB          = (PFNGLVERTEXATTRIB2FVARBPROC			)GetProcAddr("glVertexAttrib2fvARB");
	glVertexAttrib2dvARB          = (PFNGLVERTEXATTRIB2DVARBPROC			)GetProcAddr("glVertexAttrib2dvARB");
	glVertexAttrib3svARB          = (PFNGLVERTEXATTRIB3SVARBPROC			)GetProcAddr("glVertexAttrib3svARB");
		//  ... it is stil VERTEX SHADERS...
	glVertexAttrib3fvARB          = (PFNGLVERTEXATTRIB3FVARBPROC			)GetProcAddr("glVertexAttrib3fvARB");
	glVertexAttrib3dvARB          = (PFNGLVERTEXATTRIB3DVARBPROC			)GetProcAddr("glVertexAttrib3dvARB");
	glVertexAttrib4bvARB          = (PFNGLVERTEXATTRIB4BVARBPROC			)GetProcAddr("glVertexAttrib4bvARB");
	glVertexAttrib4svARB          = (PFNGLVERTEXATTRIB4SVARBPROC			)GetProcAddr("glVertexAttrib4svARB");
	glVertexAttrib4ivARB          = (PFNGLVERTEXATTRIB4IVARBPROC			)GetProcAddr("glVertexAttrib4ivARB");
	glVertexAttrib4ubvARB         = (PFNGLVERTEXATTRIB4UBVARBPROC			)GetProcAddr("glVertexAttrib4ubvARB");
	glVertexAttrib4usvARB         = (PFNGLVERTEXATTRIB4USVARBPROC			)GetProcAddr("glVertexAttrib4usvARB");
	glVertexAttrib4uivARB         = (PFNGLVERTEXATTRIB4UIVARBPROC			)GetProcAddr("glVertexAttrib4uivARB");
	glVertexAttrib4fvARB          = (PFNGLVERTEXATTRIB4FVARBPROC			)GetProcAddr("glVertexAttrib4fvARB");
	glVertexAttrib4dvARB          = (PFNGLVERTEXATTRIB4DVARBPROC			)GetProcAddr("glVertexAttrib4dvARB");
	glVertexAttrib4NbvARB         = (PFNGLVERTEXATTRIB4NBVARBPROC			)GetProcAddr("glVertexAttrib4NbvARB");
	glVertexAttrib4NsvARB         = (PFNGLVERTEXATTRIB4NSVARBPROC			)GetProcAddr("glVertexAttrib4NsvARB");
	glVertexAttrib4NivARB         = (PFNGLVERTEXATTRIB4NIVARBPROC			)GetProcAddr("glVertexAttrib4NivARB");
	glVertexAttrib4NubvARB        = (PFNGLVERTEXATTRIB4NUBVARBPROC			)GetProcAddr("glVertexAttrib4NubvARB");
	glVertexAttrib4NusvARB        = (PFNGLVERTEXATTRIB4NUSVARBPROC			)GetProcAddr("glVertexAttrib4NusvARB");
	glVertexAttrib4NuivARB        = (PFNGLVERTEXATTRIB4NUIVARBPROC			)GetProcAddr("glVertexAttrib4NuivARB");
	glVertexAttribPointerARB      = (PFNGLVERTEXATTRIBPOINTERARBPROC		)GetProcAddr("glVertexAttribPointerARB");
	glEnableVertexAttribArrayARB  = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC	)GetProcAddr("glEnableVertexAttribArrayARB");
	glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC	)GetProcAddr("glDisableVertexAttribArrayARB");
	glGetVertexAttribdvARB        = (PFNGLGETVERTEXATTRIBDVARBPROC			)GetProcAddr("glGetVertexAttribdvARB");
	glGetVertexAttribfvARB        = (PFNGLGETVERTEXATTRIBFVARBPROC			)GetProcAddr("glGetVertexAttribfvARB");	
	glGetVertexAttribivARB        = (PFNGLGETVERTEXATTRIBIVARBPROC			)GetProcAddr("glGetVertexAttribivARB");
	glGetVertexAttribPointervARB  = (PFNGLGETVERTEXATTRIBPOINTERVARBPROC	)GetProcAddr("glGetVertexAttribPointervARB");

	PRINTF("...allowing multitexturing\r\n");
	// MULTITEXTURING :
	glActiveTextureARB			= (PFNGLACTIVETEXTUREARBPROC		)GetProcAddr("glActiveTextureARB");
	glClientActiveTextureARB	= (PFNGLCLIENTACTIVETEXTUREARBPROC	)GetProcAddr("glClientActiveTextureARB");
	glMultiTexCoord1dARB 		= (PFNGLMULTITEXCOORD1DARBPROC 		)GetProcAddr("glMultiTexCoord1dARB");
	glMultiTexCoord1dvARB		= (PFNGLMULTITEXCOORD1DVARBPROC		)GetProcAddr("glMultiTexCoord1dvARB");
	glMultiTexCoord1fARB 		= (PFNGLMULTITEXCOORD1FARBPROC 		)GetProcAddr("glMultiTexCoord1fARB");
	glMultiTexCoord1fvARB		= (PFNGLMULTITEXCOORD1FVARBPROC		)GetProcAddr("glMultiTexCoord1fvARB");
	glMultiTexCoord1iARB 		= (PFNGLMULTITEXCOORD1IARBPROC 		)GetProcAddr("glMultiTexCoord1iARB");
	glMultiTexCoord1ivARB		= (PFNGLMULTITEXCOORD1IVARBPROC		)GetProcAddr("glMultiTexCoord1ivARB");
	glMultiTexCoord1sARB 		= (PFNGLMULTITEXCOORD1SARBPROC 		)GetProcAddr("glMultiTexCoord1sARB");
	glMultiTexCoord1svARB		= (PFNGLMULTITEXCOORD1SVARBPROC		)GetProcAddr("glMultiTexCoord1svARB");
	glMultiTexCoord2dARB 		= (PFNGLMULTITEXCOORD2DARBPROC 		)GetProcAddr("glMultiTexCoord2dARB");
	glMultiTexCoord2dvARB		= (PFNGLMULTITEXCOORD2DVARBPROC		)GetProcAddr("glMultiTexCoord2dvARB");
	glMultiTexCoord2fARB 		= (PFNGLMULTITEXCOORD2FARBPROC 		)GetProcAddr("glMultiTexCoord2fARB");
	glMultiTexCoord2fvARB		= (PFNGLMULTITEXCOORD2FVARBPROC		)GetProcAddr("glMultiTexCoord2fvARB");
	glMultiTexCoord2iARB 		= (PFNGLMULTITEXCOORD2IARBPROC 		)GetProcAddr("glMultiTexCoord2iARB");
	glMultiTexCoord2ivARB		= (PFNGLMULTITEXCOORD2IVARBPROC		)GetProcAddr("glMultiTexCoord2ivARB");
	glMultiTexCoord2sARB 		= (PFNGLMULTITEXCOORD2SARBPROC 		)GetProcAddr("glMultiTexCoord2sARB");
	glMultiTexCoord2svARB		= (PFNGLMULTITEXCOORD2SVARBPROC		)GetProcAddr("glMultiTexCoord2svARB");
	glMultiTexCoord3dARB 		= (PFNGLMULTITEXCOORD3DARBPROC 		)GetProcAddr("glMultiTexCoord3dARB");
	glMultiTexCoord3dvARB		= (PFNGLMULTITEXCOORD3DVARBPROC		)GetProcAddr("glMultiTexCoord3dvARB");
	glMultiTexCoord3fARB 		= (PFNGLMULTITEXCOORD3FARBPROC 		)GetProcAddr("glMultiTexCoord3fARB");
	glMultiTexCoord3fvARB		= (PFNGLMULTITEXCOORD3FVARBPROC		)GetProcAddr("glMultiTexCoord3fvARB");
	glMultiTexCoord3iARB 		= (PFNGLMULTITEXCOORD3IARBPROC 		)GetProcAddr("glMultiTexCoord3iARB");
	glMultiTexCoord3ivARB		= (PFNGLMULTITEXCOORD3IVARBPROC		)GetProcAddr("glMultiTexCoord3ivARB");
	glMultiTexCoord3sARB 		= (PFNGLMULTITEXCOORD3SARBPROC 		)GetProcAddr("glMultiTexCoord3sARB");
	glMultiTexCoord3svARB		= (PFNGLMULTITEXCOORD3SVARBPROC		)GetProcAddr("glMultiTexCoord3svARB");
	glMultiTexCoord4dARB 		= (PFNGLMULTITEXCOORD4DARBPROC 		)GetProcAddr("glMultiTexCoord4dARB");
	glMultiTexCoord4dvARB		= (PFNGLMULTITEXCOORD4DVARBPROC		)GetProcAddr("glMultiTexCoord4dvARB");
	glMultiTexCoord4fARB 		= (PFNGLMULTITEXCOORD4FARBPROC 		)GetProcAddr("glMultiTexCoord4fARB");
	glMultiTexCoord4fvARB		= (PFNGLMULTITEXCOORD4FVARBPROC		)GetProcAddr("glMultiTexCoord4fvARB");
	glMultiTexCoord4iARB 		= (PFNGLMULTITEXCOORD4IARBPROC 		)GetProcAddr("glMultiTexCoord4iARB");
	glMultiTexCoord4ivARB		= (PFNGLMULTITEXCOORD4IVARBPROC		)GetProcAddr("glMultiTexCoord4ivARB");
	glMultiTexCoord4sARB 		= (PFNGLMULTITEXCOORD4SARBPROC 		)GetProcAddr("glMultiTexCoord4sARB");
	glMultiTexCoord4svARB		= (PFNGLMULTITEXCOORD4SVARBPROC		)GetProcAddr("glMultiTexCoord4svARB");
}
