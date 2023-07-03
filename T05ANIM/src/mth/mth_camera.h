/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_camera.h
 * PURPOSE     : Animation project.
 *               Mathematics library.
 *               Space camera handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 23.07.2021.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_camera_h_
#define __mth_camera_h_

#include "mthdef.h"

/* Math library namespace */
namespace mth
{
  /* Space camera handle class */
  template<class type>
    class camera
    {
    private:
      /* Update camera project parameters function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID UpdateProj( VOID )
      {
        type ratio_x = Size / 2, ratio_y = Size / 2;
 
        if (FrameW >= FrameH)
          ratio_x *= (type)FrameW / FrameH;
        else
          ratio_y *= (type)FrameH / FrameW;
        Proj = matr<type>::Frustum(-ratio_x, ratio_x, -ratio_y, ratio_y, ProjDist, FarClip);
      } /* End of 'UpdateProj' function */
 
      /* Update camera view parameters function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID UpdateView( VOID )
      {
        View = matr<type>::View(Loc, At, Up);

        Dir[0] = -View[2];
        Dir[1] = -View[6];
        Dir[2] = -View[10];
        Right[0] = -View[0];
        Right[1] = -View[4];
        Right[2] = -View[8];
      } /* End of 'UpdateView' function */
 
    public:
      vec3<type>
        Loc,            // camera location
        Dir, Up, Right, // basis camera directions
        At;             // camera pivot point
      type
        ProjDist,       // near project plane distance
        FarClip,        // far project plane distance
        Size;           // inner project plane rectangle size
      INT
        FrameW, FrameH; // Camera frame size
      matr<type>
        View,           // view matrix
        Proj,           // projection matrix
        VP;             // View and Proj madtrix production
      ray<type> Ray;    // Ray from camera to screen

      /* Default constructor */
      camera( VOID ) :
        Loc(0, 0, 5), Dir(0, 0, -1), Up(0, 1, 0), Right(1, 0, 0), At(0, 0, 0),
        ProjDist(0.1), FarClip(1000), Size(0.1),
        FrameW(30), FrameH(30)
      {
        UpdateProj();
        UpdateView();
        VP = View * Proj;
      } /* End of 'matr' function */
 
      /* Set project camera parameters function.
       * ARGUMENTS:
       *   - new near project plane size:
       *       type NewSize;
       *   - new project distance:
       *       type NewProjDist;
       *   - new far clip plane distance:
       *       type FarC;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & SetProj( type NewSize, type NewProjDist, type NewFarClip )
      {
        // Store new projection parameters
        ProjDist = NewProjDist;
        FarClip = NewFarClip;
        Size = NewSize;
 
        UpdateProj();
        VP = View * Proj;
        return *this;
      } /* End of 'SetProj' function */
 
      /* Set camera project pixel size function.
       * ARGUMENTS:
       *   - new frame size in pixels:
       *       type NewFrameW, NewFrameH;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & Resize( type NewFrameW, type NewFrameH )
      {
        FrameW = NewFrameW;
        FrameH = NewFrameH;
 
        UpdateProj();
        VP = View * Proj;
        return *this;
      } /* End of 'Resize' function */
 
      /* Set camera location and orientation function.
       * ARGUMENTS:
       *   - new camera location:
       *       const vec3<type> &L;
       *   - new camera pivot point:
       *       const vec3<type> &A;
       *   - new camera approx up direction:
       *       const vec3<type> &U;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & SetLocAtUp( const vec3<type> &L, const vec3<type> &A, const vec3<type> &U = vec3<type>(0, 1, 0) )
      {
        Loc = L;
        At = A;
        Up = U;
 
        UpdateView();
        VP = View * Proj;
        return *this;
      } /* End of 'SetLocAtUp' function */
 
      /* Camera rotate function.
       * ARGUMENTS:
       *   - rotate axis:
       *       const vec3<type> &Axis;
       *   - rotation angle (in degree):
       *       type AngleInDegree;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & Rotate( const vec3<type> &Axis, type AngleInDegree )
      {
        //matr<type> m = matr<type>::Translate(-At) * matr<type>::Rotate(Axis, AngleInDegree) * matr<type>::Translate(At);
        //Loc = m.PointTransform(Loc);
        matr<type> m = matr<type>::Translate(-Loc) * matr<type>::Rotate(Axis, AngleInDegree) * matr<type>::Translate(Loc);
        At = m.PointTransform(At);
        Up = m.VectorTransform(Up);
        SetLocAtUp(Loc, At, Up);
        return *this;
      } /* End of 'Rotate' function */
 
      /* Camera movement function.
       * ARGUMENTS:
       *   - movement directions:
       *       const vec3<type> &Direction;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & Move( const vec3<type> &Direction )
      {
        Loc += Direction;
        At += Direction;
        SetLocAtUp(Loc, At, Up);
        return *this;
      } /* End of 'Move' function */

      /* Build ray from frame pixel to world function.
       * ARGUMENTS:
       *   - frame pixel coordinates:
       *       FLT Sx, Sy;
       * RETURNS: None.
       */
      VOID Frame2Ray( const type &Sx, const type &Sy)
      {
        ray r;
        DBL Wp, Hp;

        /* Calculate projection plane parametrs */
        Wp = Hp = Size;

        /* Correct aspect ratio */
        if (FrameW > FrameH)
          Wp *= static_cast<DBL>(FrameW) / FrameH;
        else
          Hp *= static_cast<DBL>(FrameH) / FrameW;

        /* Obtain ray direction */
        vec3 A = Dir * ProjDist;
        vec3 B = Right * (Sx + FrameW / 2.0) * Wp / FrameW;
        vec3 C = Up * (-Sy + FrameH / 2.0) * Hp / FrameH;
        vec3 X = A + B + C;

        Ray.Org = Loc + X;
        Ray.Dir = X.Normalizing();
      } /* End of 'Frame2Ray' function */

    }; /* End of 'camera' class */
} /* end of 'mth' namespace */

#endif /* __mth_camera_h_ */

/* END OF 'mth_camera.h' FILE */