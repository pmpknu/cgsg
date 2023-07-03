/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mtl.cpp
 * PURPOSE     : Animation project.
 *               Render system.
 *               Implementation of material class functions.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 23.07.2021.
 * NOTE        : Module namespace 'gogl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "mtl.h"
#include "../anim.h"
#include "rnd.h"
#include "tex.h"

/* Material applay to shader function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) shader program id.
 */
INT gogl::material::Apply( VOID )
{
  /* Set shader program Id */
  if (Shd == nullptr)
    return 0;

  if (Shd->Apply())
  {
    gogl::anim *Ani = gogl::anim::GetPtr();

    /* Set shading parameters */
    Shd->UniSet("Time", Ani->Time);
    Shd->UniSet("Ka", Ka);
    Shd->UniSet("Kd", Kd);
    Shd->UniSet("Ks", Ks);
    Shd->UniSet("Ph", Ph);

    /* Set textures */
    INT i = 0;
    CHAR tname[] = "IsTexture0";
    for (auto n : Tex)
    {
      tname[9] = '0' + i;
      if (n != nullptr)
      {
	/* Activate sampler */
	glActiveTexture(GL_TEXTURE0 + i);
	/* Bind texture to sampler */
	glBindTexture(GL_TEXTURE_2D, n->Id);
      }
      Shd->UniSet(tname, n != nullptr ? true : false); //???????????????????????????????????
    }

    return Shd->ProgId;
  }
  else
    return 0;
} /* End of 'Apply' function */

/* Add material to stock function.
 * ARGUMENTS:
 *   - material name:
 *       std::string Name;
 *   - ambient, diffuse and specular coefficient:
 *       vec3 Ka, Kd, Ks;
 *   - phong coefficient:
 *       FLT Ph;
 *   - transparency factor:
 *       FLT Trans;
 *   - textures container:
 *       std::initializer_list<std::string> Tex;
 *   - shader name:
 *       INT ShdName;
 * RETURNS:
 *   (material *) Created material pointer.
 */
gogl::material & gogl::material::CreateMtlTexPointers( const std::string &Name, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, const FLT &Ph, const FLT &Trans, const std::string &ShdName, const std::vector<texture *> &TexPtr )
{
  *this = material(Name, Ka, Kd, Ks, Ph, Trans);

  ::gogl::anim *Ani = ::gogl::anim::GetPtr();
  Shd = Ani->shader_manager::CreateShd(ShdName);

  INT i = 0;
  for (auto n : TexPtr)
    if (i < NumOfTex)
      Tex[i] = n, i++;

  return *this;
} /* End of 'Create' function */


/* Material create function.
 * ARGUMENTS:
 *   - material name:
 *       std::string Name;
 *   - ambient, diffuse and specular coefficient:
 *       vec3 Ka, Kd, Ks;
 *   - phong coefficient:
 *       FLT Ph;
 *   - transparency factor:
 *       FLT Trans;
 *   - shader name:
 *       std::string ShdName;
 *   - textures container:
 *       std::initializer_list<std::string> TexNames;
 * RETURNS:
 *   (material &) Material self reference.
 */
gogl::material & gogl::material::Create( const std::string &Name, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, const FLT &Ph, const FLT &Trans, const std::string &ShdName, const std::vector<std::string> &TexNames )
{
  *this = material(Name, Ka, Kd, Ks, Ph, Trans);

  ::gogl::anim *Ani = ::gogl::anim::GetPtr();
  Shd = Ani->shader_manager::CreateShd(ShdName);

  // Textures???
  INT i = 0;
  for (auto n : TexNames)
    if (i < NumOfTex)
    {
      Tex[i] = Ani->texture_manager::CreateTex(n);
      if (Tex[i]->Name == "")
	Tex[i] = nullptr;
      i++;
    }
  return *this;
} /* End of 'Create' function */

/* Material create function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (material &) Materia self reference.
 */
gogl::material & gogl::material::Create( VOID )
{
  ::gogl::anim *Ani = ::gogl::anim::GetPtr();
  std::string ShdName = "default";

  Shd = Ani->shader_manager::CreateShd(ShdName);

  Ka = vec3(0.25, 0.148, 0.06475);
  Kd = vec3(0.4, 0.2368, 0.1036);
  Ks = vec3(0.774597, 0.458561, 0.200621);
  Ph = 0;
  Trans = 1;
  Name = "bronze";

  return *this;
}

/* END OF 'mtl.cpp' FILE */