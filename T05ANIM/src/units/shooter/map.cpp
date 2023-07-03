/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : map.cpp
 * PURPOSE     : Animation project.
 *               Units system.
 *               Shooter game.
 *               Shooter game map unit module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 31.07.2021.
 * NOTE        : Module namespace 'gogl::units::shooter'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../../anim/anim.h"
#include "../../def.h"

/* Project namespace */
namespace gogl
{
  /* Units sample dump namespace */
  namespace units
  {
    /* Shooter game namespace */
    namespace shooter
    {
      /* unit */
      class shooter_map_unit : public gogl::unit
      {
      public:
        prims *Prs;

        /* Default class constructor */
        shooter_map_unit( gogl::anim *Ani )
        {
          Prs = Ani->render::prims_manager::CreatePrims("bin/models/city.g3dm");
          Prs->SetTrans(matr::Scale(vec3(13)));
        } /* End of 'shooter_weapon_unit' function */

        /* Class destructor */
        ~shooter_map_unit( VOID )
        {
        } /* End of '~shooter_weapon_unit' function */

        /* Unit response function.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        VOID Response( gogl::anim *Ani ) override
        {
        } /* End of 'Response' function */

        /* Unit render function.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        VOID Render( gogl::anim *Ani ) override
        {
          Ani->render::PrimsDraw(Prs, matr::Identity());
        } /* End of 'Render' function */
      }; /* end of 'shooter_map_unit' class */
    } /* end of 'shooter' namespace */
  } /* end of 'units' namespace */
} /* end of 'gogl' namespace */

static gogl::anim::unit_register<gogl::units::shooter::shooter_map_unit> _("Map");

/* END OF 'map.cpp' FILE */