/* FILE NAME : mth_matr.h
 * PROGRAMMER: DG5
 * DATE      : 01.08.2021
 * PURPOSE   : Math matrix module.
 */

#ifndef __mth_matr_h_
#define __mth_matr_h_

#include "mthdef.h"

/* Space math namespace */
namespace mth
{
  /* Matrix representation type */
  template<typename Type = FLT>
  class matr
  {
  private:
    Type M[4][4];
    mutable Type InvA[4][4];
    mutable bool IsInverseEvaluated;

    /* Calculate inversed matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (matr) inversed matrix.
     */
    matr EvaluateInverseMatrix( VOID ) const
    {
      if (IsInverseEvaluated)
        return InvA;
      IsInverseEvaluated = TRUE;

      Type det = M.Determ();

      /* build adjoint matrix */
      InvA[0][0] =
        Determ3x3(M[1][1], M[1][2], M[1][3],
                      M[2][1], M[2][2], M[2][3],
                      M[3][1], M[3][2], M[3][3]);
      InvA[1][0] =
        -Determ3x3(M[1][0], M[1][2], M[1][3],
                       M[2][0], M[2][2], M[2][3],
                       M[3][0], M[3][2], M[3][3]);
      InvA[2][0] =
        Determ3x3(M[1][0], M[1][1], M[1][3],
                      M[2][0], M[2][1], M[2][3],
                      M[3][0], M[3][1], M[3][3]);
      InvA[3][0] =
        -Determ3x3(M[1][0], M[1][1], M[1][2],
                       M[2][0], M[2][1], M[2][2],
                       M[3][0], M[3][1], M[3][2]);

      InvA[0][1] =
        -Determ3x3(M[0][1], M[0][2], M[0][3],
                       M[2][1], M[2][2], M[2][3],
                       M[3][1], M[3][2], M[3][3]);
      InvA[1][1] =
        Determ3x3(M[0][0], M[0][2], M[0][3],
                      M[2][0], M[2][2], M[2][3],
                      M[3][0], M[3][2], M[3][3]);
      InvA[2][1] =
        -Determ3x3(M[0][0], M[0][1], M[0][3],
                       M[2][0], M[2][1], M[2][3],
                       M[3][0], M[3][1], M[3][3]);
      InvA[3][1] =
        Determ3x3(M[0][0], M[0][1], M[0][2],
                      M[2][0], M[2][1], M[2][2],
                      M[3][0], M[3][1], M[3][2]);

      InvA[0][2] =
        Determ3x3(M[0][1], M[0][2], M[0][3],
                      M[1][1], M[1][2], M[1][3],
                      M[3][1], M[3][2], M[3][3]);
      InvA[1][2] =
        -Determ3x3(M[0][0], M[0][2], M[0][3],
                       M[1][0], M[1][2], M[1][3],
                       M[3][0], M[3][2], M[3][3]);
      InvA[2][2] =
        Determ3x3(M[0][0], M[0][1], M[0][3],
                      M[1][0], M[1][1], M[1][3],
                      M[3][0], M[3][1], M[3][3]);
      InvA[3][2] =
        -Determ3x3(M[0][0], M[0][1], M[0][2],
                       M[1][0], M[1][1], M[1][2],
                       M[3][0], M[3][1], M[3][2]);

      InvA[0][3] =
        -Determ3x3(M[0][1], M[0][2], M[0][3],
                       M[1][1], M[1][2], M[1][3],
                       M[2][1], M[2][2], M[2][3]);
      InvA[1][3] =
        Determ3x3(M[0][0], M[0][2], M[0][3],
                      M[1][0], M[1][2], M[1][3],
                      M[2][0], M[2][2], M[2][3]);
      InvA[2][3] =
        -Determ3x3(M[0][0], M[0][1], M[0][3],
                       M[1][0], M[1][1], M[1][3],
                       M[2][0], M[2][1], M[2][3]);
      InvA[3][3] =
        Determ3x3(M[0][0], M[0][1], M[0][2],
                      M[1][0], M[1][1], M[1][2],
                      M[2][0], M[2][1], M[2][2]);

      /* devide on determinator */
      InvA[0][0] /= det;
      InvA[1][0] /= det;
      InvA[2][0] /= det;
      InvA[3][0] /= det;

      InvA[0][1] /= det;
      InvA[1][1] /= det;
      InvA[2][1] /= det;
      InvA[3][1] /= det;

      InvA[0][2] /= det;
      InvA[1][2] /= det;
      InvA[2][2] /= det;
      InvA[3][2] /= det;

      InvA[0][3] /= det;
      InvA[1][3] /= det;
      InvA[2][3] /= det;
      InvA[3][3] /= det;
    } /* End of 'EvaluateInverseMatrix' function */
  public:

    matr( VOID ) : IsInverseEvaluated(FALSE)
    {
    }

    matr( Type A00, Type A01, Type A02, Type A03,
      Type A10, Type A11, Type A12, Type A13,
      Type A20, Type A21, Type A22, Type A23,
      Type A30, Type A31, Type A32, Type A33 ) : IsInverseEvaluated(FALSE)
    {
      M[0][0] = A00, M[0][1] = A01, M[0][2] = A02, M[0][3] = A03;
      M[1][0] = A10, M[1][1] = A11, M[1][2] = A12, M[1][3] = A13;
      M[2][0] = A20, M[2][1] = A21, M[2][2] = A22, M[2][3] = A23;
      M[3][0] = A30, M[3][1] = A31, M[3][2] = A32, M[3][3] = A33;
    }

    matr( const vec3<Type> &A00A01A02, const Type &A03,
          const vec3<Type> &A10A11A12, const Type &A13,
          const vec3<Type> &A20A21A22, const Type &A23,
          const vec3<Type> &A30A31A32, const Type &A33 ) : IsInverseEvaluated(FALSE)
    {
      M[0][0] = A00A01A02[0], M[0][1] = A00A01A02[1], M[0][2] = A00A01A02[2], M[0][3] = A03;
      M[1][0] = A10A11A12[0], M[1][1] = A10A11A12[1], M[1][2] = A10A11A12[2], M[1][3] = A13;
      M[2][0] = A20A21A22[0], M[2][1] = A20A21A22[1], M[2][2] = A20A21A22[2], M[2][3] = A23;
      M[3][0] = A30A31A32[0], M[3][1] = A30A31A32[1], M[3][2] = A30A31A32[2], M[3][3] = A33;
    }

    matr( Type A[4][4] ) : IsInverseEvaluated(FALSE)
    {
      M[0][0] = A[0][0], M[0][1] = A[0][0], M[0][2] = A[0][0], M[0][3] = A[0][0];
      M[1][0] = A[1][0], M[1][1] = A[1][0], M[1][2] = A[1][0], M[1][3] = A[1][0];
      M[2][0] = A[2][0], M[2][1] = A[2][0], M[2][2] = A[2][0], M[2][3] = A[2][0];
      M[3][0] = A[3][0], M[3][1] = A[3][0], M[3][2] = A[3][0], M[3][3] = A[3][0];
    }

    matr operator*( const matr &M ) const
    {
      matr r;

      for (INT i = 0; i < 4; i++)
        for (INT j = 0, k; j < 4; j++)
          for (r.M[i][j] = 0, k = 0; k < 4; k++)
            r.M[i][j] += this->M[i][k] * M.M[k][j];
      return r;
    }

    // Morphing
    /* Transform normal function.
     * ARGUMENTS:
     *   - point to be transformed:
     *       vec3 V;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3<Type> TransformNormal( const vec3<Type> &N ) const
    {
      EvaluateInverseMatrix();
      return vec3<Type>(N.X * InvA[0][0] + N.Y * InvA[0][1] + N.Z * InvA[0][2],
                     N.X * InvA[1][0] + N.Y * InvA[1][1] + N.Z * InvA[1][2],
                     N.X * InvA[2][0] + N.Y * InvA[2][1] + N.Z * InvA[2][2]);
    } /* End of 'TransformNormal' function */

    /* Transform point position.
     * ARGUMENTS:
     *   - point to be transformed:
     *       vec3 V;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3<Type> PointTransform( const vec3<Type> &V ) const
    {
      return vec3<Type>(V.X * this->M[0][0] + V.Y * this->M[1][0] + V.Z * this->M[2][0] + this->M[3][0],
                        V.X * this->M[0][1] + V.Y * this->M[1][1] + V.Z * this->M[2][1] + this->M[3][1],
                        V.X * this->M[0][2] + V.Y * this->M[1][2] + V.Z * this->M[2][2] + this->M[3][2]);
    } /* End of 'PointTransform' function */

    /* Transform vector position.
     * ARGUMENTS:
     *   - vector to be transformed:
     *       vec3 &V;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3<Type> VectorTransform( const vec3<Type> &V ) const
    {
      return vec3<Type>(V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0],
                        V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1],
                        V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2]);
    } /* End of 'VectorTransform' function */

    /* Multiply matrix and vector.
     * ARGUMENTS:
     *   - multiplyong vector:
     *       vec3 &V;
     * RETURNS:
     *   (vec3) result matrix.
     */
    vec3<Type> operator*( const vec3<Type> &V ) const
    {
      Type w = V.X * this->M[0][3] + V.Y * this->M[1][3] + V.Z * this->M[2][3] + this->M[3][3];

      return vec3<Type>((V.X * this->M[0][0] + V.Y * this->M[1][0] + V.Z * this->M[2][0] + this->M[3][0]) / w,
                  (V.X * this->M[0][1] + V.Y * this->M[1][1] + V.Z * this->M[2][1] + this->M[3][1]) / w,
                  (V.X * this->M[0][2] + V.Y * this->M[1][2] + V.Z * this->M[2][2] + this->M[3][2]) / w);
    } /* End of 'operator *' function */

    /* Get identity matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (matr) result matrix.
     */
    static matr Identity( VOID )
    {
      /* Unit matrix */
      return matr(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1);
    } /* End of 'Identity' function */

    /* Translate matrix function.
     * ARGUMENTS:
     *   - vector to matrix:
     *       VEC &T;
     * RETURNS:
     *   (matr) result matrix.
     */
    static matr Translate( const vec3<Type> &T )
    {
      return matr(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  T.X, T.Y, T.Z, 1);
    } /* End of 'Translate' function */

    /* rotating and scaling */

    /* Matrix scaling function.
     * ARGUMENTS:
     *   - vector to matrix:
     *       VEC S;
     * RETURNS:
     *   (MATR) result matrix.
     */
    static matr Scale( const vec3<Type> &S )
    {
      return matr(S.X, 0, 0, 0,
                  0, S.Y, 0, 0,
                  0, 0, S.Z, 0,
                  0, 0, 0, 1);
    } /* End of 'Scale' function */

    /* Rotate matrix function.
     * ARGUMENTS:
     *   - angle in degrees:
     *       Type AngleInDegree;
     *   - vector to matrix:
     *       vec3 &T;
     * RETURNS:
     *   (matr) result matrix.
     */
    static matr Rotate( const vec3<Type> &V, const Type AngleInDegree )
    {
      Type a = Degree2Radian(AngleInDegree), c = cos(a), s = sin(a);
      vec3<Type> A = V.Normalizing();

      return matr(c + A.X * A.X * (1 - c), A.X * A.Y * (1 - c) + A.Z * s, A.X * A.Z * (1 - c) - A.Y * s, 0,
                  A.Y * A.X * (1 - c) - A.Z * s, c + A.Y * A.Y * (1 - c), A.Y * A.Z * (1 - c) + A.X * s, 0,
                  A.Z * A.X * (1 - c) + A.Y * s, A.Z * A.Y * (1 - c) - A.X * s, c + A.Z * A.Z * (1 - c), 0,
                  0, 0, 0, 1);
    } /* End of 'Rotate' function */

    /* Rotate matrix by X axis function.
     * ARGUMENTS:
     *   - angle in degrees:
     *       Type AngleInDegree;
     * RETURNS:
     *   (matr) result matrix.
     */
    static matr RotateX( Type AngleInDegree )
    {
      Type a = Degree2Radian(AngleInDegree), c = cos(a), s = sin(a);

      return matr(1, 0, 0, 0,
                  0, c, s, 0,
                  0, -s, c, 0,
                  0, 0, 0, 1);
    } /* End of 'MatrRotateX' function */

    /* Rotate matrix by Y axis function.
     * ARGUMENTS:
     *   - angle in degrees:
     *       Type AngleInDegree;
     * RETURNS:
     *   (matr) result matrix.
     */
    static matr RotateY( Type AngleInDegree )
    {
      Type a = Degree2Radian(AngleInDegree), c = cos(a), s = sin(a);

      return matr(c, 0, -s, 0,
                  0, 1, 0, 0,
                  s, 0, c, 0,
                  0, 0, 0, 1);
    } /* End of 'RotateY' function */

    /* Rotate matrix by Z axis function.
     * ARGUMENTS:
     *   - angle in degrees:
     *       Type AngleInDegree;
     * RETURNS:
     *   (matr) result matrix.
     */
    static matr RotateZ( Type AngleInDegree )
    {
      Type a = Degree2Radian(AngleInDegree), c = cos(a), s = sin(a);

      return matr(c, s, 0, 0,
                  -s, c, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1);
    } /* End of 'RotateZ' function */

    /* Calculate matrix determ 3x3 function.
     * ARGUMENTS:
     *   - Elements to put in matrix:
     *       FLT A11, A21, A31,
     *           A12, A22, A32,
     *           A13, A23, A33;
     * RETURNS:
     *   (Type) result determ.
     */
    static Type Determ3x3( Type A11, Type A12, Type A13,
                           Type A21, Type A22, Type A23,
                           Type A31, Type A32, Type A33)
    {
      return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
             A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
    } /* End of 'Determ3x3' function */

    /* Calculate matrix determ function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) result determ.
     */
    Type Determ( VOID )
    {
      return
        M[0][0] * Determ3x3(M[1][1], M[1][2], M[1][3],
                            M[2][1], M[2][2], M[2][3],
                            M[3][1], M[3][2], M[3][3]) -
        M[0][1] * Determ3x3(M[1][0], M[1][2], M[1][3],
                            M[2][0], M[2][2], M[2][3],
                            M[3][0], M[3][2], M[3][3]) +
        M[0][2] * Determ3x3(M[1][0], M[1][1], M[1][3],
                            M[2][0], M[2][1], M[2][3],
                            M[3][0], M[3][1], M[3][3]) -
        M[0][3] * Determ3x3(M[1][0], M[1][1], M[1][2],
                            M[2][0], M[2][1], M[2][2],
                            M[3][0], M[3][1], M[3][2]);
    } /* End of 'Determ' function */

    /* Obtain matr first element pointer function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (const Type *) pointer to first matrix element.
     */
    operator const Type *( VOID ) const
    {
      return M[0];
    } /* end of 'operator const Type *' funciton */

    /* Matrix look at viwer setup function.
     * ARGUMENTS:
     *   - Positoin:
     *      vec3 Loc;
     *   - Where we looking for:
     *      vec3 At;
     *   - Direction to up:
     *      vec3 Up1;
     * RETURNS:
     *   (matr) result matrix.
     */
    static matr View( vec3<Type> Loc, vec3<Type> At, vec3<Type> Up1 )
    {
      vec3<Type>
        D = vec3<Type>(At - Loc).Normalizing(), /* Direction */
        R = vec3<Type>(D % Up1).Normalizing(),  /* Up */
        U = R % D;                              /* Right */

      return matr(R.X, U.X, -D.X, 0,
                  R.Y, U.Y, -D.Y, 0,
                  R.Z, U.Z, -D.Z, 0,
                  -(Loc & R), -(Loc & U), Loc & D, 1);
    } /* End of 'View' function */

    /* Normalized device coordinates function.
     * ARGUMENTS:
     *   - Screen factors:
     *      Left and Right:
     *        Type L, R;
     *      Bottom and Top:
     *        Type B, T;
     *      Near and Far:
     *        Type N, F;
     * RETURNS:
     *   (matr) result matrix.
     */
    static matr Frustum( Type L, Type R, Type B, Type T, Type N, Type F )
    {
        return matr(2 * N / (R - L), 0, 0, 0,
                    0, 2 * N / (T - B), 0, 0,
                    (R + L) / (R - L), (T + B) / (T - B), -(F + N) / (F - N), -1,
                    0, 0, -2 * N * F / (F - N), 0);
    } /* End of 'Frustum' function */

    /* Ortho projection matrix function.
     * ARGUMENTS:
     *   - Screen factors:
     *      Left and Right:
     *        Type L, R;
     *      Bottom and Top:
     *        Type B, T;
     *      Near and Far:
     *        Type N, F;
     * RETURNS:
     *   (matr) viewer matrix.
     */
    matr Ortho( Type L, Type R, Type B, Type T, Type N, Type F )
    {
      return matr(2 / (R - L),                 0,                             0,                0,
                  0,                           2 / (T - B),                   0,                0,
                  0,                           0,                            -2 / (F - N),      0,
                 -(R + L) / (R - L),          -(T + B) / (T - B),          -(N + F) / (F - N), 1);
    } /* End of 'Ortho' function */
  };
}
#endif /* __mth_matr_h_ */

/* END OF 'mth_matr.h' FILE */