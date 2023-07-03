/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : triangle.h
 * PURPOSE     : Ray tracing project.
 *               Making triangle shape handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 02.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __triangle_h_
#define __triangle_h_

#include "../../../def.h"
#include "../../rt_def.h"

/* Space gort namespace */
namespace gort
{
  /* Triangle class */
  class triangle : public shape
  {
  private:
    vec3 P0, P1, P2; // Triangle points
    vec3 N;          // Triangle normal
    DBL D;           // Distance to plane
    vec3 U1, V1;
    DBL u0, v0;

    /* Get crossing with triangle function.
     * ARGUMENTS:
     *   - ray from camera:
     *      const ray &R;
     *   - intersection data pointer:
     *      intr *Intr;
     * RETURNS:
     *   (BOOL) Is intersection with triangle.
     */
    BOOL Intersect( const ray &R, intr *Intr ) override;

    /* Evaluate shape normal function.
     * ARGUMENTS:
     *   - intersection data pointer:
     *      intr *Intr;
     * RETURNS: None.
     */
    VOID GetNormal( intr *Intr ) override;

  public:
    /* Default constructor */
    triangle( VOID )
    {
    } /* End of 'triangle' function */

    /* triangle class constructor
     * ARGUMENTS:
     *   - triangle normal:
     *     const vec3 &NewN;
     *   - triangle point:
     *     const vec3 &NewP;
     */
    triangle( const vec3 &NewP0, const vec3 &NewP1, const vec3 &NewP2 )
      : P0(NewP0), P1(NewP1), P2(NewP2), N((NewP1 - NewP0) % (NewP2 - NewP0))
    {
      vec3
        s1 = P1 - P0,
        s2 = P2 - P0;

      D = N & P0;

      U1 = (s1 * (s2 & s2) - s2 * (s1 & s2)) /
           ((s1 & s1) * (s2 & s2) - (s1 & s2) * (s1 & s2));
      u0 = P0 & U1;

      V1 = (s2 * (s1 & s1) - s1 * (s1 & s2)) /
           ((s1 & s1) * (s2 & s2) - (s1 & s2) * (s1 & s2));
      v0 = P0 & V1;
    } /* End of 'triangle' function */
  }; /* End of 'triangle' class */
} /* end of 'gort' namespace */

#endif /* __triangle_h_ */

/* END OF 'triangle.h' FILE */