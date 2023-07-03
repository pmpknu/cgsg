/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rnd.c
 * PURPOSE     : Animation project.
 *               Render system.
 *               Implementation of renderer class functions.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 23.07.2021.
 * NOTE        : Module namespace 'gogl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <cstdio>

#include "../../def.h"

#include "rnd.h"

gogl::render::render( HWND &hWnd, INT &W, INT &H ) : hWnd(hWnd), FrameW(W), FrameH(H)
{
  PIXELFORMATDESCRIPTOR pfd = {0};

  /* Store window and context handles */
  hDC = GetDC(hWnd);

  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;

  INT i = ChoosePixelFormat(hDC, &pfd);
  DescribePixelFormat(hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(hDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  hGLRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hGLRC);

  /* Initialize GLEW library */
  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    MessageBox(hWnd, "Error OpenGL initialization", "ERROR",
      MB_ICONERROR | MB_OK);
    exit(0);
  }

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
  glDebugMessageCallback(glDebugOutput, NULL);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

  /* Set default render parameters */
  glClearColor(0.30, 0.50, 0.8, 1);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
}

gogl::render::~render( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hGLRC);
  ReleaseDC(hWnd, hDC);
}

/* Resize declaration context function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::render::Resize( VOID )
{
  cam.Resize(FrameW, FrameH);
  glViewport(0, 0, FrameW, FrameH);
} /* End of 'Resize' function */

/* Frame rander copy function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::render::CopyFrame( VOID )
{
  ///SwapBuffers(hDC);
  wglSwapLayerBuffers(hDC, WGL_SWAP_MAIN_PLANE);
} /* End of 'CopyFrame' function */

/* Start rendering function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::render::Start( VOID )
{
  /* Clear frame */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} /* End of 'Start' function */

/* End rendering function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::render::End( VOID )
{
  glFinish();
} /* End of 'RndEnd' function */

/* Debug output function.
 * ARGUMENTS:
 *   - source APi or device:
 *      UINT Source;
 *   - error type:
 *      UINT Type;
 *   - error message id:
 *      UINT Id, 
 *   - message severity:
 *      UINT severity, 
 *   - message text length:
 *      INT Length, 
 *   - message text:
 *      CHAR *Message, 
 *   - user addon parameters pointer:
 *      VOID *UserParam;
 * RETURNS: None.
 */
VOID APIENTRY gogl::render::glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message, const VOID *UserParam )
{
  INT len = 0;
  static CHAR Buf[10000];
  int BufLen = sizeof( Buf );

  /* Ignore non-significant error/warning codes */
  if (Id == 131169 || Id == 131185 || Id == 131218 || Id == 131204)
    return;

  len += sprintf_s(Buf + len, BufLen, "Debug message (%i) %s\n", Id, Message);
  switch (Source)
  {
  case GL_DEBUG_SOURCE_API:
    len += sprintf_s(Buf + len, BufLen, "Source: API\n");
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    len += sprintf_s(Buf + len, BufLen, "Source: Window System\n");
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    len += sprintf_s(Buf + len, BufLen, "Source: Shader Compiler\n");
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    len += sprintf_s(Buf + len, BufLen, "Source: Third Party\n");
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    len += sprintf_s(Buf + len, BufLen, "Source: Application");
    break;
  case GL_DEBUG_SOURCE_OTHER:
    len += sprintf_s(Buf + len, BufLen, "Source: Other");
    break;
  }
  len += sprintf_s(Buf + len, BufLen, "\n");
 
  switch (Type)
  {
  case GL_DEBUG_TYPE_ERROR:
    len += sprintf_s(Buf + len, BufLen, "Type: Error");
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    len += sprintf_s(Buf + len, BufLen, "Type: Deprecated Behaviour");
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    len += sprintf_s(Buf + len, BufLen, "Type: Undefined Behaviour");
    break; 
  case GL_DEBUG_TYPE_PORTABILITY:
    len += sprintf_s(Buf + len, BufLen, "Type: Portability");
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    len += sprintf_s(Buf + len, BufLen, "Type: Performance");
    break;
  case GL_DEBUG_TYPE_MARKER:
    len += sprintf_s(Buf + len, BufLen, "Type: Marker");
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    len += sprintf_s(Buf + len, BufLen, "Type: Push Group");
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    len += sprintf_s(Buf + len, BufLen, "Type: Pop Group");
    break;
  case GL_DEBUG_TYPE_OTHER:
    len += sprintf_s(Buf + len, BufLen, "Type: Other");
    break;
  }
  len += sprintf_s(Buf + len, BufLen, "\n");
 
  switch (Severity)
  {
  case GL_DEBUG_SEVERITY_HIGH:
    len += sprintf_s(Buf + len, BufLen, "Severity: high");
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    len += sprintf_s(Buf + len, BufLen, "Severity: medium");
    break;
  case GL_DEBUG_SEVERITY_LOW:
    len += sprintf_s(Buf + len, BufLen, "Severity: low");
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    len += sprintf_s(Buf + len, BufLen, "Severity: notification");
    break;
  }
  len += sprintf_s(Buf + len, BufLen, "\n\n");
 
  OutputDebugString(Buf);
} /* End of 'glDebugOutput' function */


/* END OF 'rnd.c' FILE */