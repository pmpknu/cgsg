/* FILE NAME : winmsg.cpp
 * PROGRAMMER: DG5
 * DATE      : 22.07.2021
 * PURPOSE   : Windows message response module.
 */

#include "win.h"

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL gogl::win::OnCreate( CREATESTRUCT *CS )
{
  SetTimer(hWnd, InitTimer, 1, nullptr);

  return TRUE;
} /* End of 'win::OnCreate' function */
 
/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::win::OnDestroy( VOID )
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
VOID gogl::win::OnSize( UINT State, INT W, INT H )
{
  this->W = W;
  this->H = H;

  if (IsInit)
    Resize();
} /* End of 'gogl::win::OnSize' function */
 
/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL gogl::win::OnEraseBackground( HDC hDC )
{
  if (IsInit)
    Erase(hDC);

  return TRUE;
} /* End of 'gogl::win::OnEraseBkgnd' function */
 
/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID gogl::win::OnPaint( HDC hDC, PAINTSTRUCT *PS )
{
  if (IsInit)
    Paint(hDC);
} /* End of 'gogl::win::OnPaint' function */

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
VOID gogl::win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;

  if (IsInit)
        Activate();
} /* End of 'gogl::win::OnActivate' function */
 
/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID gogl::win::OnTimer( INT Id )
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
} /* End of 'gogl::win::OnTimer' function */
 
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
VOID gogl::win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  MouseWheel += Z;
} /* End of 'gogl::win::OnMouseWheel' function */

/* WM_GETMINMAAXINFO window message handle function.
 * ARGUMENTS:
 *   - ???:
 *       MINMAXINFO *MinMax;
 * RETURNS: None.
 */
VOID gogl::win::OnGetMinMaxInfo( MINMAXINFO *MinMax )
{
} /* End of 'gogl::win::OnGetMinMaxInfo' function */

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
VOID gogl::win::OnButtonDown( BOOL IsDblClick, INT X, INT Y, UINT Keys )
{
} /* End of 'gogl::win::OnButtonDown' function */

/* WM_BUTTONUP window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID gogl::win::OnButtonUp( INT X, INT Y, UINT Keys )
{
} /* End of 'gogl::win::OnLButtonUp' function */

/* WM_CLOSE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::win::OnClose( VOID )
{
} /* End of 'gogl::win::OnClose' function */

/* END OF 'winmsg.cpp' FILE */