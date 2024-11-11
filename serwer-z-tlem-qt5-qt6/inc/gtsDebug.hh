#ifndef URSDEBUG_HH
#define URSDEBUG_HH

#include <iostream>
#include <iomanip>
#include <string>

namespace gts {
 extern bool           Debug_Display;
 extern std::string    Debug_FunName;
 const char* MoveToLastSlash(const char* FileName);
}

#define DEBUG_ALL

#ifndef DEBUG_ALL
# define NODEBUG_1
# define NODEBUG_2
# define NODEBUG_3
# define NODEBUG_4
# define NODEBUG_5
#endif

//# undef NODEBUG_2
//# undef NODEBUG_3

/*
 *  Colors: https://misc.flogisoft.com/bash/tip_colors_and_formatting
 */

#ifdef NODEBUG_1
# define DOut1( Msg )
#else
# define DOut1( Msg ) \
  if (gts::Debug_Display) {			\
   std::cout <<  "\033[2m";			\
   if (gts::Debug_FunName != __FUNCTION__) {			\
     gts::Debug_FunName = __FUNCTION__;				\
    std::cout << "### 5 Debug_1 ("                              \
              << gts::MoveToLastSlash(__FILE__)			\
              << ":" << __LINE__  << " " << __FUNCTION__ << ")" \
              << "\033[0m" << std::endl;                        \
   }                                                            \
   std::cout << "\033[35m\033[1m"			        \
             << "... 1: " << Msg << "\033[0m" << std::endl;     \
  }
#endif


#ifdef NODEBUG_2
# define DOut2( Msg )
#else
# define DOut2( Msg )                          \
  if (gts::Debug_Display) {			\
   std::cout <<  "\033[2m";			\
   if (gts::Debug_FunName != __FUNCTION__) {			\
     gts::Debug_FunName = __FUNCTION__;				\
    std::cout << "=== 2 Debug_2 ("                              \
              << gts::MoveToLastSlash(__FILE__)			\
              << ":" << __LINE__  << " " << __FUNCTION__ << ")" \
              << "\033[0m" << std::endl;                        \
   }                                                            \
   std::cout << "\033[33m\033[1m"			        \
             << "... 2: " << Msg << "\033[0m" << std::endl;     \
  }
#endif


#ifdef NODEBUG_3
# define DOut3( Msg )
#else
# define DOut3( Msg )\
  if (gts::Debug_Display) {			\
   std::cout <<  "\033[2m";			\
   if (gts::Debug_FunName != __FUNCTION__) {			\
     gts::Debug_FunName = __FUNCTION__;				\
    std::cout << "### 3 Debug_3 ("                              \
              << gts::MoveToLastSlash(__FILE__)			\
              << ":" << __LINE__  << " " << __FUNCTION__ << ")" \
              << "\033[0m" << std::endl;                        \
   }                                                            \
   std::cout << "\033[34m\033[1m"			        \
             << "... 3: " << Msg << "\033[0m" << std::endl;     \
  }
#endif


#ifdef NODEBUG_4
# define DOut4( Msg )
#else
# define DOut4( Msg )\
  if (gts::Debug_Display) {			\
   std::cout <<  "\033[2m";			\
   if (gts::Debug_FunName != __FUNCTION__) {			\
     gts::Debug_FunName = __FUNCTION__;				\
    std::cout << "+++ 4 Debug_4 ("                              \
              << gts::MoveToLastSlash(__FILE__)			\
              << ":" << __LINE__  << " " << __FUNCTION__ << ")" \
              << "\033[0m" << std::endl;                        \
   }                                                            \
   std::cout << "\033[37m\033[1m"			        \
             << "... 4: " << Msg << "\033[0m" << std::endl;     \
  }
#endif



#ifdef NODEBUG_5
# define DOut5( Msg )
#else
# define DOut5( Msg ) \
  if (gts::Debug_Display) {			\
   std::cout <<  "\033[2m";			\
   if (gts::Debug_FunName != __FUNCTION__) {			\
     gts::Debug_FunName = __FUNCTION__;				\
    std::cout << "### 5 Debug_5 ("                              \
              << gts::MoveToLastSlash(__FILE__)			\
              << ":" << __LINE__  << " " << __FUNCTION__ << ")" \
              << "\033[0m" << std::endl;                        \
   }                                                            \
   std::cout << "\033[36m\033[1m"			        \
             << "... 5: " << Msg << "\033[0m" << std::endl;     \
  }
#endif



#ifdef NOWARNING_5
# define CWarning_1( Msg )
#else
# define CWarning_1( Msg ) \
  if (gts::Debug_Display) {			\
   std::cout <<  "\033[2m";			\
   if (gts::Debug_FunName != __FUNCTION__) {			\
     gts::Debug_FunName = __FUNCTION__;				\
    std::cout << "### 1 CWarning_1 ("                           \
              << gts::MoveToLastSlash(__FILE__)			\
              << ":" << __LINE__  << " " << __FUNCTION__ << ")" \
              << "\033[0m" << std::endl;                        \
   }                                                            \
   std::cout << "\033[36m\033[1m"			        \
             << "... 1: " << Msg << "\033[0m" << std::endl;     \
  }
#endif



#ifdef NO_CERROR_1
# define CErr_1( Msg )
#else
# define CErr_1( Msg )  std::cout << std::endl <<  "\033[2m" "!!! 1 CErr_1 ("\
                                  << gts::MoveToLastSlash(__FILE__)	     \
                                  << ":" << __LINE__  << " " << __FUNCTION__ << ")" \
                                  << "\033[0m" << std::endl	                    \
                                  << "\033[31m\033[1m"                              \
                                  << "!!! 1: " << Msg << "\033[0m" << std::endl;
#endif




#ifdef NOMSG_1
# define DMsg1( Msg )
#else
# define DMsg1( Msg ) \
  if (gts::Debug_Display) {			\
   std::cout <<  "\033[2m";			\
   if (gts::Debug_FunName != __FUNCTION__) {			\
     gts::Debug_FunName = __FUNCTION__;				\
    std::cout << "*** 1 Msg1 ("                              \
              << gts::MoveToLastSlash(__FILE__)			\
              << ":" << __LINE__  << " " << __FUNCTION__ << ")" \
              << "\033[0m" << std::endl;                        \
   }                                                            \
   std::cout << "\033[92m\033[1m"			        \
             << "*** 1: " << Msg << "\033[0m" << std::endl;     \
  }
#endif



//#define DEBUG_DOA

#endif
