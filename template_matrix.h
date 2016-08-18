#ifndef _MY_MATRIX
#define _MY_MATRIX

#include <iostream>

template <typename T>
class Matrix {
private:
	T* matrix_;
	int row_;
	int column_;
	int size_;
public:
	Matrix() noexcept;
	Matrix(int row_count, int column_count) noexcept;
    Matrix(const Matrix<T>&) noexcept;

	inline int Size() const noexcept { return size_; }
	inline int GetRowCount() const noexcept { return row_; }
	inline int GetColumnCount() const noexcept { return column_; }

	Matrix<T>& operator=(const Matrix<T>&) noexcept;

	bool operator==(const Matrix<T>&) const noexcept;
	template<typename T> friend std::ostream& operator << (std::ostream& os, const Matrix<T>& mtrx) noexcept;
	template<typename T> friend std::istream& operator >> (std::istream& is, Matrix<T>& mtrx) noexcept;
	
	Matrix<T> operator+ (const Matrix<T>&);
	Matrix<T> operator+ (const T val);
	Matrix<T> operator- (const Matrix<T>&);
	Matrix<T> operator- (const T val);
    Matrix<T> operator* (const Matrix<T>&);
	Matrix<T> operator* (const T val);
	/*
	implements += , -= , *=, and friends operators!
	*/

	~Matrix();
};

#endif

template<typename T>
Matrix<T>::Matrix() noexcept : matrix_(nullptr) , row_(0), column_(0), size_(0)
{
}

template<typename T>
Matrix<T>::Matrix(int row_count, int column_count) noexcept : row_(row_count) , column_(column_count) , size_(row_ * column_)
{
	matrix_ = new T[size_];

	for (int i = 0; i < size_; i++)
		matrix_[i] = 0;

}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &mtrx_) noexcept
{
	row_ = mtrx_.row_;
	column_ = mtrx_.column_;
	size_ = row_ * column_;
	matrix_ = new T[size_];

	for (int i = 0; i < size_; i++)
	{
		matrix_[i] = mtrx_.matrix_[i];
	}
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mtrx_t) noexcept
{
	if (this == &mtrx_t)
		return *this;

	delete[] matrix_;

	row_ = mtrx_t.row_;
	column_ = mtrx_t.column_;
	size_ = row_ * column_;
	matrix_ = new T[size_];

	for (int i = 0; i < size_; i++)
	{
		matrix_[i] = mtrx_t.matrix_[i];
	}

	return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& mtrx) const noexcept
{
	if (row_ != mtrx.row_ || column_ != mtrx.column_)
		return false;

	bool state = false;

	for (int i = 0; i < size_; i++)
	{
		if (matrix_[i] == mtrx.matrix_[i])
			state = true;
		else state = false;
	}

	return state;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& mtrx)
{
	if (row_ != mtrx.row_ || column_ != mtrx.column_)
		throw std::exception("Matrix 1 column & row count must be equal matrix 2 column & row count!");

	Matrix<T> temp(row_, column_);

	for (int i = 0; i < size_; i++)
	{
		temp.matrix_[i] = matrix_[i] + mtrx.matrix_[i];
	}

	return temp;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const T val)
{
	Matrix<T> result(*this);
	for (int i = 0; i < result.size_; i++)
		result.matrix_[i] += val;

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& mtrx)
{
	Matrix<T> result(*this);

	for (int i = 0; i < result.size_; i++)
		result.matrix_[i] -= mtrx.matrix_[i];

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const T val)
{
	Matrix<T> result(*this);

	for (int i = 0; i < result.size_; i++)
		result.matrix_[i] -= val;

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& mtrx)
{
	if (column_ != mtrx.row_)
		throw std::exception("Matrix 1 column count must be equal matrix 2 row count!");

	Matrix<T> temp(row_, mtrx.column_);
	
	T sum = 0;
	int next = 0;
	int brk = 0;
	int jrl = 0;
	for (int k = 0; k < row_; k++) {
		for (int p = 0; p < mtrx.column_; p++) {
			for (int i = jrl, j = brk++, iter = 0; iter < column_; i++, iter++, j = j + mtrx.column_) {
				sum = sum + matrix_[i] * mtrx.matrix_[j];
			}

			temp.matrix_[next++] = sum;
			sum = 0;
		}
		jrl += column_;
		brk = 0;
		sum = 0;

	}

	return temp;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T val)
{
	Matrix<T> result(*this);

	for (int i = 0; i < result.size_; i++)
		result.matrix_[i] *= val;

	return result;
}

template<typename T>
Matrix<T>::~Matrix()
{
	delete matrix_;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T>& mtrx) noexcept
{
	for (int i = 0; i < mtrx.size_; i++)
	{
		os << mtrx.matrix_[i] << " ";
		if ((i + 1) % mtrx.column_ == 0)
			os << std::endl;
	}
	os << std::endl;

	return os;
}

template<typename T>
std::istream & operator >> (std::istream & is, Matrix<T>& mtrx) noexcept
{
	for (int i = 0; i < mtrx.size_; i++)
	{
		is >> mtrx.matrix_[i];
	}

	return is;
}
