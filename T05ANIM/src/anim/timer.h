/* FILE NAME : timer.h
 * PROGRAMMER: DG5
 * DATE      : 21.07.2021
 * PURPOSE   : timer handle module.
 */

#ifndef __timer_h_
#define __timer_h_

#include <commondf.h>
#include "anim.h"
#include "../mth/mth.h"

/* Space gogl namespace */
namespace gogl
{
  /* Timer class */
  class timer
  {
  private:
    UINT64
      StartTime,    /* Start program time */
      OldTime,      /* Previous frame time */
      OldTimeFPS,   /* Old time FPS measurement */
      PauseTime,    /* Time during pause period */
      TimePerSec,   /* Timer resolution */
      FrameCounter; /* Frames counter */

  public:
    DBL
      GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
      Time, DeltaTime,             /* Time with pause and interframe interval */
      FPS;
    BOOL IsPause;

    timer( VOID )
    {
      LARGE_INTEGER t;

      QueryPerformanceFrequency(&t);
      TimePerSec = t.QuadPart;
      QueryPerformanceCounter(&t);
      StartTime = OldTime = OldTimeFPS = t.QuadPart;
      FrameCounter = 0;
      IsPause = FALSE;
      FPS = 30;
      PauseTime = 0;
    }

    /* Timer interframe response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      LARGE_INTEGER t;

      QueryPerformanceCounter(&t);
      /* Global time */
      GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
      GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
      /* Time with pause */
      if (IsPause)
      {
	DeltaTime = 0;
	PauseTime += t.QuadPart - OldTime;
      }
      else
      {
	DeltaTime = GlobalDeltaTime;
	Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
      }
      /* FPS */
      FrameCounter++;
      if (t.QuadPart - OldTimeFPS > TimePerSec)
      {
	FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
	OldTimeFPS = t.QuadPart;
	FrameCounter = 0;
      }
      OldTime = t.QuadPart;
    } /* End of 'TimerResponse' function */
  };
}

#endif /* __timer_h_ */

/* END OF 'timer.h' FILE */