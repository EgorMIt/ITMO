//
//	UI.CPP
//
//	descr : User Interface
//


#include "demo_def.h"

/*
===============================================================================

	UI Core

===============================================================================
*/
EUICore::EUICore(void)
{
}


EUICore::~EUICore(void)
{
}


/*
**	EUICore::Init()
*/
void EUICore::Init(void)
{
	PRINTF("\r\n---- UI Core Initialization -------------\r\n");
	
	font_image	= demo.RegisterImage("data\\chars.tga");
	//font_image	= demo.RegisterImage("data\\chars_ocr.tga");
	desktop = new EUIDesktop;		
	under_cursor = desktop;
	last_under_cursor = desktop;
	
	mouse[0] = 400;
	mouse[1] = 300;
	
	PRINTF("-----------------------------------------\r\n");
	
	//ShowCursor(false);
}


/*
**	EUICore::Shutdown()
*/
void EUICore::Shutdown(void)
{
	PRINTF("\r\n---- UI Core Shutting down --------------\r\n");
	//ShowCursor(true);
	
	delete desktop;
	
	PRINTF("-----------------------------------------\r\n");
}


/*
**	EUICore::TransferMessage()
*/
void EUICore::TransferMessage(uint msg, uint wp, uint lp )
{
	switch( msg )
	{ 
    case WM_DESTROY :	break;
    
    case WM_LBUTTONDOWN	:	GetFrameUnderCursor()->FMMouseDown(UI_LBTN, LOWORD(lp), HIWORD(lp));	break;
    case WM_RBUTTONDOWN	:	GetFrameUnderCursor()->FMMouseDown(UI_RBTN, LOWORD(lp), HIWORD(lp));	break;
    case WM_LBUTTONUP	:	GetFrameUnderCursor()->FMMouseUp(UI_LBTN, LOWORD(lp), HIWORD(lp));	break;
    case WM_RBUTTONUP	:	GetFrameUnderCursor()->FMMouseUp(UI_RBTN, LOWORD(lp), HIWORD(lp));	break;
    
    case WM_MOUSEMOVE	:
			mouse[0] = LOWORD(lp); 
			mouse[1] = HIWORD(lp); 
		break;
		
	case WM_CHAR	:	GetActiveFrame()->FMChar( wp ); break;
	case WM_KEYDOWN	:	GetActiveFrame()->FMKeydown( wp ); break;
	}
}


/*
**	EUICore::Process()
*/
void EUICore::Process(void)
{
	// prepare to drawing :
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho( 0, UI_DESKTOP_WIDTH, UI_DESKTOP_HEIGHT, 0, -10000, 10000 );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glPushMatrix();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// control mouse over :
		under_cursor = GetFrameUnderCursor();
		under_cursor->FMMouseIn();
		if (last_under_cursor!=under_cursor) last_under_cursor->FMMouseOut();
		last_under_cursor = under_cursor;

		// draw UI controls :
		desktop->FMPaint();
		
		/*bar(2,600-12,800-4,10, Color(UI_COLOR_ACTIVE));
		DrawString(4,600-11,8,8, hint.c_str());*/
	
		/*DrawString(0,0, 8,8, va("mouse        : %3d:%3d", mouse[0], mouse[1] ));
		DrawString(0,8, 8,8, va("under cursor : %s", GetFrameUnderCursor()->GetFrameText() ));*/
			
	glPopMatrix();
}




bool in_rect(uirect_t *r, int x, int y) {
	if (  (r->x < x)&(r->x+r->w > x) & (r->y < y)&(r->y+r->h > y)  ) return true;
	else return false;
}

HFrame	EUICore::GetFrameUnderCursor(void)
{
	uirect_t	r;
	HFrame	frm = desktop;
	
	_begin:
	for (int i=UI_MAX_CHILDS-1; i>=0; i--) 
	{
		if (frm->childs[i]) 
		{
			if (!frm->childs[i]->IsVisible()) continue;
			r = frm->childs[i]->GetAbsoluteRect();
			if (in_rect(&r, mouse[0], mouse[1]))
			{
				frm = frm->childs[i];
				goto _begin;
			}
		}
	}
	return frm;
}


/*
=======================================
	DESKTOP
=======================================
*/
EUIDesktop::EUIDesktop(void)
{
	this->SetColor(0);
	this->SetFrameText("Desktop");
	this->SetFrameRect(0, 0, UI_DESKTOP_WIDTH, UI_DESKTOP_HEIGHT);
	
	background	=	demo.RegisterImage("data\\circuit4.tga");
//	background	=	demo.RegisterImage("data\\cells_128.tga");
//	background	=	demo.RegisterImage("data\\circuit3.tga");
}

void EUIDesktop::FMPaint(void)
{
	//glColor4f(0,0,0,1);
	uicore.DrawTiledImage(0,0, 16,12, 800,600, background);
	
	glDisable(GL_TEXTURE_2D);

	
	for (int i=0; i<UI_MAX_CHILDS; i++)
		if (this->childs[i]) childs[i]->FMPaint();
}




/*
===============================================================================

	UI Frame

===============================================================================
*/
EUIFrame::EUIFrame(void)
{
	this->SetColor(1);
	this->SetFrameText("Frame");
	this->SetFrameRect(10,10,200,100);
	this->SetVisibility(true);

	parent	= NULL;		
	for (int i=0; i<UI_MAX_CHILDS; i++) childs[i] = NULL;
}


EUIFrame::~EUIFrame(void)
{
	for (int i=0; i<UI_MAX_CHILDS; i++)
		if (this->childs[i]) delete childs[i];
}


void EUIFrame::Spawn( HFrame child )
{
	for (int i=0; i<UI_MAX_CHILDS; i++)
		if (!this->childs[i]) 
		{
			child->parent = this;
			childs[i] = child;
			
			uicore.SetActiveFrame( child );
			
			return;
		}
		
	FATAL(__FUNCTION__"() : Can`not create child window!");
}



uirect_t	EUIFrame::GetAbsoluteRect(void)
{
	uirect_t	r = {0,0,rect.w,rect.h};
	HFrame	frm = this;
	
	while (frm) {
		r.x += frm->rect.x;
		r.y += frm->rect.y;
		frm = frm->parent;
	}
	return r;
}



uipoint_t	EUIFrame::GetRelativeCursorPos(void)
{
	uipoint_t	pos = uicore.GetMousePos();
	uirect_t	r = GetAbsoluteRect();
	pos.x -= r.x;
	pos.y -= r.y;
	return  pos;
}


/*
=======================================
	HANDLERS
=======================================
*/
void EUIFrame::FMPaint(void)
{
	int x,y,w,h;
	
	if (!visible) return;
	
	x = rect.x;  y = rect.y;  
	w = rect.w;  h = rect.h;


	glPushMatrix();
	glTranslatef(x, y, 0);
	
		bar(0,0, w, h, uicore.Color( UI_COLOR_FOREGROUND ) );

		if (this==uicore.GetActiveFrame())	bar(2,2, w-4, 11, uicore.Color( UI_COLOR_ACTIVE ) );
									else	bar(2,2, w-4, 11, uicore.Color( UI_COLOR_INACTIVE ) );
		
		uicore.DrawString(2+1,2+1, 8,8, this->GetFrameText());
		
	
		for (int i=0; i<UI_MAX_CHILDS; i++)
			if (this->childs[i]) childs[i]->FMPaint();

	glPopMatrix();

}



void EUIFrame::FMClick(int button, int x, int y) {
	uicore.SetActiveFrame( this );
}


void EUIFrame::FMMouseIn(void) {
	uicore.SetHint("hint : it is a simple frame...");
}

void EUIFrame::FMMouseOut(void) {
}

void EUIFrame::FMMouseDown(int button, int x, int y) {
	uicore.SetActiveFrame( this );
}

void EUIFrame::FMMouseUp(int button, int x, int y) {
}



/*
===============================================================================

	UI Panel

===============================================================================
*/
void EUIPanel::FMPaint(void)
{
	int x,y,w,h;
	
	if (!visible) return;
	
	x = rect.x;  y = rect.y;  
	w = rect.w;  h = rect.h;


	glPushMatrix();
	glTranslatef(x, y, 0);
	
		bar(0,0, w, h, uicore.Color( UI_COLOR_FOREGROUND ) );
	
		for (int i=0; i<UI_MAX_CHILDS; i++)
			if (this->childs[i]) childs[i]->FMPaint();

	glPopMatrix();
}


/*
===============================================================================

	UI Button

===============================================================================
*/
EUIButton::EUIButton(void)
{
	this->SetColor(1);
	this->SetFrameText("Button");
	this->SetFrameRect(20, 20, 100, 75);
	
	under_mouse = false;
	is_pressed	= false;
	func		= NULL;
}

EUIButton::EUIButton(btn_func_t	f)
{
	this->SetColor(1);
	this->SetFrameText("Button");
	this->SetFrameRect(20, 20, 100, 75);
	
	under_mouse = false;
	is_pressed	= false;
	func		= f;
}



void EUIButton::FMPaint(void)
{
	int x,y,w,h;
	
	x = rect.x;  y = rect.y;  
	w = rect.w;  h = rect.h;

	glPushMatrix();
	glTranslatef(x, y, 0);
	
		bar(0,0, w, h, uicore.Color( UI_COLOR_FOREGROUND ) );
		
		if (under_mouse)
			bar(0,0, w-0, h-0, uicore.Color( UI_COLOR_HIGHLIGHT ) );

		if (is_pressed)
			bar(2,2, w-4, h-4, uicore.Color( UI_COLOR_HIGHLIGHT ) );

		uint len = this->text.getlen();
			uicore.DrawString(w/2-4*len, h/2-4, 8,8, this->GetFrameText());
		
		// NO CHILDS!!!

	glPopMatrix();
}


void EUIButton::FMMouseDown(int button, int x, int y)
{
	uicore.SetActiveFrame( this );
	is_pressed = true;
}

void EUIButton::FMMouseUp(int button, int x, int y)
{
	if (func) func(NULL);
	is_pressed = false;
}

/*
===============================================================================

	UI Edit

===============================================================================
*/
EUIEdit::EUIEdit(void)
{
	text.Set("Edit");
	maxchars = 8;
}

EUIEdit::EUIEdit( uint maxchars )
{
	text.Set("Edit");
	this->maxchars	= maxchars;
} 


void EUIEdit::FMPaint(void)
{
	int x,y,w,h;
	
	x = rect.x;  y = rect.y;  
	w = rect.w;  h = rect.h;

	glPushMatrix();
	glTranslatef(x, y, 0);
	
		bar(0,0, w, h, uicore.Color( UI_COLOR_FOREGROUND ) );
		if (uicore.GetActiveFrame()==this) 
				bar(0,2, w, h-4, uicore.Color( UI_COLOR_DARKFOREGROUND ) );
		else	bar(0,2, w, h-4, uicore.Color( UI_COLOR_BACKGROUND ) );

		uint len = this->text.getlen();
		uicore.DrawString(2, 3, 8,8, this->GetFrameText());

				
		if (uicore.GetActiveFrame()==this) 
			if (sinf(sys.Milliseconds()/66)>0)	
				uicore.DrawChar( 2+len*8, 3, 8, 8);

		// NO CHILDS!!!

	glPopMatrix();
}



void EUIEdit::FMMouseDown(int button, int x, int y){	
	uicore.SetActiveFrame( this );
}


void EUIEdit::FMChar(char code)
{
	if (code==VK_BACK) {
		if (text.getlen()==0) return;
		char temp[256];
		strcpy(temp, text.c_str());
		temp[strlen(temp)-1]='\0';
		text.Set(temp);
	}
	if ( text.getlen()>=maxchars) return;
	if ( isgraph(code) ) text.va("%s%c", text.c_str(), code);
}


/*
===============================================================================

	UI Static

===============================================================================
*/
EUIStatic::EUIStatic(void)
{
	text.Set("Static");
}


void EUIStatic::FMPaint(void)
{
	int x,y,w,h;
	
	x = rect.x;  y = rect.y;  
	w = rect.w;  h = rect.h;

	glPushMatrix();
	glTranslatef(x, y, 0);
	
		uicore.DrawString(2, 3, 8,8, this->GetFrameText());

		// NO CHILDS!!!

	glPopMatrix();
}


/*
===============================================================================

	UI Spin

===============================================================================
*/
EUISpin::EUISpin(void)
{
	EUISpin(0, 1, 0.5, 0.1 );
}


EUISpin::EUISpin( float min, float max, float cur, float step )
{
	this->max	= max;
	this->min	= min;
	this->step	= step;
	
	is_pressed[0] = is_pressed[1] = false;

	if (cur==floor(cur) && step==floor(step)) text.va("%5d",	  (int)cur);
					else text.va("%5.2f", (float)cur);
}


void EUISpin::FMPaint( void ) {
	int x,y,w,h;
	
	x = rect.x;  y = rect.y;  
	w = rect.w;  h = rect.h;

	glPushMatrix();
	glTranslatef(x, y, 0);
	
		bar(0,0, w, h, uicore.Color( UI_COLOR_FOREGROUND ) );
		if (uicore.GetActiveFrame()==this) 
				bar(12,0, w-24, h, uicore.Color( UI_COLOR_DARKFOREGROUND ) );
		else	bar(12,0, w-24, h, uicore.Color( UI_COLOR_BACKGROUND ) );

		uint len = this->text.getlen();
		uicore.DrawString(14, h/2-4, 8,8, this->GetFrameText());
		
		uipoint_t	mp = GetRelativeCursorPos();
		uirect_t	r = {0,0, rect.w, rect.h};
		
		if (in_rect(&r, mp.x, mp.y)) {
			if (mp.x<12)	bar(   0,0,	12, h-0, uicore.Color( UI_COLOR_HIGHLIGHT ) );
			if (mp.x>w-12)	bar(w-12,0, 12, h-0, uicore.Color( UI_COLOR_HIGHLIGHT ) );
		}
		
		if (is_pressed[0])	bar(   2,2,	 8, h-4, uicore.Color( UI_COLOR_HIGHLIGHT ) );
		if (is_pressed[1])	bar(w-10,2,   8, h-4, uicore.Color( UI_COLOR_HIGHLIGHT ) );
						
		uicore.DrawString(0,0,0,0,"");
		uicore.DrawChar(2,		h/2-4, 8, 17);
		uicore.DrawChar(w-10,	h/2-4, 8, 16);
		// NO CHILDS!!!

	glPopMatrix();
}


void EUISpin::FMMouseDown( int button, int x, int y ) 
{
	float val = text.tof();

	int w,h;
	
	w = rect.w;  
	h = rect.h;

	uicore.SetActiveFrame( this );

	uipoint_t	mp = GetRelativeCursorPos();
	uirect_t	r = {0,0, rect.w, rect.h};
	
	if (in_rect(&r, mp.x, mp.y)) {
		if (mp.x<12)	{	is_pressed[0] = true;   val-=step;	}
		if (mp.x>w-12)	{	is_pressed[1] = true;   val+=step;	}
	}

	if (val>max) val = max;
	if (val<min) val = min;
	
	if (val==floor(val) && step==floor(step)) text.va("%5d",	  (int)val);
					else text.va("%5.2f", (float)val);
}


void EUISpin::FMMouseUp( int button, int x, int y ) {
	is_pressed[0] = is_pressed[1] = false;
}

void EUISpin::FMMouseOut(void) {
	is_pressed[0] = is_pressed[1] = false;
}


void EUISpin::FMChar( char code ) {
}


void EUISpin::FMKeydown( char code ) {
	float val = text.tof();
	if (code==39) val+=step;
	if (code==37) val-=step;
	
	if (val>max) val = max;
	if (val<min) val = min;
	
	if (val==floor(val) && step==floor(step)) text.va("%5d",	  (int)val);
					else text.va("%5.2f", (float)val);
}



/*
===============================================================================

	UI Radio

===============================================================================
*/

EUIRadio::EUIRadio(void)
{
}


EUIRadio::EUIRadio( int n, const char **list )
{
	this->num	= n;
	this->list	= const_cast<char**>(list);
	selected = 0;
}


void EUIRadio::FMPaint( void ) 
{
	int x,y,w,h, i;
	
	//EUIFrame::FMPaint();
	
	x = rect.x;  y = rect.y;  
	w = rect.w;  h = rect.h;

	glPushMatrix();
	glTranslatef(x, y, 0);
	
		//bar(0,0, w, h, uicore.Color( UI_COLOR_FOREGROUND ) );

		for (i=0; i<num; i++)
		{
			if (uicore.GetFrameUnderCursor()==this) 
			{
				uipoint_t	p = GetRelativeCursorPos();
				if (p.y/12==i) bar(0, i*12+1, w, 11, uicore.Color( UI_COLOR_HIGHLIGHT ) );
			}
			
			uicore.DrawString(18, i*12+6-4, 8,8, list[i]);
			if (selected==i) uicore.DrawChar(2, i*12+6-4,8, 9);
						else uicore.DrawChar(2, i*12+6-4,8, 10);
						
		}
		
		// NO CHILDS!!!

	glPopMatrix();
}


void EUIRadio::FMMouseDown( int button, int x, int y ) 
{
	uicore.SetActiveFrame( this );
	if (uicore.GetFrameUnderCursor()==this) 
	{
		uipoint_t	p = GetRelativeCursorPos();
		selected = p.y/12;
	}
}


void EUIRadio::FMMouseUp( int button, int x, int y ) {
}

void EUIRadio::FMMouseOut(void) {
}


void EUIRadio::FMChar( char code ) {
}


void EUIRadio::FMKeydown( char code ) {
}


/*
===============================================================================

	UI CHECK BOX

===============================================================================
*/

EUIFlag::EUIFlag(void)
{
}


EUIFlag::EUIFlag( int n, const char **list, int flags )
{
	this->num	= n;
	this->list	= const_cast<char**>(list);
	this->flags = flags;
}


void EUIFlag::FMPaint( void ) 
{
	int x,y,w,h, i;
	
	//EUIFrame::FMPaint();
	
	x = rect.x;  y = rect.y;  
	w = rect.w;  h = rect.h;

	glPushMatrix();
	glTranslatef(x, y, 0);
	
		//bar(0,0, w, h, uicore.Color( UI_COLOR_FOREGROUND ) );

		for (i=0; i<num; i++)
		{
			if (uicore.GetFrameUnderCursor()==this) 
			{
				uipoint_t	p = GetRelativeCursorPos();
				if (p.y/12==i) bar(0, i*12+1, w, 11, uicore.Color( UI_COLOR_HIGHLIGHT ) );
			}
			
			uicore.DrawString(18, i*12+6-4, 8,8, list[i]);
			if (flags & (BIT(i))) uicore.DrawChar(2, i*12+6-4,8, 11);
							else uicore.DrawChar(2, i*12+6-4,8, 12);
						
		}
		
		// NO CHILDS!!!

	glPopMatrix();
}


void EUIFlag::FMMouseDown( int button, int x, int y ) 
{
	uicore.SetActiveFrame( this );
	if (uicore.GetFrameUnderCursor()==this) 
	{
		uipoint_t	p = GetRelativeCursorPos();
		flags ^= BIT(p.y/12);
		//PRINTF("%d\r\n", flags);
	}
}


void EUIFlag::FMMouseUp( int button, int x, int y ) {
}

void EUIFlag::FMMouseOut(void) {
}


void EUIFlag::FMChar( char code ) {
}


void EUIFlag::FMKeydown( char code ) {
}




















