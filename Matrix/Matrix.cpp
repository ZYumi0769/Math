﻿/* OSL/Matrix/matrix.cpp
 *
 * Copyright (C) 2021 YuminZhan
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this
 * program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "pch.h"
#include "matrix.h"
using osl::element;
using osl::vector;
using osl::matrix;
using std::cout;
using std::cin;
using std::endl;

// Constructors & Destructor ------------------------------------------------------------

template<class elm>
matrix<elm>::matrix(int nrow, int ncol, agm_elm value) :
	_nrow(nrow), _ncol(ncol), pointer(NULL)
{
	if (_nrow < 0) {
		throw exc::matrix(4U, "matrix(int nrow, int ncol, agm_elm value)");
	}
	if (_ncol < 0) {
		throw exc::matrix(5U, "matrix(int nrow, int ncol, agm_elm value)");
	}
	if (_nrow == 0) {
		return;
	}
	pointer = new vector<elm>[_nrow];
	if (pointer == NULL) {
		throw exc::matrix(0U, "matrix(int nrow, int ncol, agm_elm value)");
	}
	if (_ncol == 0) {
		return;
	}
	for (int i(0); i < _nrow; i++) {
		try {
			pointer[i].append(_ncol, value);
		}
		catch (exc::vector excv) {
			delete[] pointer;
			throw exc::matrix(excv.code, "matrix(int nrow, int ncol, agm_elm value)");
		}
	}
}

template<class elm>
matrix<elm>::matrix(agm_mat origin) :
	_nrow(origin._nrow), _ncol(origin._ncol), pointer(NULL)
{
	if (_nrow == 0) {
		return;
	}
	pointer = new vector<elm>[_nrow];
	if (pointer == NULL) {
		throw exc::matrix(0U, "matrix(agm_mat origin)");
	}
	if (_ncol == 0) {
		return;
	}
	for (int i(0); i < _nrow; i++) {
		try {
			pointer[i].append(origin.pointer[i]);
		}
		catch (exc::vector excv) {
			delete[] pointer;
			throw exc::matrix(excv.code, "matrix(agm_mat origin)");
		}
	}
}

template<class elm>
matrix<elm>::matrix(agm_mat origin, int start_row, int end_row, int start_col, int end_col) :
	_nrow(end_row + 1 - start_row), _ncol(end_col + 1 - start_col), pointer(NULL)
{
	if (_nrow < 0 || _ncol < 0) {
		throw exc::matrix(6U, "matrix(agm_mat origin, int start_row, int end_row, int start_col, int end_col)");
	}
	if (_nrow == 0) {
		return;
	}
	pointer = new vector<elm>[_nrow];
	if (pointer == NULL) {
		throw exc::matrix(0U, "matrix(agm_mat origin, int start_row, int end_row, int start_col, int end_col)");
	}
	if (_ncol == 0) {
		return;
	}
	for (int i(0); i < _nrow; i++) {
		try {
			pointer[i].append(0.0, _ncol);
			pointer[i].cover(origin.pointer[i + start_row], start_col);
		}
		catch (exc::vector excv) {
			delete[] pointer;
			throw exc::matrix(excv.code, "matrix(agm_mat origin, int start_row, int end_row, int start_col, int end_col)");
		}
	}
}

template<class elm>
matrix<elm>::matrix(agm_vec vec, int n) :
	_nrow(n), _ncol(vec.size()), pointer(NULL)
{
	if (_nrow < 0) {
		throw exc::matrix(4U, "matrix(agm_vec vec, int n)");
	}
	if (_nrow == 0) {
		return;
	}
	pointer = new vector<elm>[n];
	if (pointer == NULL) {
		throw exc::matrix(0U, "matrix(agm_vec vec, int n)");
	}
	for (int i(0); i < _nrow; i++) {
		try {
			pointer[i].append(vec);
		}
		catch (exc::vector excv) {
			delete[] pointer;
			throw exc::matrix(excv.code, "matrix(agm_vec vec, int n)");
		}
	}
}

template<class elm>
matrix<elm>::matrix(c_ary ary, int ncol, int n) :
	_nrow(n), _ncol(ncol), pointer(NULL)
{
	if (_nrow < 0) {
		throw exc::matrix(4U, "matrix(c_ary ary, int ncol, int n)");
	}
	if (_ncol < 0) {
		throw exc::matrix(5U, "matrix(c_ary ary, int ncol, int n)");
	}
	if (_nrow == 0) {
		return;
	}
	if (ary == NULL) {
		throw exc::matrix(1U, "matrix(c_ary ary, int ncol, int n)");
	}
	pointer = new vector<elm>[_nrow];
	if (pointer == NULL) {
		throw exc::matrix(0U, "matrix(c_ary ary, int ncol, int n)");
	}
	for (int i(0); i < _nrow; i++) {
		try {
			pointer[i].append(ary, _ncol);
		}
		catch (exc::vector excv) {
			delete[] pointer;
			throw exc::matrix(excv.code, "matrix(c_ary ary, int ncol, int n)");
		}
	}
}

template<class elm>
matrix<elm>::matrix(c_rary rary, int nrow, int ncol) :
	_nrow(nrow), _ncol(ncol), pointer(NULL)
{
	if (_nrow < 0) {
		throw exc::matrix(4U, "matrix(c_rary rary, int nrow, int ncol)");
	}
	if (_ncol < 0) {
		throw exc::matrix(5U, "matrix(c_rary rary, int nrow, int ncol)");
	}
	if (_nrow == 0) {
		return;
	}
	if (rary == NULL) {
		throw exc::matrix(1U, "matrix(c_rary rary, int nrow, int ncol)");
	}
	pointer = new vector<elm>[_nrow];
	if (pointer == NULL) {
		throw exc::matrix(0U, "matrix(c_rary rary, int nrow, int ncol)");
	}
	for (int i(0); i < _nrow; i++) {
		try {
			pointer[i].append(c_rary[i], _ncol);
		}
		catch (exc::vector excv) {
			delete[] pointer;
			throw exc::matrix(excv.code, "matrix(c_rary rary, int nrow, int ncol)");
		}
	}
}

template<class elm>
matrix<elm>::~matrix()
{
	if (pointer != NULL) {
		delete[] pointer;
	}
}

template<class elm>
inline bool matrix<elm>::empty() const
{
	return (_nrow == 0 || _ncol == 0);
}

template<class elm>
inline int matrix<elm>::nrow() const
{
	return _nrow;
}

template<class elm>
inline int matrix<elm>::ncol() const
{
	return _ncol;
}

template<class elm>
inline elm& matrix<elm>::at(int row, int col) const
{
	if (row < 0 || row >= _nrow) {
		throw exc::matrix(2U, "at(int row, int col)");
	}
	if (col < 0 || col >= _ncol) {
		throw exc::matrix(3U, "at(int row, int col)");
	}
	return pointer[row].at(col);
}

template<class elm>
inline vector<elm> matrix<elm>::at(int row) const
{
	if (row < 0 || row >= _nrow) {
		throw exc::matrix(2U, "at(int row, int col)");
	}
	return pointer[row];
}

template<class elm>
element<elm> matrix<elm>::MAX() const
{
	if (empty()) {
		throw exc::matrix(1U, "MAX()");
	}
	int row(0), col(0);
	element<elm> rst(pointer[0].MAX());
	for (int i(0); i < _nrow; i++) {
		element<elm> t(pointer[i].MAX());
		if (t.value > rst.value) {
			rst = t;
			rst.row = i;
		}
	}
	return rst;
}

template<class elm>
element<elm> osl::matrix<elm>::MIN() const
{
	if (empty()) {
		throw exc::matrix(1U, "MIN()");
	}
	int row(0), col(0);
	element<elm> rst(pointer[0].MIN());
	for (int i(0); i < _nrow; i++) {
		element<elm> t(pointer[i].MIN());
		if (t.value < rst.value) {
			rst = t;
			rst.row = i;
		}
	}
	return rst;
}

template<class elm>
element<elm> osl::matrix<elm>::absmax() const
{
	if (empty()) {
		throw exc::matrix(1U, "absmax()");
	}
	int row(0), col(0);
	element<elm> rst(pointer[0].absmax());
	for (int i(0); i < _nrow; i++) {
		element<elm> t(pointer[i].absmax());
		if (t.value > rst.value) {
			rst = t;
			rst.row = i;
		}
	}
	return rst;
}

template<class elm>
element<elm> osl::matrix<elm>::absmin() const
{
	if (empty()) {
		throw exc::matrix(1U, "absmin()");
	}
	int row(0), col(0);
	element<elm> rst(pointer[0].absmin());
	for (int i(0); i < _nrow; i++) {
		element<elm> t(pointer[i].absmin());
		if (t.value < rst.value) {
			rst = t;
			rst.row = i;
		}
	}
	return rst;
}

template<class elm>
inline vector<elm> matrix<elm>::operator[](int row)
{
	try
	{
		return at(row);
	}
	catch (exc::matrix excm)
	{
		throw exc::matrix(excm.code, "operator[](int row)");
	}
}

template<class elm>
void osl::matrix<elm>::print(c_str separator)
{
	for (int i(0); i < _nrow; i++) {
		pointer[i].print(separator);
	}
}

namespace osl {
	template<typename elm>
	MATRIX_API std::ostream& operator<<(std::ostream& os, const matrix<elm>& mat)
	{
		for (int i(0); i < mat._nrow; i++) {
			os << mat.pointer[i] << endl;
		}
		return os;
	}

	template<typename elm>
	MATRIX_API std::istream& operator>>(std::istream& is, matrix<elm>& mat)
	{
		for (int i(0); i < mat._nrow; i++) {
			is >> mat.pointer[i];
		}
		return is;
	}
}

namespace {
	template <typename elm>
	void template_instantiate(const elm& value) {
		// Constructors & Destructor
		matrix<elm>* a = new matrix<elm>;
		matrix<elm>* b = new matrix<elm>(*a);
		matrix<elm>* c = new matrix<elm>(*b, 0, -1, 0, -1);
		delete a, b, c;
		vector<elm>* vec = new vector<elm>;
		matrix<elm>* d = new matrix<elm>(vec, 1);
		delete d;
		double* ary = new double(0.0);
		matrix<elm>* e = new matrix<elm>(ary, 1);
		delete e;
		double** rary = &ary;
		matrix<elm>* f = new matrix<elm>(rary, 1, 1);
		delete ary; ary = NULL; rary = NULL;

		// Properties
		f->empty();
		f->nrow();
		f->ncol();

		// Element
		f->at(0, 0);
		f->at(0);
		f->MAX();
		f->MIN();
		f->absmax();
		f->absmin();

		// Operators
		(*f)[0];
		cout << (*f);
		cin >> (*f);
		f->print();

		delete f;
	}

	void instantiate() {
		template_instantiate(int(1));
		template_instantiate(double(1));
		template_instantiate(osl::rational(1));
		// template_instantiate(osl::complex(1));
	}
}

