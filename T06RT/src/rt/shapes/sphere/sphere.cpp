/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : sphere.cpp
 * PURPOSE     : Ray tracing project.
 *               Sphere shape class functions implementation module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 02.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "sphere.h"

/* Get crossing with sphere function.
 * ARGUMENTS:
 *   - ray from camera:
 *      const ray &R;
 *   - intersection data pointer:
 *      intr *Intr;
 * RETURNS:
 *   (BOOL) Is intersection with sphere.
 */
BOOL gort::sphere::Intersect( const ray &R, intr *Intr )
{
  vec3 a = C - R.Org;
  DBL OC2 = a & a;
  DBL OK = a & R.Dir;
  DBL h2 = R2 - (OC2 - OK * OK);

  // the ray starts inside the sphere
  if (OC2 < R2)
  {
    Intr->T = OK + sqrt(h2);
    Intr->Sh = this;
    Intr->N = (R(Intr->T) - C).Normalizing();
    return true;
  }

  // the ray leaves the center of the sphere behind
  if (OK < 0)
    return false;

  // the ray passes by the sphere
  if (h2 < 0)
    return false;

  // the ray starts from outside the sphere
  Intr->T = OK - sqrt(h2);
  Intr->Sh = this;
  Intr->P = R(Intr->T);
  return true;
} /* End of 'Intersection' function */

/* Evaluate shape normal function.
 * ARGUMENTS:
 *   - intersection data pointer:
 *      intr *Intr;
 * RETURNS: None.
 */
VOID gort::sphere::GetNormal( intr *Intr )
{
  Intr->N = (Intr->P - C).Normalizing();
} /* End of 'GetNormal' funciton */


/* END OF 'sphere.cpp' FILE */