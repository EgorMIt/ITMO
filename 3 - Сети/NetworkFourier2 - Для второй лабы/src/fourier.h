//
//	FOURIER.H
//	

#pragma once

const int	FE_PHYS_CODE_NRZ		=	0;
const int	FE_PHYS_CODE_RZ			=	1;
const int	FE_PHYS_CODE_AMI		=	2;
const int	FE_PHYS_CODE_MANCH		=	3;

const int	FE_LOGIC_CODE_PHYS		=	0;
const int	FE_LOGIC_CODE_SUPER45	=	1;
const int	FE_LOGIC_CODE_SCRAMBLE	=	2;

const int	MSG_LENGTH		=	8;


class EUIQDiagram: public	EUIFrame {
	private:
		int		amp;
		int		min, max;
		int		*table;
		int		gridX, subgridX;
		int		gridY, subgridY; 
		
	public:
				EUIQDiagram	( void );
	
		void	SetDiagram	( int amp, int min, int max, int *table );
		void	SetGrid		(  int gx, int sgx, int gy, int sgy );
							
		virtual	void	FMPaint	( void );	
	};
	
typedef float (*float_func_t)(float);

class EUIFDiagram: public EUIFrame {
	private:
		float	amp;
		float	min, max;
		float	step;
		float_func_t	func;
		float	gridX, subgridX;
		float	gridY, subgridY;
		
	public:
				EUIFDiagram	( void );
		void	SetDiagram	( float amp, float min, float max, float step, float_func_t func );
		void	SetGrid		(  float gx, float sgx, float gy, float sgy );
		
		virtual	void	FMPaint	( void );
	};
	



class EFourierEngine
	{
		char		msg[MSG_LENGTH+1];		
		char		msgend;					// always zero!
		int			msg_length;				// number of bytes
		int			msg_bits[MSG_LENGTH*8];	// 8 bit per byte

		int			coded_msg_length;			// number of bits
		int			coded_msg[MSG_LENGTH*10*2];	// 10 bits per byte, and 2 level per bit

		float		a[256];		
		float		b[256];
		
		float		noise_amplitude;
		float		current_system_time;		// float value, seconds...
		
		int			low_range, high_range;
		
		int			decoded_msg[MSG_LENGTH*10];	// 10 bits per byte, one level per bit
		char		recv_msg[MSG_LENGTH+1];

		int			test_count, error_count;
		

		// generate message bits :
		void		CodeMessage		( void );		
		
		// make logic coding :		
		void		LogicCodePhys		( void );
		void		LogicCodeSuper45	( void );
		void		LogicCodeScrambling	( void );
		// make physical coding :
		void		PhysCodeNRZ		( void );
		void		PhysCodeRZ		( void );
		void		PhysCodeAMI		( void );
		void		PhysCodeManch	( void );

		// build Fourier series :
		void		BuildFourierSeries	( void );		
		
		// recognize signal in Fourier series form :
		void		RecognizeSignal	( void );

		//	physical decoding :
		void		PhysDecodeNRZ	( void );
		void		PhysDecodeRZ	( void );
		void		PhysDecodeAMI	( void );
		void		PhysDecodeManch	( void );
		// logical decoding :	
		void		LogicDecodePhys			( void );
		void		LogicDecodeSuper45		( void );
		void		LogicDecodeScrambling	( void );

		void		CheckMessage	( void );
		
	public:
		void		Init		( void );
		void		Shutdown	( void );
		
		void		SetMessage	( void );
		void		UpdateControls	( void );	// обновляет состояние "контролов" таких как 'freq' и 'state'
		void		TransmitMessage	( void );	// пересылает сообшение, строит ряды, кодит, декодит и т.п.
		
		float		FourierSeriesFunc	( float x, int low, int high );
		float		NoiseFunc		( float x, int n );

		void		DrawSamplers	( float xmin, float xmax );
		
		void		ResetStats		( void ) { test_count=0; error_count=0; }
		
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	