/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : reader.h
 * PURPOSE     : Animation project.
 *               Render system.
 *               Textures resource handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 26.07.2021.
 * NOTE        : Module namespace 'gogl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __reader_h_
#define __reader_h_

#include <cstring>

#include "../def.h"

/* Project namespace */
namespace gogl
{
  /* Unstructured data file reader class */
  class rdr
  {
  private:
    // Memory pointer reference
    BYTE *&Ptr;
 
  public:
    /* Class constructor.
      * ARGUMENTS:
      *   - reference to memory pointer:
      *       BYTE *&PtrRef;
      */
    rdr( BYTE *&PtrRef ) : Ptr(PtrRef)
    {
    } /* End of 'rdr' function */
 
    /* Read data function.
      * ARGUMENT:
      *   - read data pointer:
      *       type *Data;
      *   - read data count:
      *       INT Count;
      * RETURNS: None.
      */
    template<typename type>
      VOID operator()( type *Data, const INT Count = 1 )
      {
        if (Count == 1)
          *Data = *(type *)Ptr, Ptr += sizeof(type);
        else
          memcpy(Data, Ptr, sizeof(type) * Count), Ptr += sizeof(type) * Count;
      } /* End of 'operator()' function */
  }; /* End of 'rdr' class */
} /* end of 'gogl' namespace */

#endif /* __tex_h_ */

/* END OF 'reader.h' FILE */