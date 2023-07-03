/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : prims.cpp
 * PURPOSE     : Animation project.
 *               Animation system.
 *               Render system.
 *               Resources.
 *               Primitives.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Dan Gorlyakov.
 * LAST UPDATE : 31.07.2021.
 * NOTE        : Module namespace 'gogl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "../../anim/anim.h"
#include "prims.h"
#include "../../def.h"
#include "../../utilities/reader.h"

/* Free render primitive function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::prims::Free( VOID )
{
  if (Prims.Size() != 0)
  {
    Prims.Walk([]( prim *Pr ){ Pr->Free(); });
    Prims.Clear();
  }
} /* End of 'gogl::prims::Free' function */

/* Load array of primitives from .G3DM file function.
 * ARGUMENTS:
 *   - file name:
 *       const std::string &FileName;
 *   - evaluate bb flag:
 *       const bool &IsEvalBB;
 * RETURNS:
 *   (prims *) self-reference.
 */
gogl::prims & gogl::prims::LoadG3DM( const std::string &FileName, const bool &IsEvalBB)
{
  std::fstream f(FileName, std::fstream::in | std::fstream::binary);

  if (!f.is_open())
    return *this;
 
  f.seekg(0, std::fstream::end);
  INT flen = (INT)f.tellg();
  f.seekg(0, std::fstream::beg);
 
  BYTE *mem = new BYTE[flen], *ptr = mem;
  f.read(reinterpret_cast<CHAR *>(mem), flen);

  rdr rd(ptr);

  DWORD sign;
  rd(&sign);
  if (sign != *(DWORD *)"G3DM")
  {
    delete[] mem;
    return *this;
  }

  INT NumOfPrims;
  rd(&NumOfPrims);
 
  INT NumOfMtls;
  rd(&NumOfMtls);

  INT NumOfTexs;
  rd(&NumOfTexs);

  /* Primitives */
  struct G3DMprim
  {
    DWORD NumOfVertexes;
    DWORD NumOfFacetIndexes;
    DWORD MtlNo;
    std::vector<vertex::std> V;
    std::vector<INT> Ind;
  } *prim = new G3DMprim[NumOfPrims];

  for (INT p = 0; p < NumOfPrims; p++)
  {
    rd(&prim[p].NumOfVertexes);
    prim[p].V.reserve(prim[p].NumOfVertexes);
    rd(&prim[p].NumOfFacetIndexes);
    prim[p].Ind.reserve(prim[p].NumOfFacetIndexes);
    rd(&prim[p].MtlNo);

    for (INT i = 0; i < prim[p].NumOfVertexes; i++)
    {
      vertex::std v;
      rd(&v);
      prim[p].V.emplace_back(v);
    }

    for (INT i = 0; i < prim[p].NumOfFacetIndexes; i++)
    {
      INT ind;
      rd(&ind);
      prim[p].Ind.emplace_back(ind);
    }
  }

  /* Materials */
  struct G3DMmtl
  {
    CHAR Name[300];     /* Material name */

    /* Illumination coefficients */
    vec3 Ka, Kd, Ks; /* Ambient, diffuse, specular coefficients */
    FLT Ph;          /* Phong power coefficient – shininess */
    FLT Trans;       /* Transparency factor */
    INT Tex[8];      /* Texture references 
                      * (8 time: texture number in G3DM file, -1 if no texture) */

    /* Shader information */
    CHAR ShaderString[300]; /* Additional shader information */
    DWORD Shader;       /* Shader number (uses after load into memory) */
  } *mtl = new G3DMmtl[NumOfMtls];

  rd(mtl, NumOfMtls);

  /* Textures */
  struct G3DMtex
  {
    CHAR Name[300]; /* Texture name */
    DWORD W, H;     /* Texture image size in pixels */
    DWORD C;        /* Texture image components (1-mono, 3-bgr or 4-bgra) */
    BYTE *Bits;     /* Texture image data */
   } *tex = new G3DMtex[NumOfTexs];

  for (INT t = 0; t < NumOfTexs; t++)
  {  
    rd(tex[t].Name, 300);
    rd(&tex[t].W);
    rd(&tex[t].H);
    rd(&tex[t].C);

    tex[t].Bits = new BYTE[tex[t].W * tex[t].H * tex[t].C];
    rd(tex[t].Bits, tex[t].W * tex[t].H * tex[t].C);
  }

  /* Animation context */
  anim *Ani = anim::GetPtr();

  /* Output data */

  for (INT p = 0; p < NumOfPrims; p++)
  {
    topology::trimesh<vertex::std> Topo(prim[p].V, prim[p].Ind);
    material *Mtl;
    std::vector<texture *> TexPtr;
    if (mtl[prim[p].MtlNo].Tex[0] != -1)
    {
      G3DMtex T = tex[mtl[prim[p].MtlNo].Tex[0]];
      

      TexPtr.push_back(Ani->render::texture_manager::CreateTex(T.Name, T.W, T.H, T.C, T.Bits));

      Mtl =
        Ani->render::material_manager::CreateMtlTex(mtl[prim[p].MtlNo].Name,
          mtl[prim[p].MtlNo].Ka, mtl[prim[p].MtlNo].Kd, mtl[prim[p].MtlNo].Ks,
          mtl[prim[p].MtlNo].Ph, mtl[prim[p].MtlNo].Trans, TexPtr, "default");
    }
    else
    {
      TexPtr.push_back(nullptr);
      Mtl =
        Ani->render::material_manager::CreateMtlTex(mtl[prim[p].MtlNo].Name,
          mtl[prim[p].MtlNo].Ka, mtl[prim[p].MtlNo].Kd, mtl[prim[p].MtlNo].Ks,
          mtl[prim[p].MtlNo].Ph, mtl[prim[p].MtlNo].Trans, TexPtr, "default");

    }

    if (IsEvalBB)
    {
      gogl::prim *Pr = Ani->CreatePrim(Topo, Mtl);
      Pr->EvalBB(prim[p].V, prim[p].Ind, prim[p].NumOfVertexes);
      this->Prims << Pr;
    }
    else
      this->Prims << Ani->CreatePrim(Topo, Mtl);
  }
  /*
  for (INT p = 0; p < NumOfPrims; p++)
  {
    topology::trimesh<vertex::std> Topo(prim[p].V, prim[p].Ind);
    material *Mtl;
    std::vector<std::string> TexNames;
    std::vector<texture *> TexPtr;

    TexPtr.reserve(8);
    
    for (INT i = 0; i < 8; i++)
    {
      if (mtl[prim[p].MtlNo].Tex[i] != -1)
      {
        G3DMtex T = tex[mtl[prim[p].MtlNo].Tex[i]];
        TexPtr.push_back(Ani->render::texture_manager::CreateTex(T.Name, T.W, T.H, T.C, T.Bits));
      }
      else
        TexPtr.push_back(nullptr);
    }
    Mtl =
          Ani->render::material_manager::CreateMtlTex(mtl[prim[p].MtlNo].Name,
            mtl[prim[p].MtlNo].Ka, mtl[prim[p].MtlNo].Kd, mtl[prim[p].MtlNo].Ks,
            mtl[prim[p].MtlNo].Ph, mtl[prim[p].MtlNo].Trans, TexPtr, "default");

    Prims->Prims << Ani->CreatePrim(Topo, Mtl);
  }
  */
  for (INT t = 0; t < NumOfTexs; t++)
    delete[] tex[t].Bits;
  
  delete[] mem;
  delete[] tex;
  delete[] prim;
  delete[] mtl;

  this->NumOfPrims = NumOfPrims;
  this->Transform = matr::Identity();
  this->Name = FileName;

  return *this;
} /* End of 'LoadG3DM' function */

/* Create primitive function.
 * ARGUMENTS:
 *   - '*.G3DM' file name:
 *       const std::string &FileName;
 *   - evaluate bb flag:
 *       const bool &IsEvalBB;
 * RETURNS:
 *   (model *) created primitive interface.
 */
gogl::prims * gogl::prims_manager::CreatePrims( const std::string &FileName, const bool &IsEvalBB )
{
  prims *find = {};
  
  if ((find = Find(FileName)) != nullptr)
    return find;

  return Add(prims().LoadG3DM(FileName, IsEvalBB));
} /* End of 'gogl::prims_manager::Createprims' function */

/* END OF 'prims.cpp' FILE */