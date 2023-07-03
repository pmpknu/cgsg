/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_ray.h
 * PURPOSE     : Animation project.
 *               Mathematics library.
 *               Ray handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 30.07.2021.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_ray_h_
#define __mth_ray_h_

#include "mthdef.h"

/* Math library namespace */
namespace mth
{
  /* Space ray representation class */
  template<class type>
    class ray
    {
    public:
      vec3<type> Org, Dir; /* Ray origin and direction */

      /* Default class constructor */
      ray( VOID )
      {
      } /* End of 'ray' function */


      /* Class constructor
       * ARGUMENTS:
       *   - ray components:
       *       const vec3<type> &NewOrg, const vec3<type> &NewDir;
       */
      ray( const vec3<type> &NewOrg, const vec3<type> &NewDir ) : Org(NewOrg), Dir(NewDir)
      {
      } /* End of 'ray' function */

    }; /* End of 'ray' class */
} /* end of 'mth' namespace */

#endif /* __mth_ray_h_ */

/* END OF 'mth_ray.h' FILE */