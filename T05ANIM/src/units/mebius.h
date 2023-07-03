/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mebius.h
 * PURPOSE     : Animation project.
 *               Units system.
 *               Mebius strip create and draw module module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 29.07.2021.
 * NOTE        : Module namespace 'gogl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mebius_h_
#define __mebius_h_

#include "../anim/anim.h"
#include "../def.h"

class mebius : public gogl::unit
{
public:
  gogl::prim *Pr;

  static vec3 Lenta( const FLT &u, const FLT &v )
  {
    FLT cos2 = cos(u / 2);

    return vec3((1 + v / 2 * cos2) * cos(u),
                (1 + v / 2 * cos2) * sin(u),
                 v / 2 * sin(u / 2));
  }

  mebius( gogl::anim *Ani )
  {
    std::vector<gogl::vertex::std> Ver = std::vector<gogl::vertex::std>(4000);
    INT i = 0;
    for (FLT u = 0; u < 2 * mth::PI; u += 0.01 * mth::PI)
      for (FLT v = -1; v <= 1; v += 0.1, i++)
        Ver[i].P = Lenta(u, v);

    gogl::topology::grid<gogl::vertex::std> V(40, 100, Ver);
    //gogl::topology::cube<gogl::vertex::std> ;
    gogl::topology::base<gogl::vertex::std> *B = reinterpret_cast<gogl::topology::base<gogl::vertex::std> *>(&V);

    Pr = Ani->prim_manager::CreatePrim(*B, Ani->material_manager::CreateMtl());
  }

  ~mebius( VOID )
  {
  }

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
    Ani->render::PrimDraw(&(*Pr), mth::matr<>::RotateX(0 * Ani->Time));
  } /* End of 'Render' function */
};

#endif /* __mebius_h_ */

/* END OF 'mebius.h' FILE */