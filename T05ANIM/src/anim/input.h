/* FILE NAME : input.h
 * PROGRAMMER: DG5
 * DATE      : 22.07.2021
 * PURPOSE   : Input devices handle module.
 */

#ifndef __input_h_
#define __input_h_

#include <cstring>

#include "../win/win.h"
#include "../mth/mth.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm") /* winmm.lib */

#define GOGL_INPUT_GET_JOYSTIC_AXIS(A) \
   (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min) - 1)

/* Space gogl namespace */
namespace gogl
{
  /* Keyboard class */
  class keyboard
  {
  public:
    BYTE Keys[256];       // state of keys on the current frame
    BYTE KeysClick[256];  // signs of a single click of the keyboard
    BYTE KeysOld[256];    // state of keys on the current frame

    keyboard( VOID )
    {
      memset(Keys, 0, 256);
      memset(KeysClick, 0, 256);
      memset(KeysOld, 0, 256);
    }

    /* Animation input keyboard response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      INT i;

      GetKeyboardState(Keys);
      for (i = 0; i < 256; i++)
      {
        Keys[i] >>= 7;
        KeysClick[i] = Keys[i] && !KeysOld[i];
      }
      memcpy(KeysOld, Keys, 256);
    } /* End of 'Response' function */
  };

  /* Mouse class */
  class mouse
  {
  private:
    INT &Wheel;
    HWND hWnd;  // window handle
  public:
    INT
      MouseX, MouseY, MouseZ,    // mouse coordinates
      MouseDX, MouseDY, MouseDZ; // delta mouse coordinates

    mouse( HWND &hWndRef, INT &WheelRef ) : Wheel(WheelRef), hWnd(hWndRef)
    {
      MouseX = MouseY = MouseZ = MouseDX = MouseDY = MouseDZ = 0;
    }

    /* Animation input mouse response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      POINT pt;

      GetCursorPos(&pt);
      ScreenToClient(hWnd, &pt);

      /* transform coordinates on the screen */
      MouseDX = pt.x - MouseX;
      MouseDY = pt.y - MouseY;
      MouseDZ = Wheel;
      /* absolute val */
      MouseX = pt.x;
      MouseY = pt.y;
      MouseZ += Wheel;

      Wheel = 0;
    } /* End of 'Response' function */

  };

  /* Joystick class */
  class joystick
  {
  public:
    BYTE
      JBut[32], JButOld[32], JButClick[32]; /* joystick button states */
    INT JPov;                               /* joystick point-of-view control [-1, 0..7] */
    DBL
      JoyX, JoyY, JoyZ, JoyR;               /* joystick axes */


    joystick( VOID )
    {
      JoyX = JoyY = JoyZ = JoyR = 0;
      JPov = 0;

      memset(JBut, 0, 32);
      memset(JButClick, 0, 32);
      memset(JButOld, 0, 32);
    }

    /* Animation joystick response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      INT i;

      if (joyGetNumDevs() > 0)
      {
        JOYCAPS jc;

        /* get joysick info */
        if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
        {
          JOYINFOEX ji;

          ji.dwSize = sizeof(JOYINFOEX);
          ji.dwFlags = JOY_RETURNALL;
          if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
          {
            /* buttons */
            for (i = 0; i < 32; i++)
            {
              JBut[i] = (ji.dwButtons >> i) & 1;
              JButClick[i] = JBut[i] && !JButOld[i];
              JButOld[i] = JBut[i];
            }
            /* axes */
            JoyX = GOGL_INPUT_GET_JOYSTIC_AXIS(X);
            JoyY = GOGL_INPUT_GET_JOYSTIC_AXIS(Y);
            JoyZ = GOGL_INPUT_GET_JOYSTIC_AXIS(Z);
            JoyR = GOGL_INPUT_GET_JOYSTIC_AXIS(R);
          }
        }
      }
    } /* End of 'Response' function */
  };

  /* Input class */
  class input : public keyboard, public mouse, public joystick
  {
  public:
    input( HWND hWndRef, INT &WheelRef ) : mouse(hWndRef, WheelRef)
    {
    }

    VOID Response( VOID )
    {
      keyboard::Response();
      mouse::Response();
      joystick::Response();
    }
  };
}

#endif /* __input_h_ */

/* END OF 'input.h' FILE */