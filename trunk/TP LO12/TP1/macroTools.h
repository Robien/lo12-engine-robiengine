/*
 * macroTools.h
 *
 *  Created on: Feb 16, 2012
 *      Author: romain
 */

#ifndef MACROTOOLS_H_
#define MACROTOOLS_H_

#include <iostream>

#ifdef BUILD_TYPE
#define _DEBUG_
#else
#define _RELEASE_
#endif

#if C11 // enable C++11 ?
#define ARRAY std::array
#else
#define ARRAY boost::array
#endif

#define CLEAR std::cout << "\e[2J\e[H";

//#define onDebugOnly(x) if (CMAKE_BUILD_TYPE == Debug) x
#define CONTEXT_INFO "line "<<__LINE__<<" in "<<__FILE__
#define DEBUG_POINT std::cout << "Debug point at line "<<__LINE__<<" in "<<__FILE__ << std::endl;

#define WARNING std::cout << "Warning at line "<<__LINE__<<" in "<<__FILE__ << std::endl;
#define WARNING_IF(a) if(a){std::cout << "Warning at line "<<__LINE__<<" in "<<__FILE__ << std::endl;}
#ifndef ERROR
#define ERROR std::cerr << "Error at line "<<__LINE__<<" in "<<__FILE__ << std::endl;
#endif
#define ERROR_IF(a) if(a){std::cerr << "Error at line "<<__LINE__<<" in "<<__FILE__ << std::endl;}
#define FATAL_ERROR std::cerr << "Error at line "<<__LINE__<<" in "<<__FILE__ << std::endl; exit(1);
#define FATAL_ERROR_MESSAGE(a) std::cerr << "Error at line "<<__LINE__<<" in "<<__FILE__ << std::endl;std::cerr<<a<<std::endl;exit(1);
#define FATAL_ERROR_MESSAGES(a, b, c) std::cerr << "Error at line "<<__LINE__<<" in "<<__FILE__ << std::endl;std::cerr<<a << b << c <<std::endl;exit(1);
#define FATAL_ERROR_IF(a) if(a){std::cerr << "Error at line "<<__LINE__<<" in "<<__FILE__ << std::endl;exit(1);}

#ifdef _DEBUG_

#define ON_DEBUG(a) a

#define DEBUG_WARNING std::cout << "Warning at line "<<__LINE__<<" in "<<__FILE__ << std::endl;
#define DEBUG_WARNING_IF(a) if(a){std::cout << "Warning at line "<<__LINE__<<" in "<<__FILE__ << std::endl;}
#define DEBUG_ERROR std::cerr << "Error at line "<<__LINE__<<" in "<<__FILE__ << std::endl;
#define DEBUG_ERROR_IF(a) if(a){std::cerr << "Error at line "<<__LINE__<<" in "<<__FILE__ << std::endl;}
#define DEBUG_FATAL_ERROR std::cerr << "Error at line "<<__LINE__<<" in "<<__FILE__ << std::endl;exit(1);
#define DEBUG_FATAL_ERROR_MESSAGE(a) std::cerr << "Error at line "<<__LINE__<<" in "<<__FILE__ << std::endl;std::cerr<<a<<std::endl;exit(1);
#define DEBUG_FATAL_ERROR_IF(a) if(a){std::cerr << "Error at line "<<__LINE__<<" in "<<__FILE__ << std::endl;exit(1);}

#else

#define ON_DEBUG(a)
#define DEBUG_WARNING
#define DEBUG_WARNING_IF(a)
#define DEBUG_ERROR
#define DEBUG_ERROR_IF(a)
#define DEBUG_FATAL_ERROR
#define DEBUG_FATAL_ERROR_MESSAGE(a)
#define DEBUG_FATAL_ERROR_IF(a)

#endif

#endif /* MACROTOOLS_H_ */
