//
//	STRING2.H
//
//	coded by : Demiurg-HG
//	descr :
//

#pragma once

// FIXME : Bad practice... :P
typedef unsigned long int	uint;


uint	StupidHash	( const char *str );
uint	RSHash		( const char *str );
uint	JSHash		( const char *str );
char	*va			( const char *frmt, ...);
int		strncmpi	( const char *s1, const char *s2, int n );
void	common_part	( char *s, const char *sample );
int		qsort_strcmpi( const void *s1, const void *s2 );


class EStr
	{
	private:
		int		length;
		char	*string;
	public:
					EStr(void);
					EStr(const char *s);
					EStr(const EStr &s);
					~EStr(void);

		const char	*c_str	( void )	const;
		const char	*c_strn	( int n )	const;
			  char	getch	( int n )	const;
			  int	getlen	( void )	const;

		void		va		( const char *frmt, ...);			
		void		Set		( const EStr &s);
		void		Set		( const char *s);
		void		Copy	( const char *beg, int len);		
		EStr		&Upper	( void );							
		EStr		&Lower	( void );							
		EStr		&operator = ( const EStr &s ){ Set(s); return *this; }
		EStr		&operator = ( const char *s ){ Set(s); return *this; }

		int			toi() const { return (int)atoi(c_str()); }
		uint		tou() const { return (uint)atoi(c_str()); }
		float		tof() const { return (float)atof(c_str()); }

		int			FindChar( const char ch )	const;
		int			FindStr	( const char *s )	const;
		int			FindStr	( const EStr &s )	const;

		// Functions of comparing of the strings:
		/*friend	int		StrCmp	( const EStr &s1, const EStr &s2 ){ return  strcmp(s1.c_str(),	s2.c_str()); }
		friend	int		StrCmp	( const char *s1, const EStr &s2 ){ return	 strcmp(s1,			s2.c_str()); }
		friend	int		StrCmp	( const EStr &s1, const char *s2 ){ return	 strcmp(s1.c_str(),	s2); }
		friend	int		StrCmpi	( const EStr &s1, const EStr &s2 ){ return	strcmpi(s1.c_str(), s2.c_str()); }
		friend	int		StrCmpi	( const char *s1, const EStr &s2 ){ return	strcmpi(s1,			s2.c_str()); }
		friend	int		StrCmpi	( const EStr &s1, const char *s2 ){ return	strcmpi(s1.c_str(), s2); }

		friend	int		StrCmp	( const char *s1, const char *s2 ) { return	strcmp(s1, s2); }
		friend	int		StrCmpi	( const char *s1, const char *s2 ) { return	strcmpi(s1, s2); }

		// operators of comparing of the strings:
		friend	bool	operator == (EStr &s1, EStr &s2){ return !StrCmp(s1, s2); }
		friend	bool	operator == (EStr &s1, char *s2){ return !StrCmp(s1, s2); }
		friend	bool	operator == (char *s1, EStr &s2){ return !StrCmp(s1, s2); }

		friend	bool	operator != (EStr &s1, EStr &s2){ return !!StrCmp(s1, s2); }
		friend	bool	operator != (EStr &s1, char *s2){ return !!StrCmp(s1, s2); }
		friend	bool	operator != (char *s1, EStr &s2){ return !!StrCmp(s1, s2); }

		friend	bool	operator >	(EStr &s1, EStr &s2){ return (StrCmp(s1,s2)>0); }
		friend	bool	operator <	(EStr &s1, EStr &s2){ return (StrCmp(s1,s2)<0); }
		friend	bool	operator >= (EStr &s1, EStr &s2){ return (StrCmp(s1,s2)>=0); }
		friend	bool	operator <= (EStr &s1, EStr &s2){ return (StrCmp(s1,s2)<=0); }*/
	};
