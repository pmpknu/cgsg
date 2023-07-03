/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : topology.h
 * PURPOSE     : Animation project.
 *               Render system.
 *               Topology handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 24.07.2021.
 * NOTE        : Module namespace 'gogl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __topology_h_
#define __topology_h_

#include <vector>
#include <string>
#include <cassert>

#include "../../def.h"

/* Project namespace */
namespace gogl
{
   /* Vertex collection namespace */
  namespace vertex
  {
    /* Standard vertex representation type */
    struct std
    {
      vec3 P;  /* Vertex position */
      vec2 T;  /* Vertex texture coordinates */
      vec3 N;  /* Normal at vertex */
      vec4 C;  /* Vertex color */
 
      /* Vertex content description string */
      static const ::std::string Description;
 
      /* Class default constructor */
      std( VOID )
      {
      } /* End of 'std' function */
 
      /* Class constructor.
       * ARGUMENTS:
       *   - new vertex position:
       *       const vec &NewP;
       *   - new vertex texture coordinates:
       *       const vec2 &NewT;
       *   - new vertex normal:
       *       const vec &NewN;
       *   - new vertex color:
       *       const vec4 &NewC;
       */
      std( const vec3 &NewP,
           const vec2 &NewT = vec2(0, 0),
           const vec3 &NewN = vec3(0, 1, 0),
           const vec4 &NewC = vec4(1) ) :
        P(NewP), T(NewT), N(NewN), C(NewC)
      {
      } /* End of 'std' function */
    }; /* end of 'std' struct */
  } /* end of 'vertex' namespace */

  // Forward declaration from 'prim.h'
  class prim;

  /* Primitive shape representation type */
  enum struct prim_type
  {
    TRIMESH,   /* Triangle mesh - array of triangles */
    TRISTRIP,  /* Triangle strip - array of stripped triangles */
    LINES,     /* Line segments (by 2 points) */
    POINTS,    /* Arrauy of points */
    PATH,      /* Path of points */
   }; /* End of 'prim_type' enum structure */
 
  /* Topology structures namespase */
  namespace topology
  {
    /* Base topology class */
    template<typename vertex_type>
      class base
      {
        friend class ::gogl::prim;
      protected:
        prim_type Type = prim_type::TRIMESH;
 
        /* Vertex array */
        std::vector<vertex_type> V;
        /* Index array */
        std::vector<INT> I;
 
      public:
        /* Class default constructor */
        base( VOID )
        {
        } /* End of 'base' function */
 
        /* Class constructor.
         * ARGUMENTS:
         *   - primitive type:
         *       prim_type NewType;
         *   - vertex array:
         *       const std::vector<vertex_type> &NewV;
         *   - index array:
         *       const std::vector<INT> &NewI;
         */
        base( prim_type NewType,
              const std::vector<vertex_type> &NewV = {},
              const std::vector<INT> &NewI = {} ) : Type(NewType), V(NewV), I(NewI)
        {
        } /* End of 'base' function */
      };
 
    /* Trimesh topology class */
    template<typename vertex_type>
      class trimesh : public base<vertex_type>
      {
      public:
        /* Class default constructor */
        trimesh( VOID )
        {
        } /* End of 'trimesh' function */
 
        /* Class constructor.
         * ARGUMENTS:
         *   - vertex array:
         *       const std::vector<vertex> &NewV;
         *   - index array:
         *       const std::vector<INT> &NewI;
         */
        trimesh( const std::vector<vertex_type> &NewV,
                 const std::vector<INT> &NewI = {} ) : base<vertex_type>(prim_type::TRIMESH, NewV, NewI)
        {
        } /* End of 'trimesh' function */
 
        /* Evaluate trimesh vertex normals function.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        VOID EvalNormals( VOID )
        {
          INT i;

          for (i = 0; i < base<vertex_type>::I.size() - 2; i += 3)
          {
            vec3 N =
              ((base<vertex_type>::V[base<vertex_type>::I[i + 1]].P - base<vertex_type>::V[base<vertex_type>::I[i]].P) %
               (base<vertex_type>::V[base<vertex_type>::I[i + 2]].P - base<vertex_type>::V[base<vertex_type>::I[i]].P)).Normalizing();

            base<vertex_type>::V[base<vertex_type>::I[i + 0]].N = (base<vertex_type>::V[base<vertex_type>::I[i + 0]].N + N).Normalizing();
            base<vertex_type>::V[base<vertex_type>::I[i + 1]].N = (base<vertex_type>::V[base<vertex_type>::I[i + 1]].N + N).Normalizing();
            base<vertex_type>::V[base<vertex_type>::I[i + 2]].N = (base<vertex_type>::V[base<vertex_type>::I[i + 2]].N + N).Normalizing();
          }
        } /* End of 'EvalNormals' function */
      };
 
    template<typename vertex_type>
      class grid : public base<vertex_type>
      {
      public:
        /* Class default constructor */
        grid( VOID )
        {
        } /* End of 'grid' function */
 
        /* Class constructor.
         * ARGUMENTS:
         *   - grid size:
         *       const INT &NewW, &NewH;
         */
        grid( const INT &NewW, const INT &NewH ) : W(NewW), H(NewH), base<vertex_type>(prim_type::TRISTRIP)
        {
          Create(W, H);
          EvalNormals();
        } /* End of 'grid' function */

        /* Class constructor.
         * ARGUMENTS:
         *   - grid size:
         *       const INT &NewW, &NewH;
         *   - vertex container:
         *       const std::vector<vertex_type> &NewV;
         */
        grid( const INT &NewW, const INT &NewH, const std::vector<vertex_type> &NewV ) : W(NewW), H(NewH), base<vertex_type>(prim_type::TRISTRIP, NewV)
        {
          Create(NewW, NewH, NewV);
          EvalNormals();
        } /* End of 'grid' function */

      protected:
        /* Grid size */
        INT W, H;

        /* Create grid handle function.
         * ARGUMENTS:
         *   - grid size:
         *       INT NewW, NewH;
         */
        VOID Create( const INT &NewW, const INT &NewH, const std::vector<vertex_type> &NewV )
        {
          base<vertex_type>::I = std::vector<INT>(((NewH - 1) * (NewW * 2 + 1) - 1));

          for (INT i = 0, k = 0; i < NewH - 1; i++)
          {
            for (INT j = 0; j < NewW; j++)
            {
              base<vertex_type>::I[k++] = (i + 1) * NewW + j;
              base<vertex_type>::I[k++] = i * NewW + j;
            }
            if (i != NewH - 2)
              base<vertex_type>::I[k++] = -1;
          }
        } /* End of 'Create' function */

        /* Create grid handle function.
         * ARGUMENTS:
         *   - grid size:
         *       INT NewW, NewH;
         */
        VOID Create( const INT &NewW, const INT &NewH )
        {
          if (NewW < 2 && NewH < 2)
            return;

          base<vertex_type>::V = std::vector<vertex_type>(NewW * NewH);
          base<vertex_type>::I = std::vector<INT>(((NewH - 1) * (NewW * 2 + 1) - 1));

          for (INT x = 0; x < NewW; x++)
            for (INT z = 0; z < NewH; z++)
              base<vertex_type>::V[x * NewW + z].P = vec3(x, 0, z);

          for (INT i = 0, k = 0; i < NewH - 1; i++)
          {
            for (INT j = 0; j < NewW; j++)
            {
              base<vertex_type>::I[k++] = (i + 1) * NewW + j;
              base<vertex_type>::I[k++] = i * NewW + j;
            }
            if (i != NewH - 2)
              base<vertex_type>::I[k++] = -1;
          }
        } /* End of 'Create' function */

        /* Obtain grid width function.
         * ARGUMENTS: None.
         * RETURNS:
         *   (INT) grid width.
         */
        INT GetW( VOID ) const
        {
          return W;
        } /* End of 'GetW' function */
 
        /* Obtain grid height function.
         * ARGUMENTS: None.
         * RETURNS:
         *   (INT) grid height.
         */
        INT GetH( VOID ) const
        {
          return H;
        } /* End of 'GetH' function */
 
        /* Grid 2D array vertex access function.
         * ARGUMENTS:
         *   - row index:
         *       INT Row;
         * RETURNS:
         *   (vertex *) vertex row pointer.
         */
        vertex_type * operator[]( INT Row )
        {
          assert(Row >= 0 && Row < H);
          return &this->V[Row * W];
        } /* End of 'operator[]' function */
 
        /* Evaluate grid vertex normals function.
         * ARGUMENTS: None.
         * RETURNS: None.
         */
        VOID EvalNormals( VOID )
        {
          for (INT i = 0; i < H - 1; i++)
            for (INT j = 0; j < W - 1; j++)
            {
              vertex::std
                *P00 = &base<vertex_type>::V[i * W + j],
                *P01 = &base<vertex_type>::V[i * W + j + 1],
                *P10 = &base<vertex_type>::V[(i + 1) * W + j],
                *P11 = &base<vertex_type>::V[(i + 1) * W + j + 1];

              vec3 N = ((P00->P - P10->P) % (P11->P - P10->P)).Normalize();
              P00->N = (P00->N + N).Normalize();
              P10->N = (P10->N + N).Normalize();
              P11->N = (P11->N + N).Normalize();

              N = ((P11->P - P01->P) % (P00->P - P01->P)).Normalize();;
              P00->N = (P00->N + N).Normalize();
              P01->N = (P01->N + N).Normalize();
              P11->N = (P11->N + N).Normalize();
            }
        } /* End of 'EvalNormals' function */
      }; /* end of 'grid' class */

    template<typename vertex_type>
      class cube : public base<vertex_type>
      {
      public:
        /* Class default constructor */
        cube( VOID )
        {
        } /* End of 'grid' function */
 
        /* Class constructor.
         * ARGUMENTS:
         *   - cube box vectors:
         *       const vec3 &Min, &Max;
         */
        cube( const vec3 &Min, const vec3 &Max ) : Min(Min), Max(Max), base<vertex_type>(prim_type::TRIMESH)
        {
          Create(Min, Max);
        } /* End of 'grid' function */
      protected:
        vec3 Min, Max;

        /* Create grid handle function.
         * ARGUMENTS:
         *   - cube box vectors:
         *       const vec3 &Min, &Max;
         */
        VOID Create( const vec3 &Min, const vec3 &Max )
        {
          base<vertex_type>::V = std::vector<vertex_type>(24);
          base<vertex_type>::I = std::vector<INT>(36);

          // faces of the cube
          /* first */
          base<vertex_type>::V[0].P = Min;
          base<vertex_type>::V[1].P = Min + vec3(0, 0, Max[2]);
          base<vertex_type>::V[2].P = Min + vec3(0, Max[1], Max[2]);
          base<vertex_type>::V[3].P = Min + vec3(0, Max[1], 0);

          base<vertex_type>::V[0].N = vec3(-1, 0, 0).Normalizing();
          base<vertex_type>::V[1].N = vec3(-1, 0, 0).Normalizing();
          base<vertex_type>::V[2].N = vec3(-1, 0, 0).Normalizing();
          base<vertex_type>::V[3].N = vec3(-1, 0, 0).Normalizing();

          base<vertex_type>::V[0].T = vec2(0, 0);
          base<vertex_type>::V[1].T = vec2(1, 0);
          base<vertex_type>::V[2].T = vec2(1, 1);
          base<vertex_type>::V[3].T = vec2(0, 1);

          base<vertex_type>::I[0] = 0;
          base<vertex_type>::I[1] = 1;
          base<vertex_type>::I[2] = 2;
          base<vertex_type>::I[3] = 0;
          base<vertex_type>::I[4] = 2;
          base<vertex_type>::I[5] = 3;

          /* second */
          base<vertex_type>::V[4].P = Min;
          base<vertex_type>::V[5].P = Min + vec3(Max[0], 0, 0);
          base<vertex_type>::V[6].P = Min + vec3(Max[0], Max[1], 0);
          base<vertex_type>::V[7].P = Min + vec3(0, Max[1], 0);

          base<vertex_type>::V[4].N = vec3(0, 0, -1).Normalizing();
          base<vertex_type>::V[5].N = vec3(0, 0, -1).Normalizing();
          base<vertex_type>::V[6].N = vec3(0, 0, -1).Normalizing();
          base<vertex_type>::V[7].N = vec3(0, 0, -1).Normalizing();

          base<vertex_type>::V[4].T = vec2(0, 0);
          base<vertex_type>::V[5].T = vec2(1, 0);
          base<vertex_type>::V[6].T = vec2(0, 1);
          base<vertex_type>::V[7].T = vec2(1, 1);

          base<vertex_type>::I[6] = 4;
          base<vertex_type>::I[7] = 5;
          base<vertex_type>::I[8] = 6;
          base<vertex_type>::I[9] = 4;
          base<vertex_type>::I[10] = 6;
          base<vertex_type>::I[11] = 7;

          /* third */
          base<vertex_type>::V[8].P = Min + vec3(0, 0, Max[2]);
          base<vertex_type>::V[9].P = Min + vec3(0, Max[1], Max[2]);
          base<vertex_type>::V[10].P = Max;
          base<vertex_type>::V[11].P = Min + vec3(Max[0], 0, Max[2]);

          base<vertex_type>::V[8].N = vec3(0, 0, 1).Normalizing();
          base<vertex_type>::V[9].N = vec3(0, 0, 1).Normalizing();
          base<vertex_type>::V[10].N = vec3(0, 0, 1).Normalizing();
          base<vertex_type>::V[11].N = vec3(0, 0, 1).Normalizing();

          base<vertex_type>::V[8].T = vec2(0, 0);
          base<vertex_type>::V[9].T = vec2(1, 0);
          base<vertex_type>::V[10].T = vec2(0, 1);
          base<vertex_type>::V[11].T = vec2(1, 1);

          base<vertex_type>::I[12] = 8;
          base<vertex_type>::I[13] = 9;
          base<vertex_type>::I[14] = 10;
          base<vertex_type>::I[15] = 8;
          base<vertex_type>::I[16] = 10;
          base<vertex_type>::I[17] = 11;

          /* fourth */
          base<vertex_type>::V[12].P = Min + vec3(Max[0], 0, 0);
          base<vertex_type>::V[13].P = Min + vec3(Max[0], Max[1], 0);
          base<vertex_type>::V[14].P = Max;
          base<vertex_type>::V[15].P = Min + vec3(Max[0], 0, Max[2]);

          base<vertex_type>::V[12].N = vec3(1, 0, 0).Normalizing();
          base<vertex_type>::V[13].N = vec3(1, 0, 0).Normalizing();
          base<vertex_type>::V[14].N = vec3(1, 0, 0).Normalizing();
          base<vertex_type>::V[15].N = vec3(1, 0, 0).Normalizing();

          base<vertex_type>::V[12].T = vec2(0, 0);
          base<vertex_type>::V[13].T = vec2(1, 0);
          base<vertex_type>::V[14].T = vec2(0, 1);
          base<vertex_type>::V[15].T = vec2(1, 1);

          base<vertex_type>::I[18] = 12;
          base<vertex_type>::I[19] = 13;
          base<vertex_type>::I[20] = 14;
          base<vertex_type>::I[21] = 12;
          base<vertex_type>::I[22] = 14;
          base<vertex_type>::I[23] = 15;

          /* fifth */
          base<vertex_type>::V[16].P = Min + vec3(0, Max[1], 0);
          base<vertex_type>::V[17].P = Min + vec3(Max[0], Max[1], 0);
          base<vertex_type>::V[18].P = Max;
          base<vertex_type>::V[19].P = Min + vec3(0, Max[1], Max[2]);

          base<vertex_type>::V[16].N = vec3(0, 1, 0).Normalizing();
          base<vertex_type>::V[17].N = vec3(0, 1, 0).Normalizing();
          base<vertex_type>::V[18].N = vec3(0, 1, 0).Normalizing();
          base<vertex_type>::V[19].N = vec3(0, 1, 0).Normalizing();

          base<vertex_type>::V[16].T = vec2(0, 0);
          base<vertex_type>::V[17].T = vec2(1, 0);
          base<vertex_type>::V[18].T = vec2(0, 1);
          base<vertex_type>::V[19].T = vec2(1, 1);

          base<vertex_type>::I[24] = 16;
          base<vertex_type>::I[25] = 17;
          base<vertex_type>::I[26] = 18;
          base<vertex_type>::I[27] = 16;
          base<vertex_type>::I[28] = 18;
          base<vertex_type>::I[29] = 19;

          /* sixth */
          base<vertex_type>::V[20].P = Min;
          base<vertex_type>::V[21].P = Min + vec3(0, 0, Max[2]);
          base<vertex_type>::V[22].P = Min + vec3(Max[0], 0, Max[2]);
          base<vertex_type>::V[23].P = Min + vec3(Max[0], 0, 0);

          base<vertex_type>::V[20].N = vec3(0, -1, 0).Normalizing();
          base<vertex_type>::V[21].N = vec3(0, -1, 0).Normalizing();
          base<vertex_type>::V[22].N = vec3(0, -1, 0).Normalizing();
          base<vertex_type>::V[23].N = vec3(0, -1, 0).Normalizing();

          base<vertex_type>::V[20].T = vec2(0, 0);
          base<vertex_type>::V[21].T = vec2(1, 0);
          base<vertex_type>::V[22].T = vec2(0, 1);
          base<vertex_type>::V[23].T = vec2(1, 1);

          base<vertex_type>::I[30] = 20;
          base<vertex_type>::I[31] = 21;
          base<vertex_type>::I[32] = 22;
          base<vertex_type>::I[33] = 20;
          base<vertex_type>::I[34] = 22;
          base<vertex_type>::I[35] = 23;
        } /* End of 'Create' function */
      }; /* end of 'grid' class */

  } /* end of 'topology' namespace */
} /* end of 'gogl' namespace */

#endif /* __topology_h_ */

/* END OF 'topology.h' FILE */