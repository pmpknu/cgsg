/* FILE NAME : mth_vec3.h
 * PROGRAMMER: DG5
 * DATE      : 20.07.2021
 * PURPOSE   : Math vector module.
 */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include <cmath>
#include <cstdlib>

#include "mthdef.h"

/* Space math namespace */
namespace mth
{
  /* 3 Dimensions vector representation type */
  template<typename Type = FLT>
  class vec3
  {
  private:
    Type X, Y, Z; /* Dimensions axes */

  /* Delegating access right to other classes */
  template<class Type1> friend class matr;
  public:
    /* Void vector constructor */
    vec3( VOID )
    {
    } /* end of 'vec3' constructor */

    /* 3 axes vector constructor */
    vec3( Type X, Type Y, Type Z ) : X( X ), Y( Y ), Z( Z )
    {
    } /* end of 'vec3' constructor */

    /* 3 axes by one vector constructor */
    explicit vec3( Type A ) : X( A ), Y( A ), Z( A )
    {
    } /* end of 'vec3' constructor */

    /* Addition operator function */
    vec3 operator+( const vec3 &V ) const
    {
      return vec3<Type>(X + V.X, Y + V.Y, Z + V.Z);
    } /* end of '+' funciton */

    /* Addition operator function */
    vec3 operator+=( const vec3 &V )
    {
      return vec3<Type>(X += V.X, Y += V.Y, Z += V.Z);
    } /* end of '+' funciton */

    /* Subtraction operator function */
    vec3 operator-( VOID ) const
    {
      return vec3<Type>(-X, -Y, -Z);
    } /* end of '-' funciton */

    /* Subtraction operator function */
    vec3 operator-( const vec3 &V ) const
    {
      return vec3<Type>(X - V.X, Y - V.Y, Z - V.Z);
    } /* end of '-' funciton */

    /* Subtraction operator function */
    vec3 operator-=( vec3 &V )
    {
      return vec3<Type>(X -= V.X, Y -= V.Y, Z -= V.Z);
    } /* end of '-=' funciton */

    /* Ñomponentwise multiplication operator function */
    vec3 operator*( const vec3 &V ) const
    {
      return vec3<Type>(X * V.X, Y * V.Y, Z * V.Z);
    } /* end of '*' funciton */

    /* Vector and number multiplication operator function */
    vec3 operator*( const Type &N ) const
    {
      return vec3<Type>(X * N, Y * N, Z * N);
    } /* end of '*' funciton */

    /* Ñomponentwise multiplication operator function */
    vec3 operator*=( vec3 &V )
    {
      return vec3<Type>(X *= V.X, Y *= V.Y, Z *= V.Z);
    } /* end of '*=' funciton */

    /* Divide vector by num operator function */
    vec3 operator/( const Type &N ) const
    {
      return vec3<Type>(X / N, Y / N, Z / N);
    } /* end of '/' funciton */

    /* Scalar(dot) multiplication operator function */
    Type operator&( const vec3 &V ) const
    {
      return X * V.X + Y * V.Y + Z * V.Z;
    } /* end of '&' funciton */

    /* Vector(cross) multiplication operator function */
    vec3 operator%( const vec3 &V ) const
    {
      return vec3<Type>(Y * V.Z - V.Y * Z,
	                Z * V.X - V.Z * X,
	                X * V.Y - V.X * Y);
    } /* end of '%' funciton */

    /* Vector lenght operator function */
    Type operator!( VOID ) const
    {
      return sqrt(*this & *this);
    } /* end of '!' funciton */

    /* Vector lenght operator function */
    Type Lenght2( VOID ) const
    {
      return *this & *this;
    } /* end of 'Lenght2' funciton */

    /* Normalize vector itselffunction */
    vec3 Normalize( VOID )
    {
      DBL len = *this & *this;
 
      if (len == 1 || len == 0)
        return *this;
      len = sqrt(len);
      return *this = *this / len;
    } /* end of 'Normalize' funciton */

    /* Vector normalize function */
    vec3 Normalizing( VOID ) const
    {
      DBL len = !(*this);
 
      if (len == 1 || len == 0)
        return *this;
      return *this / len;
    } /* end of 'Normalizing' funciton */

    /* Distance between vector and point function */
    Type Distance( const vec3 &P ) const
    {
      return !(*this - P);
    } /* end of 'Distance' funciton */

    /* Zero vector set function */
    /*vec3 Zero( VOID )
    {
      return *this = vec3(0);
    } *//* end of 'Zero' funciton */

    /* Zero vector set function */
    static vec3 Zero( VOID )
    {
      return vec3(0);
    } /* end of 'Zero' funciton */


    /* Random vector from 0 to 1 function */

    vec3 Rnd0( VOID )
    {
      return *this = vec3(static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX),
	                  static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX),
	                  static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX));
    } /* end of 'Rnd0' funciton */

    /* Random vector from -1 to 1 function */
    vec3 Rnd1( VOID )
    {
      return *this = vec3(static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX * 2 - 1),
	                  static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX * 2 - 1),
	                  static_cast<Type>(static_cast<DBL>(rand()) / RAND_MAX * 2 - 1));
    } /* end of 'Rnd1' funciton */

    /* Get axes by num in arr operator function */
    Type & operator[]( const INT N )
    {
      switch (N)
      {
      case 0:
	return X;
      case 1:
	return Y;
      case 2:
	return Z;
      default:
	return vec3(0)[0];
      }
    } /* end of '[]' funciton */

    /* Get axes by num in arr operator function */
    Type operator[]( const INT N ) const
    {
      switch (N)
      {
      case 0:
	return X;
      case 1:
	return Y;
      case 2:
	return Z;
      default:
	return vec3(0)[0];
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

    /* Min bound box vector function.
     * ARGUMENTS:
     *   - vector:
     *       const vec3 &V2;
     * RETURNS:
     *   (vec3) result vector.
     */
    VOID MinBB( const vec3 &V2 )
    {
      if (X > V2.X)
	X = V2.X;
      if (Y > V2.Y)
	Y = V2.Y;
      if (Z > V2.Z)
	Z = V2.Z;
    } /* End of 'MinBB' function */

    /* Max bound box vector function.
     * ARGUMENTS:
     *   - vector:
     *       const vec3 &V2;
     * RETURNS:
     *   (vec3) result vector.
     */
    VOID MaxBB( const vec3 &V2 )
    {
      if (X < V2.X)
	X = V2.X;
      if (Y < V2.Y)
	Y = V2.Y;
      if (Z < V2.Z)
	Z = V2.Z;
    } /* End of 'MaxBB' function */
  };
}
#endif /* __mth_vec3_h_ */


/* END OF 'mth_vec3.h' FILE */