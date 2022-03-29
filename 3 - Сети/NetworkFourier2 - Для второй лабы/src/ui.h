//
//	UI.H
//


#pragma once


void bar(int x, int y, int w, int h, const float *clr);
void bar_flat(int x, int y, int w, int h, const float *clr);
void cursor(int shp, int x, int y);

const int	UI_LBTN		= 0;
const int	UI_RBTN		= 1;
const int	UI_MBTN		= 2;


const int	UI_DESKTOP_WIDTH		= 800;
const int	UI_DESKTOP_HEIGHT		= 600;

const uint	UI_COLOR_BACKGROUND			= 0;	
const uint	UI_COLOR_FOREGROUND			= 1;	
const uint	UI_COLOR_TEXT				= 2;
const uint	UI_COLOR_ACTIVE				= 3;
const uint	UI_COLOR_INACTIVE			= 4;
const uint	UI_COLOR_HIGHLIGHT			= 5;
const uint	UI_COLOR_DARKFOREGROUND		= 6;
	

const uint	UI_MAX_CHILDS			= 16;

const float	uicolors[16][4]	= {
				0.0f,	0.0f,	0.0f,	0.0f,		// background
				1.0f,	1.0f,	1.0f,	0.2f,		// foreground
				0.9f,	0.9f,	0.9f,	1.0f,		// text
				
				0.0f,	0.0f,	0.0f,	1.0f,		// active
				0.3f,	0.3f,	0.3f,	1.0f,		// inactive
				0.0f,	0.1f,	0.2f,	0.4f,		// highlight
				
				0.0f,	0.0f,	0.0f,	0.4f,		// darken
								
				0,0,0,0
			};


typedef struct	uirect_s {	
		int	x,y;
		int	w,h;
	}uirect_t;
	
typedef struct uipoint_s {
		int x,y;
	}uipoint_t;


class	EUICore;
class	EUIFrame;
typedef EUIFrame	*HFrame;


class EUIFrame	
	{	
	friend EUICore;
	protected:
		HFrame		childs[UI_MAX_CHILDS];
		HFrame		parent;
		
		uirect_t	rect;	
		EStr		text;
		int			color;
		
		bool		visible;
		
	public:
					EUIFrame		( void );
		virtual		~EUIFrame		( void );
		
		void		Spawn			( HFrame child );
		
		// Utility function :
		void		SetFrameRect	( int x, int y, int w, int h ) {
						rect.x = x; rect.y = y; rect.w = w; rect.h = h; 
					}
		void		SetFrameRect	( uirect_t *r ) {
						rect.x = r->x; rect.y = r->y;  rect.w = r->w; rect.h = r->h; 
					}
		uirect_t	GetFrameRect	( void ) { return rect; }
		uirect_t	GetAbsoluteRect	( void );
					
		void		SetFrameText	( const char *newtext ) { text.Set( newtext ); }
		const char	*GetFrameText	( void ) { return text.c_str(); }
		
		void		SetColor		( uint clr ) { color = clr; }
		int			GetColor		( void )	{ return color; }
		
		bool		IsVisible		( void ) { return visible; };
		void		SetVisibility	( bool vis ) { visible = vis; };
		
		uipoint_t	GetRelativeCursorPos	( void );		

		// Handlers :
		virtual	void	FMPaint			( void );
		virtual void	FMMouseIn		( void );	// mouse come to the frame
		virtual void	FMMouseOut		( void );	// mouse leave the frame
		virtual	void	FMClick			( int button, int x, int y );
		virtual void	FMMouseDown		( int button, int x, int y );
		virtual void	FMMouseUp		( int button, int x, int y );
		//virtual	void	FMMouseClick	( int button, int x, int y );
		virtual void	FMChar			( char code ) {/**/};
		virtual void	FMKeydown		( char code ) {/**/};
	};



class EUIDesktop: public EUIFrame
	{
		uint	background;
	public:
						EUIDesktop		( void );	 
		virtual	void	FMPaint			( void );		// draw frame
	};


class EUICore	
	{
	private:
		EUIFrame	*desktop;
		uint		font_image;
		
		HFrame		active;
		
		int			mouse[2];
		HFrame		under_cursor;
		HFrame		last_under_cursor;
		EStr		hint;
		
	public:
					EUICore			( void );
					~EUICore		( void );

		// general :				
		void		Init			( void );
		void		Shutdown		( void );
		void		Process			( void );
		void		TransferMessage	( uint msg, uint wp, uint lp );

		// ui :		
		HFrame		Desktop			( void ) { return desktop; }
		void		SetActiveFrame	( HFrame f ) { active = f; }
		HFrame		GetActiveFrame	( void ) { return active; }

		//uirect_t	GetAbsoluteRect	( HFrame *frm );		
		HFrame		GetFrameUnderCursor	( void );
		uipoint_t	GetMousePos		( void ) { uipoint_t p = {mouse[0],mouse[1]}; return p; }
		
		void		SetHint			( const char *text ) { hint.Set(text); }
		
		
		// drawing :
		uint		GetFontImage	( void );
		void		DrawImage	( float x, float y, float w, float h, uint image );
		void		DrawChar	( float x, float y, float size, int ch );
		void		DrawString	( float x, float y, float width, float height, const char *str );
		void		DrawTiledImage(float x, float y, float rep_x, float rep_y, float w, float h, uint image);
		
		const float	*Color	( uint clr ){ return uicolors[clr]; };
	};



/*-----------------------------------------------------------------------------
	CUSTOM UI CONTROLS
-----------------------------------------------------------------------------*/
typedef void	(*btn_func_t)(void *);

class EUIPanel: public EUIFrame
	{
	public:
		virtual void	FMPaint		( void );
	};

class EUIButton: public EUIFrame
	{
		bool	under_mouse;
		bool	is_pressed;
		btn_func_t	func;
		
	public:
				EUIButton	( void );
				EUIButton	( btn_func_t f );
				
		virtual	void	FMPaint		( void );
		virtual	void	FMMouseIn	( void ) { under_mouse = true; }
		virtual	void	FMMouseOut	( void ) { under_mouse = false; is_pressed = false; }
		virtual void	FMMouseDown	( int button, int x, int y );
		virtual void	FMMouseUp	( int button, int x, int y );
			
	};


class EUIEdit: public EUIFrame
	{
		int		maxchars;
	public:
				EUIEdit		( void );
				
				EUIEdit		( uint maxchars );
				
		virtual	void	FMPaint		( void );
		virtual void	FMMouseDown	( int button, int x, int y );
		virtual void	FMMouseUp	( int button, int x, int y ) {/**/}
		virtual void	FMChar		( char code );
	};


class EUIStatic: public EUIFrame
	{
		int		maxchars;
	public:
				EUIStatic		( void );
				
		virtual	void	FMPaint		( void );
	};


class EUISpin:	public EUIFrame
	{
		float	max;
		float	min;
		float	current;
		float	step;
		bool	is_pressed[2];		// for left and right
	public:
				EUISpin		( void );
				EUISpin		( float min, float max, float cur, float step );
				
		virtual	void	FMPaint		( void );
		virtual void	FMMouseOut	( void );
		virtual void	FMMouseDown	( int button, int x, int y );
		virtual void	FMMouseUp	( int button, int x, int y );
		virtual void	FMChar		( char code );
		virtual void	FMKeydown	( char code );
	};



class EUIRadio:	public EUIFrame
	{
		int		selected;
		int		num;
		char	**list;
	public:
				EUIRadio	( void );
				EUIRadio	( int n, const char **list );
				
		int		GetSelected	( void ) { return selected; }
				
		virtual	void	FMPaint		( void );
		virtual void	FMMouseOut	( void );
		virtual void	FMMouseDown	( int button, int x, int y );
		virtual void	FMMouseUp	( int button, int x, int y );
		virtual void	FMChar		( char code );
		virtual void	FMKeydown	( char code );
	};


class EUIFlag:	public EUIFrame
	{
		int		flags;
		int		num;
		char	**list;
	public:
				EUIFlag	( void );
				EUIFlag	( int n, const char **list, int flags );
				
		int		GetFlags	( void ) { return flags; }
				
		virtual	void	FMPaint		( void );
		virtual void	FMMouseOut	( void );
		virtual void	FMMouseDown	( int button, int x, int y );
		virtual void	FMMouseUp	( int button, int x, int y );
		virtual void	FMChar		( char code );
		virtual void	FMKeydown	( char code );
	};
















