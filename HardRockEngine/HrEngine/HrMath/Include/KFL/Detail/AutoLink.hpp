#ifndef KLAYGE_LIB_NAME
	#error "Macro KLAYGE_LIB_NAME not set (internal error)"
#endif

#ifdef KLAYGE_COMPILER_MSVC
	#define LIB_FILE_NAME KFL_STRINGIZE(KLAYGE_LIB_NAME) KLAYGE_OUTPUT_SUFFIX ".lib"

	#pragma comment(lib, LIB_FILE_NAME)
	//#pragma message("Linking to lib file: " LIB_FILE_NAME)
	#undef LIB_FILE_NAME
#endif

#undef KLAYGE_LIB_NAME
