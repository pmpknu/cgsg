/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rt_def.h
 * PURPOSE     : Ray tracing project.
 *               Ray tracing handle module.
 * PROGRAMMER  : Dan Gorlyakov.
 * LAST UPDATE : 02.08.2021.
 * NOTE        : Module namespace 'gort'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rt_def_h_
#define __rt_def_h_

#include <vector>

#include "../def.h"

/* Space gort namespace */
namespace gort
{
  // Forward declaration
  class shape;

  const DBL Threshold = 1e-9;  // to correct dbl error

  /* Intersection class */
  class intr
  {
  public:
    DBL T;  // distance to intersection
    shape *Sh;  // shape pointer

    vec3 N;    // Shape normal
    BOOL IsN;  // Is shape normal evaluated

    vec3 P;    // Point of intersection
    BOOL IsP;  // Is point of intersection evaluated

    // addons
    INT I[5];
    DBL D[5];

    /* Default constructor */
    intr( VOID ) : Sh(nullptr), IsN(FALSE), IsP(FALSE)
    {
    } /* End of 'intr' funciton */
  }; /* End of 'intr' class */

  /* Surface class */
  class surface
  {
  public:
    vec3 Ka {0.1}, Kd {0.8}, Ks {0.2}; // ambient, diffuse, specular
    DBL Ph {1};          // Bui Tong Phong coefficient
    DBL Kr {0.1}, Kt {0.1};      // reflected, transmitted

    /* Default constructor */
    surface( VOID )
    {
    } /*End of 'surface' function */

    surface( const vec3 &NewKa, const vec3 &NewKd, const vec3 &NewKs, const DBL &NewPh, const DBL &NewKr, const DBL &NewKt )
      : Ka(NewKa), Kd(NewKd), Ks(NewKs), Ph(NewPh), Kr(NewKr), Kt(NewKt)
    {
    } /*End of 'surface' function */
  }; /* End of 'surface' class */

  /* Enviroment class */
  class envi
  {
  public:
    DBL RefractionCoef;
    DBL DecayCoef;

    envi( const DBL &NewRefractionCoef, const DBL &NewDecayCoef ) : RefractionCoef(NewRefractionCoef), DecayCoef(NewDecayCoef)
    {
    }
  }; /* End of 'envi' class */

  /* Shape class */
  class shape
  {
  public:
    surface Mtl;  // Shape material
    envi Media {0, 0};   // Enviroment coef

    /* Is crossing with shape function.
     * ARGUMENTS:
     *   - ray from camera:
     *      const ray &R;
     *   - intersection data pointer:
     *      intr *Intr;
     * RETURNS:
     *   (BOOL) Is intersection with shape.
     */
    virtual BOOL Intersect( const ray &R, intr *Intr )
    {
      return FALSE;
    } /* End of 'Intersect' funciton */

    /* Evaluate shape normal function.
     * ARGUMENTS:
     *   - intersection data pointer:
     *      intr *Intr;
     * RETURNS: None.
     */
    virtual VOID GetNormal( intr *Intr )
    {
    } /* End of 'GetNormal' funciton */
  }; /* End of 'shape' class */

  /* Light information class */
  class light_info
  {
  public:
    vec3 L;     // light source direction
    vec3 Color; // light source color
    DBL Dist;   // distance to light source
  }; /* End of 'light_info' class */

  /* Light class */
  class light
  {
  protected:
    DBL Cc, Cl, Cq;
 
  public:
    /* Shadow light function.
     * ARGUMENTS:
     *   - position:
     *       HINSTANCE hInstance;
     */
    virtual DBL Shadow( const vec3 &P, light_info *L )
    {
      return 0;
    }
  }; /* End of 'light' class */

  /* Scene class */
  class scene
  {
  private:
    std::vector<shape *> Shapes;  // shapes container
    std::vector<light *> Lights;  // light container

    vec3 AmbientColor, Background;
    INT MaxRecLevel;  // Recursion in trace level and recursion max level
 
  public:
    envi Air {1, 0}; // Air enviroment coef

    /* Default constructor */
    scene( VOID ) : MaxRecLevel(8), Background(vec3(0)), AmbientColor(vec3(1, 0, 0))
    {
    }

    /* Scene destructor */
    ~scene( VOID )
    {
      for (auto Sh : Shapes)
        delete Sh;

      for (auto Lgt : Lights)
        delete Lgt;
    } /* End of '~scene' function */

    /* Shade color by parametrs function.
     * ARGUMENTS:
     *   - direction of ray:
     *      const vec3 &Dir;
     *   - enviroment coefs:
     *      const envi &Media;
     *   - intersection data pointer:
     *      intr *Intr;
     *   - weight of light:
     *      const DBL &Weight;
     *   - recursion level:
     *      INT RecLevel;
     * RETURNS:
     *   (vec3) new color.
     */
    vec3 Shade( const vec3 &Dir, const envi &Media, intr *Intr, const DBL &Weight, INT RecLevel )
    {
      vec3 color = vec3(0);
      light_info li;
      DBL att;

      color += Intr->Sh->Mtl.Ka * AmbientColor;

      for (auto lgt : Lights)
      {
        att = lgt->Shadow(Intr->P, &li); //+ li.L * Threshold??

        // reverse normal if need
        envi OutMedia = Intr->Sh->Media;
        if ((Intr->N & Dir) > 0)
          Intr->N = -Intr->N, OutMedia = Media;

        // eval reflected vector
        vec3 R = Dir - Intr->N * 2 * (Dir & Intr->N);

        color += li.Color *
          ((Intr->Sh->Mtl.Kd * max(0, (Intr->N & li.L)) + Intr->Sh->Mtl.Ks * pow(max(0, (R & li.L)), Intr->Sh->Mtl.Ph)) * att +
           Trace(ray(Intr->P + R * Threshold, R), OutMedia, Weight * Intr->Sh->Mtl.Kr, RecLevel + 1) * Intr->Sh->Mtl.Kr) * exp(-Intr->T * Media.DecayCoef);// * exp(-Intr->T * Media.RefractionCoef) +
           //Trace(ray(Intr->P + R * Threshold, R), Media, Weight) * Intr->Sh->Mtl.Kt * exp(-Intr->T * Media.DecayCoef));

        // eval refraction vector
        DBL n = Intr->Sh->Media.RefractionCoef / Media.RefractionCoef;
        DBL dn = -Dir & Intr->N;
        vec3 T = (Dir - Intr->N * (Dir & Intr->N)) * n - Intr->N *  sqrt(1 - (1 - dn * dn) * n * n);

        color += li.Color * Trace(ray(Intr->P + T * Threshold, T), OutMedia, Weight * Intr->Sh->Mtl.Kt, RecLevel + 1) * Intr->Sh->Mtl.Kt * exp(-Intr->T * Media.DecayCoef);

        intr in;
        if (Intersection(ray(Intr->P + li.L * Threshold, li.L), &in) && in.T < li.Dist)
          color *= 0.30;
      }

      return color * Weight;
    } /* End of 'Shade' function */

    /* Shade color by parametrs function.
     * ARGUMENTS:
     *   - ray from screen:
     *      const ray &R;
     *   - enviroment coefs:
     *      const envi &Media;
     *   - weight of light:
     *      const DBL &Weight;
     *   - recursion level:
     *      INT RecLevel;
     * RETURNS:
     *   (vec3) new color.
     */
    vec3 Trace( const ray &R, const envi &Media, DBL Weight, INT RecLevel )
    {
      vec3 color = Background;
      /*
      vec3 FogColor = vec3(1, 0, 0);//AmbientColor;
      DBL FogStart = 5;
      DBL FogEnd = 25;
      */
      if (RecLevel < MaxRecLevel && Weight > Threshold)
      {
        RecLevel++;
        //. . .look for closest intersection
        intr intersection;
        if (Intersection(R, &intersection))
        {
          if (!intersection.IsP)
            intersection.P = R(intersection.T);
          if (!intersection.IsN)
            intersection.Sh->GetNormal(&intersection);

          color = Shade(R.Dir, Media, &intersection, Weight, RecLevel);

          /* //???
          DBL fog = 0;
          if (intersection.T < FogStart)
            fog = 1;
          else if (intersection.T > FogEnd)
            fog = 0;
          else
            fog = (intersection.T - FogStart) / (FogEnd - FogStart);

          color = color * fog + FogColor * (1 - fog);
          */
        }
        else
          color = Background;

        RecLevel--;
      }
      return color;
    } /* End of 'Trace' function */

    /* Is ray crossing with all shapes in scene function.
     * ARGUMENTS:
     *   - ray from camera:
     *      const ray &R;
     *   - intersection data pointer:
     *      intr *Intr;
     * RETURNS:
     *   (BOOL) Is intersection with shapes.
     */
    BOOL Intersection( const ray &R, intr *Intr )
    {
      intr intrsec;

      Intr->T = HUGE_VAL;

      for (auto Sh : Shapes)
        if (Sh->Intersect(R, &intrsec))
          if (intrsec.T < Intr->T)
            *Intr = intrsec;

      if (Intr->T == HUGE_VAL)
        return FALSE;
      return TRUE;
    } /* End of 'Intersection' function */
    /*    ????????
    BOOL Intersection( const ray &R, intr *Intr )
    {
      intr closest_intrsec, intrsec;

      Intr->T = HUGE_VAL;

      for (auto Sh : Shapes)
        if (Sh->Intersect(R, &intrsec) && (closest_intrsec.Sh == nullptr || closest_intrsec.T > intrsec.T))
          if (intrsec.T < Intr->T)
            closest_intrsec.T = intrsec.T;

      if (Intr->T == HUGE_VAL)
        return FALSE;
      return TRUE;
    }
    */
 
    /* Add shape to scene operator.
     * ARGUMENTS:
     *   - shape pointer:
     *       shape *Shape;
     * RETURNS:
     *   (scene &) Self-reference.
     */
    scene & operator<<( shape *Shape )
    {
      Shapes.push_back(Shape);

      return *this;
    } /* End of '<<' function */

    /* Add shape to scene operator.
     * ARGUMENTS:
     *   - light pointer:
     *       light *Light;
     * RETURNS:
     *   (scene &) Self-reference.
     */
    scene & operator<<( light *Light )
    {
      Lights.push_back(Light);

      return *this;
    } /* End of '<<' function */
  }; /* End of 'scene' class */
} /* end of 'gort' namespace */

#endif /* __rt_def_h_ */

/* END OF 'rt_def.h' FILE */