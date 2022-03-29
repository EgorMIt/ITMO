//
//	UI_DRAW2D.CPP
//

#include "demo_def.h"


void EUICore::DrawImage(float x, float y, float w, float h, uint image)
{
	demo.BindTexture( image );

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
		glTexCoord2f(0,0);	glVertex3f( x+0,	y+h, 0 );
		glTexCoord2f(0,1);	glVertex3f( x+0,	y+0, 0 );
		glTexCoord2f(1,1);	glVertex3f( x+w,	y+0, 0 );
		glTexCoord2f(1,0);	glVertex3f( x+w,	y+h, 0 );
	glEnd();
}

void EUICore::DrawTiledImage(float x, float y, float rep_x, float rep_y, float w, float h, uint image)
{
	demo.BindTexture( image );

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
		glTexCoord2f(	0,	0		);	glVertex3f( x+0,	y+h, 0 );
		glTexCoord2f(	0,	rep_y	);	glVertex3f( x+0,	y+0, 0 );
		glTexCoord2f(rep_x,	rep_y	);	glVertex3f( x+w,	y+0, 0 );
		glTexCoord2f(rep_x,	0		);	glVertex3f( x+w,	y+h, 0 );
	glEnd();
}


void EUICore::DrawChar(float x, float y, float size, int ch )
{
	float u, v, s, d;
	ch &= 0xFF;
	s = 0.0625;

	d = size;
	u = (ch & 0x0F) * s;
	v = (ch >> 4) * s;

	//glColor4f(1.0f,1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(u,		1-v-0);	glVertex3f(x+0, y+0, 0);
		glTexCoord2f(u+s,	1-v-0); glVertex3f(x+d, y+0, 0);
		glTexCoord2f(u+s,	1-v-s); glVertex3f(x+d, y+d, 0);
		glTexCoord2f(u,		1-v-s);	glVertex3f(x+0, y+d, 0);
	glEnd();
}


void EUICore::DrawString(float x, float y, float width, float height, const char *str )
{
	int i, len;
	float cx, cy;

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	demo.BindTexture( font_image );	// 0 - is a font image...

	len = strlen(str);
	cx = x;
	cy = y;
	
	for (i=0; i<len; i++)
	{
		if (str[i]=='\r'){ cx = x; cy += height;	continue; }
		if (str[i]=='\n') continue;
		DrawChar(cx, cy, height, str[i]);
		cx+=width;
	}
}



















