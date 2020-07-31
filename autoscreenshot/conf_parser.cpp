#include "conf_parser.h"

CConfParser::CConfParser( String^ file ) {
	__filename = (char*)Marshal::StringToHGlobalAnsi(file).ToPointer();
}

String^ CConfParser::MakeCLRString( char* input ) {
	String^ converted_str;
	for( INT i = 0; input[i] != '\0'; i++ ) {
	converted_str += wchar_t(input[i]);
	}
	return converted_str;
}

String^ CConfParser::GetValue( String^ key ) {
	array< String^ >^ config_file = IO::File::ReadAllLines( MakeCLRString(__filename) );
	for( INT i = 0; i < config_file->Length; i++ ) {
		if( config_file[i]->Contains(key) ) {
			return config_file[i]->Substring( key->Length+3, config_file[i]->Length-(key->Length+3) );
		}
	}
	MessageBox::Show( "Couldn't find a value for key "+key+"\nExiting...", "Error" );
	exit( -1 );
}