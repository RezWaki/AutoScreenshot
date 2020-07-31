#include <Windows.h>
#include <ctime>
#include "conf_parser.h"
#pragma comment( lib, "user32.lib" )

using namespace System;
using namespace System::Drawing;

INT WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, INT ) {
	while(TRUE) {
		if( GetAsyncKeyState(VK_SNAPSHOT) ) {
			time_t* current_time;
			tm* datetime;
			Graphics^ graph;
			Bitmap^ bmp;
			String^ filename;

			current_time = new time_t( time(NULL) );
			datetime = localtime( current_time );
			bmp = gcnew Bitmap( GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) );
			graph = Graphics::FromImage(bmp);

			//config job
			CConfParser* pConfig = new CConfParser("config.dat"); //open up our config file
			if( pConfig->GetValue("filename") != "DATE" ) { //seek some info & apply filename
				filename = pConfig->GetValue("catalog")+"\\"+pConfig->GetValue("filename");
			}
			else{
				filename = pConfig->GetValue("catalog")+"\\"+datetime->tm_mon.ToString()+"-"+datetime->tm_mday.ToString()+"-"+(datetime->tm_year-100).ToString()+"-"+
				datetime->tm_hour.ToString()+"-"+datetime->tm_min.ToString()+"-"+datetime->tm_sec.ToString()+".bmp";
			}
			memset( pConfig, NULL, NULL );
			delete pConfig;

			//capture screenshot
			graph->CopyFromScreen(0, 0, 0, 0, bmp->Size);
			bmp->Save( filename );

			//clean some memory
			memset( current_time, NULL, NULL );
			memset( datetime, NULL, NULL );
			memset( &graph, NULL, NULL );
			memset( &bmp, NULL, NULL );

			delete graph;
			delete bmp;
		}
		SleepEx( 100, FALSE ); //reduce cpu usage
	}
	return TRUE;
}