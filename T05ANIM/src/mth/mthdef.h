/* FILE NAME : mthdef.h
 * PROGRAMMER: DG5
 * DATE      : 20.07.2021
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
  const DBL PI = 3.14159265358979323846;

  template<typename Type>
  Type Degree2Radian( Type A )
  {
    return ((A) * (PI / 180.0));
  }

  // Forward declaration
  template<typename type> class vec2;
  template<typename type> class vec3;
  template<typename type> class vec4;
  template<typename type> class matr;
  template<typename type> class camera;
  template<typename type> class ray;
}

#endif /* __mthdef_h_ */

/* END OF 'mthdef.h' FILE */