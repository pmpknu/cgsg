/* FILE NAME : t04list.cpp
 * PROGRAMMER: DG5
 * DATE      : 19.07.2021
 * PURPOSE   : List sample.
 */

#include <iostream>
#include <cstdlib>

#include <commondf.h>

/* Debug memory allocation support */ 
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h>
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy 
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __ooppss;
#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

/* List handle namespace */
namespace dg5
{
  /* Linear single-connected list handle class */
  template<typename Type = INT>
  class list
  {
  private:
    /* Data structure */
    struct entry
    {
      Type Data;   // List data
      entry *Next; // Next list element
    
      /* entry constructor */
      entry( Type NewData, entry *NewNext = nullptr ) : Data(NewData), Next(NewNext)
      {
      }
    } *Start; /* end of 'entry' struct */
  public:
    list() : Start( nullptr )
    {
    }

    list( list &L )
    {
      if (Start != nullptr)
	Clear();

      entry **ptr = &Start;
      entry *ls = L.Start;

      while (ls != nullptr)
      {
	*ptr = new entry(ls->Data);
	ls = ls->Next;
	ptr = &(*ptr)->Next;
      }
    }

    ~list()
    {
      while (Start != nullptr)
      {
	entry *old = Start;
	Start = Start->Next;
	delete old;
      }
    }

    VOID Display( VOID )
    {
      if (Start == nullptr)
      {
	std::cout << "empty list\n";
	return;
      }

      entry *ptr = Start;

      while (ptr != nullptr)
      {

	std::cout << ptr->Data << (ptr->Next == nullptr ? "\n" : ", ");
	ptr = ptr->Next;
      }
    }

    list & PushFront( Type NewData )
    {
      Start = new entry(NewData, Start);

      return *this;
    }

    list & PushBack( Type NewData )
    {
      entry **ptr = &Start;

      while (*ptr != nullptr)
	ptr = &(*ptr)->Next;
      *ptr = new entry(NewData, nullptr);

      return *this;
    }

    BOOL PopFront( Type *OldData )
    {
      if (Start == nullptr)
	return FALSE;

      entry *Old = Start;

      *OldData = Old->Data;
      Start = Start->Next;

      delete Old;
      return TRUE;
    }

    BOOL PopBack( Type *OldData )
    {
      if (Start == nullptr || Start->Next == nullptr)
	return FALSE;

      entry *ptr = Start;

      while (ptr->Next->Next != nullptr)
	ptr = ptr->Next;

      entry *Old = ptr->Next;

      *OldData = Old->Data;
      ptr->Next = nullptr;
      delete Old;

      return TRUE;
    }

    VOID Clear( VOID )
    {
      while (Start != nullptr)
      {
	entry *old = Start;

	Start = Start->Next;
	delete old;
      }
    }

    BOOL IsEmpty( VOID )
    {
      if (Start == nullptr)
	return TRUE;
      return FALSE;
    }

    list &operator=( list &L )
    {
      if (L.Start != nullptr)
      {
	int cntsrc = 0, cntdsc = 0;
	entry *ptrsrc = L.Start;

	while (ptrsrc != nullptr)
	  ptrsrc = ptrsrc->Next, cntsrc++;

	if (Start != nullptr)
	{
	  entry *ptrdsc = Start;

	  while (ptrdsc != nullptr)
	    ptrdsc = ptrdsc->Next, cntdsc++;
	}

	int sub = cntsrc - cntdsc;

	if (sub > 0)
	{
	  for (int i = 0; i < sub; i++)
	  {
	    Start = new entry( L.Start->Data, Start );
	  }
	}
	else if (sub < 0)
	{
	  for (int i = 0; i < -sub; i++)
	  {
	    entry *Old = Start;

	    Start = Start->Next;
	    delete Old;
	  }
	}

	entry **ptrdsc = &Start;
	entry *newptrsrc = L.Start;

	while (newptrsrc != nullptr)
	{
	  *ptrdsc = newptrsrc;
	  newptrsrc = newptrsrc->Next;
	  ptrdsc = &(*ptrdsc)->Next;
	}
      }
      else
	Start = nullptr;

      return *this;
    } /* not dopisano */

  }; /* end of 'list' class */

} /* end of 'dg5' namespace */

INT main( void )
{
  dg5::list<> L;

  int x;

  L.PushFront(1).PushFront(2).PushFront(3).PushBack(0);
  L.PopBack(&x);

  /*
  for (int i = 0; i < 102; i++)
  {
    dg5::list<> L1(L);
    int n = static_cast<double>(rand()) / RAND_MAX * 102, ii = 0;

    while (ii++ < n)
      L1.PushFront(ii).PushBack(ii), L1.PopBack(&x), L1.PopFront(&x);
  }
  */
  dg5::list<> L1;

  L1 = L;

  L.Display();

  return 0;
}

/* END OF 't04list' FILE */




/*
class list
  {
    // Data structure
    struct entry
    {
      INT Data;    // List data
      entry *Next; // Next list element

      entry( INT NewData, entry *NewNext = nullptr ) : Data( NewData ), Next( NewNext )
      {
      }
    } *Start;

    list() : Start( nullptr )
    {
    }
    ~list()
    {
      while (Start != nullptr)
      {
	entry *old = Start;
	Start = Start->Next;
	delete old;
      }
    }
    VOID Add( INT NewData )
    {
      Start = new entry( NewData, Start );
    }
    VOID AddBack( INT NewData )
    {
      entry **ptr = &Start;

      while (*ptr != nullptr)
	ptr = &(*ptr)->Next;
      *ptr = new entry( NewData, Start );
    }
 */
