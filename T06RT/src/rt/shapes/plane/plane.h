/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : plane.h
 * PURPOSE     : Ray tracing project.
 *               Making plane shape handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 02.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __plane_h_
#define __plane_h_

#include "../../../def.h"
#include "../../rt_def.h"

/* Space gort namespace */
namespace gort
{
  /* Plane class */
  class plane : public shape
  {
  private:
    vec3 N; // Plane normal
    vec3 P; // Plane point
    DBL D;  // Plane distance (N & P)

    /* Get crossing with plane function.
     * ARGUMENTS:
     *   - ray from camera:
     *      const ray &R;
     *   - intersection data pointer:
     *      intr *Intr;
     * RETURNS:
     *   (BOOL) Is intersection with plane.
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
    plane( VOID )
    {
    } /* End of 'plane' function */

    /* plane class constructor
     * ARGUMENTS:
     *   - plane normal:
     *     const vec3 &NewN;
     *   - plane point:
     *     const vec3 &NewP;
     *   - plane material:
     *     const surface &NewMtl;
     */
    plane( const vec3 &NewN, const vec3 &NewP, const surface &NewMtl ) : N(NewN.Normalizing()), P(NewP), D(-(NewN & NewP))
    {
      Mtl = NewMtl;
    } /* End of 'plane' function */

    /* plane class constructor
     * ARGUMENTS:
     *   - plane normal:
     *     const vec3 &NewN;
     *   - plane distance:
     *     const DBL &NewD;
     *   - plane material:
     *     const surface &NewMtl;
     */
    plane( const vec3 &NewN, const DBL &NewD, const surface &NewMtl ) : N(NewN.Normalizing()), D(NewD)
    {
      Mtl = NewMtl;
    } /* End of 'plane' function */

  }; /* End of 'plane' class */
} /* end of 'gort' namespace */

#endif /* __plane_h_ */

/* END OF 'plane.h' FILE */