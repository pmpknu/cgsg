/* FILE NAME : def.h
 * PROGRAMMER: DG5
 * DATE      : 22.07.2021
 * PURPOSE   : Project common declaration module.
 */

#ifndef __def_h_
#define __def_h_

#include "mth/mth.h"

#include "utilities/stock.h"

/* Debug memory allocation support */ 
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h>
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy 
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __ooppss;
#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

#pragma comment(lib, "opengl32")

#define GLEW_STATIC
#include "anim/rnd/GLEW/glew.h"

#endif /* __def_h_ */

/* END OF 'def.h' FILE */