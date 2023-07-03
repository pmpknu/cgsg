/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_vec2.h
 * PURPOSE     : Animation project.
 *               Mathematics library.
 *               Math vector 2 dementions functions.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 23.07.2021.
 * NOTE        : Module namespace 'gogl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */


#ifndef __mth_vec2_h_
#define __mth_vec2_h_

#include <cmath>
#include <cstdlib>

#include "mthdef.h"

/* Space math namespace */
namespace mth
{
  /* 3 Dimensions vector representation type */
  template<typename Type = FLT>
  class vec2
  {
  private:
    Type X, Y; /* Dimensions axes */

  public:
    /* Default vector constructor */
    vec2( VOID )
    {
    } /* end of 'vec2' constructor */

    /* 2 axes vector constructor */
    vec2( Type X, Type Y ) : X( X ), Y( Y )
    {
    } /* end of 'vec2' constructor */

    /* 2 axes by one vector constructor */
    explicit vec2( Type A ) : X( A ), Y( A )
    {
    } /* end of 'vec2' constructor */

    /* Addition operator function
     * ARGUMENTS:
     *   - added vector:
     *       const vec2 &V;
     * RETURNS:
     *   (vec2) addition result.
     */
    vec2 operator+( const vec2 &V ) const
    {
      return vec2<Type>(X + V.X, Y + V.Y);
    } /* end of '+' funciton */

    /* Addition operator function
     * ARGUMENTS:
     *   - added vector:
     *       vec2 &V;
     * RETURNS:
     *   (vec2) addition result.
     */
    vec2 operator+=( vec2 &V )
    {
      return vec2<Type>(X += V.X, Y += V.Y);
    } /* end of '+' funciton */

    /* Subtraction operator function
     * ARGUMENTS:
     *   - subtrahend vector:
     *       const vec2 &V;
     * RETURNS:
     *   (vec2) subtraction result.
     */
    vec2 operator-( const vec2 &V ) const
    {
      return vec2<Type>(X - V.X, Y - V.Y);
    } /* end of '-' funciton */

    /* Subtraction operator function
     * ARGUMENTS:
     *   - subtrahend vector:
     *       vec2 &V;
     * RETURNS:
     *   (vec2) subtraction result.
     */
    vec2 operator-=( vec2 &V )
    {
      return vec2<Type>(X -= V.X, Y -= V.Y);
    } /* end of '-=' funciton */

    /* Ñomponentwise multiplication operator function
     * ARGUMENTS:
     *   - factor vector:
     *       const vec2 &V;
     * RETURNS:
     *   (vec2) multiplication result.
     */
    vec2 operator*( const vec2 &V ) const
    {
      return vec2<Type>(X * V.X, Y * V.Y);
    } /* end of '*' funciton */

    /* Vector and number multiplication operator function
     * ARGUMENTS:
     *   - factor number:
     *       const Type &N;
     * RETURNS:
     *   (vec2) multiplication result.
     */
    vec2 operator*( const Type &N ) const
    {
      return vec2<Type>(X * N, Y * N);
    } /* end of '*' funciton */

    /* Ñomponentwise multiplication operator function
     * ARGUMENTS:
     *   - factor vector:
     *       vec2 &V;
     * RETURNS:
     *   (vec2) multiplication result.
     */
    vec2 operator*=( vec2 &V )
    {
      return vec2<Type>(X *= V.X, Y *= V.Y);
    } /* end of '*=' funciton */

    /* Divide vector by num operator function
     * ARGUMENTS:
     *   - divider num:
     *       const Type &N;
     * RETURNS:
     *   (vec2) devidition result.
     */
    vec2 operator/( const Type &N ) const
    {
      return vec2<Type>(X / N, Y / N);
    } /* end of '/' funciton */

    /* Scalar(dot) multiplication operator function
     * ARGUMENTS:
     *   - second vector:
     *       const vec2 &V;
     * RETURNS:
     *   (Type) scalar result.
     */
    Type operator&( const vec2 &V ) const
    {
      return X * V.X + Y * V.Y;
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
     *   (vec2) normalized vector.
     */
    vec2 Normalize( VOID )
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
     *   (vec2) normalized vector.
     */
    vec2 Normalizing( VOID ) const
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
    Type Distance( const vec2 &P ) const
    {
      return !(*this - P);
    } /* end of 'Distance' funciton */

    /* Return zero vector function
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec2) result vector.
     */
    static vec2 Zero( VOID )
    {
      return vec2(0);
    } /* end of 'Zero' funciton */

    /* Random vector from 0 to 1 function
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 Rnd0( VOID )
    {
      return *this = vec2(static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX),
	                  static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX));
    } /* end of 'Rnd0' funciton */

    /* Random vector from -1 to 1 function
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 Rnd1( VOID )
    {
      return *this = vec2(static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX * 2 - 1),
	                  static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX * 2 - 1));
    } /* end of 'Rnd1' funciton */

    /* Get axes by num in arr operator function
     * ARGUMENTS:
     *   - num in vec array:
     *       const INT N;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 & operator[]( const INT N )
    {
      switch (N)
      {
      case 0:
	return X;
      case 1:
	return Y;
      default:
	return nullptr;
      }
    } /* end of '[]' funciton */

    /* Get axes by num in arr operator function
     * ARGUMENTS:
     *   - num in vec array:
     *       const INT N;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 operator[]( const INT N ) const
    {
      switch (N)
      {
      case 0:
        return X;
      case 1:
        return Y;
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
#endif /* __mth_vec2_h_ */

/* END OF 'mth_vec2.h' FILE */