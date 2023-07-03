/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mtl.h
 * PURPOSE     : Animation project.
 *               Render system.
 *               Materials resource handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 26.07.2021.
 * NOTE        : Module namespace 'gogl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mtl_h_
#define __mtl_h_

#include <string>
#include <vector>

#include "../../def.h"
#include "res.h"
#include "shd.h"
#include "tex.h"

/* Project namespace */
namespace gogl
{
  /* Material class */
  class material
  {
    friend class render;
    friend class material_manager;
    template<typename entry_type, typename index_type>
    friend class resource_manager;

  private:
    std::string Name; /* Material name */

    // Illumination coefficients
    vec3 Ka;     /* Ambient coefficient */
    vec3 Kd;     /* Diffuse coefficient */
    vec3 Ks;     /* Specular coefficient */
    FLT Ph;      /* Phong power coefficient */
    FLT Trans;   /* Transparency factor */

    static const INT NumOfTex = 8;
    texture *Tex[NumOfTex];  /* Texture pointers array */

    shader *Shd;   /* Material shader pointer */

  public:
    material( VOID )
    {
      Ka = vec3(0);
      Kd = vec3(0);
      Ks = vec3(0);
      Ph = 0;
      Shd = nullptr;
      Trans = 0;
      Name = "";

      for (INT i = 0; i < NumOfTex; i++)
	Tex[i] = nullptr;
    }

    material( const std::string &Name, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, const FLT &Ph, const FLT &Trans)
      : Name(Name), Ka(Ka), Kd(Kd), Ks(Ks), Ph(Ph), Trans(Trans), Shd(nullptr)
    {
      for (INT i = 0; i < NumOfTex; i++)
	Tex[i] = nullptr;
    }
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
     *   - textures pointers:
     *       std::vector<texture *> TexNames;
     * RETURNS:
     *   (material &) Material self reference.
     */
    material & CreateMtlTexPointers( const std::string &Name, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, const FLT &Ph, const FLT &Trans, const std::string &ShdName, const std::vector<texture *> &TexPtr );

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
    material & Create( const std::string &Name, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, const FLT &Ph, const FLT &Trans, const std::string &ShdName, const std::vector<std::string> &TexNames );

    /* Material create function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (material &) Materia self reference.
     */
    material & Create( VOID );

    /* Material applay to shader function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) shader program id.
     */
    INT Apply( VOID );

    /* Free material function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID )
    {
    } /* End of 'Free' function */
  }; /* End of 'material' class */

  /* Material manager class */
  class material_manager : public resource_manager<material, std::string>
  {
  public:
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
    material * CreateMtlTex( const std::string &Name, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, const FLT &Ph, const FLT &Trans, const std::vector<texture *> &Tex, const std::string &ShdName )
    {
      return Add(material().CreateMtlTexPointers(Name, Ka, Kd, Ks, Ph, Trans, ShdName, Tex));
    } /* End of 'Add' function */


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
    material * CreateMtl( const std::string &Name, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, const FLT &Ph, const FLT &Trans, const std::vector<std::string> &Tex, const std::string &ShdName )
    {
      return Add(material().Create(Name, Ka, Kd, Ks, Ph, Trans, ShdName, Tex));
    } /* End of 'Add' function */

    /* Add material to stock function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (material *) Created material pointer.
     */
    material * CreateMtl( VOID )
    {
      return Add(material().Create());
    } /* End of 'Add' function */
  }; /* End of 'material_manager' class */
} /* end of 'gogl' namespace */

#endif /* __mtl_h_ */

/* END OF 'mtl.h' FILE */
