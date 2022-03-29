//
//	FOURIER.CPP
//
//


#include "demo_def.h"

const char *code1_list[4] = {
		"NRZ", "RZ", "AMI", "Manchester"
	};

const char *code2_list[4] = {
		"Physical", "Super 4/5", "Scrambling"
	};

/*
===============================================================================

	UI

===============================================================================
*/
#include "about_box.h"


EUIQDiagram::EUIQDiagram()
{
	static int table[8] = {1,-1,1,-1, 1,0,-1,0, };
	this->SetGrid(2,1, 2,1);
	this->SetDiagram(1,0,8, table);
}


void EUIQDiagram::SetDiagram(int amp, int min, int max, int *table) 
{
	this->amp	=	amp;
	this->min	=	min;
	this->max	=	max;
	this->table	=	table;	
}

void EUIQDiagram::SetGrid(int gx, int sgx, int gy, int sgy)
{
	gridX		=	gx;
	subgridX	=	sgx;
	gridY		=	gy;
	subgridY	=	sgy;
}


void EUIQDiagram::FMPaint(void)
{
	EUIFrame::FMPaint();
	
	int x,y,w,h, i;

	uirect_t	r = GetAbsoluteRect();

	glPushMatrix();
	glTranslatef(rect.x, rect.y, 0);
	
		x = 4;			y = 16;
		w = rect.w-8;	h = rect.h-4-16;

		bar_flat(x, y, w, h, uicore.Color( UI_COLOR_DARKFOREGROUND ) );
		//glDisable(GL_TEXTURE_2D);

		glEnable(GL_SCISSOR_TEST);
		glScissor(r.x+4,	UI_DESKTOP_HEIGHT-(r.y+r.h-4), r.w+1-8, r.h+1-4-16);
		glViewport(r.x+4,	UI_DESKTOP_HEIGHT-(r.y+r.h-4), r.w+1-8, r.h+1-4-16);
		//------------------------------------------------------
		
		glPushMatrix();
		glLoadIdentity();
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		
		glLoadIdentity();
		float width = (-min+max)*0.03f;
		glOrtho( -width+min, width+max,  -amp*1.2f, amp*1.2f,  -8,8);
		
			//--------------------------------------------------
			// diagram :
			glColor4f(1,1,1, 0.7f);
		
			glBegin(GL_LINES);	
				glVertex3f(0, amp*1.1f, 0);
				glVertex3f(0, -amp*1.1f, 0);

				glVertex3f(min, 0, 0);
				glVertex3f(max,  0, 0);
				
				for (i=min; i<=max; i+=subgridX) {
					glVertex3f(i,  amp*0.05f, 0);
					glVertex3f(i, -amp*0.05f, 0);
				}
				for (i=-amp; i<=amp; i+=subgridY) {
					glVertex3f( width/4.0f, i, 0);
					glVertex3f(-width/4.0f, i, 0);
				}
				
				for (i=min; i<=max; i+=gridX) {
					glVertex3f(i,  amp*0.15f, 0);
					glVertex3f(i, -amp*0.15f, 0);
				}
				for (i=-amp; i<=amp; i+=gridY) {
					glVertex3f( width/2.0f, i, 0);
					glVertex3f(-width/2.0f, i, 0);
				}
				
			glEnd();
			
			glColor4f(1,1,1, 0.4f);

			glBegin(GL_LINE_STRIP);
			for (i=min; i<max; i++)	{
				glVertex3f(i+0, table[i], 0);
				glVertex3f(i+1, table[i], 0);
			}
			glEnd();			

			//--------------------------------------------------
			
		glPopMatrix();		
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		//------------------------------------------------------
		glScissor( 0, 0, UI_DESKTOP_WIDTH, UI_DESKTOP_HEIGHT);
		glViewport( 0, 0, UI_DESKTOP_WIDTH, UI_DESKTOP_HEIGHT);
		glDisable(GL_SCISSOR_TEST);

		glColor4f(1,1,1,1);		
		
	glPopMatrix();
}


//=============================================================================
float null_float_func_t	(float x) {
	return sinf(6.28*sinf(x));
}

EUIFDiagram::EUIFDiagram()
{
	this->SetGrid(5,1, 5,1);
	this->SetDiagram(1,0,8, 0.01, null_float_func_t);
}


void EUIFDiagram::SetDiagram(float amp, float min, float max, float step, float_func_t func )
{
	this->amp	=	amp;
	this->min	=	min;
	this->max	=	max;
	this->step	=	step;
	this->func	=	func;	
}

void EUIFDiagram::SetGrid(float gx, float sgx, float gy, float sgy)
{
	gridX		=	gx;
	subgridX	=	sgx;
	gridY		=	gy;
	subgridY	=	sgy;
}


void EUIFDiagram::FMPaint(void)
{
	EUIFrame::FMPaint();
	
	int x,y,w,h, i;

	uirect_t	r = GetAbsoluteRect();

	glPushMatrix();
	glTranslatef(rect.x, rect.y, 0);
	
		x = 4;			y = 16;
		w = rect.w-8;	h = rect.h-4-16;

		bar_flat(x, y, w, h, uicore.Color( UI_COLOR_DARKFOREGROUND ) );
		//glDisable(GL_TEXTURE_2D);

		glEnable(GL_SCISSOR_TEST);
		glScissor(r.x+4,	UI_DESKTOP_HEIGHT-(r.y+r.h-4), r.w+1-8, r.h+1-4-16);
		glViewport(r.x+4,	UI_DESKTOP_HEIGHT-(r.y+r.h-4), r.w+1-8, r.h+1-4-16);
		//------------------------------------------------------
		
		glPushMatrix();
		glLoadIdentity();
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		
		glLoadIdentity();
		float width = (-min+max)*0.03f;
		glOrtho( -width+min, width+max,  -amp*1.2f, amp*1.2f,  -8,8);
		
			//--------------------------------------------------
			// diagram :
			glColor4f(1,1,1, 0.7f);
			float fy = 0, fx = 0;
		
			glBegin(GL_LINES);	
				glVertex3f(0, amp*1.1f, 0);
				glVertex3f(0, -amp*1.1f, 0);

				glVertex3f(min, 0, 0);
				glVertex3f(max,  0, 0);
				
				for (fx=min; fx<=max; fx+=subgridX) {
					glVertex3f(fx,  amp*0.05f, 0);
					glVertex3f(fx, -amp*0.05f, 0);
				}
				for (fy=0; fy<=amp; fy+=subgridY) {
					glVertex3f( width/4.0f, fy, 0);
					glVertex3f(-width/4.0f, fy, 0);
					glVertex3f( width/4.0f, -fy, 0);
					glVertex3f(-width/4.0f, -fy, 0);
				}
				
				for (fx=min; fx<=max; fx+=gridX) {
					glVertex3f(fx,  amp*0.15f, 0);
					glVertex3f(fx, -amp*0.15f, 0);
				}
				for (fy=0; fy<=amp; fy+=gridY) {
					glVertex3f( width/2.0f, fy, 0);
					glVertex3f(-width/2.0f, fy, 0);
					glVertex3f( width/2.0f, -fy, 0);
					glVertex3f(-width/2.0f, -fy, 0);
				}  
				
			glEnd();

			fe.DrawSamplers(this->min, this->max);
	
			glColor4f(1,1,1, 0.4f);

			glBegin(GL_LINE_STRIP);
			for (fx=min; fx<max; fx+=step)	{
				glVertex3f(fx, func(fx), 0);
			}
			glEnd();			

			//--------------------------------------------------
			
		glPopMatrix();		
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		//------------------------------------------------------
		glScissor( 0, 0, UI_DESKTOP_WIDTH, UI_DESKTOP_HEIGHT);
		glViewport( 0, 0, UI_DESKTOP_WIDTH, UI_DESKTOP_HEIGHT);
		glDisable(GL_SCISSOR_TEST);

		glColor4f(1,1,1,1);		
		
	glPopMatrix();
}


/*
=======================================
	GUI CONTROLS
=======================================
*/
	
#define SPAWN_FRAME(owner, ctrl, x,y,w,h, caption)		\
			ctrl	= new EUIFrame;						\
			ctrl->SetFrameRect(x,y,w,h);			\
			ctrl->SetFrameText(caption);			\
			owner->Spawn(ctrl);
			
#define SPAWN_PANEL(owner, ctrl, x,y,w,h, caption)		\
			ctrl	= new EUIPanel;						\
			ctrl->SetFrameRect(x,y,w,h);			\
			ctrl->SetFrameText(caption);			\
			owner->Spawn(ctrl);
			
#define SPAWN_ABOUTBOX(owner, ctrl, x,y,w,h, caption)		\
			ctrl	= new EUIAbout;					\
			ctrl->SetFrameRect(x,y,w,h);			\
			ctrl->SetFrameText(caption);			\
			owner->Spawn(ctrl);
			
#define SPAWN_BUTTON(owner, ctrl, x,y,w,h, caption, handler)	\
			ctrl	= new EUIButton(handler);			\
			ctrl->SetFrameRect(x,y,w,h);			\
			ctrl->SetFrameText(caption);			\
			owner->Spawn(ctrl);
			
#define SPAWN_STATIC(owner, ctrl, x,y,w,h, caption)	\
			ctrl	= new EUIStatic;				\
			ctrl->SetFrameRect(x,y,w,h);			\
			ctrl->SetFrameText(caption);			\
			owner->Spawn(ctrl);

#define SPAWN_EDIT(owner, ctrl, x,y,w,h, caption, num)	\
			ctrl	= new EUIEdit(num);				\
			ctrl->SetFrameRect(x,y,w,h);			\
			ctrl->SetFrameText(caption);			\
			owner->Spawn(ctrl);
			
#define SPAWN_SPIN(owner, ctrl, x,y,w,h, min, max, cur, step)	\
			ctrl	= new EUISpin(min,max, cur, step);			\
			ctrl->SetFrameRect(x,y,w,h);			\
			owner->Spawn(ctrl);
			
#define SPAWN_RADIO(owner, ctrl, x,y,w,h, num, list)	\
			ctrl	= new EUIRadio(num, list);			\
			ctrl->SetFrameRect(x,y,w,h);			\
			owner->Spawn(ctrl);
			
#define SPAWN_FLAG(owner, ctrl, x,y,w,h, num, list, flags)	\
			ctrl	= new EUIFlag(num, list, flags);		\
			ctrl->SetFrameRect(x,y,w,h);			\
			owner->Spawn(ctrl);
			

#define SPAWN_QDIAGRAM(owner, ctrl, x,y,w,h, caption)		\
			ctrl	= new EUIQDiagram;						\
			ctrl->SetFrameRect(x,y,w,h);			\
			ctrl->SetFrameText(caption);			\
			owner->Spawn(ctrl);
			
#define SPAWN_FDIAGRAM(owner, ctrl, x,y,w,h, caption)		\
			ctrl	= new EUIFDiagram;						\
			ctrl->SetFrameRect(x,y,w,h);			\
			ctrl->SetFrameText(caption);			\
			owner->Spawn(ctrl);
			
//=============================================================================			
//--------------------
HFrame	wnd_main;					// main menu window
HFrame		btn_exit;				// button 'exit'
HFrame		btn_about;				// button 'about'
HFrame	wnd_bottom;

HFrame	wnd_about;
HFrame		btn_about_ok;
HFrame		txt_about;

void btnproc_exit(void *p)		{ sys.Quit(); }
void btnproc_about(void *p)		{ wnd_about->SetVisibility(true); }
void btnproc_about_ok(void *p)	{ wnd_about->SetVisibility(false); }

//--------------------
HFrame	wnd_sender;					// sender tuning window
HFrame		txt;					// some static texts
HFrame		edit_msg;				// edit for input 'message'
HFrame		btn_send;				// button 'transmit'
HFrame		spin_high;				// spin control for highest harmonics
HFrame		spin_low;				// spin control for lowest harmonics
HFrame		txt_freq;				// static, that show frequensy info
EUIRadio	*rad_code_phys;				//	selects RZ, NRZ, AMI, MANCHESTER etc
EUIRadio	*rad_code_logic;				//	selects Phys, Super, Scramble

void btnproc_send(void *p)		{ fe.SetMessage(); }

//--------------------
HFrame	wnd_receiver;				// receiver tunning window
HFrame		spin_noise;
HFrame		spin_desync;
HFrame		spin_defase;
HFrame		spin_edge_voltage;
EUIFlag		*flag_show;
HFrame		txt_recvmsg;
HFrame		btn_reset;

void btnproc_reset(void *p)	{ fe.ResetStats(); }


//--------------------
HFrame	wnd_state;
HFrame	txt_state;

EUIQDiagram		*qdiag_signal;
EUIQDiagram		*qdiag_recv;
EUIFDiagram		*fdiag_fourier;

//=============================================================================			

void EFourierEngine::Init(void)
{
	int y;
	// UI initializing :
	//-------------------------------------------	
	// Main menu :
	SPAWN_PANEL		(uicore.Desktop(),	wnd_main,		 5,  5,790, 25,	"Main");
	SPAWN_BUTTON	(wnd_main,			btn_exit,		 5,  5,140, 15,	"Exit",  btnproc_exit);
	SPAWN_BUTTON	(wnd_main,			btn_about,	   155,  5,140, 15,	"About", btnproc_about);

	SPAWN_PANEL		(uicore.Desktop(),	wnd_bottom,		 5,  575,790, 20,	"Main");

	//-------------------------------------------	
	// Sender :
	SPAWN_FRAME		(uicore.Desktop(),	wnd_sender,	   635, 40, 160, 290,	"Sender");
	y = 20;
	SPAWN_STATIC	(wnd_sender,		txt,			10, y,  140, 16,	"Enter Message:");			y+=20;
	SPAWN_EDIT		(wnd_sender,		edit_msg,		10, y,	 140, 16,	"", 16);					y+=25;
	SPAWN_BUTTON	(wnd_sender,		btn_send,		10, y,	 140, 16,	"Transmit!", btnproc_send);	y+=25;
	
	SPAWN_STATIC	(wnd_sender,		txt,			10, y,  40, 16,	"Spectrum\r\nharmonics:");		y+=25;
	SPAWN_STATIC	(wnd_sender,		txt,			10, y,  40, 16,	"highest:");	
	SPAWN_SPIN		(wnd_sender,		spin_high,		80, y,  70, 14, 0,255,128,1);	y+=20;
	SPAWN_STATIC	(wnd_sender,		txt,			10, y,  40, 16,	"lowest:");		
	SPAWN_SPIN		(wnd_sender,		spin_low,		80, y,  70, 14, 0,255,0,1);		y+=25;
	
	SPAWN_STATIC	(wnd_sender,		txt_freq,			10, y,  40, 16,	"freq :");		y+=20;

	SPAWN_RADIO		(wnd_sender,		rad_code_phys,			10, y,  140, 48,	4, code1_list);	y+=60;
	SPAWN_RADIO		(wnd_sender,		rad_code_logic,			10, y,  140, 36,	3, code2_list);	y+=25;
	
	//-------------------------------------------	
	SPAWN_FRAME		(uicore.Desktop(),	wnd_receiver,	635, 340, 160, 225,	"Receiver");
	y = 25;
	SPAWN_STATIC	(wnd_receiver,		txt,			10,	y,	40, 16,	"Noise:")
	SPAWN_SPIN		(wnd_receiver,		spin_noise,		80,y,	70, 14, 0.0, 2.0, 0.0, 0.01);	y+=20;
	
	SPAWN_STATIC	(wnd_receiver,		txt,			10,	y,	40, 16,	"Desync:");
	SPAWN_SPIN		(wnd_receiver,		spin_desync,	80,y,	70, 14, 0.0, 1.0, 0.0, 0.01);	y+=25;
	
	SPAWN_STATIC	(wnd_receiver,		txt,			10,	y,	40, 16,	"Voltage:")
	SPAWN_SPIN		(wnd_receiver,	spin_edge_voltage,	80,y,	70, 14, 0.0, 1.0, 0.5, 0.01);	y+=25;
	

	//-------------------------------------------	
	// Diagrams :
	y = 40;
	SPAWN_QDIAGRAM(uicore.Desktop(),	qdiag_signal,	 5,   y, 620, 140, "Signal");	y+=150;
	SPAWN_FDIAGRAM(uicore.Desktop(),	fdiag_fourier,	 5,   y, 620, 140, "Fourier Series");	y+=150;
	SPAWN_QDIAGRAM(uicore.Desktop(),	qdiag_recv,		 5,   y, 620, 100, "Received Signal");	y+=110;
	

	//-------------------------------------------	
	// State window :
	SPAWN_FRAME		(uicore.Desktop(),	wnd_state,		 5,  y, 620,  115,	"State");
	SPAWN_STATIC	(wnd_state,			txt_state,		 5,  20, 140, 120,	"State");

	y = 20;
	SPAWN_STATIC	(wnd_state,		txt,				400,	y,	40, 16,	"Show:");	y+=15;
	static const char *show_list[4] = {"Fourier series", "Noise", "Samplers", "Voltage"};
	SPAWN_FLAG		(wnd_state,		flag_show,			400, y,	140, 48, 4, show_list, 15);	y+=60;

	y = 20;
	SPAWN_STATIC	(wnd_state,		txt_recvmsg,		200, y,	140, 48, "recv msg");	y+=60;
	SPAWN_BUTTON	(wnd_state,		btn_reset,			200, y,	140, 16, "Reset stats", btnproc_reset); y+=20;

	
	//-------------------------------------------	
	// About window : 
	SPAWN_ABOUTBOX	(uicore.Desktop(),	wnd_about,		200,150, 400, 250,	"About");
	wnd_about->SetVisibility(false);

	
	uicore.SetActiveFrame(edit_msg);
	

	// ...at last :	
	SetMessage();
	TransmitMessage();
}


void EFourierEngine::Shutdown(void)
{
}


/*
===============================================================================

	Fourier Engine

===============================================================================
*/
void EFourierEngine::UpdateControls(void)
{
	int i;
	float hf, lf;
	char msg_printable[128]	;

	TransmitMessage();	

	hf = atof(spin_high->GetFrameText())/coded_msg_length/2.0f	* 10.0f;
	lf = atof(spin_low->GetFrameText())/coded_msg_length/2.0f	* 10.0f;
	txt_freq->SetFrameText( va("%5.1f / %5.1f Mhz", lf, hf) );

	char state[512];

	strcpy(msg_printable, msg);
	for (i=0; i<strlen(msg); i++) if (!isgraph(msg_printable[i])) msg_printable[i] = ' ';
	
	sprintf(state, 
		"msg : '%s'\r\n"
		"%02X%02X%02X%02X %02X%02X%02X%02X\r\n"
		"length : %d\r\n\r\n"
		"bitrate : 10 Mb/s\r\n",
	
		msg_printable,
		 0xFF&(int)msg[0], 0xFF&(int)msg[1], 0xFF&(int)msg[2], 0xFF&(int)msg[3], 
		 0xFF&(int)msg[4], 0xFF&(int)msg[5], 0xFF&(int)msg[6], 0xFF&(int)msg[7],
		msg_length);
	
	txt_state->SetFrameText( state );

	strcpy(msg_printable, recv_msg);
	for (i=0; i<strlen(recv_msg); i++) if (!isgraph(msg_printable[i])) msg_printable[i] = ' ';

	if (test_count==0) test_count=1;
	sprintf(state, 
		"recv msg : '%s'\r\n"
		"%02X%02X%02X%02X %02X%02X%02X%02X\r\n\r\n"
		"bits count  : %d\r\n"
		"error count : %d\r\n"
		"error %%     : %1.2f %%\r\n",
		msg_printable,
		 0xFF&(int)recv_msg[0], 0xFF&(int)recv_msg[1], 0xFF&(int)recv_msg[2], 0xFF&(int)recv_msg[3], 
		 0xFF&(int)recv_msg[4], 0xFF&(int)recv_msg[5], 0xFF&(int)recv_msg[6], 0xFF&(int)recv_msg[7],
		 test_count, error_count, 100.0*error_count/test_count
		);
	txt_recvmsg->SetFrameText(state);
	
	

}



void EFourierEngine::SetMessage(void)
{
	// Parse input message :
	int val = 0x0;
	char text[128];
	strcpy(text, edit_msg->GetFrameText());

	if (text[0]=='\\' && text[1]!='\\')	{	// "\12345ABCD"
		
		sscanf(&text[1], "%X", &msg);
		
		msg[4] = msg[5] = msg[6] = msg[7] = 0;
		msg_length = strlen(text)/2;
	}
	
	if (text[0]=='\\' && text[1]=='\\')	{	// "\\blah-blah-blah"
		strncpy(msg, &text[1], 8);
		msg[8] = 0;
		msg_length = strlen(msg);
	}
	
	if (text[0]!='\\') {					// "blah-blah-blah"
		strncpy(msg, &text[0], 8);
		msg[8] = 0;
		msg_length = strlen(msg);
	}

	// checl zero-length message :
	if (msg_length<=0) {
		msg_length = 1;
		msg[0] = 0;
		msg[1] = 0;
	}
}


void _build_table();
void EFourierEngine::TransmitMessage(void)
{
	//SetMessage();
	static int hits = 0;
	if ((hits++)%4!=0) return;
	
	low_range = atoi( spin_low->GetFrameText() );
	high_range = atoi( spin_high->GetFrameText() );
	
	noise_amplitude = atof(spin_noise->GetFrameText());
	current_system_time = sys.Milliseconds()/1000.0;

	_build_table();
	// Coding of the message :	
	CodeMessage();
	
	BuildFourierSeries();
	
	RecognizeSignal();
}



void EFourierEngine::CodeMessage(void)
{
	int i;
	for (i=0; i<msg_length; i++) {
		msg_bits[i*8+0] = (msg[i]>>7)&1;
		msg_bits[i*8+1] = (msg[i]>>6)&1;
		msg_bits[i*8+2] = (msg[i]>>5)&1;
		msg_bits[i*8+3] = (msg[i]>>4)&1;
		msg_bits[i*8+4] = (msg[i]>>3)&1;
		msg_bits[i*8+5] = (msg[i]>>2)&1;
		msg_bits[i*8+6] = (msg[i]>>1)&1;
		msg_bits[i*8+7] = (msg[i]>>0)&1;
	}
	
	int phys_code_method	 = rad_code_phys->GetSelected();
	if (phys_code_method<0) phys_code_method = 0;
	if (phys_code_method>3) phys_code_method = 3;

	int logic_code_method	 = rad_code_logic->GetSelected();
	if (logic_code_method<0) logic_code_method = 0;
	if (logic_code_method>3) logic_code_method = 3;
	
	
	if (logic_code_method == FE_LOGIC_CODE_PHYS)		LogicCodePhys();
	if (logic_code_method == FE_LOGIC_CODE_SUPER45)		LogicCodeSuper45();
	if (logic_code_method == FE_LOGIC_CODE_SCRAMBLE)	LogicCodeScrambling();
	

	
	if (phys_code_method == FE_PHYS_CODE_NRZ)		PhysCodeNRZ();
	if (phys_code_method == FE_PHYS_CODE_RZ)		PhysCodeRZ();
	if (phys_code_method == FE_PHYS_CODE_AMI)		PhysCodeAMI();
	if (phys_code_method == FE_PHYS_CODE_MANCH)		PhysCodeManch();
	

}


/*
===============================================================================

	FE CODERS	

===============================================================================
*/
void EFourierEngine::LogicCodePhys(void)
{
	for (int i=0; i<msg_length*8; i++) {
		coded_msg[i*2+0] = (msg_bits[i]);
		coded_msg[i*2+1] = (msg_bits[i]);
	}
	coded_msg_length = msg_length*8;

	qdiag_signal->SetDiagram(1, 0, coded_msg_length*2, coded_msg);
	qdiag_signal->SetGrid(16, 2, 1,1);
}


void EFourierEngine::LogicCodeSuper45(void)
{
	int table[] = {
		0x1E, 0x09, 0x14, 0x15,
		0x0A, 0x0B, 0x0E, 0x0F,

		0x12, 0x13, 0x16, 0x17,
		0x1A, 0x1B, 0x1C, 0x1D
	};

	int i, key;
	for (i=0; i<msg_length*2; i++) 
	{
		key = 0;
		key |= msg_bits[4*i+3]<<4;	key = key>>1;
		key |= msg_bits[4*i+2]<<4;	key = key>>1;
		key |= msg_bits[4*i+1]<<4;	key = key>>1;
		key |= msg_bits[4*i+0]<<4;	key = key>>1;

		coded_msg[2*5*i+8] = (table[key] & BIT(0))>>0;		 coded_msg[2*5*i+8+1] = coded_msg[2*5*i+8];
		coded_msg[2*5*i+6] = (table[key] & BIT(1))>>1;		 coded_msg[2*5*i+6+1] = coded_msg[2*5*i+6];
		coded_msg[2*5*i+4] = (table[key] & BIT(2))>>2;		 coded_msg[2*5*i+4+1] = coded_msg[2*5*i+4];
		coded_msg[2*5*i+2] = (table[key] & BIT(3))>>3;		 coded_msg[2*5*i+2+1] = coded_msg[2*5*i+2];
		coded_msg[2*5*i+0] = (table[key] & BIT(4))>>4;		 coded_msg[2*5*i+0+1] = coded_msg[2*5*i+0];
	}

	coded_msg_length = msg_length*10;
	//LogicCodePhys();

	qdiag_signal->SetGrid(20, 2, 1,1);
	qdiag_signal->SetDiagram(1, 0, coded_msg_length*2, coded_msg);
}


void EFourierEngine::LogicCodeScrambling(void)
{
	// polynom : Ai (+) Bi-3 (+) Bi-5
	int a,b,c;
	a=b=c=0;
	
	coded_msg_length = msg_length*8;

	for (int i=0; i<coded_msg_length; i++) {
		a = b = c = 0;
		if (i>=3) b = coded_msg[ 2*(i-3) ];
		if (i>=5) c = coded_msg[ 2*(i-5) ];
		a = msg_bits[ (i) ];
		
		coded_msg[i*2+0] = (a+b+c)&1;
		coded_msg[i*2+1] = (a+b+c)&1;
	}
	

	qdiag_signal->SetDiagram(1, 0, coded_msg_length*2, coded_msg);
	qdiag_signal->SetGrid(16, 2, 1,1);
}




void EFourierEngine::PhysCodeNRZ(void)
{
	for (int i=0; i<coded_msg_length; i++) {
		int val = coded_msg[i*2+0];
		coded_msg[i*2+0] = (2*val)-1;
		coded_msg[i*2+1] = (2*val)-1;
	}
}

void EFourierEngine::PhysCodeRZ(void)
{
	for (int i=0; i<coded_msg_length; i++) {
		int val = coded_msg[i*2+0];
		coded_msg[i*2+0] = (2*val)-1;
		coded_msg[i*2+1] = 0;
	}
}

void EFourierEngine::PhysCodeAMI(void)
{
	int sign = 1;
	for (int i=0; i<coded_msg_length; i++) {
		int val = coded_msg[i*2+0];
		coded_msg[i*2+0] = val*sign;
		coded_msg[i*2+1] = val*sign;
		if (val==1) sign*=-1;
	}
}

void EFourierEngine::PhysCodeManch(void)
{
	int val;
	for (int i=0; i<coded_msg_length; i++) {
		val = coded_msg[i*2+0];
		coded_msg[i*2+0] = (2*val-1);
		coded_msg[i*2+1] = (2*val-1)*(-1);
	}
}



/*
===============================================================================

	FOURIER SERIES BUILDING

===============================================================================
*/
#define PI	3.141592654f

bool	sin_table_created = false;
float	sint[65536];
float	cost[65536];

#define SIN(x) sint[((unsigned short int)((x)*65536.0f/PI/2.0f))&0xFFFF]
#define COS(x) cost[((unsigned short int)((x)*65536.0f/PI/2.0f))&0xFFFF]

/*#define SIN(x) sinf(x)
#define COS(x) cosf(x)*/


void _build_table(void)
{
	if (!sin_table_created) {
		PRINTF("Building SIN/COS table...\r\n");
		for (int i=0; i<65536; i++) 
		{
			sint[i] = sinf((float)i/65536.0f*2*PI);
			cost[i] = cosf((float)i/65536.0f*2*PI);
		}
		sin_table_created = true;
	}
}


float EFourierEngine::FourierSeriesFunc(float x, int low, int high )
{
	//_build_table();

	float result = 0;
	float L = coded_msg_length;
	
	for (int k=low_range, float kf=low_range; k<=high_range; k++, kf+=1.0f) {
		result += ( a[k]*COS(kf*x*PI/L) + b[k]*SIN(kf*x*PI/L) );
		if (k==0) result/=2.0;	// a0/2+...
	}
	return result;
}


float _fourier(float x) 
{
	//int low		= atoi(spin_low->GetFrameText());
	//int high	= atoi(spin_high->GetFrameText());
	
	float result = 0;

	if (flag_show->GetFlags() & BIT(0))	result += fe.FourierSeriesFunc(x, 0, 0);	// 0, 0 - does not matter..
	if (flag_show->GetFlags() & BIT(1))	result += fe.NoiseFunc(x, 16);
	
	return result;
}


void EFourierEngine::BuildFourierSeries(void)
{
	int k, i;
	float L = coded_msg_length;
	float x, fk;
	
	a[0] = b[0] = 0;
	
	for (x=0; x<L; x+=0.5)	{
		i = (int)(x*2);
		a[0] += 0.5*((float)coded_msg[i])/L;
	}

	for (x=-L; x<0; x+=0.5)	{
		i = (int)(x*2+L*2);
		a[0] += 0.5*((float)coded_msg[i])/L;
	}
	
	for (k=1; k<256; k++)
	{
		fk = k;
		a[k] = 0;
		b[k] = 0;
		for (x=0; x<L; x+=0.5)	// over half-bit
		{
			i = (int)(x*2);
			a[k] += ((float)coded_msg[i])/(PI*fk) * ( SIN( (PI*fk/L)*(x+0.5f) ) - SIN( (PI*fk/L)*(x+0.0f) ) );
			b[k] -= ((float)coded_msg[i])/(PI*fk) * ( COS( (PI*fk/L)*(x+0.5f) ) - COS( (PI*fk/L)*(x+0.0f) ) );
		}
	
		for (x=-L; x<0; x+=0.5)	// over half-bit
		{
			i = (int)(x*2+L*2);
			a[k] += ((float)coded_msg[i])/(PI*fk) * ( SIN( (PI*fk/L)*(x+0.5f) ) - SIN( (PI*fk/L)*(x+0.0f) ) );
			b[k] -= ((float)coded_msg[i])/(PI*fk) * ( COS( (PI*fk/L)*(x+0.5f) ) - COS( (PI*fk/L)*(x+0.0f) ) );
		} 
	} 
	
	// set control params :
	fdiag_fourier->SetGrid(10.0f, 1.0f, 1.0, 0.2); 
	fdiag_fourier->SetDiagram(2.0f, 0, L*1.0f, L/500.0, _fourier);
	
}



/*
===============================================================================

	RECEIVER STUFF.

===============================================================================
*/
/*
	float s=0; for(int i=0;i<13;i++) s+=((float)rand()/(float)RAND_MAX-.5);
*/

float EFourierEngine::NoiseFunc(float x, int n)
{
	static float time = 1;	time+=0.01;
	float result = 0;
	float i;

	time = current_system_time;	
	//if (time>6.28) time = 0.0;
	//int low = atoi(spin_low->GetFrameText());
	//int high = atoi(spin_high->GetFrameText());

	result = 0;	
	for (i=1; i<high_range; i++) {	// may be: for (i=low+1; i<high; i++)
		 result += (0.5/i) * SIN(i*x + i*i*i*i*time);
	}
	
	result *= noise_amplitude;
	return result;
}



/*
========================================================
	DECODERS
========================================================
*/
float signrandf(void){ return rand()%4096/2048.0f - 1.0f; }

void EFourierEngine::DrawSamplers( float xmin, float xmax)
{
	float x;
	float sw = atof(spin_desync->GetFrameText());
	int code = rad_code_phys->GetSelected();
	if (flag_show->GetFlags() & BIT(2))
		for (x=xmin; x<xmax; x+=1.0f)
		{
			if (code==FE_PHYS_CODE_NRZ) {
				glBegin(GL_QUADS);
					glColor4f(1,1,1,0.0f);	glVertex3f( 0.50+x+sw/2, 2.0f, 0);	glVertex3f( 0.48+x-sw/2, 2.0f, 0);
					glColor4f(1,1,1,0.2f);	glVertex3f( 0.48+x-sw/2, 0.0f, 0);	glVertex3f( 0.50+x+sw/2, 0.0f, 0);

					glColor4f(1,1,1,0.2f);	glVertex3f( 0.50+x+sw/2, 0.0f, 0);	glVertex3f( 0.48+x-sw/2, 0.0f, 0);
					glColor4f(1,1,1,0.0f);	glVertex3f( 0.48+x-sw/2,-2.0f, 0);	glVertex3f( 0.50+x+sw/2,-2.0f, 0);
				glEnd();
			}
			if (code==FE_PHYS_CODE_RZ) {
				glBegin(GL_QUADS);
					glColor4f(1,1,1,0.0f);	glVertex3f( 0.25+x+sw/4, 2.0f, 0);	glVertex3f( 0.25+x-sw/4, 2.0f, 0);
					glColor4f(1,1,1,0.2f);	glVertex3f( 0.25+x-sw/4, 0.0f, 0);	glVertex3f( 0.25+x+sw/4, 0.0f, 0);

					glColor4f(1,1,1,0.2f);	glVertex3f( 0.25+x+sw/4, 0.0f, 0);	glVertex3f( 0.25+x-sw/4, 0.0f, 0);
					glColor4f(1,1,1,0.0f);	glVertex3f( 0.25+x-sw/4,-2.0f, 0);	glVertex3f( 0.25+x+sw/4,-2.0f, 0);
				glEnd();
			}
			if (code==FE_PHYS_CODE_AMI) {
				glBegin(GL_QUADS);
					glColor4f(1,1,1,0.0f);	glVertex3f( 0.50+x+sw/2, 2.0f, 0);	glVertex3f( 0.50+x-sw/2, 2.0f, 0);
					glColor4f(1,1,1,0.2f);	glVertex3f( 0.50+x-sw/2, 0.0f, 0);	glVertex3f( 0.50+x+sw/2, 0.0f, 0);

					glColor4f(1,1,1,0.2f);	glVertex3f( 0.50+x+sw/2, 0.0f, 0);	glVertex3f( 0.50+x-sw/2, 0.0f, 0);
					glColor4f(1,1,1,0.0f);	glVertex3f( 0.50+x-sw/2,-2.0f, 0);	glVertex3f( 0.50+x+sw/2,-2.0f, 0);
				glEnd();
			}
			if (code==FE_PHYS_CODE_MANCH) {
				glBegin(GL_QUADS);
					glColor4f(1,1,1,0.0f);	glVertex3f( 0.25+x+sw/4, 2.0f, 0);	glVertex3f( 0.25+x-sw/4, 2.0f, 0);
					glColor4f(1,1,1,0.2f);	glVertex3f( 0.25+x-sw/4, 0.0f, 0);	glVertex3f( 0.25+x+sw/4, 0.0f, 0);
																									   
					glColor4f(1,1,1,0.2f);	glVertex3f( 0.25+x+sw/4, 0.0f, 0);	glVertex3f( 0.25+x-sw/4, 0.0f, 0);
					glColor4f(1,1,1,0.0f);	glVertex3f( 0.25+x-sw/4,-2.0f, 0);	glVertex3f( 0.25+x+sw/4,-2.0f, 0);

					glColor4f(1,1,1,0.0f);	glVertex3f( 0.75+x+sw/4, 2.0f, 0);	glVertex3f( 0.75+x-sw/4, 2.0f, 0);
					glColor4f(1,1,1,0.2f);	glVertex3f( 0.75+x-sw/4, 0.0f, 0);	glVertex3f( 0.75+x+sw/4, 0.0f, 0);
																									   
					glColor4f(1,1,1,0.2f);	glVertex3f( 0.75+x+sw/4, 0.0f, 0);	glVertex3f( 0.75+x-sw/4, 0.0f, 0);
					glColor4f(1,1,1,0.0f);	glVertex3f( 0.75+x-sw/4,-2.0f, 0);	glVertex3f( 0.75+x+sw/4,-2.0f, 0);
				glEnd();
			}
		}
	if (flag_show->GetFlags() & BIT(3))
	{
		float v = atof(spin_edge_voltage->GetFrameText());
		glBegin(GL_QUADS);
			glColor4f(1,1,1,0.15);
			glVertex3f(xmax,  v, 0);
			glVertex3f(xmin,  v, 0);
			glVertex3f(xmin, -v, 0);
			glVertex3f(xmax, -v, 0);
		glEnd();
	}
}


void EFourierEngine::PhysDecodeNRZ(void)
{
	int i;
	float desync	= atof(spin_desync->GetFrameText());
	float edgevolt	= atof(spin_edge_voltage->GetFrameText());

	low_range = atoi( spin_low->GetFrameText() );
	high_range = atoi( spin_high->GetFrameText() );
	
	for (i=0; i<coded_msg_length; i++)	
	{
		float x = (float)i+0.5f + desync*signrandf()*0.5;
		float y = FourierSeriesFunc(x, low_range, high_range) + NoiseFunc(x, 16);

		if ( fabs(y)<edgevolt ) decoded_msg[i] = 0;	// FIXME : Or rand()&1 ???
		if ( y>+edgevolt ) decoded_msg[i] = 1;
		if ( y<-edgevolt ) decoded_msg[i] = 0;
	}
	
	qdiag_recv->SetDiagram(1, 0, coded_msg_length, decoded_msg);
	qdiag_recv->SetGrid(8, 1, 1,1);
}


void EFourierEngine::PhysDecodeRZ(void)
{
	int i;
	float desync	= atof(spin_desync->GetFrameText());
	float edgevolt	= atof(spin_edge_voltage->GetFrameText());

	low_range = atoi( spin_low->GetFrameText() );
	high_range = atoi( spin_high->GetFrameText() );
	
	for (i=0; i<coded_msg_length; i++)	
	{
		float x = (float)i+0.25f + desync*signrandf()*0.25;
		float y = FourierSeriesFunc(x, low_range, high_range) + NoiseFunc(x, 16);

		if ( fabs(y)<edgevolt ) decoded_msg[i] = 0;
		if ( y>+edgevolt ) decoded_msg[i] = 1;
		if ( y<-edgevolt ) decoded_msg[i] = 0;
	}
	
	qdiag_recv->SetDiagram(1, 0, coded_msg_length, decoded_msg);
	qdiag_recv->SetGrid(8, 1, 1,1);
}


void EFourierEngine::PhysDecodeAMI(void)
{
	int i;
	float desync	= atof(spin_desync->GetFrameText());
	float edgevolt	= atof(spin_edge_voltage->GetFrameText());

	low_range = atoi( spin_low->GetFrameText() );
	high_range = atoi( spin_high->GetFrameText() );
	
	int sign = 1;
	
	for (i=0; i<coded_msg_length; i++)	
	{
		float x = (float)i+0.50f + desync*signrandf()*0.50;
		float y = FourierSeriesFunc(x, low_range, high_range) + NoiseFunc(x, 16);

		decoded_msg[i] = 0;
		if ( fabs(y)<edgevolt ) decoded_msg[i] = 0;
		else {
			/*if (sign>0 && y>0)	decoded_msg[i] = 1;
			if (sign<0 && y<0)	decoded_msg[i] = 1;*/
			decoded_msg[i] = 1;
			sign*=(-1);
		}
	}
	
	qdiag_recv->SetDiagram(1, 0, coded_msg_length, decoded_msg);
	qdiag_recv->SetGrid(8, 1, 1,1);
}


void EFourierEngine::PhysDecodeManch(void)
{
	int i;
	float desync	= atof(spin_desync->GetFrameText());
	float edgevolt	= atof(spin_edge_voltage->GetFrameText());

	low_range = atoi( spin_low->GetFrameText() );
	high_range = atoi( spin_high->GetFrameText() );
	
	int sign = 1;
	
	for (i=0; i<coded_msg_length; i++)	
	{
		float x1 = (float)i+0.25f + desync*signrandf()*0.25;
		float x2 = (float)i+0.75f + desync*signrandf()*0.25;
		float y1 = FourierSeriesFunc(x1, low_range, high_range) + NoiseFunc(x1, 16);
		float y2 = FourierSeriesFunc(x2, low_range, high_range) + NoiseFunc(x2, 16);

		if (y1>y2)	decoded_msg[i] = 1;
			else	decoded_msg[i] = 0;
	}

	qdiag_recv->SetDiagram(1, 0, coded_msg_length, decoded_msg);
	qdiag_recv->SetGrid(8, 1, 1,1);
}





void EFourierEngine::LogicDecodePhys(void)
{
	memset(recv_msg, 0, MSG_LENGTH+1);
	for (int i=0; i<coded_msg_length; i++)
	{
		if (decoded_msg[i]==1) recv_msg[i/8] |= BIT(7-i&7);
	}
}

void EFourierEngine::LogicDecodeSuper45(void)
{
	int table[] = {
		0x1E, 0x09, 0x14, 0x15,
		0x0A, 0x0B, 0x0E, 0x0F,

		0x12, 0x13, 0x16, 0x17,
		0x1A, 0x1B, 0x1C, 0x1D
	};
	// build inv table:
	int invtable[] = {
		0x00,	0x00,	0x00,	0x00,		0x00,	0x00,	0x00,	0x00,	//	00..07
		0x00,	0x01,	0x04,	0x05,		0x00,	0x00,	0x06,	0x07,	//	08..0F

		0x00,	0x00,	0x08,	0x09,		0x02,	0x03,	0x0A,	0x0B,	//	10..17
		0x00,	0x00,	0x0C,	0x0D,		0x0E,	0x0F,	0x00,	0x00	//	18..1F
	};

	memset(recv_msg, 0, MSG_LENGTH+1);

	for (int i=0; i<coded_msg_length/10; i++)
	{
		int key = 0;
		key |= decoded_msg[i*10+0]<<9;
		key |= decoded_msg[i*10+1]<<8;
		key |= decoded_msg[i*10+2]<<7;
		key |= decoded_msg[i*10+3]<<6;
		key |= decoded_msg[i*10+4]<<5;
		key |= decoded_msg[i*10+5]<<4;
		key |= decoded_msg[i*10+6]<<3;
		key |= decoded_msg[i*10+7]<<2;
		key |= decoded_msg[i*10+8]<<1;
		key |= decoded_msg[i*10+9]<<0;
		
		recv_msg[i] = 0;
		recv_msg[i] |= invtable[(key>>5)&0x1F]<<4;
		recv_msg[i] |= invtable[(key>>0)&0x1F]<<0;
	}
	//LogicDecodePhys();
}

void EFourierEngine::LogicDecodeScrambling(void)
{
	memset(recv_msg, 0, MSG_LENGTH+1);
	int a,b,c, s;

	for (int i=0; i<coded_msg_length; i++) {
		a = b = c = 0;
		if (i>=5) c = decoded_msg[ (i-5) ];
		if (i>=3) b = decoded_msg[ (i-3) ];
		a = decoded_msg[ (i) ];

		s = (a+b+c)&1;
		recv_msg[i/8] |= (s<<(0x7-i&0x7));
		//PRINTF("%d", s);
	}
	/*PRINTF("\r\n");
	PRINTF("%d\r\n", (unsigned int)recv_msg[0]&0xFF); */


	/*memset(recv_msg, 0, MSG_LENGTH+1);
	for (int i=0; i<coded_msg_length; i++)
	{
		if (decoded_msg[i]==1) recv_msg[i/8] |= BIT(7-i&7);
	}  */
	/*for (int i=0; i<coded_msg_length; i++) {
		a = coded_msg[ (i-0)%coded_msg_length ];
		b = coded_msg[ (i-3)%coded_msg_length ];
		c = coded_msg[ (i-5)%coded_msg_length ];
		
		recv_msg[i/8] |= (((a+b+c)&1)<<(i&0x7));
	}  */
}




void EFourierEngine::RecognizeSignal(void)
{
	int phys_code_method	 = rad_code_phys->GetSelected();
	if (phys_code_method<0) phys_code_method = 0;
	if (phys_code_method>3) phys_code_method = 3;

	int logic_code_method	 = rad_code_logic->GetSelected();
	if (logic_code_method<0) logic_code_method = 0;
	if (logic_code_method>3) logic_code_method = 3;

	if (phys_code_method == FE_PHYS_CODE_NRZ)	PhysDecodeNRZ();
	if (phys_code_method == FE_PHYS_CODE_RZ)	PhysDecodeRZ();
	if (phys_code_method == FE_PHYS_CODE_AMI)	PhysDecodeAMI();
	if (phys_code_method == FE_PHYS_CODE_MANCH)	PhysDecodeManch();
	
	if (logic_code_method == FE_LOGIC_CODE_PHYS)	LogicDecodePhys();
	if (logic_code_method == FE_LOGIC_CODE_SUPER45)	LogicDecodeSuper45();
	if (logic_code_method == FE_LOGIC_CODE_SCRAMBLE)LogicDecodeScrambling();
	
	CheckMessage();
}



void EFourierEngine::CheckMessage(void)
{
	int b1, b2;
	for (int i=0; i<coded_msg_length; i++)
	{
		test_count++;
		b1 = msg[i/8]&BIT(i&7);
		b2 = recv_msg[i/8]&BIT(i&7);
		
		if (b1!=b2) error_count++;
	}
}





























