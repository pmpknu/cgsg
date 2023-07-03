/* FILE NAME : win.cpp
 * PROGRAMMER: DG5
 * DATE      : 21.07.2021
 * PURPOSE   : Main program module.
 */

#include "win.h"

gogl::win::win( HINSTANCE hInst ) : hInstance( hInst )
{
  WNDCLASS wc;
  HWND hWnd;

  /* cheking for memory leaks */
  //SetDbgMemHooks();

  /* Create and register window class */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = sizeof( win * );
  wc.hbrBackground = (HBRUSH)COLOR_MENU;
  wc.hCursor = LoadCursor(NULL, IDC_CROSS);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = WindowClassName;
  wc.lpfnWndProc = WinFunc;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK | MB_ICONERROR);
    return;
  }

  /* Create window */
  hWnd = CreateWindow(WindowClassName, "3D animation",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    nullptr, nullptr, hInstance, reinterpret_cast<VOID *>(this));
 }

gogl::win::~win( VOID )
{
}

LRESULT CALLBACK gogl::win::WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  win *Win;
  HDC hDC;
  PAINTSTRUCT ps;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;
  case WM_CREATE:
    SetWindowLongPtr(hWnd, 0, (UINT_PTR)((CREATESTRUCT *)lParam)->lpCreateParams);
  default:
    Win = reinterpret_cast<win *>(GetWindowLongPtr(hWnd, 0));
    if (Win != nullptr)
      switch (Msg)
      {
      case WM_CREATE:
        Win->hWnd = hWnd;
        return Win->OnCreate( (CREATESTRUCT *)lParam ) ? 0 : -1;
      case WM_SIZE:
        Win->OnSize(wParam, LOWORD( lParam ), HIWORD( lParam ));
        return 0;
      case WM_ERASEBKGND:
        return (LRESULT)Win->OnEraseBackground( (HDC)wParam );
      case WM_PAINT:
        hDC = BeginPaint( hWnd, &ps );
        Win->OnPaint( hDC, &ps );
        EndPaint( hWnd, &ps );
        return 0;
      case WM_TIMER:
        Win->OnTimer( (UINT)wParam );
        return 0;
      case WM_MOUSEWHEEL:
        Win->OnMouseWheel( (INT)(SHORT)LOWORD( lParam ),
          (INT)(SHORT)HIWORD( lParam ),
          (INT)(SHORT)HIWORD( wParam ),
          (UINT)(SHORT)LOWORD( wParam ) );
        return 0;
      case WM_LBUTTONDOWN:
      case WM_RBUTTONDOWN:
      case WM_MBUTTONDOWN:
        SetCapture(hWnd);
        Win->OnButtonDown(FALSE,
          (INT)(SHORT)LOWORD(lParam),
          (INT)(SHORT)HIWORD(lParam),
          (UINT)(SHORT)LOWORD(wParam));
      case WM_LBUTTONUP:
      case WM_RBUTTONUP:
      case WM_MBUTTONUP:
        ReleaseCapture();
        Win->OnButtonUp( (INT)(SHORT)LOWORD( lParam ),
          (INT)(SHORT)HIWORD( lParam ),
          (UINT)(SHORT)LOWORD( wParam ) );
        return 0;
      //. . .
      case WM_DESTROY:
        Win->OnDestroy();
        PostQuitMessage( 30 );
        return 0;
      }
  }
  return DefWindowProc( hWnd, Msg, wParam, lParam );
}

WPARAM gogl::win::Run( VOID )
{
  MSG msg;

  /* Message loop */
  while (TRUE)
  {
    /* Check message at window message queue */
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      if (msg.message == WM_QUIT)
        break;
      else
      {
        if (IsInit)
          Idle();

        /* Displatch message to window */
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    else
      Idle();
    //else
    // Render & Copy frame
  }
  return msg.wParam;
}

/* END OF 'win.cpp' FILE */