/* Please refer to license.txt */

#pragma once

#define ENGINE_VERSION 0.0.0.1

//All operating specific code.
//Check http://sourceforge.net/apps/mediawiki/predef/index.php?title=Operating_Systems
//to keep this section of code up to date.


#define OS_WINDOWS 0
#define OS_APPLE 1
#define OS_LINUX 2
#define OS_UNIX 3
#define OS_OTHER 4

//Determine OS.
//First, check if it's windows.
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(WIN64) || defined(_WIN64) || defined(__WIN64) && !defined(__CYGWIN__)
	#define OS OS_WINDOWS
	//Now check if it's 32 or 64 bit windows.
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
		#define OS_BITS_32
	#else
		#define OS_BITS_64
	#endif
//Now check for apple operating systems.
#elif defined(__APPLE__) || defined(macintosh) || defined(Macintosh) || (defined(__MACH__) && defined(__APPLE__))
	#define OS OS_APPLE
//Now check for Linux.
#elif defined(linux) || defined(__linux) || defined(__linux_) || defined(__CYGWIN__)
	#define OS OS_LINUX
//Now check if it's a unix environment not defined above.
#elif defined(__unix) || defined(__unix__)
//Default case (unkown OS).
#else
	#define OS OS_OTHER
#endif


//Define some basic types here.
#if defined(_MSC_VER) || defined(__BORLANDC__)
	typedef unsigned __int64 ulong64;
	typedef signed __int64 long64;
#else
	typedef unsigned long long ulong64;
	typedef signed long long long64;
#endif
