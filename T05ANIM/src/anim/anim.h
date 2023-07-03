/* FILE NAME : anim.h
 * PROGRAMMER: DG5
 * DATE      : 22.07.2021
 * PURPOSE   : Animation module.
 */

#ifndef __anim_h_
#define __anim_h_

#include "../win/win.h"
#include "input.h"
#include "timer.h"
#include "./rnd/rnd.h"
#include "../utilities/stock.h"
#include "../def.h"

/* Space gogl namespace */
namespace gogl
{
  // Forward declaration
  class anim;
  class scene;

  /* Unit class */
  class unit
  {
  public:
    virtual ~unit( VOID )
    {
    }

    /* Unit response function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID Response( anim *Ani )
    {
    } /* End of 'Response' function */

    /* Unit render function.
     * ARGUMENTS: None.
     *   - animation context:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID Render( anim *Ani )
    {
    } /* End of 'Render' function */
  }; /* End of 'unit' class */

  /* Scene units class */
  class scene : public unit
  {
  protected:
    stock <unit *> Units;
  public:
    /* Scene constructor */
    scene( VOID )
    {
    } /* End of 'scene' constructor function */

    /* Scene destructor */
    ~scene( VOID )
    {
      Units.Walk([]( unit *Uni ){ delete Uni; });
    } /* End of '~scene' destructor function */

    /* Scene response function.
     * ARGUMENTS: None.
     *   - animation context:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Response( anim *Ani ) override
    {
      Units.Walk([Ani]( unit *Uni ){ Uni->Response(Ani); });
    } /* End of 'Response' function */

    /* Scene response function.
     * ARGUMENTS: None.
     *   - animation context:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Render( anim *Ani ) override
    {
      Units.Walk([Ani]( unit *Uni ){ Uni->Render(Ani); });
    } /* End of 'Render' function */

    /* Add unit to scene operator.
     * ARGUMENTS:
     *   - name of the unit:
     *       const std::string &Name;
     * RETURNS:
     *   (scene &) Self-reference.
     */
    scene & operator<<( const std::string &Name );
  }; /* end of 'scene' class */

  /* Animation class */
  class anim : public win, public render, public input, public timer, public scene
  {
  private:
    anim( VOID ) : win(), input(win::hWnd, win::MouseWheel), render(win::hWnd, win::W, win::H)
    {
    }

    VOID Init( VOID ) override;
    VOID Close( VOID ) override;
    VOID Resize( VOID ) override;
    VOID Timer( VOID  ) override;
    VOID Activate( VOID ) override;
    VOID Idle( VOID ) override;
    VOID Erase( HDC hDC ) override;
    VOID Paint( HDC hDC ) override;

    static anim Instance; //Single copy of class
  public:
    std::map<std::string, unit * (*)( VOID )> UnitNames; // Autoregistration units map
    scene Scene;

    /* Units autoregistration class */
    template<class UnitType>
    class unit_register
    {
    public:
      /* Add unit in type.
       * ARGUMENTS: None.
       * RETURNS:
       *   (static unit *) added unit.
       */
      static unit * Create( VOID )
      {
        return new UnitType(&Instance);
      } /* End of 'Create' function */

      /* Class constructor
       * ARGUMENTS:
       *   - unit name:
       *     const std::string &Name;
       */
      unit_register( const std::string &Name )
      {
        Instance.UnitNames[Name] = Create;
      }
    }; /* end of 'unit_register' class */

    /* Returning variable method */
    static anim &Get( VOID )
    {
      return Instance;
    }

    /* Returning variable pointer method */
    static anim * GetPtr( VOID )
    {
      return &Instance;
    }

    /* Animation rendering function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID )
    {
      timer::Response();
      input::Response();
      Scene.Response(GetPtr());

      render::Start();

      Scene.Render(GetPtr());

      render::End();
    } /* End of 'Render' function */
  };
}

#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */