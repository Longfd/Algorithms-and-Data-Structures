// create or delete a 2D array; 
// catch exception thrown by new when sufficient memory is not available
// return true iff successful in creating the 2d array

#pragma once

#include <exception>

template <class T>
bool make2dArray(T ** &x, int numberOfRows, int numberOfColumns)
{// Create a two dimensional array.

	//try {
		// create pointers for the rows
		x = new T *[numberOfRows];

		// get memory for each row
		for (int i = 0; i < numberOfRows; i++)
			x[i] = new int[numberOfColumns];
		return true;
	//}
	//catch (std::bad_alloc) { return false; }
}

template <class T>
void delete2dArray(T ** &theArray, int numberOfRows)
{// Delete the two-dimensional array theArray.

   // delete the memory for each row
	for (int i = 0; i < numberOfRows; i++)
		delete[] theArray[i];

	// delete the row pointers
	delete[] theArray;
	theArray = 0;
}

