/* FILE NAME : mth.h
 * PROGRAMMER: DG5
 * DATE      : 20.07.2021
 * PURPOSE   : Common math module.
 */

#ifndef __mth_h_
#define __mth_h_

#include "mth_vec2.h"
#include "mth_vec3.h"
#include "mth_vec4.h"
#include "mth_matr.h"
#include "mth_camera.h"
#include "mth_ray.h"

typedef mth::vec2<FLT> vec2;
typedef mth::vec3<FLT> vec3;
typedef mth::vec4<FLT> vec4;
typedef mth::matr<FLT> matr;
typedef mth::ray<FLT> ray;

#endif /* __mth_h_ */

/* END OF 'mth.h' FILE */