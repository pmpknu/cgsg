/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rnd_prim.cpp
 * PURPOSE     : Animation project.
 *               Render system.
 *               Implementation of renderer primitives class functions.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 24.07.2021.
 * NOTE        : Module namespace 'gogl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <cstring>
#include <cstdio>

#include "rnd.h"
#include "../anim.h"

/* Draw render primitive function.
 * ARGUMENTS:
 *   - primitive:
 *      prim *Pr;
 *   - matrix:
 *      MATR World;
 * RETURNS: None.
 */
VOID gogl::render::PrimDraw( prim *Pr, matr World )
{
  matr
    w = Pr->Transform * World,
    wvp = w * cam.VP;
  INT gl_prim_type = Pr->Type == prim_type::LINES ? GL_LINES :
                     Pr->Type == prim_type::TRIMESH ? GL_TRIANGLES :
                     Pr->Type == prim_type::TRISTRIP ? GL_TRIANGLE_STRIP :
                     Pr->Type == prim_type::PATH ? GL_PATCHES :
                     GL_POINTS;

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);

  Pr->Mtl->Shd->UniSet("MatrWVP", wvp);
  Pr->Mtl->Shd->UniSet("CamLoc", cam.Loc);
  Pr->Mtl->Apply();
  //glLoadMatrixf(wvp);

  /* making an array of vertices active */
  // Old without instance
  //glBindVertexArray(Pr->VA);
  //if (Pr->Type == prim_type::PATH)
  //{
  //  glPatchParameteri(GL_PATCH_VERTICES, 16);
  //  glDrawArrays(gl_prim_type, 0, Pr->NumOfElements);
  //}
  //else if (Pr->IBuf == 0)
  //  glDrawArrays(gl_prim_type, 0, Pr->NumOfElements);
  //else
  //{
  //  /* making an array of indexes active */
  //  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
  //  /* drawing */
  //  glDrawElements(gl_prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
  //  /* disable index array */
  //  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  //}
  ///* disable vertex array */
  //glBindVertexArray(0);

  if (Pr->InstanceCnt < 2)
    if (Pr->IBuf != 0)
    {
      glBindVertexArray(Pr->VA);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
      glDrawElements(gl_prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }
    else
    {
      glBindVertexArray(Pr->VA);
      glDrawArrays(gl_prim_type, 0, Pr->NumOfElements);
      glBindVertexArray(0);
    }
  else
    if (Pr->IBuf != 0)
    {
      glBindVertexArray(Pr->VA);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
      glDrawElementsInstanced(gl_prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL,
        Pr->InstanceCnt);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }
    else
    {
      glBindVertexArray(Pr->VA);
      glDrawArraysInstanced(gl_prim_type, 0, Pr->NumOfElements, Pr->InstanceCnt);
      glBindVertexArray(0);
    }
} /* End of 'PrimDraw' function */

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       dg5PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID gogl::render::PrimsDraw( prims *Prs, matr World )
{
  anim *Ani = anim::GetPtr();
  matr W = Prs->Transform * World;
  INT NumOfInst = Prs->InstanceCnt;

  Prs->Prims.Walk([&]( prim *Pr ){ Pr->InstanceCnt = NumOfInst, Ani->render::PrimDraw(Pr, W); });
} /* End of 'PrimsDraw' function */

/* !!! DO NOT USE!!! Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 *   - model material:
 *       material *Mtl;
 * RETURNS:
 *   (prim *) loaded model.
 */
gogl::prim * gogl::render::LoadOBJ( CHAR *FileName, material *Mtl )
{
  INT
    noofv = 0,
    noofi = 0;
  FILE *F;
  CHAR Buf[1000];

  /* Open file */
  fopen_s(&F, FileName, "r");
  if (F == NULL)
    return FALSE;

  /* Count vertex and index quantities */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      noofv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      noofi++;
  }

  std::vector<INT> Ind(3 * noofi);
  std::vector<vertex::std> V(noofv);

  /* Read vertices and facets data */
  rewind(F);
  noofv = noofi = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      FLT x, y, z;

      sscanf_s(Buf + 2, "%f%f%f", &x, &y, &z);

      V[noofv++].P = vec3(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n1, n2, n3;

      /* Read one of possible facet references */
      sscanf_s(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf_s(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
        sscanf_s(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
        sscanf_s(Buf + 2, "%d %d %d", &n1, &n2, &n3);
      n1--;
      n2--;
      n3--;
      Ind[noofi++] = n1;
      Ind[noofi++] = n2;
      Ind[noofi++] = n3;
    }
  }

  gogl::topology::trimesh<vertex::std> T(V, Ind);
  /* making an auto normalize */
  T.EvalNormals();

  gogl::topology::base<vertex::std> *B = reinterpret_cast<gogl::topology::base<vertex::std> *>(&T);
  /* create primitive */
  //Pr->Create(*B);

  prim *Pr = CreatePrim(*B, Mtl);
  Pr->EvalBB(V, Ind, Ind.size());

  fclose(F);
  return Pr;
} /* End of 'LoadOBJ' function */

/* END OF 'prim.cpp' FLE */