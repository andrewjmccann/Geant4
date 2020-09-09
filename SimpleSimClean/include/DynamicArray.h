/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.              *
*   hseywerd@nrcan.gc.ca                                                  *
*                                                                         *
***************************************************************************/
/**
 * @file DynamicArray.h
 * @brief A template class to all building of a dynamic array.
 *
 * @date Feb 5, 2010
 *
 * @author hseywerd
 **/


#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

	/**
	 * @class A template class to all building of a dynamic array.
	 */
	template<typename T>
	class DynamicArray {
	public:
		DynamicArray() {
		}
		DynamicArray(int rows, int cols) :
			dArray(rows, std::vector<T>(cols)) {
		}
		std::vector<T> & operator[](int i) {
			return dArray[i];
		}
		const std::vector<T> & operator[](int i) const {
			return dArray[i];
		}
		void resize(int rows, int cols)//resize the two dimentional array .
		{
			dArray.resize(rows);
			for (int i = 0; i < rows; ++i)
				dArray[i].resize(cols);
		}
	private:
		std::vector<std::vector<T> > dArray;
	};

#endif /* DYNAMICARRAY_H_ */
