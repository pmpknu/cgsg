/* FILE NAME : T02SORTS.cpp
 * PROGRAMMER: DG5
 * DATE      : 18.07.2021
 * PURPOSE   : Sort example.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

/* Array data structure */
template<typename Type>
  struct array
  {
    int N;     // Number of array elements
    Type* Arr; // Data of array

    array(void) : Arr(nullptr), N(0)
    {
    }

    array( int Size )
    {
      N = Size;
    }

    ~array(void)
    {
      if (Arr != nullptr)
        delete[] Arr;
    }

    /* Swap two elements function.
      * ARGUMENTS:
      *   - elements:
      *       Type Arr;
      * RETURNS: None.
      */
    void swap(Type &A, Type &B)
    {
      Type tmp = A;

      A = B;
      B = tmp;
    } /* End of 'swap' function */

    /* Quick sort function.
     * ARGUMENTS:
     *   - array of elements:
     *       double Arr;
     *   - num of elements:
     *       int n;
     * RETURNS: None.
     */
    void sort(Type *Arr, int N)
    {
      if (N < 2)
        return;

      int b = 0, e = N - 1;
      Type x = Arr[N / 2];

      while (b <= e)
      {
        while (Arr[b] < x)
          b++;
        while (Arr[e] > x)
          e--;
        if (b <= e)
        {
          swap(Arr[b], Arr[e]);
          b++, e--;
        }
      }

      sort(Arr, e + 1);
      sort(Arr + b, N - b);
    } /* End of 'sort' function */

    void sort(void)
    {
      sort(Arr, N);
    }

    void load(const std::string FileName)
    {
      if (Arr != nullptr)
        delete[] Arr, Arr = nullptr, N = 0;

      std::fstream f;

      /* Open input file */
      f.open(FileName, std::fstream::in);
      f >> N;

      try
      {
        Arr = new double[N];
      }
      catch (std::bad_alloc &)
      {
        std::cout << "No memory\n";
      }

      /* Read data from file */
      for (int i = 0; i < N; i++)
        f >> Arr[i];
      f.close();
    }

    void save(const std::string FileName)
    {
      std::fstream f;

      /* Write data to outup file */
      f.open(FileName, std::fstream::out);
      for (int i = 0; i < N; i++)
        f << Arr[i] << "\n";
      f.close();
    }
 };

 /* Main program function.
  * ARGUMENTS: None.
  * RETURNS:
  *   (INT) exit code.
  */
int main(void)
{
  array<double> Arr;
  array<double> Arr2;

  Arr.load("test.txt");
  Arr2.load("test.txt");
  Arr.sort();
  Arr.save("123.txt");

  return 0;
} /* End of 'main' function */

/* END OF 'T02SORTS.cpp' FILE */

 
/* Get input file name */
  /*std::string inputFileName;
  std::cout << "Input file name: ";
  std::cin >> inputFileName;*/

  /* Get output file name */
  /*std::string outputFileName;
  std::cout << "Output file name: ";
  std::cin >> outputFileName;*/