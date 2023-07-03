/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : tex.h
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

#ifndef __tex_h_
#define __tex_h_

#include <string>
#include <fstream>
#include <cmath>

#include "../../def.h"
#include "res.h"

/* Project namespace */
namespace gogl
{
  /* Texture class */
  class texture
  {
    /* Delegating access right to other classes */
    friend class render;
    friend class texture_manager;
    template<typename entry_type, typename index_type>
    friend class resource_manager;

  public:
    // Class fields
    INT Id; /* Texture identificator */
    std::string Name; /* Texture name */
  private:
    // Class methods
    /* Add texture from image function.
     * ARGUMENTS:
     *   - image width:
     *       INT W;
     *   - image hight:
     *       INT H;
     *   - components:
     *       INT C;
     *   - color bits:
     *       VOID *Bits;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture & AddImg( const INT &w, const INT &h, const INT &C, const VOID *Bits )
    {
      FLT mips;

      mips = w > h ? h : w;
      mips = log(mips) / log(2);
      if (mips < 1)
	mips = 1;

      /* Allocate texture space */
      glGenTextures(1, reinterpret_cast<UINT *>(&Id));
      glBindTexture(GL_TEXTURE_2D, Id);

      /* Upload texture */
      ///gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);
      glTexStorage2D(GL_TEXTURE_2D, mips, C == 3 ? GL_RGB8 : C == 4 ? GL_RGBA8 : GL_R8, w, h);
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, Bits);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
      glBindTexture(GL_TEXTURE_2D, 0);

      return *this;
    } /* End of 'AddImg' function */

    /* Texture load from *.G32 or *.G24 file function.
     * ARGUMENTS:
     *   - texture file name:
     *       std::string &TextureFileName;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture & Load( const std::string &TextureFileName )
    {
      /* Build file name */
      CHAR Buf[_MAX_PATH];
      GetCurrentDirectory(sizeof(Buf), Buf);
  
      std::string sBuf = Buf;

      std::fstream f(sBuf + "/BIN/TEXTURES/" + TextureFileName, std::fstream::in | std::fstream::binary);

      if (!f.is_open())
	return *this;   //?..
 
      f.seekg(0, std::fstream::end);
      INT flen = (INT)f.tellg();
      f.seekg(0, std::fstream::beg);

      WORD w = 0, h = 0;
      f.read(reinterpret_cast<CHAR *>(&w), 2);
      f.read(reinterpret_cast<CHAR *>(&h), 2);

      WORD tag = 3;
      if (w * h * 4 == flen - 4)
        tag = 4;

      DWORD *img = new DWORD[flen];
      for (INT x = 0; x < w; x++)
        for (INT y = 0; y < h; y++)
        {
          DWORD d = 0;

          f.read(reinterpret_cast<CHAR *>(&d), tag);
          d |= 0xFF000000;
          img[(h - y - 1) * w + x] = d;
        }

      AddImg(w, h, tag, img);
      delete[] img;

      return *this;
    } /* End of 'Load' function */
  public:
    /* Free material function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID )
    {
    } /* End of 'Free' function */


    /* Default texture constructor */
    texture( VOID )
    {
    } /* End of 'texture' function */

    /* Texture cunstructor.
     * ARGUMENTS:
     *   - texture file name:
     *       std::string &TextureFileName;
     *   - texture name:
     *       std::string &Name;
     * RETURNS: None.
     */
    texture( const std::string &TextureFileName ) : Name(TextureFileName)
    {
    } /* End of 'texture' function */

  }; /* end of 'texture' class */

  /* Texture manager class */
  class texture_manager : public resource_manager<texture, std::string>
  {
  public:
    /* Create texture function.
     * ARGUMENTS:
     *   - texture file name:
     *       std::string &TextureFileName;
     * RETURNS:
     *   (texture *) texture create interface.
     */
    texture * CreateTex( const std::string &Name, const DWORD &W, const DWORD &H, const DWORD &C, const VOID *Bits )
    {
      texture *find = {};
 
      if ((find = Find(Name)) != nullptr)
        return find;

      return Add(texture(Name).AddImg(W, H, C, Bits));//, Name));
    } /* End of 'CreateTex' function */

    /* Create texture function.
     * ARGUMENTS:
     *   - texture file name:
     *       std::string &TextureFileName;
     * RETURNS:
     *   (texture *) texture create interface.
     */
    texture * CreateTex( const std::string &TextureFileName )
    {
      return Add(texture(TextureFileName).Load(TextureFileName));//, Name));
    } /* End of 'CreateTex' function */

  }; /* End of 'texture_manager' class */
} /* end of 'gogl' namespace */

#endif /* __tex_h_ */

/* END OF 'tex.h' FILE */