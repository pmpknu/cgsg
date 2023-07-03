/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : main.cpp
 * PURPOSE     : Ray tracing project.
 *               Main module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 01.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "def.h"
#include "./win/win.h"
#include "./rt/frame/frame.h"
#include "./rt/rt.h"
#include "timer.h"

#include <cstdlib>
#include <ctime>
#include <thread>

/* Project namespace */
namespace gort
{
  class raytracer : public win, public timer
  {
  private:
    camera Cam;  // Camera
    frame Frame; // Frame buffer

    // Threads for prallel rendering
    std::thread Threads[8];  // Treads for drawing array
    const int ThCount;       // Treads for drawing count

  public:
    scene Scene; // Scene of shapes

    /* Default constructor */
    raytracer( VOID ) : ThCount(std::thread::hardware_concurrency() - 11)
    {
    } /* End of 'raytracer' function */

    /* Render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID )
    {
      // Starting drawing threads
      for (INT i = 1; i <= ThCount; i++)
        Threads[i - 1] = std::thread([this, i]()
          {
            for (INT y = i; y < Frame.GetH(); y += i)
              for (INT x = 0; x < Frame.GetW(); x++)
              {
                vec3 color = Scene.Trace(Cam.FrameRay(x, y), Scene.Air, 1, 0);
                Frame.PutPixel(x, y, mth::toRGB(color));
                InvalidateRect(hWnd, nullptr, TRUE);
              }
          });

      // Waiting for all threads
      for (INT i = 1; i <= ThCount; i++)
        Threads[i - 1].join();
    } /* End of 'Render' function */

    /* Rendering thread handle function.
     * ARGUMENTS:
     *   - thread input pointer:
     *       
     * RETURNS:
     *  (DWORD) thread returns value.
     */
    static DWORD WINAPI RenderThread( __in LPVOID lpParameter )
    {
      raytracer *Win = reinterpret_cast<raytracer *>(lpParameter);

      while(TRUE)
        Win->Render();
    } /* End of 'RenderThread' function */

    /* User message handle function
     * ARGUMENTS:
     *   - word parametr:
     *     WPARAM wParam;
     *   - long parametr:
     *     LPARAM lParam;
     * RETURNS: None.
     */
    /*
    VOID User( WPARAM wParam, LPARAM lParam ) override
    {
      INT ys = wParam;
      vec3 *Row = (vec3 *)lParam;

      for (INT xs = 0; xs < Frame.GetW(); xs++)
      {
        vec3 col = Row[xs];

        Frame.PutPixel(xs, ys, mth::toRGB(col));
      }
      InvalidateRect(hWnd, nullptr, false);
    } *//* End of 'User' function */


    /* Render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    /*VOID Render( VOID )
    {
      timer::Response();
      Scene.Air.RefractionCoef = 0.9;
      //Scene.Air.DecayCoef = 0.1;
      ray R1 = Cam.FrameRay(5, 5);
      for (INT y = 0; y < Frame.GetH(); y++)
        for (INT x = 0; x < Frame.GetW(); x++)
        {
          ray R = Cam.FrameRay(x + 0.5, y + 0.5);
          intr Intr;
          vec3 Color = Scene.Trace(R, Scene.Air, 1, 0);

          Frame.PutPixel(x, y, mth::toRGB(Color));
        }

      Frame.SaveTGA();
    } *//* End of 'Render' function */

    /* Render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
/*    VOID Render( VOID )
    {
      timer::Response();
      DBL t = timer::GlobalTime;

      static auto fthread = []( raytracer *rt, INT y )
      {
        for (INT x = 0; x < rt->Frame.GetW(); x++)
        {
          ray R = rt->Cam.FrameRay(x + 0.5, y + 0.5);
          intr Intr;
          vec3 Color = rt->Scene.Trace(R, rt->Scene.Air, 1, 0);

          rt->Frame.PutPixel(x, y, mth::toRGB(Color));
        }
      };

      SetWindowText(hWnd, std::to_string(timer::FPS).c_str());
      for (INT y = 0; y < Frame.GetH(); y += NumOfThreads)
      {
        for (INT i = 0; i < NumOfThreads; i++)
          Ths[i] = std::thread(fthread, this, y + i);
        for (INT i = 0; i < NumOfThreads; i++)
          Ths[i].join();
      }

      timer::Response();
      t = timer::GlobalTime - t;

      Frame.SaveTGA();
    } *//* End of 'Render' function */
 
    #pragma region KAL
        //  for (INT y = 0; y < Frame.GetH(); y++)
        //for (INT x = 0; x < Frame.GetW(); x++)
        //{
        //  //Frame.PutPixel(x, y, (x - y) * (x - y) * x * y + (x + y) * (x + y));
        //  ray R = Cam.FrameRay(x + 0.5, y + 0.5);
        //  intr Intr;
        //  vec3 Color = vec3(0);
        //
        //  if (Scene.Intersection(R, &Intr))
        //  {
        //    vec3 Lamp = vec3(1).Normalizing();
        //    if (!Intr.IsP)
        //      Intr.P = R(Intr.T);
        //    if (!Intr.IsN)
        //      Intr.Sh->GetNormal(&Intr);
        //
        //    Color = vec3(0.8, 0.47, 0.30) * (Intr.N & Lamp); //vec3(0.7 / Intr.T, 0.7 / Intr.T, 1 / Intr.T);
        //    if (Scene .Intersection(ray(R(Intr.T) + Lamp * Threshold, Lamp), &Intr))
        //      Color *= 0.30;
        //  }
        //  Frame.PutPixel(x, y, toRGB(Color));
        //}
    #pragma endregion
    #pragma region OVERRIDEFUNCS
    /* Initialize frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID ) override//final
    {
      //Frame.Resize(1920, 1080);
      Frame.Resize(100, 100);
      //Frame.Resize(W / 4 * 3, H / 4 * 3);
      Cam.Resize(Frame.GetW(), Frame.GetH());
      //Cam.Rotate(vec3(0, 1, 0), -30);
      //Cam.Move(vec3(0, 0, 10));
      //Cam.SetLocAtUp(gort::vec3(-20, 6, 20), gort::vec3(0, 5, 4));
      
      //Render();
      //InvalidateRect(hWnd, nullptr, true);

      DWORD Thid;
      HANDLE RenderThreadHandle = CreateThread(0, 0, RenderThread, this, 0, &Thid);
    } /* End of  */

    VOID Resize( VOID ) override
    {
      //Frame.Resize(W, H);
      InvalidateRect(hWnd, nullptr, true);
    }

    VOID Idle( VOID ) override
    {
      //Cam.Rotate(vec3(0, 1, 0), clock() / 5000);
      //Render();
      //InvalidateRect(hWnd, nullptr, true);
    }

    VOID Paint( HDC hDC ) override
    {
      INT AvW = (W - Frame.GetW()) / 2;
      INT AvH = (H - Frame.GetH()) / 2;
      HPEN hPen = CreatePen(PS_SOLID, 5, 0x0000FF);

      SelectObject(hDC, hPen);
      //SelectObject(hDC, GetStockObject(BLACK_PEN));
      Rectangle(hDC,  AvW - 10, AvH - 10, AvW + 10 + Frame.GetW(), AvH + 10 + Frame.GetH());

      Frame.Draw(hDC, AvW, AvH);
    }

    VOID Erase( HDC hDC ) override
    {
      //SelectObject(hDC, GetStockObject(NULL_PEN));
      //Rectangle(hDC, 0, 0, W, H);
    }

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
    VOID Keyboard( UINT Key, BOOL IsPress,
                       INT RepeatCount, UINT ShiftKeysFlags ) override
    {
      switch (Key)
      {
      case 'W':
        Cam.Move(vec3(Cam.Dir[0], 0, Cam.Dir[2]));
        Render();
        InvalidateRect(hWnd, nullptr, true);
        break;
      case 'S':
        Cam.Move(-vec3(Cam.Dir[0], 0, Cam.Dir[2]));
        Render();
        InvalidateRect(hWnd, nullptr, true);
        break;
      case 'A':
        Cam.Move(-vec3(Cam.Right[0], 0, Cam.Right[2]));
        Render();
        InvalidateRect(hWnd, nullptr, true);
        break;
      case 'D':
        Cam.Move(vec3(Cam.Right[0], 0, Cam.Right[2]));
        Render();
        InvalidateRect(hWnd, nullptr, true);
        break;
      }
    } /* End of 'Keyboard' function */
    #pragma endregion
  };
} /* end of 'gort' namespace */

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
  gort::raytracer rt;
  gort::surface Mtl(gort::vec3(0.4, 0.2, 0.8), gort::vec3(0.3, 0.1, 0.89), gort::vec3(0.4, 0.2, 0.9), 1, 0.4, 0.9);
  gort::surface Mtl1(gort::vec3(0.1), gort::vec3(0.8), gort::vec3(0.2), 1, 0.9, 0.1);
  //gort::surface Mtl2(gort::vec3(0.47), gort::vec3(0.6), gort::vec3(0.8), 1, 0.9, 0.9);
  gort::surface mtl = gort::surface(gort::vec3(0), gort::vec3(0.2), gort::vec3(0.4), 32.8, 0.4, 0.9);

  rt.Scene
    << new gort::sphere(gort::vec3(0), 1, Mtl, gort::envi(1, 0))
    << new gort::sphere(gort::vec3(-0.2, 0, -2), 1, Mtl1, gort::envi(1, 0))
    << new gort::plane(gort::vec3(0, 1, 0), gort::vec3(0, -1, 0), Mtl)
    << new gort::point(gort::vec3(1, 7, 2), gort::vec3(0.5, 0, 1), 1, 20, 0, 0.1, 0);

 //   << new gort::sphere(gort::vec3(0, 2, -3.5), 2, gort::surface(gort::vec3(0.1745, 0.01175, 0.01175), gort::vec3(0.61424, 0.04136, 0.04136), gort::vec3(0.727811, 0.626959, 0.626959), 76.8, 0.68, 0.7), gort::envi(0, 0)) //RUBY
 //   << new gort::sphere(gort::vec3(5, 2, -3.5), 2, gort::surface(gort::vec3(0.0215, 0.1745, 0.0215), gort::vec3(0.07568, 0.61424, 0.07568), gort::vec3(0.633, 0.727811, 0.633), 76.8, 0.68, 0.7), gort::envi(0, 0))
 //   << new gort::sphere(gort::vec3(0.5, 1.5, 6.5), 1, mtl, gort::envi(1.01, 0.99));
 //
 // for (INT i = -1; i < 1; i++)
 //   for (INT j = -1; j < 1; j++)
 // for (INT i = -2; i < 3; i++)
 //   for (INT j = -2; j < 3; j++)
 //     rt.Scene
 //       << new gort::point(gort::vec3(j * 3, 7, i * 3), gort::vec3(1, 1, 1), 10, 20, 1, 0.3, 0.1);
 //
 // mtl = gort::surface(gort::vec3(0.10588,0.058824,0.113725), gort::vec3(0.427451,0.470588,0.541176), gort::vec3(0.3333,0.3333,0.521569), 9.84615, 0.40, 0.1);
 // rt.Scene << new gort::plane(gort::vec3(0, 1, 0), 0, mtl);

    //MEGACAL SCENE
    /*
    << new gort::sphere(gort::vec3(0), 1, Mtl, gort::envi(1, 0))
    << new gort::sphere(gort::vec3(-0.2, 0, -2), 1, Mtl1, gort::envi(1, 0))
    << new gort::plane(gort::vec3(0, 1, 0), gort::vec3(0, -1, 0), Mtl)
    << new gort::point(gort::vec3(1, 7, 2), gort::vec3(0.5, 0, 1), 1, 20, 0, 0.1, 0);
    */

    //<< new gort::sphere(gort::vec3(2, 0, 0), 1, Mtl)
    //<< new gort::point(gort::vec3().Rnd0() * 4, gort::vec3().Rnd0(), 10, 20, 0.2, 0.2, 0.2)
    //<< new gort::point(gort::vec3().Rnd0() * 2, gort::vec3().Rnd0(), 10, 20, 0.2, 0.2, 0.2)
    //<< new gort::point(gort::vec3().Rnd0() * 6, gort::vec3().Rnd0(), 10, 20, 0.2, 0.2, 0.2)
    //<< new gort::point(gort::vec3().Rnd0(), gort::vec3(1, 1, 1), 10, 20, 0.2, 0.2, 0.2)
 
    //<< new gort::box(gort::vec3(-2, -1, -2), gort::vec3(5, 3.8, 0.30));
    //<< new gort::triangle(gort::vec3(1, 0, 0), gort::vec3(0, 1, 0), gort::vec3(0, 0, 1));

    //<< new gort::sphere(gort::vec3(0, 4, 4), 1, Mtl1)
    //<< new gort::sphere(gort::vec3(3, 4, 4), 1, Mtl)
    //<< new gort::point(gort::vec3(4, 10, 4), gort::vec3(1, 0, 0), 1, 30, 0.2, 0.2, 0.2)
    //<< new gort::point(gort::vec3(1, 20, 1), gort::vec3(0, 1, 0), 1, 20, 0.2, 0.2, 0.2);

    //<< new gort::plane(gort::vec3(0, 1, 0), 3, gort::surface(gort::vec3(0.05375, 0.05, 0.06625), gort::vec3(0.18275, 0.17, 0.22525), gort::vec3(0.332741, 0.328634, 0.346435), 38.4, 0.1, 0))
    //<< new gort::sphere(gort::vec3(0, 5, 4), 1, gort::surface(gort::vec3(0.25, 0.148, 0.06475), gort::vec3(0.4, 0.2368, 0.1036), gort::vec3(0.774597, 0.458561, 0.200621), 76.8, 0.4, 0))
    //<< new gort::sphere(gort::vec3(3, 4, 4), 1, gort::surface(gort::vec3(0.1986, 0, 0), gort::vec3(0.5922, 0.0166, 0), gort::vec3(0.5974, 0.2084, 0.2084), 100.22, 0.2, 0.5))
    //<< new gort::sphere(gort::vec3(-3, 4, 4), 1, gort::surface(gort::vec3(0.3, 0.3, 0.3), gort::vec3(0.2, 0.2, 0.2), gort::vec3(0.94597, 0.94597, 0.94597), 76.8, 0.5, 0))
    //<< new gort::sphere(gort::vec3(-3, 6, 4), 1, gort::surface(gort::vec3(0.25, 0.20725, 0.20725), gort::vec3(0.5, 0.429, 0.429), gort::vec3(0.156648, 0.156648, 0.156648), 100, 0.3, 0))
    //<< new gort::sphere(gort::vec3(6, 6, 15), 3 ,gort::surface(gort::vec3(0.10588,0.058824,0.113725), gort::vec3(0.427451,0.470588,0.541176), gort::vec3(0.3333,0.3333,0.521569), 10, 1, 0))
    //<< new gort::sphere(gort::vec3(-2, 4, 3), 0.5, gort::surface(gort::vec3(0.2295, 0.08825, 0.0275), gort::vec3(0.5508, 0.2118, 0.066), gort::vec3(0.580594, 0.223257, 0.0695701), 51.2, 0.3, 0))
    
    //<< new gort::point(gort::vec3(12, 8, 1), gort::vec3(0.13, 0.57, 0.7), 1, 30, 0, 0.1, 0)
    //<< new gort::point(gort::vec3(2, 20, 4), gort::vec3(0, 1, 0), 1, 30, 0, 0.1, 0)
    //<< new gort::point(gort::vec3(4, 10, 4), gort::vec3(0.635, 1, 0), 1, 30, 0, 0.1, 0)

  /*
  int size = 2;
  for (int j = -size; j < size; j++)
    for (int i = -size; i < size; i++)
      rt.Scene << new gort::sphere(gort::vec3(j + i, i * j + size, i), fabs(i * j + j) / size, gort::surface(gort::vec3(0.25, 0.148, 0.06475), gort::vec3(0.4, 0.2368, 0.1036), gort::vec3(0.774597, 0.458561, 0.200621), 76.8, 0.4, 1));
  */
  rt.Run();
  return 30;
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */