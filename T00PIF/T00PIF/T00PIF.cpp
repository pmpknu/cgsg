/* FILE NAME : T00PIF.cpp
 * PROGRAMMER: DG5
 * DATE      : 18.07.2021
 * PURPOSE   : Pifagor triangle.
 */

#include <iostream>

/* Pifagor table display funtion.
 * ARGUMENTS:
 *   - start number:
 *       FLT Start;
 *   - pif step:
 *       FLT Step;
 *   - table size:
 *       FLT Size;
 * RETURNS: None.
 */
void pif( float Start, float Step, float Size )
{
	///float max_num = (Start + Step * Size) * (Start + Step * Size);
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			std::cout.width(7);
			std::cout.precision(2);
			std::cout << std::fixed << (Start + Step * i) * (Start + Step * j);
		}
		std::cout << "\n";	
	}

} /* End of 'pif' function */

/* Main program function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) exit code.
 */
int main(void)
{
	float Start, Step, Size;

	std::cout << "Input start number: ";
	std::cin >> Start;
	std::cout << "Input step: ";
	std::cin >> Step;
	std::cout << "Input size: ";
	std::cin >> Size;

	pif(Start, Step, Size);

	return 0;
} /* End of 'main' function */

/* END OF 'T00PIF.cpp' FILE */