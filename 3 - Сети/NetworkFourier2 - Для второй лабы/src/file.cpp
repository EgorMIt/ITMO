//
//	FILESYS.CPP
//
//	descr : file system
//

#include "demo_def.h"

EFile::EFile(void)
{
	hFile	= NULL;
	mode	= FS_NOT_OPENED;
}

EFile::~EFile(void)
{
}

/*
**	EFile::Open()
*/
bool EFile::Open(const char  *filename, uint openmode)
{
	mode = openmode;
	if (mode==FS_READ) 
	{
		name = filename;
		hFile = CreateFile(name.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile==INVALID_HANDLE_VALUE) goto _failed;
		else return true;
	}
	if (mode==FS_WRITE) 
	{
		name = filename;
		DeleteFile(filename);
		hFile = CreateFile(name.c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, 
							FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile==INVALID_HANDLE_VALUE) goto _failed;
		else return true;
	}
	
_failed:
	hFile	= NULL;
	name	= "";
	mode	= FS_NOT_OPENED;
	return false;
}

/*
**	EFile::Close()
*/
void EFile::Close(void)
{
	if (mode==FS_NOT_OPENED){WARNING("EFile::Close() : file is not opened"); return; }
	CloseHandle(hFile);
}

/*
**	EFile::Read()
*/
void EFile::Read(void *buf, uint size)
{
	if (mode!=FS_READ){ WARNING("EFile::Read() : wrong mode"); return; }
	uint num;
	ReadFile(hFile, buf, size, &num, NULL);
}

/*
**	EFile::Write()
*/
void EFile::Write(const void *buf, uint size)
{
	if (mode!=FS_WRITE){ WARNING("EFile::Write() : wrong mode"); return; }
	uint num;
	WriteFile(hFile, buf, size, &num, NULL);
}

/*
**	EFile::WriteText()
*/
void EFile::WriteText(const char *text)
{
	if (mode!=FS_WRITE){ WARNING("EFile::Write() : wrong mode"); return; }
	uint num;
	WriteFile(hFile, text, strlen(text), &num, NULL);
}


/*
**	EFile::Flush()
*/
void EFile::Flush(void)
{
	if (mode==FS_NOT_OPENED) { WARNING("EFile::Flush() : file is not opened"); return; }
	FlushFileBuffers(hFile);
}

/*
**	EFile::SetPtr()
*/
void EFile::SetPtr(int dist, uint method)
{
	if (mode==FS_NOT_OPENED) { WARNING("EFile::SetPtr() : file is not opened"); return; }
	if (method==FS_BEGIN)	SetFilePointer(hFile, dist, NULL, FILE_BEGIN);
	if (method==FS_CURRENT) SetFilePointer(hFile, dist, NULL, FILE_CURRENT);
	if (method==FS_END)		SetFilePointer(hFile, dist, NULL, FILE_END);
}

/*
**	EFile::Read()
*/
uint EFile::GetSize(void)
{
	if (mode==FS_NOT_OPENED) { WARNING("EFile::Size() : file is not opened"); return 0; }
	return GetFileSize(hFile, NULL);
}