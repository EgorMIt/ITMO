//
//	STRING2.CPP
//
//	coded by : Demiurg-HG
//	descr : string definition, fully independent of system, core etc.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "string2.h"


/*
**	Contrustors & Destructor
*/
EStr::EStr(void)
{
	length = 0;
	string = new char[length+1];
	string[0] = '\0';
}

EStr::EStr(const char *s)
{
	length = (int)strlen(s);
	string = new char[length+1];
	strcpy(string, s);
}

EStr::EStr(const EStr &s)
{
	if (this==&s){} 
	length = s.length;
	string = new char[length+1];
	strcpy(string, s.string);
}

EStr::~EStr(void)
{
	delete[] string;
	length = -1;
} 


void EStr::Set(const char *s)
{
	delete[] string;
	length = (int)strlen(s);
	string = new char[length+4];
	strcpy(string, s);
}

void EStr::Set(const EStr &s)
{
	Set(s.c_str());
}

void EStr::Copy(const char *beg, int len)
{
	delete[] string;
	if (len<0) len = 0;
	length = len;
	string = new char[length+1];
	memset(string, 0, len+1);
	strncpy(string, beg, len);
}

const char *EStr::c_str(void) const 
{	
	return &string[0];	
}

const char *EStr::c_strn(int n) const 
{
	if (n<0 || n>length) return "";
	else return &string[n];
}

char EStr::getch(int n) const	
{
	if (n<0 || n>=length) return '\0';
	else return string[n];
}

int EStr::getlen(void) const 
{
	return length;
}


EStr &EStr::Lower(void)
{
	for (char *scan = &string[0]; *scan; scan++) *scan = tolower(*scan);
	return *this;
}

EStr &EStr::Upper(void)
{
	for (char *scan = &string[0]; *scan; scan++) *scan = toupper(*scan);
	return *this;
}


void EStr::va(const char *frmt, ...)
{
	char	bigstr[16384];
	va_list	argptr;
	int		len;

	va_start (argptr, frmt);
	len = vsprintf (bigstr, frmt, argptr);
	va_end (argptr);

	delete[] string;
	length = len;
	string = new char[length+1];
	strcpy(string, bigstr);
}


int EStr::FindChar(const char ch) const 
{
	for (int i=0; i<length; i++) if (ch==string[i]) return i;
	return -1;
}

int EStr::FindStr(const EStr &s) const
{
	char *pch = strstr(string, s.string);
	if (pch) return (int)(pch - string); 
	else return -1;
}

int EStr::FindStr(const char *s) const
{
	char *pch = strstr(string, s);
	if (pch) return (int)(pch - string); 
	else return -1;
}


/*
===============================================================================
									
	C-String routines

===============================================================================
*/
/*
**	va()
**	returns pointer to formatted string
*/
char *va(const char *frmt, ...)
{
	// FIXME : multithreating !?
	static char text[16384];
	va_list	argptr;

	va_start (argptr, frmt);
	vsprintf (text, frmt, argptr);
	va_end (argptr);

	return &text[0];
}

/*
**	srtncmpi()
*/
int strncmpi(const char *s1, const char *s2, int n)
{
	int i;
	for (i=0; i<n; i++)	
	{
		if ( tolower(s1[i])!=tolower(s2[i]) ) return ( tolower(s1[i])-tolower(s2[i]) );
		if ( s1[i]=='\0' ) return 0;
		if ( s2[i]=='\0' ) return 0;
	}
	return 0;
}

/*
**	common_part()
**	copy to "s" common part of "s" & "sample"
*/
void common_part(char *s, const char *sample)
{
	int i;
	for (i=0; s[i], sample[i]; i++)
	{	
		if ( tolower(s[i])!=tolower(sample[i]) )
		{
			s[i]='\0';
			return;
		}
	}
}

/*
**	qsort_strcmpi()
**	useful function for c-std qsort()
*/
int qsort_strcmpi(const void *s1, const void *s2)
{ 
	return strcmpi(*(char**)s1, *(char**)s2); 
}

/*
===============================================================================

	HASHING	 

===============================================================================
*/
uint StupidHash(const char *str)
{
	int hash = 7;
	for ( ; *str; str++) hash += tolower(*str);
	return (hash & 0x7FFFFFFF);
}

uint RSHash(const char *str)
{
	unsigned int b    = 378551;
	unsigned int a    = 63689;		 
	unsigned int hash = 0;			 

	for( ; *str; str++)	{
		hash = hash*a + tolower(*str);
		a = a*b;
	}   

	return (hash & 0x7FFFFFFF);
}

uint JSHash(const char* str)
{
	unsigned int hash = 1315423911;

	for( ; *str; str++)
			hash ^= ((hash << 5) + tolower(*str) + (hash >> 2));
	return (hash & 0x7FFFFFFF);
}

