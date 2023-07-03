/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : sphere.h
 * PURPOSE     : Ray tracing project.
 *               Making sphere shape handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 02.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __sphere_h_
#define __sphere_h_

#include <cmath>

#include "../../../def.h"
#include "../../rt_def.h"

/* Space gort namespace */
namespace gort
{
  /* Sphere class */
  class sphere : public shape
  {
  private:
    vec3 C; // Sphere centre
    DBL R2; // Sphere square number

    /* Get crossing with sphere function.
     * ARGUMENTS:
     *   - ray from camera:
     *      const ray &R;
     *   - intersection data pointer:
     *      intr *Intr;
     * RETURNS:
     *   (BOOL) Is intersection with sphere.
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
    sphere( VOID )
    {
    } /* End of 'sphere' function */

    /* Sphere class constructor
     * ARGUMENTS:
     *   - sphere centre:
     *     const vec3 &NewC;
     *   - sphere radius:
     *     const DBL &NewR;
     *   - sphere material:
     *     const surface &NewMtl;
     */
    sphere( const vec3 &NewC, const DBL &NewR, const surface &NewMtl ) : C(NewC), R2(NewR * NewR)
    {
      Mtl = NewMtl;
    } /* End of 'sphere' function */

    /* Sphere class constructor
     * ARGUMENTS:
     *   - sphere centre:
     *     const vec3 &NewC;
     *   - sphere radius:
     *     const DBL &NewR;
     *   - sphere material:
     *     const surface &NewMtl;
     */
    sphere( const vec3 &NewC, const DBL &NewR, const surface &NewMtl, const envi &NewEnvi ) : C(NewC), R2(NewR * NewR)
    {
      Mtl = NewMtl;
      Media = NewEnvi;
    } /* End of 'sphere' function */

  }; /* End of 'sphere' class */
} /* end of 'gort' namespace */

#endif /* __sphere_h_ */

/* END OF 'sphere.h' FILE */