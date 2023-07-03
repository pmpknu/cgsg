/* FILE NAME : T01LIST.cpp
 * PROGRAMMER: DG5
 * DATE      : 18.07.2021
 * PURPOSE   : List sample.
 */

#include <iostream>

/* List structure */
struct list
{
	/* Data structure */
	struct entry
	{
		int Data;    /* List data */
		entry* Next; /* Next list element */

		entry( int NewData, entry* NewNext = nullptr ) : Data(NewData), Next(NewNext)
		{
		}
	} *Start;

	list() : Start(nullptr)
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
	void Add( int NewData )
	{
		Start = new entry(NewData, Start);
	}
	void AddBack( int NewData )
	{
		entry** ptr = &Start;

		while (*ptr != nullptr)
			ptr = &(*ptr)->Next;
		*ptr = new entry(NewData, Start);
	}


};

/* .    
 * ARGUMENTS:
 *   - :
 *       ;
 * RETURNS:
 *   () .
 */
