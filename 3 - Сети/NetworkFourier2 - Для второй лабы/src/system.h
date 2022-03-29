//
//	SYSTEM.H
//

#pragma once

class ESystem
	{
		private:
			HANDLE	hConsole;
			uint	start_time;
		public:
				ESystem(void) {
					timeBeginPeriod(1);
					start_time = timeGetTime();
					AllocConsole();
					hConsole	= CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE,
											NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);					
				}

				~ESystem(void) {
					timeEndPeriod(1);
					CloseHandle(hConsole);
					FreeConsole();
				}

		void	Printf(char *frmt, ...){
					va_list	argptr;
					char	text[16384];
					uint	num;

					va_start (argptr, frmt);
					vsprintf (text, frmt, argptr);
					va_end (argptr);

					WriteFile(hConsole, text, strlen(text),&num,NULL);
				}

		void	Fatalf(char *frmt, ...)	{
					va_list	argptr;
					char	text[4096];

					va_start (argptr, frmt);
					vsprintf (text, frmt, argptr);
					va_end (argptr);

					MessageBox(NULL, text, "Fatal error", MB_OK | MB_ICONERROR );
					ExitProcess(0);
				}
				
		void	FailAssert(char *expr, char *func, char *file, uint line) {
					char	text[4096];

					sprintf (text, "Assertion failed!\r\n"
									"expr	: %s\r\n"
									"func	: %s\r\n"
									"file	: %s\r\n"
									"line	: %d\r\n"
									, expr, func, file, line);

					MessageBox(NULL, text, "Fatal error", MB_OK | MB_ICONERROR );
					ExitProcess(0);
				}

		uint	Milliseconds(void) {
					return timeGetTime();
				}

		bool	ScanKey(int key) {
					return !!(GetKeyState(key)&0x80);
				}
				
		void	Quit(void) {
					PostQuitMessage(0);
				}			
	};
	
	

