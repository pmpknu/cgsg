/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : prim.h
 * PURPOSE     : Animation project.
 *               Render system.
 *               Primitives handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 24.07.2021.
 * NOTE        : Module namespace 'gogl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __prim_h_
#define __prim_h_

#include "../../def.h"
#include "topology.h"
#include "res.h"
#include "mtl.h"

/* Project namespace */
namespace gogl
{
  /* Primitive handle class */
  class prim
  {
    friend class render;
    friend class prim_manager;
    template<typename entry_type, typename index_type>
    friend class resource_manager;
  private:
    prim_type Type = prim_type::TRIMESH;  /* Primitive type */
    UINT VA;                              /* Primitive vertex array */
    UINT VBuf;                            /* Vertex buffer */
    UINT IBuf;                            /* Index buffer */
    INT NumOfElements = 0;                /* Number of elements for OpenGL */

  public:
    matr Transform;  /* Primitive transformation matrix */
    material *Mtl;   /* Material pointer */
    vec3
      MinBB,  /* Minimal primitive position */
      MaxBB;  /* Maximal primitive position */
    INT InstanceCnt;   /* Counter for instancing, 0 - not use */
 
    /* Class constructor */
    prim( VOID ) : VA(0), VBuf(0), IBuf(0), MinBB(0), MaxBB(0)
    {
    } /* End of 'prim' function */
 
    /* Class destructor */
    ~prim( VOID )
    {
    } /* End of '~prim' function */

    /* Bound box calculate function.
     * ARGUMENTS:
     *   - vertex array:
     *      const std::vector<vertex::std> &V;
     *   - index:
     *      const std::vector<INT> &I;
     *   - num of vertex:
     *      const INT &NoofV;
     * RETURNS: None.
     */
    VOID EvalBB( const std::vector<vertex::std> &V, const std::vector<INT> &I, const INT &NoofV)
    {
      MinBB = MaxBB = V[I[0]].P;
      for (INT i = 0; i < NoofV; i ++)
      {
       MinBB.MinBB(V[i].P);
       MaxBB.MaxBB(V[i].P);
      }
    }/* End of 'EvalBB' function */

    /* Free render primitive function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID )
    {
      if (VA != 0)
      {
        /* making an array of vertices active */
        glBindVertexArray(VA);

        /* unhooking the buffer */
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &VBuf);

        /* making an array of vertices inactive */
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &VA);

        /* making an array of indexes inactive */
        glDeleteBuffers(1, &IBuf);
      }
      else
        VBuf = IBuf = 0;
    } /* End of 'Free' function */

    /* Primitive creation function.
     * ARGUMENTS:
     *   - topology base reference:
     *       const topology::base &T;
     *   - primitive material:
     *       const material *Mtl;
     * RETURNS:
     *   (prim &) self reference.
     */
    template<class vertex>
      prim & Create( const topology::base<vertex> &T, material *NewMtl )
      {
        Free();

        // Setup data order due to vertex description string
        const std::string dsc = vertex::Description;
 
        Type = T.Type;

        if (!T.V.empty() && T.V.size())
        {
          glGenBuffers(1, &VBuf);
          glGenVertexArrays(1, &VA);
 
          glBindVertexArray(VA);
          glBindBuffer(GL_ARRAY_BUFFER, VBuf);
          glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * T.V.size(), T.V.data(), GL_STATIC_DRAW);

          // Setup data order due to vertex description string
          // for (auto c = vertex::Description.begin(); c != vertex::Description.end(); c++)
          INT attr = 0, offset = 0;
          for (auto c = dsc.begin(); c != dsc.end(); c++)
            if (*c == 'f' || *c == 'i')
            {
              CHAR type = *c++;
              INT n = *c - '0';

              if (n < 0 || n > 9)
                break;
              // Enable used attributes
              glEnableVertexAttribArray( attr );
              glVertexAttribPointer( attr, n, type == 'f' ? GL_FLOAT : GL_INT, FALSE,
                sizeof( vertex ), (VOID *)offset );
              offset += n * 4;
              attr++;
            }
            else
              break;

          glBindVertexArray(0);
        }

        if (!T.I.empty() && T.I.size())
        {
          glGenBuffers(1, &IBuf);
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
          glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * T.I.size(), T.I.data(), GL_STATIC_DRAW);
          NumOfElements= T.I.size();
        }
        else
          NumOfElements= T.V.size();

        Transform = matr::Identity();
        Mtl = NewMtl;

        return *this;
      } /* End of 'Create' function */
  }; /* end of 'prim' class */

  /* Primitive manager handle class */
  class prim_manager : public resource_manager<prim, INT>
  {
  //protected:
    public:
    /* Primitive creation function.
     * ARGUMENTS:
     *   - topology base reference:
     *       const topology::base &T;
     *   - primitive material:
     *       const material *Mtl;
     * RETURNS:
     *   (prim *) primitive create interface.
     */
    template<class vertex_type>
    prim * CreatePrim( const topology::base<vertex_type> &T, material *Mtl )
    {
      return Add(prim().Create(T, Mtl));
    } /* End of 'CreatePrim' function */
  }; /* End of 'prim_manager' class */
} /* end of 'gogl' namespace */

#endif /* __prim_h_ */

/* END OF 'prim.h' FILE */