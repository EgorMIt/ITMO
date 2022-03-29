//
//	DEMO.H
//	

#pragma once


class EDemo
	{
	private:
		struct	camera_s{
				float pos[3];
				float ang[3];
			}cam;
		uint texbase;
		uint image_count;

		GLuint	texobj[256];
		uint	viewtex[256][256];
	public:
					EDemo(void);
					~EDemo(void);

		void		Init(void);
		void		Shutdown(void);
		void		Frame(void);

		void		DrawScene(void);
		void		MakeViewTexture(void);

		void		SetCamera(float fov, float nearf, float farf, float *ang, float *pos);
		void		Grid(int size);
		void		Control(void);

		void		LoadTexture(int n, const char *name);
		vhandle		RegisterImage(const char *name);
		void		BindTexture(int n);
	};