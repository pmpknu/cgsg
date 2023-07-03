/* FILE NAME : T01SORT.cpp
 * PROGRAMMER: DG5
 * DATE      : 18.07.2021
 * PURPOSE   : Sort example.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

/* Swap two elements function.
 * ARGUMENTS:
 *   - elements:
 *       double Arr;
 * RETURNS: None.
 */
void swap( double *A, double *B )
{
	double tmp = *A;

	*A = *B;
	*B = tmp;
} /* End of 'swap' function */

/* Quick sort function.
 * ARGUMENTS:
 *   - array of elements:
 *       double Arr;
 *   - num of elements:
 *       int n;
 * RETURNS: None.
 */
void sort(double *Arr, int N)
{
	if (N < 2)
		return;

	int b = 0, e = N - 1;
	double x = Arr[N / 2];

	while (b <= e)
	{
		while (Arr[b] < x)
			b++;
		while (Arr[e] > x)
			e--;
		if (b <= e)
		{
			swap(&Arr[b], &Arr[e]);
			b++, e--;
		}
	}

	sort(Arr, e + 1);
	sort(Arr + b, N - b);
} /* End of 'sort' function */

 /* Main program function.
	* ARGUMENTS: None.
	* RETURNS:
	*   (INT) exit code.
	*/
int main(void)
{
	/* Get input file name */
	std::string inputFileName;
	std::cout << "Input file name: ";
	std::cin >> inputFileName;

	std::fstream f;
	int n;

	/* Open input file */
	f.open(inputFileName/*"test.txt"*/, std::fstream::in);
	f >> n;

	double* arr;

	/* Allocating memory for array */
	if ((arr = (double *)malloc(sizeof(double) * n)) == nullptr)
		return 0;

	/* Read data from file */
	for (int i = 0; i < n; i++)
		f >> arr[i];
	f.close();

	/* Sort data */
	sort(arr, n);

	/* Get output file name */
	std::string outputFileName;
	std::cout << "Output file name: ";
	std::cin >> outputFileName;

	/* Write data to outup file */
	f.open(outputFileName/*"test.txt"*/, std::fstream::out);
	for (int i = 0; i < n; i++)
		f << arr[i] << "\n";
	f.close();

	free(arr);
	return 0;
} /* End of 'main' function */

/* END OF 'T01SORT.cpp' FILE */