/* FILE NAME : win.h
 * PROGRAMMER: DG5
 * DATE      : 21.07.2021
 * PURPOSE   : Common math module.
 */

#ifndef __win_h_
#define __win_h_

#include "../def.h"
#include <windowsx.h>

/* Space gogl namespace */
namespace gogl
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
  };
}

#endif /* __win_h_ */

/* END OF 'win.h' FILE */