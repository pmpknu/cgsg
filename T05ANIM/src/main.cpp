/* FILE NAME : main.cpp
 * PROGRAMMER: DG5
 * DATE      : 20.07.2021
 * PURPOSE   : Math test main program file.
 */

#include "anim/anim.h"

#include "anim/rnd/rnd.h"

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  gogl::anim *myw = gogl::anim::GetPtr();

  myw->Scene << "Player" << "Target" << "Map";

  return myw->Run();
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */