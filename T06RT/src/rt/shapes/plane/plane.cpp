/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : plane.cpp
 * PURPOSE     : Ray tracing project.
 *               plane shape class functions implementation module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 02.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "plane.h"

/* Get crossing with plane function.
 * ARGUMENTS:
 *   - ray from camera:
 *      const ray &R;
 *   - intersection data pointer:
 *      intr *Intr;
 * RETURNS:
 *   (BOOL) Is intersection with plane.
 */
BOOL gort::plane::Intersect( const ray &R, intr *Intr )
{
  // Check for intersect existing
  DBL nd = N & R.Dir;
  if (fabs(nd) < Threshold)
    return FALSE;

  DBL t = -((R.Org & N) + D) / nd;

  if (t < Threshold)
    return FALSE;

  Intr->T = t;
  Intr->Sh = this;
  return TRUE;
} /* End of 'Intersection' function */

/* Evaluate shape normal function.
 * ARGUMENTS:
 *   - intersection data pointer:
 *      intr *Intr;
 * RETURNS: None.
 */
VOID gort::plane::GetNormal( intr *Intr )
{
  Intr->N = N;
} /* End of 'GetNormal' funciton */



/* END OF 'plane.cpp' FILE */