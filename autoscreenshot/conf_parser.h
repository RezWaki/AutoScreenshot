#include <Windows.h>
#include <msclr\marshal.h>

using namespace msclr::interop;
using namespace System::Runtime::InteropServices;
using namespace System;
using namespace System::Windows::Forms;

class CConfParser {
	private:
		char* __filename;
	public:
		String^ MakeCLRString( char* input );
		String^ GetValue( String^ key );
		CConfParser( String^ file );
};