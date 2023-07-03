/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : frame.h
 * PURPOSE     : Ray tracing project.
 *               Frame handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 01.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __frame_h_
#define __frame_h_

#pragma pack(push, 1)
#include <tgahead.h>
#pragma pack(pop)

#include <string>
#include <fstream>
#include <filesystem>

#include "../../def.h"

/* Space gort namespace */
namespace gort
{
  /* Frame class */
  class frame
  {
  private:
    INT W = 0, H = 0; // Frame size
    DWORD *Pixels = nullptr; // Frame buffer pixels

  public:
    /* Obtain width function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) frame width.
     */
    INT GetW( VOID ) const
    {
      return W;
    } /* End of 'GetW' function */
   
    /* Obtain height function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) frame height.
     */
    INT GetH( VOID ) const
    {
      return H;
    } /* End of 'GetH' function */

    /* Default constructor */
    frame( VOID )
    {
    } /* End of 'frame' function */

    /* Frame class constructor.
     * ARGUMENTS:
     *   - frame size:
     *     INT W, H;
     */
    frame( INT NewW, INT NewH ) : W(NewW), H(NewH)
    {
      Pixels = new DWORD[NewW * NewH];
    } /* End of 'frame' function */

    /* Frame class destructor */
    ~frame( VOID )
    {
      delete[] Pixels;
    } /* End of '~frame' function */

    /* Resize frame buffer function
     * ARGUMENTS:
     *   - frame new size:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID Resize( INT NewW, INT NewH )
    {
      W = NewW, H = NewH;

      if (Pixels != nullptr)
	delete[] Pixels;
      Pixels = new DWORD[NewW * NewH];
    } /* End of 'Resize' function */

    /* Put pixel in frame buffer function
     * ARGUMENTS:
     *   - pixel coords:
     *       INT X, Y;
     *   - pixel color:
     *       DWORD Color;
     * RETURNS: None.
     */
    VOID PutPixel( INT X, INT Y, DWORD Color )
    {
      // Clipping
      if (X < 0 || Y < 0 || Y >= H || X >= W)
	return;

      // Set pixel color
      Pixels[Y * W + X] = Color;
    } /* End of 'PutPixel' function */

    /* Draw frame buffer function.
     * ARGUMENTS:
     *   - device context:
     *       HDC hDC;
     *   - pixel coords:
     *       INT X, Y;
     * RETURNS: None.
     */
    VOID Draw( HDC hDC, INT X, INT Y )
    {
      BITMAPINFOHEADER bih;

      bih.biSize = sizeof(BITMAPINFOHEADER);
      bih.biBitCount = 32;
      bih.biPlanes = 1;
      bih.biWidth = W;
      bih.biHeight = -H;
      bih.biSizeImage = W * H * 4;
      bih.biCompression = BI_RGB;
      bih.biClrUsed = 0;
      bih.biClrImportant = 0;
      bih.biXPelsPerMeter = 30;
      bih.biYPelsPerMeter = 30;

      SetStretchBltMode(hDC, COLORONCOLOR);
      StretchDIBits(hDC, X, Y, W, H, 0, 0, W, H, Pixels, (BITMAPINFO *)&bih, DIB_RGB_COLORS, SRCCOPY);
    } /* End of 'Draw' function */

    /* Save frame buffer to tga function.
    * ARGUMENTS: None.
    * RETURNS:
    *   (BOOL) TRUE if image saved, FALSE if not.
    */
    BOOL SaveTGA( VOID )
    {
      tgaFILEHEADER fh;
      tgaFILEFOOTER ff;

      fh.IDLength = static_cast<BYTE>(strlen("Copyright (C) 2021 Computer Graphics Support Group of 30 Phys-Math Lyceum"));
      fh.ColorMapType = 0;

      fh.ImageType = 2;

      fh.X = 0;
      fh.Y = 0;
      fh.Width = W;
      fh.Height = H;
      fh.BitsPerPixel = 32;

      fh.ImageDescr = 32;

      ff.ExtensionOffset = 0;
      ff.DeveloperOffset = 0;
      CopyMemory(ff.Signature, TGA_EXT_SIGNATURE, 18);

      /* Build file name */
      /*CHAR Buf[_MAX_PATH];
      GetCurrentDirectory(sizeof(Buf), Buf);
      std::string sBuf = Buf;*/

      SYSTEMTIME st;
      GetLocalTime(&st);

      std::string path =
            "bin/rendered/" + 
            std::to_string(st.wYear) + "_" +
            std::to_string(st.wMonth) + "_" +
            std::to_string(st.wDay);
 
      std::filesystem::create_directories(path);

      std::string FileName = "DG5_RT_RES_" +
            std::to_string(st.wYear) + "_" +
            std::to_string(st.wMonth) + "_" +
            std::to_string(st.wDay) + "_" +
            std::to_string(st.wHour) + "_" +
            std::to_string(st.wMinute) + "_" +
            std::to_string(st.wSecond) + "_" +
            std::to_string(st.wMilliseconds) + "_" +
            std::to_string(rand() % 3000);

      std::fstream f(path + "/" + FileName + ".tga", std::fstream::out | std::fstream::binary);
      if (!f.is_open())
        return FALSE;

      f.write((CHAR *)&fh, sizeof(fh));
      //f.write((CHAR *)0, sizeof(WORD));
      //f.write((CHAR *)"Dan Gorlyakov, CGSG 2021", sizeof(WORD));
      //f.write((CHAR *), sizeof(WORD));
      f.write("Copyright (C) 2021 Computer Graphics Support Group of 30 Phys-Math Lyceum", fh.IDLength);
      f.write((CHAR *)Pixels, W * H * 4);
      f.write((CHAR *)&ff, sizeof(ff));

      return TRUE;
    } /* End of 'SaveTGA' function */
  }; /* End of 'frame' class */
} /* end of 'gort' namespace */

#endif /* __frame_h_ */

/* END OF 'frame.h' FILE */