//	
//	TGA_IMAGE.CPP
//

#include "demo_def.h"


/*
**	ETgaImage::ETgaImage()
*/
ETgaImage::ETgaImage(void)
{
	static uint null_image[] = {
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF};
	is_loaded	= false;
	width		= 4;
	height		= 4;
	colorbpp	= 32;	
	image_data	= reinterpret_cast<uchar*>(null_image);
}


/*
**	ETgaImage::Load()
*/
void ETgaImage::Load(const char *name)
{
	tga_header_t	header;
	PRINTF("...loading : tga image : \"%s\" ", name);
	if (!file.Open(name, FS_READ))
	{
		PRINTF("failed\r\n");
		return;
	}

	file.Read(&header.IndFiled,			1);
	file.Read(&header.ColorMapType,		1);
	file.Read(&header.ImageTypeCode,	1);
		file.Read(&header.ColorMapOrigin,	2);
		file.Read(&header.ColorMapLength,	2);
		file.Read(&header.ColorMapEntrySize,1);
	file.Read(&header.XOrigin,	2);
	file.Read(&header.YOrigin,	2);
	file.Read(&header.Width,	2);
	file.Read(&header.Height,	2);
		file.Read(&header.ImagePixelSize,		1);
		file.Read(&header.ImageDescriptorByte,	1);

	// check compatible :
	if (header.ImageTypeCode!=2) {
		file.Close();
		PRINTF("failed (typecode!=2)\r\n");
		return;
	}
	if (header.ImagePixelSize<24) {
		file.Close();
		PRINTF("failed (pixelsize<24)\r\n");
		return;
	}

	// read image data :
	int size = header.Width * header.Height * header.ImagePixelSize/8;
	image_data = new uchar[size];

	file.SetPtr(18, FS_BEGIN);
	file.Read(image_data, size);

	width	=	header.Width;
	height	=	header.Height;
	colorbpp =	header.ImagePixelSize;

	uchar temp;
	for (int i=0; i<size/((int)colorbpp/8); i++)
	if (colorbpp==32) {
		temp				= image_data[i*4];
		image_data[i*4]		= image_data[i*4+2];
		image_data[i*4+2]	= temp;
	}else {
		temp			= image_data[i*3];
		image_data[i*3]	= image_data[i*3+2];
		image_data[i*3+2] = temp;
	}

	PRINTF("ok\r\n");
	is_loaded = true;

	file.Close();
}

/*
**	ETgaImage::Free()
*/
void ETgaImage::Free(void)
{
	if (is_loaded)	delete[] image_data;
}