/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : win.h
 * PURPOSE     : Ray tracing project.
 *               Main program handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 01.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */


#ifndef __win_h_
#define __win_h_

#include "../def.h"
#include <windowsx.h>

/* Space gort namespace */
namespace gort
{
  /* Window class */
  class win
  {
  protected:
    HWND hWnd;           // window handle
    INT W = 0, H = 0;            // window size
    HINSTANCE hInstance; // application handle

    INT MouseWheel;
  private:
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
      WPARAM wParam, LPARAM lParam );

    BOOL IsFullScreen;
    RECT FullScreenSaveRect;
    BOOL IsInit; // Inicialization flag

    const INT
      InitTimer = 30,     // Initialization timer code
      RefreshTimer = 47;  // Refresh timer code
  public:
    BOOL IsActive = false;
    const CHAR WindowClassName[21] = "t05anim window class";

    win( HINSTANCE hInst = GetModuleHandle(nullptr) );
    ~win( VOID );

    WPARAM Run( VOID );
    //VOID FlipFullScreen( VOID );

    /* Returning hWnd variable method */
    HWND & GethWnd( VOID )
    {
      return hWnd;
    }

  private:
    //callbacks
    virtual VOID Init( VOID )
    {
    }

    virtual VOID Close( VOID )
    {
    }

    virtual VOID Resize( VOID )
    {
    }

    virtual VOID Timer( VOID )
    {
    }

    virtual VOID Activate( VOID )
    {
    }

    virtual VOID Idle( VOID  )
    {
    }

    virtual VOID Erase( HDC hDC )
    {
    }

    virtual VOID Paint( HDC hDC )
    {
    }

    /* User message handle function
     * ARGUMENTS:
     *   - word parametr:
     *     WPARAM wParam;
     *   - long parametr:
     *     LPARAM lParam;
     * RETURNS: None.
     */
    virtual VOID User( WPARAM wParam, LPARAM lParam )
    {
    } /* End of 'User' function */

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
    virtual VOID Keyboard( UINT Key, BOOL IsPress,
                       INT RepeatCount, UINT ShiftKeysFlags )
    {
    } /* End of 'Keyboard' function */


    // message cracks
    VOID OnGetMinMaxInfo( MINMAXINFO *MinMax );
    BOOL OnCreate( CREATESTRUCT *CS );
    VOID OnSize( UINT State, INT W, INT H );
    VOID OnTimer( INT Id );
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );
    VOID OnButtonDown( BOOL IsDblClick, INT X, INT Y, UINT Keys );
    VOID OnButtonUp( INT X, INT Y, UINT Keys );
    BOOL OnEraseBackground( HDC hDC );
    VOID OnPaint( HDC hDC, PAINTSTRUCT *PS );
    VOID OnClose( VOID );
    VOID OnDestroy( VOID );
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
    VOID OnKey( UINT Key, BOOL IsPress, INT RepeatCount, UINT ShiftKeysFlags );
  };
}

#endif /* __win_h_ */

/* END OF 'win.h' FILE */