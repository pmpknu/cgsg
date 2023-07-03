/* FILE NAME : anim.cpp
 * PROGRAMMER: DG5
 * DATE      : 22.07.2021
 * PURPOSE   : Animation method implementation module.
 */

#include "anim.h"

gogl::anim gogl::anim::Instance;

//CALLBACKS

/* Initialization callback function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::anim::Init( VOID )
{
} /* End of 'gogl::anim::Init' function */

/* Deinitialization callback function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::anim::Close( VOID )
{
} /* End of 'gogl::anim::Close' function */

/* Animation resize declaration context callback function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::anim::Resize( VOID )
{
  render::Resize();
} /* End of 'gogl::anim::Resize' function */

/* Animation timer callback function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::anim::Timer( VOID )
{
  if (Keys['W'])
    SetWindowText(win::hWnd, "kal naklal");

  if (Keys['R'])
    shader_manager::Update();

  Render();
  CopyFrame();
} /* End of 'gogl::anim::Timer' function */

/* Animation activate callback function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::anim::Activate( VOID )
{
} /* End of 'gogl::anim::Activate' function */

/* During idle cpu callback function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID gogl::anim::Idle( VOID )
{
  Render();
  CopyFrame();
} /* End of 'gogl::anim::Idle' function */

/* Errase callback function.
 * ARGUMENTS:
 *   - device context:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID gogl::anim::Erase( HDC hDC )
{
} /* End of 'gogl::anim::Erase' function */

/* Paint callback function.
 * ARGUMENTS:
 *   - device context:
 *       HDC hDC;
 * RETURNS: None.
 */
VOID gogl::anim::Paint( HDC hDC )
{
} /* End of 'gogl::anim::Paint' function */


/* Add unit to scene operator.
 * ARGUMENTS:
 *   - name of the unit:
 *       const std::string &Name;
 * RETURNS:
 *   (scene &) Self-reference.
 */
gogl::scene & gogl::scene::operator<<( const std::string &Name )
{
  anim &Ani = anim::Get();
  if (Ani.UnitNames.find(Name) != Ani.UnitNames.end())
  {
    Units << Ani.UnitNames[Name]();
  }
  return *this;
} /* End of '<<' function */

/* END OF 'anim.cpp' FILE */