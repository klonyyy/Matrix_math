/*
 * matrix_base.h
 *
 *  Created on: 6 kwi 2020
 *      Author: UMB
 */

#ifndef INC_MATRIX_BASE_H_
#define INC_MATRIX_BASE_H_


template<typename derived>
class Matrix_base
{
private:

	Matrix

public:

	Matrix_base operator*(const Matrix_base<derived> rhs);





};

template<typename derived>
template<typename otherderived>
Matrix_base<otherderived> operator*(const Matrix_base<derived> rhs)
{
	Matrix_base<otherderived> temp;

	arm_mat_mult_f32(&this->_matrix, &rhs._matrix, &temp._matrix);

	return temp;
}

#endif /* INC_MATRIX_BASE_H_ */
