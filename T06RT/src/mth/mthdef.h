/* FILE NAME : mthdef.h
 * PROGRAMMER: DG5
 * DATE      : 01.08.2021
 * PURPOSE   : Common declaration module.
 */

#ifndef __mthdef_h_
#define __mthdef_h_

#include <commondf.h>

typedef DOUBLE DBL;
typedef FLOAT FLT;

//template<typename Type> class vec3;
//??template<typename Type> class matr;

/* Space math namespace */
namespace mth
{
  // Forward declaration
  template<typename type> class vec2;
  template<typename type> class vec3;
  template<typename type> class vec4;
  template<typename type> class matr;
  template<typename type> class camera;
  template<typename type> class ray;

  const DBL PI = 3.14159265358979323846;

  template<typename Type>
  Type Degree2Radian( Type A )
  {
    return ((A) * (PI / 180.0));
  }

  /* Clamp between to arguments function.
   * ARGUMENTS:
   *   - variable value:
   *       const Type &Val;
   *   - lower and upper bounds:
   *       const Type &Lo, &Up;
   * RETURNS:
   *   (Type) result clamped meaning.
   */
  template<typename type>
  static type Clamp( const type &Val, const type &Lo, const type &Up )
  {
    if (Val < Lo)
      return Lo;
    if (Val > Up)
      return Up;
    return Val;
  } /* End of 'ToRGB' function */

  /* Make rgb from vec3 function.
   * ARGUMENTS:
   *   - vector:
   *       const vec3 &V2;
   * RETURNS:
   *   (DWORD) result color.
   */
  template<typename type>
  static DWORD toRGB( const vec3<type> &V )
  {
    DWORD Color = 0;
  
    Color |= (DWORD)Clamp(V[0] * 255, 0.0, 255.0);
    Color |= (DWORD)Clamp(V[1] * 255, 0.0, 255.0) << 8;
    Color |= (DWORD)Clamp(V[2] * 255, 0.0, 255.0) << 16;
  
    return Color;
  } /* End of 'ToRGB' function */

  /* Make rgb from vec3 function.
   * ARGUMENTS:
   *   - vars to be swapped:
   *       type &A, &B;
   * RETURNS: None.
   */
  template<typename type>
  static VOID Swap( type &A, type &B )
  {
    type tmp = A;

    A = B;
    B = tmp;
  } /* End of 'ToRGB' function */
}

#endif /* __mthdef_h_ */

/* END OF 'mthdef.h' FILE */