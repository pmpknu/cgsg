/* FILE NAME : stock.h
 * PROGRAMMER: DG5
 * DATE      : 23.07.2021
 * PURPOSE   : Stock handle module.
 */

#ifndef __stock_h_
#define __stock_h_

#include <cassert>

// implementation

/* Stock class template */
template<typename type>
  class stock
  {
  private:
    INT
      RealSize,  // Real number of array elements
      MaxSize;   // Allocated array elements count
    type *Array; // Data array
 
  public:
    /* Class constructor.
     * ARGUMENTS: None.
     */
    stock( VOID ) : Array(nullptr), RealSize(0), MaxSize(0)
    {
    } /* End of 'stock' function */
 
    /* Class destructor */
    ~stock( VOID )
    {
      if (Array != nullptr)
        delete[] Array;
      Array = nullptr;
      RealSize = 0;
      MaxSize = 0;
    } /* End of '~stock' function */
 
    /* Class copying constructor.
     * ARGUMENTS:
     *   - stock to be copy:
     *       const stock<type> &CopyData;
     */
    stock( const stock<type> &CopyData ) :
      Array(new type[CopyData.RealSize]),
      RealSize(CopyData.RealSize),
      MaxSize(CopyData.RealSize)
    {
      for (INT i = 0; i < RealSize; i++)
        Array[i] = CopyData.Array[i];
    } /* End of 'stock' function */
 
    /* Assignment operator function.
     * ARGUMENTS:
     *   - stock to be assign:
     *       const stock<type> &CopyData;
     * RETURNS:
     *   (stock &) self reference.
     */
    stock & operator=( const stock<type> &CopyData )
    {
      if (Array != nullptr)
        delete[] Array;
      Array = new type[CopyData.RealSize];
      RealSize = CopyData.RealSize;
      MaxSize = CopyData.RealSize;
      for (int i = 0; i < RealSize; i++)
        Array[i] = CopyData.Array[i];
      return *this;
    } /* End of 'operator=' function */
 
    /* Obtain stock length function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) number of stock elements.
     */
    INT Size( VOID ) const
    {
      return RealSize;
    } /* End of 'Size' function */
 
    /* Add new element to stock function.
     * ARGUMENTS:
     *   - value to be add:
     *       const type &NewData;
     * RETURNS:
     *   (stock &) self reference.
     */
    stock & Add( const type &NewData )
    {
      if (RealSize >= MaxSize)
      {
        // increase allocated memory
        if (MaxSize == 0)
          MaxSize = 1;
        else
          MaxSize *= 2;
 
        type *new_bulk = new type[MaxSize];
        if (Array != nullptr)
        {
          // copy old data
          for (int i = 0; i < RealSize; i++)
            new_bulk[i] = Array[i];
          // remove old data
          delete[] Array;
        }
        Array = new_bulk;
      }
      Array[RealSize++] = NewData;
      return *this;
    } /* End of 'Add' function */
 
    /* Add new element to stock (as operator) function.
     * ARGUMENTS:
     *   - value to be add:
     *       const type &NewData;
     * RETURNS:
     *   (stock &) self reference.
     */
    stock & operator<<( const type &NewData )
    {
      return Add(NewData);
    } /* End of '<<' function */
 
    /* Lvalue element access function.
     * ARGUMENTS:
     *   - element index:
     *       INT Index;
     * RETURNS:
     *   (type &) element reference.
     */
    type & operator[]( INT Index )
    {
      assert(Index >= 0 && Index < RealSize);
      return Array[Index];
    } /* End of 'operator[]' function */
 
    /* Constant element access function.
     * ARGUMENTS:
     *   - element index:
     *       INT Index;
     * RETURNS:
     *   (type &) element reference.
     */
    type & operator[]( INT Index ) const
    {
      assert(Index >= 0 && Index < RealSize);
      return Array[Index];
    } /* End of 'operator[]' function */
 
    /* Clear stock content function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Clear( VOID )
    {
      RealSize = 0;
    } /* End of 'Clear' function */
 
    /* Stock walker function.
     * ARGUMENTS:
     *   - access function-functor reference:
     *       type2 &Walker;
     * RETURNS: None.
     */
    template<typename type2>
      VOID Walk( const type2 &Walker )
      {
        for (int i = 0; i < RealSize; i++)
          Walker(Array[i]);
      } /* End of 'Walk' function */
  }; /* End of 'stock' class */

#endif /* __stock_h_ */

/* END OF 'stock.h' FILE */