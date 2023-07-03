/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : box.cpp
 * PURPOSE     : Ray tracing project.
 *               Box shape class functions implementation module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 02.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "box.h"

/* Get crossing with box function.
 * ARGUMENTS:
 *   - ray from camera:
 *      const ray &R;
 *   - intersection data pointer:
 *      intr *Intr;
 * RETURNS:
 *   (BOOL) Is intersection with box.
 */
BOOL gort::box::Intersect( const ray &R, intr *Intr )
{
  INT Ind = 1, ind = 0;
  DBL tnear = 0, tfar = HUGE_VAL;

  // X axis
  if (fabs(R.Dir[0]) < Threshold)
    if (R.Org[0] < MinBB[0] || R.Org[0] > MaxBB[0])
      return FALSE;

  DBL
    t0 = (MinBB[0] - R.Org[0]) / R.Dir[0],
    t1 = (MaxBB[0] - R.Org[0]) / R.Dir[0];

  if (t0 > t1)
    mth::Swap(t0, t1);
  if (t0 > tnear)
    tnear = t0, Ind = ind;
  if (t1 < tfar)
    tfar = t1;

  // the ray passes by cube
  if (tnear > tfar)
    return FALSE;

  // parallelepiped behind ray
  if (tfar < 0)
    return FALSE;

  // Y axis
  if (fabs(R.Dir[1]) < Threshold)
    if (R.Org[1] < MinBB[1] || R.Org[1] > MaxBB[1])
      return FALSE;

  t0 = (MinBB[1] - R.Org[1]) / R.Dir[1];
  t1 = (MaxBB[1] - R.Org[1]) / R.Dir[1];
  ind = 3;
  if (t0 > t1)
    mth::Swap(t0, t1), ind = 2;
  if (t0 > tnear)
    tnear = t0, Ind = ind;
  if (t1 < tfar)
    tfar = t1;

  // the ray passes by cube
  if (tnear > tfar)
    return FALSE;

  // parallelepiped behind ray
  if (tfar < 0)
    return FALSE;
  

  // Z axis
  if (fabs(R.Dir[2]) < Threshold)
    if (R.Org[2] < MinBB[2] || R.Org[2] > MaxBB[2])
      return FALSE;

  t0 = (MinBB[2] - R.Org[2]) / R.Dir[2];
  t1 = (MaxBB[2] - R.Org[2]) / R.Dir[2];
  ind = 5;
  if (t0 > t1)
    mth::Swap(t0, t1), ind = 4;
  if (t0 > tnear)
    tnear = t0, Ind = ind;
  if (t1 < tfar)
    tfar = t1;

  // the ray passes by cube
  if (tnear > tfar)
    return FALSE;

  // parallelepiped behind ray
  if (tfar < 0)
    return FALSE;

  Intr->T = tnear;
  Intr->P = R(tnear);
  Intr->Sh = this;
  Intr->I[0] = Ind;
  return TRUE;
} /* End of 'Intersection' function */

/* Evaluate shape normal function.
 * ARGUMENTS:
 *   - intersection data pointer:
 *      intr *Intr;
 * RETURNS: None.
 */
VOID gort::box::GetNormal( intr *Intr )
{
  const static vec3 Normals[6] =
  {
    vec3(1, 0, 0), vec3(-1,  0,  0),
    vec3(0, 1, 0), vec3( 0, -1,  0),
    vec3(0, 0, 1), vec3( 0,  0, -1),
  };

  Intr->N = Normals[Intr->I[0]];
} /* End of 'GetNormal' funciton */


/* END OF 'box.cpp' FILE */