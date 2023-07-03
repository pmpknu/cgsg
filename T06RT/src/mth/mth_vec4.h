/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_vec4.h
 * PURPOSE     : Animation project.
 *               Mathematics library.
 *               Math vector 2 dementions functions.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 23.07.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */


#ifndef __mth_vec4_h_
#define __mth_vec4_h_

#include <cmath>
#include <cstdlib>

#include "mthdef.h"

/* Space math namespace */
namespace mth
{
  /* 3 Dimensions vector representation type */
  template<typename Type = FLT>
  class vec4
  {
  private:
    Type X, Y, Z, A; /* Dimensions axes */

  public:
    /* Default vector constructor */
    vec4( VOID )
    {
    } /* end of 'vec4' constructor */

    /* 2 axes vector constructor */
    vec4( Type X, Type Y, Type Z, Type A ) : X( X ), Y( Y ), Z( Z ), A( A )
    {
    } /* end of 'vec4' constructor */

    /* 2 axes by one vector constructor */
    explicit vec4( Type A ) : X( A ), Y( A ), Z( A ), A( A )
    {
    } /* end of 'vec4' constructor */

    /* Addition operator function
     * ARGUMENTS:
     *   - added vector:
     *       const vec4 &V;
     * RETURNS:
     *   (vec4) addition result.
     */
    vec4 operator+( const vec4 &V ) const
    {
      return vec4<Type>(X + V.X, Y + V.Y, Z + V.Z, A + V.A);
    } /* end of '+' funciton */

    /* Addition operator function
     * ARGUMENTS:
     *   - added vector:
     *       vec4 &V;
     * RETURNS:
     *   (vec4) addition result.
     */
    vec4 operator+=( vec4 &V )
    {
      return vec4<Type>(X += V.X, Y += V.Y, Z += V.Z, A += V.A);
    } /* end of '+' funciton */

    /* Subtraction operator function
     * ARGUMENTS:
     *   - subtrahend vector:
     *       const vec4 &V;
     * RETURNS:
     *   (vec4) subtraction result.
     */
    vec4 operator-( const vec4 &V ) const
    {
      return vec4<Type>(X - V.X, Y - V.Y, Z - V.Z, A - V.A);
    } /* end of '-' funciton */

    /* Subtraction operator function
     * ARGUMENTS:
     *   - subtrahend vector:
     *       vec4 &V;
     * RETURNS:
     *   (vec4) subtraction result.
     */
    vec4 operator-=( vec4 &V )
    {
      return vec4<Type>(X -= V.X, Y -= V.Y, Z -= V.Z, A -= V.A);
    } /* end of '-=' funciton */

    /* Ñomponentwise multiplication operator function
     * ARGUMENTS:
     *   - factor vector:
     *       const vec4 &V;
     * RETURNS:
     *   (vec4) multiplication result.
     */
    vec4 operator*( const vec4 &V ) const
    {
      return vec4<Type>(X * V.X, Y * V.Y, Z * V.Z, A * V.A);
    } /* end of '*' funciton */

    /* Vector and number multiplication operator function
     * ARGUMENTS:
     *   - factor number:
     *       const Type &N;
     * RETURNS:
     *   (vec4) multiplication result.
     */
    vec4 operator*( const Type &N ) const
    {
      return vec4<Type>(X * N, Y * N, Z * N, A * N);
    } /* end of '*' funciton */

    /* Ñomponentwise multiplication operator function
     * ARGUMENTS:
     *   - factor vector:
     *       vec4 &V;
     * RETURNS:
     *   (vec4) multiplication result.
     */
    vec4 operator*=( vec4 &V )
    {
      return vec4<Type>(X *= V.X, Y *= V.Y, Z *= V.Z, A *= V.A);
    } /* end of '*=' funciton */

    /* Divide vector by num operator function
     * ARGUMENTS:
     *   - divider num:
     *       const Type &N;
     * RETURNS:
     *   (vec4) devidition result.
     */
    vec4 operator/( const Type &N ) const
    {
      return vec4<Type>(X / N, Y / N, Z / N, A / N);
    } /* end of '/' funciton */

    /* Scalar(dot) multiplication operator function
     * ARGUMENTS:
     *   - second vector:
     *       const vec4 &V;
     * RETURNS:
     *   (Type) scalar result.
     */
    Type operator&( const vec4 &V ) const
    {
      return X * V.X + Y * V.Y + Z * V.Z + A * V.A;
    } /* end of '&' funciton */

    /* Vector lenght operator function
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) vector lenght.
     */
    Type operator!( VOID ) const
    {
      return sqrt(*this & *this);
    } /* end of '!' funciton */

    /* Vector lenght operator function
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) vector lenght.
     */
    Type Lenght2( VOID ) const
    {
      return *this & *this;
    } /* end of 'Lenght2' funciton */

    /* Normalize vector itselffunction
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) normalized vector.
     */
    vec4 Normalize( VOID )
    {
      DBL len = *this & *this;
 
      if (len == 1 || len == 0)
        return *this;
      len = sqrt(len);
      return *this = *this / len;
    } /* end of 'Normalize' funciton */

    /* Vector normalize function
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) normalized vector.
     */
    vec4 Normalizing( VOID ) const
    {
      DBL len = !(*this);
 
      if (len == 1 || len == 0)
        return *this;
      return *this / len;
    } /* end of 'Normalizing' funciton */

    /* Distance between vector and point function
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) result distance.
     */
    Type Distance( const vec4 &P ) const
    {
      return !(*this - P);
    } /* end of 'Distance' funciton */

    /* Return zero vector function
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) result vector.
     */
    static vec4 Zero( VOID )
    {
      return vec4(0);
    } /* end of 'Zero' funciton */

    /* Random vector from 0 to 1 function
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) result vector.
     */
    static vec4 Rnd0( VOID )
    {
      return vec4(static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX),
        static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX),
        static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX),
        static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX));
    } /* end of 'Rnd0' funciton */

    /* Random vector from 0 to 1 function
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) result vector.
     * ???/
    vec4 Rnd0( VOID )
    {
      return *this = vec4(static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX),
        static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX),
        static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX),
        static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX));
    } /* end of 'Rnd0' funciton */

    /* Random vector from -1 to 1 function
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 Rnd1( VOID )
    {
      return *this = vec4(static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX * 2 - 1),
                          static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX * 2 - 1),
                          static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX * 2 - 1),
                          static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX * 2 - 1));
    } /* end of 'Rnd1' funciton */

    /* Get axes by num in arr operator function
     * ARGUMENTS:
     *   - num in vec array:
     *       const INT N;
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 & operator[]( const INT N )
    {
      switch (N)
      {
      case 0:
	return X;
      case 1:
	return Y;
      case 2:
	return Z;
      case 3:
	return A;
      default:
	return nullptr;
      }
    } /* end of '[]' funciton */

    /* Get axes by num in arr operator function
     * ARGUMENTS:
     *   - num in vec array:
     *       const INT N;
     * RETURNS:
     *   (vec4) result vector.
     */
    vec4 operator[]( const INT N ) const
    {
      switch (N)
      {
      case 0:
        return X;
      case 1:
        return Y;
      case 2:
	return Z;
      case 3:
	return A;
      default:
	return nullptr;
      }
    } /* end of '[]' funciton */

    /* Obtain vector first element pointer function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (const Type *) pointer to X coordinate.
     */
    operator const Type *( VOID ) const
    {
      return &X;
    } /* end of 'operator const Type *' funciton */
  };
}
#endif /* __mth_vec4_h_ */

/* END OF 'mth_vec4.h' FILE */