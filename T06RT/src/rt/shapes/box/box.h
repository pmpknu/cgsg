/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : box.h
 * PURPOSE     : Ray tracing project.
 *               Making box shape handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 02.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __box_h_
#define __box_h_

#include "../../../def.h"
#include "../../rt_def.h"

/* Space gort namespace */
namespace gort
{
  /* box class */
  class box : public shape
  {
  private:
    vec3 MinBB; // box min vector
    vec3 MaxBB; // box max vector

    /* Get crossing with box function.
     * ARGUMENTS:
     *   - ray from camera:
     *      const ray &R;
     *   - intersection data pointer:
     *      intr *Intr;
     * RETURNS:
     *   (BOOL) Is intersection with box.
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
    box( VOID )
    {
    } /* End of 'box' function */

    /* box class constructor
     * ARGUMENTS:
     *   - min box vec:
     *     const vec3 &NewMinBB;
     *   - max box vec:
     *     const vec3 &NewMaxBB;
     */
    box( const vec3 &NewMinBB, const vec3 &NewMaxBB ) : MinBB(NewMinBB), MaxBB(NewMaxBB)
    {
    } /* End of 'box' function */
  }; /* End of 'box' class */
} /* end of 'gort' namespace */

#endif /* __box_h_ */

/* END OF 'box.h' FILE */