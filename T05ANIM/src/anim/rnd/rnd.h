/* FILE NAME : rnd.h
 * PROGRAMMER: DG5
 * DATE      : 21.07.2021
 * PURPOSE   : Render handle module.
 */

#ifndef __rnd_h_
#define __rnd_h_

#include "../../mth/mthdef.h"

#include "prim.h"
#include "prims.h"
#include "shd.h"
#include "mtl.h"

/* Space gogl namespace */
namespace gogl
{
  /* Window class */
  class render : public prim_manager, public prims_manager, public shader_manager, public material_manager, public texture_manager
  {
  private:
    HWND &hWnd;
    INT &FrameW, &FrameH;

    HDC hDC;
    HGLRC hGLRC;

  public:
    mth::camera<FLT> cam;

    render( HWND &hWnd, INT &W, INT &H );

    ~render( VOID );

    /* Resize declaration context function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID );

    /* Frame rander copy function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CopyFrame( VOID );

    /* Start rendering function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Start( VOID );

    /* End rendering function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID End( VOID );

    /* Debug output function.
     * ARGUMENTS:
     *   - source APi or device:
     *      UINT Source;
     *   - error type:
     *      UINT Type;
     *   - error message id:
     *      UINT Id,
     *   - message severity:
     *      UINT severity,
     *   - message text length:
     *      INT Length,
     *   - message text:
     *      CHAR *Message,
     *   - user addon parameters pointer:
     *      VOID *UserParam;
     * RETURNS: None.
     */
    static VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
      INT Length, const CHAR *Message, const VOID *UserParam );

    /* Draw render primitive function.
     * ARGUMENTS:
     *   - primitive:
     *      prim *Pr;
     *   - matrix:
     *      MATR World;
     * RETURNS: None.
     */
    VOID PrimDraw( prim *Pr, matr World );

    /* Draw render primitive function.
     * ARGUMENTS:
     *   - primitive:
     *      prim *Pr;
     *   - matrix:
     *      MATR World;
     * RETURNS: None.
     */
    VOID PrimsDraw( prims *Prs, matr World );

    /* Load primitive from '*.OBJ' file function.
     * ARGUMENTS:
     *   - '*.OBJ' file name:
     *       CHAR *FileName;
     *   - model material:
     *       material *Mtl;
     * RETURNS:
     *   (prim *) loaded model.
     */
    prim * LoadOBJ( CHAR *FileName, material *Mtl );
  };
}

#endif /* __rnd_h_ */

/* END OF 'rnd.h' FILE */