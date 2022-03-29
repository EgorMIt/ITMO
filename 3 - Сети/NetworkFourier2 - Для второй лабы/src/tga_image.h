//
//	TGA_IMAGE.H
//

#pragma once

typedef struct
	{
		char				IndFiled;
		char				ColorMapType;
		char				ImageTypeCode;
		// Color map specification 
		short unsigned int	ColorMapOrigin;
		short unsigned int	ColorMapLength;
		char				ColorMapEntrySize;
		// Image specification 
		short unsigned int	XOrigin;
		short unsigned int	YOrigin;
		short unsigned int	Width;
		short unsigned int	Height;
		char				ImagePixelSize;
		short unsigned int	ImageDescriptorByte;
	}tga_header_t;


class ETgaImage
	{
	private:
		EFile	file;
		
		bool	is_loaded;
		uchar	*image_data;
		uint	width;
		uint	height;
		uint	colorbpp;

	public:
					ETgaImage(void);

		void		Load(const char *name);
		void		Free(void);

		const uchar	*GetImageData(void)	const { return image_data; }
		uint		GetWidth(void)		const { return width; }
		uint		GetHeight(void)		const { return height; }
		uint		GetColorBpp(void)	const { return colorbpp; }

	};