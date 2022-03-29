//
//	FILESYS.H
//

#ifndef _FILESYS_H_
#define _FILESYS_H_

const uint	FS_BEGIN		= 0;
const uint	FS_CURRENT		= 1;
const uint	FS_END			= 2;

const uint	FS_NOT_OPENED	= 0;
const uint	FS_READ			= 1;
const uint	FS_WRITE		= 2;


class EFile
	{
	private:
		EStr	name;
		uint	mode;
		HANDLE	hFile;
	public:		
					EFile(void);
					~EFile(void);

		bool		Open(const char *filename, uint openmode);
		void		Close(void);
		EStr		&GetName(void){ return name; }

		void		Read(void *buf,			uint size);
		void		Write(const void *buf,	uint size);
		void		WriteText(const char *text);
		
		uint		GetSize(void);
		void		SetPtr(int dist, uint method);		
		void		Flush(void);
	};

#endif // _FILESYS_H_