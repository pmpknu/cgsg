/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : winmsg.cpp
 * PURPOSE     : Ray tracing project.
 *               Windows message response module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 01.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */


#include "win.h"

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL gort::win::OnCreate( CREATESTRUCT *CS )
{
  SetTimer(hWnd, InitTimer, 1, nullptr);

  return TRUE;
} /* End of 'win::OnCreate' function */
 
/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gort::win::OnDestroy( VOID )
{
  if (IsInit)
  {
    Close();
    KillTimer(hWnd, RefreshTimer);
  }
  else
    KillTimer(hWnd, InitTimer);
} /* End of 'win::OnDestroy' function */
 
/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID gort::win::OnSize( UINT State, INT W, INT H )
{
  this->W = W;
  this->H = H;

  if (IsInit)
    Resize();
} /* End of 'gort::win::OnSize' function */
 
/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL gort::win::OnEraseBackground( HDC hDC )
{
  if (IsInit)
    Erase(hDC);

  return TRUE;
} /* End of 'gort::win::OnEraseBkgnd' function */
 
/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID gort::win::OnPaint( HDC hDC, PAINTSTRUCT *PS )
{
  if (IsInit)
    Paint(hDC);
} /* End of 'gort::win::OnPaint' function */

/* WM_ACTIVATE window message handle function.
 * ARGUMENTS:
 *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
 *       UINT Reason;
 *   - handle of active window:
 *       HWND hWndActDeact;
 *   - minimized flag:
 *       BOOL IsMinimized;
 * RETURNS: None.
 */
VOID gort::win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;

  if (IsInit)
        Activate();
} /* End of 'gort::win::OnActivate' function */
 
/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID gort::win::OnTimer( INT Id )
{
  if (!IsInit)
  {
    KillTimer(hWnd, InitTimer);
    SetTimer(hWnd, RefreshTimer, 1, nullptr);
    IsInit = TRUE;

    // call callbacks
    Init();
    Resize();
    Timer();
  }
  else
    Timer();
} /* End of 'gort::win::OnTimer' function */
 
/* WM_MOUSEWHEEL window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse wheel relative delta value:
 *       INT Z;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID gort::win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  MouseWheel += Z;
} /* End of 'gort::win::OnMouseWheel' function */

/* WM_GETMINMAAXINFO window message handle function.
 * ARGUMENTS:
 *   - ???:
 *       MINMAXINFO *MinMax;
 * RETURNS: None.
 */
VOID gort::win::OnGetMinMaxInfo( MINMAXINFO *MinMax )
{
} /* End of 'gort::win::OnGetMinMaxInfo' function */

/* WM_BUTTONDOWN window message handle function.
 * ARGUMENTS:
 *   - is button double clicked flag:
 *       BOOL IsDblClick;
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID gort::win::OnButtonDown( BOOL IsDblClick, INT X, INT Y, UINT Keys )
{
} /* End of 'gort::win::OnButtonDown' function */

/* WM_BUTTONUP window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID gort::win::OnButtonUp( INT X, INT Y, UINT Keys )
{
} /* End of 'gort::win::OnLButtonUp' function */

/* WM_CLOSE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gort::win::OnClose( VOID )
{
} /* End of 'gort::win::OnClose' function */

/* WM_KEYDOWN/WM_KEYUP window message handle function.
 * ARGUMENTS:
 *   - virtual key number (see VK_***, 'A', ..., '0', ...):
 *       UINT Key;
 *   - press flag:
 *       BOOL IsPress;
 *   - autorepeat counter:
 *       INT RepeatCount;
 *   - shift/control etc key states bits (see MK_***):
 *       UINT ShiftKeysFlags;
 * RETURNS: None.
 */
VOID gort::win::OnKey( UINT Key, BOOL IsPress,
                       INT RepeatCount, UINT ShiftKeysFlags )
{
  Keyboard(Key, IsPress, RepeatCount, ShiftKeysFlags);
} /* End of 'virt::win::OnKey' function */

/* END OF 'winmsg.cpp' FILE */