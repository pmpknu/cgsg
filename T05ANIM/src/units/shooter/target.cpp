/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : target.h
 * PURPOSE     : Animation project.
 *               Units system.
 *               Shooter game.
 *               Target responsing and firing ray to target unit module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 30.07.2021.
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
      /* Target creating and responsing unit */
      class shooter_target_unit : public gogl::unit
      {
      private:
        /* target sphere struct */
        struct target_sphere
        {
          vec3 C; // Sphere centre
          FLT R;  // Sphere radius
        }; /* end of 'traget_sphere' struct */

        /* target class */
        class target
        {
        public:
          target_sphere S; // sphere model of primitive
          prims *Prs;        // target primitive

          /* Class default constructor */
          target( VOID )
          {
          } /* end of 'target' constructor */

          /* Class constructor
           * ARGUMENTS:
           *   - target primitive:
           *       prim *NewPr;
           */
          target( prims *NewPr ) : Prs(NewPr)
          {
            S.C = (Prs->MaxBB - Prs->MinBB) / 2 + Prs->MinBB;

            /*FLT ttmp, tmp = (Prs->MaxBB[0] - Prs->MinBB[0]);
            if (tmp < (ttmp = Prs->MaxBB[1] - Prs->MinBB[1]))
              tmp = ttmp;
            else if (tmp < (ttmp = Prs->MaxBB[2] - Prs->MinBB[2]))
              tmp = ttmp;

            S.R = tmp / 2;*/
            S.R = ((Prs->MaxBB[0] - Prs->MinBB[0]) + (Prs->MaxBB[1] - Prs->MinBB[1]) + (Prs->MaxBB[2] - Prs->MinBB[2])) / 3 / 1.5;
          }
        }; /* end of 'target' class */

        /* Get crossing with target (sphere) function.
         * ARGUMENTS:
         *   - ray from camera:
         *      const ray &R;
         *   - sphere target:
         *      const target_sphere &S;
         * RETURNS:
         *   (BOOL) Is intersection with sphere.
         */
        BOOL IsSphereIntersection( const ray &Ray, const target_sphere &S )
        {
          vec3 a = S.C - Ray.Org;
          FLT OC2 = a & a;
          FLT OK = a & Ray.Dir;
          FLT R2 = S.R * S.R;
          FLT h2 = R2 - (OC2 - OK * OK);

          // the ray starts inside the sphere
          if (OC2 < R2)
            return true;

          // the ray leaves the center of the sphere behind
          if (OK < 0)
            return false;

          // the ray passes by the sphere
          if (h2 < 0)
            return false;

          // the ray starts from outside the sphere
          return true;
        } /* End of 'IsSphereIntersection' function */

      public:
        target trg;

        /* Default class constructor */
        shooter_target_unit( gogl::anim *Ani )
        {
          prims *Prs = Ani->render::prims_manager::CreatePrims("bin/models/target.g3dm", true);
          Prs->EvalBB();
          Prs->SetTrans(matr::Translate(vec3(0, 5, 0)));
          trg = target(Prs);
        } /* End of 'shooter_weapon_unit' function */

        /* Class destructor */
        ~shooter_target_unit( VOID )
        {
        } /* End of '~shooter_weapon_unit' function */

        /* Unit response function.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        VOID Response( gogl::anim *Ani ) override
        {
          if (Ani->Keys[VK_LBUTTON])
          {
            if (IsSphereIntersection(ray(Ani->cam.Loc, Ani->cam.Dir), trg.S))
            {
              SetWindowText(Ani->GethWnd(), "megacal");

              trg.S.C.Rnd1();
              trg.S.C[0] *= 100;
              trg.S.C[2] *= 100;
              trg.S.C[1] = 5;
              trg.Prs->SetTrans(matr::Translate(trg.S.C));
            }
            else
              SetWindowText(Ani->GethWnd(), "not megacal");//, trg.Prs->SetTrans(matr::Scale(vec3(1)));
          }
        } /* End of 'Response' function */

        /* Unit render function.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        VOID Render( gogl::anim *Ani ) override
        {
          Ani->render::PrimsDraw(trg.Prs, matr::Identity());
        } /* End of 'Render' function */
      }; /* end of 'shooter_target_unit' class */
    } /* end of 'shooter' namespace */
  } /* end of 'units' namespace */
} /* end of 'gogl' namespace */

static gogl::anim::unit_register<gogl::units::shooter::shooter_target_unit> _("Target");

/* END OF 'target.h' FILE */