/*
 * matrix_math.h
 *
 *  Created on: 27 mar 2020
 *      Author: UMB
 */

#ifndef MATRIX_MATH_H_
#define MATRIX_MATH_H_

#include "arm_math.h"
#include <stdlib.h>
#include <initializer_list>

template<typename type, size_t row, size_t column>
class Matrix
{
	private:

	size_t _rows;
	size_t _cols;
	type _matrix_data[row*column];

	public:

	arm_matrix_instance_f32 _matrix;

	Matrix();

	/*constructor with a list of elements*/
    Matrix(std::initializer_list<std::initializer_list<type>>lst);

    /*returns the number of rows*/
    size_t rows();

	/*returns the number of columns*/
	size_t columns();

	/*returns the item on _row _col position*/
	type get_item(size_t _row, size_t _col);

	/* makes an identity matrix */
	Matrix<type,row,column> & identity(void);

	/* add a matrix to a matrix*/
	auto & operator=(Matrix<type,row,column> rhs);

	/* add a matrix to a matrix*/
	Matrix<type,row,column> operator+(Matrix<type,row,column> rhs);

	/* subtract a matrix to a matrix*/
	Matrix<type,row,column> operator-(Matrix<type,row,column> rhs);

	/* multiply a matrix by a scalar*/
	Matrix<type,row,column> operator*(type scalar);

	/* multiply a matrix by a matrix*/
	Matrix<type,row,row> operator*(Matrix<type,column,row> rhs);

	/* matrix transpose*/
	Matrix<type,column,row> transpose();

	/* matrix inverse*/
	Matrix<type,column,row> inverse();

	/* check if two matrices are equal*/
	int isequal(Matrix<type,row,column> rhs, float EPSILON);

};


/*constructor*/
template<typename type, size_t row, size_t column>
Matrix<type,row,column>::Matrix()
{
	_rows=row;
	_cols=column;

	for(size_t i=0;i<_cols*_rows;i++)
	{
		_matrix_data[i]=0;
	}

	arm_mat_init_f32(&_matrix, _rows, _cols, (float32_t *)_matrix_data);
}


/*constructor with a list of elements*/
template<typename type, size_t row, size_t column>
Matrix<type,row,column>::Matrix(const std::initializer_list<std::initializer_list<type>>lst){

	auto it=lst.begin();
	_rows=row;
	_cols=column;

	for(size_t i=0;i<_cols*_rows;i++)
	{
		_matrix_data[i]=it->begin()[i];
	}

	arm_mat_init_f32(&_matrix, _rows, _cols, (float32_t *)_matrix_data);
}


/*returns the number of rows*/
template<typename type, size_t row, size_t column>
size_t Matrix<type,row,column>::rows(void)
{
	return _rows;
}


/*returns the number of columns*/
template<typename type, size_t row, size_t column>
size_t Matrix<type,row,column>::columns(void)
{
	return _cols;
}


/*returns the item on _row _col position*/
template<typename type, size_t row, size_t column>
type Matrix<type,row,column>::get_item(size_t _row, size_t _col)
{
	return _matrix_data[_rows*_col+_row];
}


/* makes an identity matrix */
template<class type, size_t row,size_t column>
Matrix<type,row,column> & Matrix<type,row,column>::identity()
{
	for (size_t i=0; i<_rows; i++) {
		for (size_t j=0; j<_cols; j++){
			if(i==j)_matrix_data[_rows*j+i]=1.0f;
		}
	}
	return *this;
}


template<class type, size_t row,size_t column>
auto & Matrix<type,row,column>::operator=(Matrix<type,row,column> rhs)
{
	for (size_t i=0; i<_rows; i++) {
		for (size_t j=0; j<_cols; j++){
			_matrix_data[_rows*j+i]=rhs.get_item(i,j);
		}
	}
	return *this;
}


/*add a matrix to a matrix*/
template<typename type, size_t row,size_t column>
Matrix<type,row,column> Matrix<type,row,column>::operator+(Matrix<type,row,column> rhs)
{
	Matrix<type,row,column> temp;

	arm_mat_add_f32(&this->_matrix, &rhs._matrix, &temp._matrix);

	return temp;
}


/* subtract a matrix to a matrix*/
template<typename type, size_t row,size_t column>
Matrix<type,row,column> Matrix<type,row,column>::operator-(Matrix<type,row,column> rhs)
{
	Matrix<type,row,column> temp;

	arm_mat_sub_f32(&this->_matrix, &rhs._matrix, &temp._matrix);

	return temp;
}


/*multiply a matrix by a scalar*/
template<typename type, size_t row,size_t column>
Matrix<type,row,column> Matrix<type,row,column>::operator*(type scalar)
{
	Matrix<type,row,column> temp;

	size_t size = this->rows()*this->columns();

	for(size_t i=0;i<size;i++)
	{
		temp._matrix_data[i]*=scalar;
	}

	return temp;
}


/*multiply a matrix by a matrix*/
template<typename type, size_t row,size_t column>
Matrix<type,row,row> Matrix<type,row,column>::operator*(Matrix<type,column,row> rhs)
{
	Matrix<type,row,row> temp;

	arm_mat_mult_f32(&this->_matrix, &rhs._matrix, &temp._matrix);

	return temp;
}


/*matrix transpose*/
template<typename type, size_t row,size_t column>
Matrix<type,column,row>  Matrix<type,row,column>::transpose(void)
{
	Matrix<type,column,row> temp;

	arm_mat_trans_f32(&this->_matrix, &temp._matrix);

	return temp;
}


/*matrix inverse*/
template<typename type, size_t row,size_t column>
Matrix<type,column,row>  Matrix<type,row,column>::inverse(void)
{
	Matrix<type,column,row> temp;

	arm_mat_inverse_f32(&this->_matrix, &temp._matrix);

	return temp;
}


/*is equal check */
template<typename type, size_t row,size_t column>
int Matrix<type,row,column>::isequal(Matrix<type,row,column> rhs, float EPSILON)
{
	size_t size = this->rows()*this->columns();

	for(size_t i=0;i<size;i++)
	{
		if(fabs(this->_matrix_data[i] - rhs._matrix_data[i]) > EPSILON) return 0;
	}

	return 1;
}

#endif /* MATRIX_MATH_H_ */

