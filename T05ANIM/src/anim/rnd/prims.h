/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : prims.h
 * PURPOSE     : Animation project.
 *               Render system.
 *               Primitives collection handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 29.07.2021.
 * NOTE        : Module namespace 'gogl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __prims_h_
#define __prims_h_

#include "../../def.h"
#include "prim.h"

/* Project namespace */
namespace gogl
{
  /* Primitive collection handle class */
  class prims
  {
    friend class render;
    friend class prims_manager;
    template<typename entry_type, typename index_type>
    friend class resource_manager;
  private:
    INT NumOfPrims;      /* Number of primitives in array */  
    stock<prim *> Prims; /* Array of primitives */
    matr Transform;      /* Common transformation matrix */
    bool IsEvaluatedBB;  /* Eval bb flag */
  public:
    std::string Name;    /* Name of primitives model */
    vec3 MinBB, MaxBB;   /* Model bound box */
    INT InstanceCnt;   /* Counter for instancing, 0 - not use */

    /* Class constructor */
    prims( VOID ) : NumOfPrims(0), Transform(matr::Identity()), IsEvaluatedBB(false), InstanceCnt(0)
    {
    } /* End of 'prim' function */
 
    /* Class destructor */
    ~prims( VOID )
    {
      OutputDebugString("Prims destructed \n");
      //Prims.Walk([]( prim *Pr ){ delete Pr; });
    } /* End of '~prim' function */

    /* Eval model bound box.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID EvalBB( VOID )
    {
      if (IsEvaluatedBB)
	return;

      IsEvaluatedBB = true;

      MinBB = Prims[0]->MinBB;
      MaxBB = Prims[0]->MaxBB;

      Prims.Walk([&]( prim *Pr )
        {
          MinBB.MinBB(Pr->MinBB);
          MaxBB.MinBB(Pr->MaxBB);
        });
    } /* End of 'SetTrans' function */

    /* Set transform matrix.
     * ARGUMENTS:
     *   - transformation matrix:
     *       const matr &Tr;
     * RETURNS: None.
     */
    VOID SetTrans( const matr &Tr )
    {
      Transform = Tr;
    } /* End of 'SetTrans' function */

  private:
    /* Free render primitive function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

    /* Load array of primitives from .G3DM file function.
     * ARGUMENTS:
     *   - file name:
     *       const std::string &FileName;
     *   - evaluate bb flag:
     *       const bool &IsEvalBB;
     * RETURNS:
     *   (prims *) self-reference.
     */
    prims & LoadG3DM( const std::string &FileName, const bool &IsEvalBB);
  }; /* end of 'prims' class */

  /* Primitives manager class */
  class prims_manager : public resource_manager<prims, std::string>
  {
  //protected: ??
  public:
    /* Create primitive function.
     * ARGUMENTS:
     *   - '*.G3DM' file name:
     *       const std::string &FileName;
     *   - evaluate bb flag:
     *       const bool &IsEvalBB;
     * RETURNS:
     *   (model *) created primitive interface.
     */
    prims * CreatePrims( const std::string &FileName, const bool &IsEvalBB = false );
  };
} /* end of 'gogl' namespace */

#endif /* __prims_h_ */

/* END OF 'prims.h' FILE */