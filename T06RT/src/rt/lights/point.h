/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Suppopoint Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : point.h
 * PURPOSE     : Ray tracing project.
 *               Point light handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 03.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No papoint of this file may be changed without agreement of
 * Computer Graphics Suppopoint Group of 30 Phys-Math Lyceum
 */

#ifndef __point_h_
#define __point_h_

#include "../rt_def.h"

/* Space gort namespace */
namespace gort
{
  /* Point light class */
  class point : public light
  {
  private:
    vec3 Pos; // Point light position
    vec3 Color; // Light color
    DBL R1, R2; // Decay radius

    /* Shadow light function.
     * ARGUMENTS:
     *   - intersection point:
     *       const vec3 &P;
     *   - light information:
     *       light_info *L;
     * RETURNS: attenuation.
     */
    DBL Shadow( const vec3 &P, light_info *L ) override
    {
      L->Color = Color;
      L->Dist = !(Pos - P);
      L->L = (Pos - P) / L->Dist;

      return min(1 / (Cc + Cl * L->Dist + Cq * L->Dist * L->Dist), 1);
    } /* End of 'Shadow' function */

  public:

    /* Default constructor */
    point( VOID )
    {
    } /* End of 'point' function */

    /* Light class constructor
     * ARGUMENTS:
     *   - light position:
     *     const vec3 &NewPos;
     *   - light color:
     *     const vec3 &NewColor;
     *   - light decay radius:
     *     const DBL &NewR1, &NewR2;
     *   - ???:
     *     const DBL &Cc, &Cl, &Cq;
     */
    point( const vec3 &NewPos, const vec3 &NewColor, const DBL &NewR1, const DBL &NewR2, const DBL &NewCc, const DBL &NewCl, const DBL &NewCq )
      : Pos(NewPos), Color(NewColor), R1(NewR1), R2(NewR2)
    {
      Cc = NewCc;
      Cl = NewCl;
      Cq = NewCq;
    } /* End of 'point' function */

  }; /* End of 'point' class */
} /* end of 'gort' namespace */

#endif /* __point_h_ */

/* END OF 'point.h' FILE */