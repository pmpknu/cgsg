/* FILE NAME : t03mandl.cpp
 * PROGRAMMER: DG5
 * DATE      : 19.07.2021
 * PURPOSE   : Mandelbrot & Julia set drawing program.
 */

#include <ctime>
#include <math.h>
#include <thread>

#include <glut.h>

#include <commondf.h>

#define WINDOW_W 500
#define WINDOW_H 500
DOUBLE Zoom = 1;
DOUBLE JulZoom = 1;
DOUBLE JulX = 0;
DOUBLE JulY = 0;

/* Frame size */
const INT FrameW = 192,
          FrameH = 108;
struct frame
{
  const INT w = FrameW,
            h = FrameH;

  BYTE Frame[FrameH][FrameW][4];
} Frame;

VOID PutPixel( INT X, INT Y, BYTE R, BYTE G, BYTE B )
{
  if (X >= 0 && Y >= 0 && X < Frame.w && Y < Frame.h)
  {
    Frame.Frame[Y][X][0] = B % 256;
    Frame.Frame[Y][X][1] = G % 256;
    Frame.Frame[Y][X][2] = R % 256;
    Frame.Frame[Y][X][3] = 1;
  }
} /* End of 'PutPixel' function */

struct cmpl
{
  DOUBLE re, im;

  cmpl( void )
  {
  }

  cmpl( DOUBLE Re, DOUBLE Im ) : re(Re), im(Im) 
  {
  }

  ~cmpl( void )
  {
  }

  cmpl operator+( const cmpl &C ) const
  {
    return cmpl(re + C.re, im + C.im);
  }

  cmpl operator*( const cmpl &C ) const
  {
    return cmpl(re * C.re - im * C.im, re * C.im + im * C.re);
  }

  double module2( void ) const
  {
    return re * re + im * im;
  }

  INT Julia( cmpl C )
  {
    cmpl Z = cmpl(re, im);
    cmpl Z0 = Z;
    INT n = 0;

    while (n < 255 && Z.module2() < 4)
    {
      Z = Z0 * Z0 + C;
      Z0 = Z;
      n++;
    }

    return n;
  }
};

VOID DrawMandl( VOID )
{
  DOUBLE t = static_cast<DOUBLE>(clock()) / CLOCKS_PER_SEC;
  cmpl C = cmpl(sin(t), cos(t));

  INT n;

  int num_ths = std::thread::hardware_concurrency();

  std::thread Th;
  Th = std::thread();
  Th.join();

  /*
  for (int ys = 0; ys < Frame.h; ys++)
    for (int xs = 0; xs < Frame.w; xs++)
    {
      //n = Julia(cmpl(static_cast<DOUBLE>(ys + JulY) / FRAME_H * 2 * JulZoom - JulZoom, static_cast<DOUBLE>(xs + JulX) / FRAME_W * 2 * JulZoom - JulZoom), C);
      n = cmpl(static_cast<DOUBLE>(ys + JulY) / Frame.h * 2 * JulZoom - JulZoom, static_cast<DOUBLE>(xs + JulX) / Frame.w * 2 * JulZoom - JulZoom).Julia(
	cmpl(static_cast<DOUBLE>(ys + JulY) / Frame.h * 2 * JulZoom - JulZoom, static_cast<DOUBLE>(xs + JulX) / Frame.w * 2 * JulZoom - JulZoom));
      PutPixel(xs, ys, n * 30, n * 3, n * 8);
    }
  */
}

/* Display GLUT callback function */
VOID Display( VOID )
{
  glClearColor(0.3, 0.5, 0.7, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  DrawMandl();

  glRasterPos2d(-1, 1);
  glPixelZoom(Zoom, -Zoom);
  glDrawPixels(Frame.w, Frame.h, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Frame.Frame);

  glFinish();

  glutSwapBuffers();
  glutPostRedisplay();
} /* End of 'Display' function */

/* Keyboard GLUT callback function */
VOID Keyboard( UCHAR Key, INT X, INT Y )
{
  switch (Key)
  {
  case 27:
    exit(30);
  case 'f':
    glutFullScreen();
    break;
  case '+':
    JulZoom /= 2;
    break;
  case '-':
    JulZoom *= 2;
    break;
  case 'w':
    JulY += 4.7 + 1 / JulZoom;
    break;
  case 'a':
    JulX += 4.7 + 1 / JulZoom;
    break;
  case 's':
    JulY -= 4.7 + 1 / JulZoom;
    break;
  case 'd':
    JulX -= 4.7 + 1 / JulZoom;
    break;
  case '1':
    Zoom--;
    break;
  case '2':
    Zoom++;
    break;
  }
} /* End of 'Keyboard' function */

/* The program entry point */
INT main( INT ArgC, CHAR *ArgV[] )
{
  glutInit(&ArgC, ArgV);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowSize(WINDOW_H, WINDOW_W);
  glutCreateWindow("CGSGFOREVER");

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  glutMainLoop();
  return 0;
} /* End of 'main' function */

/* END OF 't03mandl.cpp' FILE */