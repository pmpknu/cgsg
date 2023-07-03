/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : triangle.cpp
 * PURPOSE     : Ray tracing project.
 *               Triangle shape class functions implementation module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 02.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "triangle.h"

/* Get crossing with triangle function.
 * ARGUMENTS:
 *   - ray from camera:
 *      const ray &R;
 *   - intersection data pointer:
 *      intr *Intr;
 * RETURNS:
 *   (BOOL) Is intersection with triangle.
 */
BOOL gort::triangle::Intersect( const ray &R, intr *Intr )
{
  // Check for intersect existing
  DBL nd = N & R.Dir;
  if (fabs(nd) < Threshold)
    return FALSE;

  DBL t = -((R.Org & N) + D) / nd;

  if (t < Threshold)
    return FALSE;

  vec3 P = R(t);

  DBL
    u = (P & U1) - u0,
    v = (P & V1) - v0;

  if (u >= 0 && u <= 1 && v >= 0 && v <=1 && u + v <= 1)
  {
    Intr->T = t;
    Intr->P = R(t);
    Intr->Sh = this;
    return TRUE;
  }
  return FALSE;
} /* End of 'Intersection' function */

/* Evaluate shape normal function.
 * ARGUMENTS:
 *   - intersection data pointer:
 *      intr *Intr;
 * RETURNS: None.
 */
VOID gort::triangle::GetNormal( intr *Intr )
{
  Intr->N = N;
} /* End of 'GetNormal' funciton */



/* END OF 'triangle.cpp' FILE */