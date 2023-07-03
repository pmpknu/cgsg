/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : player.h
 * PURPOSE     : Animation project.
 *               Units system.
 *               Shooter game.
 *               Weapon animation and player control unit module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 30.07.2021.
 * NOTE        : Module namespace 'gogl::units::shooter'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../../anim/anim.h"
#include <string>

/* Project namespace */
namespace gogl
{
  /* Units sample dump namespace */
  namespace units
  {
    /* Shooter game namespace */
    namespace shooter
    {
      /* Weapon animation and player control unit */
      class shooter_player_unit: public gogl::unit
      {
      private:
        /* Flip full screen function.
         * ARGUMENTS: None.
         *   - window handle:
         *       HWND hWnd;
         * RETURNS: None.
         */
        VOID FlipFullScreen( const HWND &hWnd )
        {
          static BOOL IsFullScreen = FALSE; /* store current mode */
          static RECT SaveRC;               /* save old window size */

          if (!IsFullScreen)
          {
            HMONITOR hMon;
            MONITORINFOEX moninfo;
            RECT rc;

            IsFullScreen = TRUE;

            /* Save old window size and position */
            GetWindowRect(hWnd, &SaveRC);

            /* Get closest monitor */
            hMon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

            /* Get monitor information */
            moninfo.cbSize = sizeof(moninfo);
            GetMonitorInfo(hMon, (MONITORINFO *)&moninfo);

            rc = moninfo.rcMonitor;
            AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

            /* Expand window to full screen */
            SetWindowPos(hWnd, HWND_TOP,
              rc.left, rc.top,
              rc.right - rc.left, rc.bottom - rc.top,
              SWP_NOOWNERZORDER);
          }
          else
          {
            IsFullScreen = FALSE;

            /* Restore window size and position */
            SetWindowPos(hWnd, HWND_NOTOPMOST,
              SaveRC.left, SaveRC.top,
              SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
              SWP_NOOWNERZORDER);
          }
        } /* End of 'FlipFullScreen' function */

      public:
        gogl::prims *Prs;
        matr m_cammove;
        matr m_start;
        matr m_end;
        matr m_current;
        bool IsScope;

        /* Default class constructor */
        shooter_player_unit( gogl::anim *Ani )
        {
          //ShowCursor(FALSE);
          Prs = Ani->render::prims_manager::CreatePrims("bin/models/weapon.g3dm");
          m_end = matr::RotateY(90) * matr::RotateZ(-0.3) * matr::Scale(vec3(0.005)) * matr::Translate(vec3(0.27, -0.08, 0));
          m_current = m_start = matr::RotateY(90) * matr::Scale(vec3(0.005)) * matr::Translate(vec3(0.33, -0.15, 0.12)) * matr::RotateZ(3);

          Prs->SetTrans(m_start);
          IsScope = false;

          Ani->cam.Move(vec3(0, 3.3, 0));
        }

        /* Class destructor */
        ~shooter_player_unit( VOID )
        {
        } /* End of '~shooter_weapon_unit' function */
        
        /* Unit response function.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        VOID Response( gogl::anim *Ani ) override
        {
          /* full screen toggle */
          if (Ani->KeysClick[VK_RETURN] && Ani->Keys[VK_MENU])
            FlipFullScreen(Ani->GethWnd());


          if (Ani->Keys['W'] || Ani->Keys['A'] || Ani->Keys['S'] || Ani->Keys['D'])
            Ani->cam.Move((vec3(Ani->cam.Dir[0], 0, Ani->cam.Dir[2]) * ((Ani->Keys['W'] - Ani->Keys['S'])) + 
                           vec3(Ani->cam.Right[0], 0, Ani->cam.Right[2]) * (Ani->Keys['A'] - Ani->Keys['D'])) * 30 * Ani->GlobalDeltaTime);

          //if (Ani->Keys[VK_CONTROL] || Ani->Keys[VK_SPACE])
          //  Ani->cam.Move(vec3(0, 20 * Ani->GlobalDeltaTime, 0) * (Ani->Keys[VK_SPACE] - Ani->Keys[VK_CONTROL]));

          /*if (Ani->Keys[VK_RBUTTON])
          {
            FLT Hp, Wp = Hp = Ani->cam.ProjDist;

            if (Ani->cam.FrameW > Ani->cam.FrameH)
              Wp *= static_cast<FLT>(Ani->cam.FrameW) / Ani->cam.FrameH;
            else
              Hp *= static_cast<FLT>(Ani->cam.FrameH) / Ani->cam.FrameW;

            FLT Dist = !(Ani->cam.At - Ani->cam.Loc);

            FLT sx = -Ani->MouseDX * Wp / Ani->cam.FrameW * Dist / Ani->cam.ProjDist;
            FLT sy = Ani->MouseDY * Hp / Ani->cam.FrameH * Dist / Ani->cam.ProjDist;

            Ani->cam.Move(Ani->cam.Right * sx +
                              Ani->cam.Up * sy);
          }*/
          Ani->cam.Rotate(vec3(0, 1, 0), -Ani->MouseDX * Ani->GlobalDeltaTime * 30); //(Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]))
          Ani->cam.Rotate(Ani->cam.Right, Ani->MouseDY * Ani->GlobalDeltaTime * 30);

          POINT pt1, pt2;

          GetCursorPos(&pt1);
          pt2 = pt1;
          ScreenToClient(Ani->GethWnd(), &pt1);
          SetCursorPos(pt2.x - pt1.x + Ani->cam.FrameW / 2, pt2.y - pt1.y + Ani->cam.FrameH / 2);
          Ani->input::mouse::Response();

          /*if (Ani->Keys[VK_LBUTTON] || Ani->Keys[VK_UP] || Ani->Keys[VK_DOWN])
            Ani->cam.Rotate(Ani->cam.Right, (-Ani->Keys[VK_LBUTTON] * Ani->MouseDY +
                                                   (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])) * Ani->GlobalDeltaTime * 30);*/

          std::string s;
          s = "x: " + std::to_string(Ani->cam.Loc[0]) + ", " + "y: " + std::to_string(Ani->cam.Loc[1]) + ", "+ "z: " + std::to_string(Ani->cam.Loc[2]) + "FPS: " + std::to_string(Ani->FPS);

          SetWindowText(Ani->GethWnd(), s.c_str());

          m_cammove = matr(Ani->cam.Dir,   0,
                           Ani->cam.Up,    0,
                           Ani->cam.Right, 0,
                           Ani->cam.Loc,   1);

          if (Ani->Keys[VK_RBUTTON])
          {
            static FLT LerpTime = 0;
            if (LerpTime < 1)
            {
              LerpTime += Ani->DeltaTime;
              m_current = matr::Lerp(m_current, m_end, LerpTime);
              //m_current = matr::Lerp(m_start, m_end, LerpTime);
              //Ani->cam.SetProj(Ani->cam.Size, Ani->cam.ProjDist + 0.001, Ani->cam.FarClip);

              IsScope = true;
            }
            else
              LerpTime = 0;
          }
          if (!Ani->Keys[VK_RBUTTON] && IsScope)
          {
            static FLT LerpTime = 0;
            if (LerpTime < 1)
            {
              LerpTime += Ani->DeltaTime;
              m_current = matr::Lerp(m_current, m_start, LerpTime);
              //m_current = matr::Lerp(m_end, m_start, LerpTime);
            }
            else
              IsScope = false, LerpTime = 0;
          }
          Prs->SetTrans(m_current);
        } /* End of 'Response' function */
        
        /* Unit render function.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        VOID Render( gogl::anim *Ani ) override
        {
          Ani->render::PrimsDraw(Prs, m_cammove);
        } /* End of 'Render' function */
      }; /* end of 'shooter_player_unit' class */
    } /* end of 'shooter' namespace */
  } /* end of 'units' namespace */
} /* end of 'gogl' namespace */

static gogl::anim::unit_register<gogl::units::shooter::shooter_player_unit> _("Player"); //gogl::units::shooter::shooter_player_unit

/* END OF 'player.cpp' FILE */