#include "matrix.h"
#include "comparinator.h"
#include "tuple.h"
#include <cmath>
#include <iostream>

Matrix::Matrix()
{
	mbrRows = 4;
	mbrColumns = 4;
	// this->mbrGrid = new double* [mbrRows];
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	this->mbrGrid[i] = new double[mbrColumns];
	// }
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	for (int j = 0; j < mbrColumns; ++j)
	// 	{
	// 		i == j ? this->mbrGrid[i][j] = 1 : this->mbrGrid[i][j] = 0;
	// 	}
	// }
	for (int i = 0; i < mbrRows; ++i)
	{
		mbrGrid.push_back(std::vector<double>());
		for (int j = 0; j < mbrColumns; ++j)
		{
			i == j ? mbrGrid[i].push_back(1) : mbrGrid[i].push_back(0);
		}
	}
}
Matrix::Matrix(int rows, int columns)
{
	mbrRows = rows;
	mbrColumns = columns;
	// this->mbrGrid = new double* [mbrRows];
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	this->mbrGrid[i] = new double[mbrColumns];
	// }
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	for (int j = 0; j < mbrColumns; ++j)
	// 	{
	// 		i == j ? this->mbrGrid[i][j] = 1 : this->mbrGrid[i][j] = 0;
	// 	}
	// }
	for (int i = 0; i < mbrRows; ++i)
	{
		mbrGrid.push_back(std::vector<double>());
		for (int j = 0; j < mbrColumns; ++j)
		{
			i == j ? mbrGrid[i].push_back(1) : mbrGrid[i].push_back(0);
		}
	}
}

Matrix::Matrix(const Matrix& other)
{
	//std::cout << "matrix copy ctor" << std::endl;
	this->mbrRows = other.mbrRows;
	this->mbrColumns = other.mbrColumns;
	//std::cout << "this: " << mbrRows << mbrColumns << " other:" << other.mbrRows << other.mbrColumns << std::endl;
	for (int i = 0; i < mbrRows; ++i)
	{
		mbrGrid.push_back(std::vector<double>());
		for (int j = 0; j < mbrColumns; ++j)
		{
			mbrGrid[i].push_back(other.mbrGrid[i][j]);
		}
	}
	// this->mbrGrid = new double* [mbrRows];
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	this->mbrGrid[i] = new double[mbrColumns];
	// }
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	for (int j = 0; j < mbrColumns; ++j)
	// 	{
	// 		this->mbrGrid[i][j] = other.mbrGrid[i][j];
	// 		//std::cout << "this: " << mbrGrid[i][j] << " other:" << other.mbrGrid[i][j] << std::endl;
	// 	}
	// }
}
Matrix::Matrix(Matrix &&argOther) noexcept {
	mbrRows = argOther.mbrRows;
	mbrColumns = argOther.mbrColumns;
	mbrGrid = argOther.mbrGrid;
}
Matrix::Matrix(Matrix *other)
{
	//std::cout << "matrix copy ctor" << std::endl;
	mbrRows = other->mbrRows;
	mbrColumns = other->mbrColumns;
	//std::cout << "this: " << mbrRows << mbrColumns << " other:" << other.mbrRows << other.mbrColumns << std::endl;
	for (int i = 0; i < mbrRows; ++i)
	{
		mbrGrid.push_back(std::vector<double>());
		for (int j = 0; j < mbrColumns; ++j)
		{
			mbrGrid[i].push_back(other->mbrGrid[i][j]);
		}
	}
	// this->mbrGrid = new double* [mbrRows];
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	this->mbrGrid[i] = new double[mbrColumns];
	// }
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	for (int j = 0; j < mbrColumns; ++j)
	// 	{
	// 		this->mbrGrid[i][j] = other->mbrGrid[i][j];
	// 		//std::cout << "this: " << mbrGrid[i][j] << " other:" << other.mbrGrid[i][j] << std::endl;
	// 	}
	// }
}

Matrix::Matrix(int rows, int columns, double* values)
{
	mbrRows = rows;
	mbrColumns = columns;
	// this->mbrGrid = new double* [mbrRows];
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	this->mbrGrid[i] = new double[mbrColumns];
	// }
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	for (int j = 0; j < mbrColumns; ++j)
	// 	{
	// 		this->mbrGrid[i][j] = values[(i * columns) + j];
	// 	}
	// }
	for (int i = 0; i < mbrRows; ++i)
	{
		mbrGrid.push_back(std::vector<double>());
		for (int j = 0; j < mbrColumns; ++j)
		{
			mbrGrid[i].push_back(values[(i * columns) + j]);
		}
	}
}

Matrix::~Matrix()
{
	//std::cout << "deleting matrix" << &grid << std::endl;
	// if (mbrGrid!=nullptr) {
	// 	for (int i = 0; i < mbrRows; ++i)
	// 	{
	// 		if (mbrGrid[i]!=nullptr) {
	// 			delete[] this->mbrGrid[i];
	// 			this->mbrGrid[i] = nullptr;
	// 		}
	// 	}
	// 		delete[] this->mbrGrid;
	// 		this->mbrGrid = nullptr;
	// }
}

Matrix& Matrix::operator=(const Matrix &other)
{
	if (this == &other) return *this;
	//std::cout << "matrix copy assign" << std::endl;
	this->mbrRows = other.mbrRows;
	this->mbrColumns = other.mbrColumns;
	for (int i = 0; i < mbrRows; ++i)
	{
		mbrGrid.push_back(std::vector<double>());
		for (int j = 0; j < mbrColumns; ++j)
		{
			this->mbrGrid[i][j] = other.mbrGrid[i][j];
		}
	}
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	delete[] this->mbrGrid[i];
	// 	this->mbrGrid[i] = nullptr;
	// }
	// delete[] this->mbrGrid;
	// this->mbrGrid = nullptr;
	// this->mbrGrid = new double* [mbrRows];
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	this->mbrGrid[i] = new double[mbrColumns];
	// }
	// for (int i = 0; i < mbrRows; ++i)
	// {
	// 	for (int j = 0; j < mbrColumns; ++j)
	// 	{
	// 		this->mbrGrid[i][j] = other.mbrGrid[i][j];
	// 	}
	// }
	return *this;
}
Matrix& Matrix::operator=(const Matrix &&argOther) noexcept {
	if (this == &argOther) { return *this; }
	mbrRows = argOther.mbrRows;
	mbrColumns = argOther.mbrColumns;
	mbrGrid = argOther.mbrGrid;
	return *this;
}
bool Matrix::operator==(const Matrix &other) const
{
	//std::cout << "matrix equality operator" << std::endl;
	if (other.mbrRows != mbrRows || other.mbrColumns != mbrColumns)
	{
		return false;
	}
	for (int i = 0; i < mbrRows; ++i)
	{
		for (int j = 0; j < mbrColumns; ++j)
		{
			//std::cout << "addresses this:" << &grid[i][j] << ":other:" << &other.grid[i][j] << std::endl;
			//std::cout << "values this:" << grid[i][j] << ":other:" << other.grid[i][j] << std::endl;
			if (other.mbrGrid[i][j] != this->mbrGrid[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool Matrix::checkEqual(const Matrix &other) const
{
	//std::cout << "matrix equality" << std::endl;
	if (other.mbrRows != mbrRows || other.mbrColumns != mbrColumns)
	{
		return false;
	}
	Comparinator ce = Comparinator();
	//std::cout << "row == column" << std::endl;
	for (int i = 0; i < mbrRows; ++i)
	{
		for (int j = 0; j < mbrColumns; ++j)
		{
			//std::cout << "addresses this:" << & grid[i][j] << ":other:" << &other.grid[i][j] << std::endl;
			//std::cout << "values this:" << grid[i][j] << ":other:" << other.grid[i][j] << std::endl;
			if (!ce.checkFloat(other.mbrGrid[i][j],this->mbrGrid[i][j]))
			{
				return false;
			}
		}
	}
	return true;
}
Matrix Matrix::operator*(const Matrix &other)
{
	//std::cout << "matrix multiplication" << std::endl;
	Matrix result = Matrix(other.mbrRows, other.mbrColumns);
	for (int i = 0; i < result.mbrRows; ++i)
	{
		for (int j = 0; j < result.mbrColumns; ++j)
		{
			double value = 0;
			for (int k = 0; k < result.mbrColumns; k++)
			{
				//std::cout << "i:" << i << "j:" << j << "k:" << k << "=" << grid[i][k] << "*" << other.grid[k][j] << std::endl;
				value += mbrGrid[i][k] * other.mbrGrid[k][j];
			}
			//std::cout << value << std::endl;
			result.setRC(i, j, value);
		}
	}
	return result;
}
// Matrix* Matrix::operator*(const Matrix &other)
// {
// 	//std::cout << "matrix multiplication" << std::endl;
// 	Matrix* result = new Matrix(other.mbrRows, other.mbrColumns);
// 	for (int i = 0; i < result->mbrRows; ++i)
// 	{
// 		for (int j = 0; j < result->mbrColumns; ++j)
// 		{
// 			double value = 0;
// 			for (int k = 0; k < result->mbrColumns; k++)
// 			{
// 				//std::cout << "i:" << i << "j:" << j << "k:" << k << "=" << grid[i][k] << "*" << other.grid[k][j] << std::endl;
// 				value += mbrGrid[i][k] * other.mbrGrid[k][j];
// 			}
// 			//std::cout << value << std::endl;
// 			result->setRC(i, j, value);
// 		}
// 	}
// 	return result;
// }

Tuple Matrix::operator*(const Tuple &other)
{
	if (mbrRows != 4 && mbrColumns != 4) return other;
	//std::cout << "matrix tuple multiplication" << std::endl;
	double pseudoMatrix[4] = {other.mbrX, other.mbrY, other.mbrZ, other.mbrW};
	double results[4] = { 0,0,0,0 };
	double res = 0;
	for (int tuple = 0; tuple < 4; tuple++)
	{
		res = 0;
		for (int col = 0; col < mbrColumns; col++)
		{
			//std::cout << "i:" << col << "j:" << tuple << "k:" << res << "=" << pseudoMatrix[col] << "*" << grid[tuple][col] << std::endl;
			res += mbrGrid[tuple][col] * pseudoMatrix[col];
		}
		results[tuple] = res;
	}
	return Tuple(results[0],results[1],results[2],results[3]);
}
Point Matrix::operator*(const Point &other)
{
	Tuple tp = Tuple(other.mbrX, other.mbrY, other.mbrZ, other.mbrW);
	Tuple res = *(this) * tp;
	return Point(res.mbrX, res.mbrY, res.mbrZ);
}
Vector Matrix::operator*(const Vector &other)
{
	Tuple tp = Tuple(other.mbrX, other.mbrY, other.mbrZ, other.mbrW);
	Tuple res = *(this) * tp;
	return Vector(res.mbrX, res.mbrY, res.mbrZ);
}

bool Matrix::checkInvertible() const {
	return determinant() != 0;
}
bool Matrix::checkValid(int row, int column) const
{
	return row >= 0 && row < mbrRows && column >= 0 && column < mbrColumns;
}

double Matrix::getRC(int row, int column) const
{
	if (checkValid(row, column))
	{
		return this->mbrGrid[row][column];
	}
	return 0;
}

void Matrix::setRC(int row, int column, double value)
{
	if (checkValid(row, column))
	{
		this->mbrGrid[row][column] = value;
	}
}
Matrix Matrix::transpose()
{
	Matrix copy = Matrix(mbrColumns, mbrRows);
	for (int i = 0; i < copy.mbrRows; ++i)
	{
		for (int j = 0; j < copy.mbrColumns; ++j)
		{
			copy.setRC(i, j, getRC(j, i));
			//std::cout << "i:" << i << "j:" << j << "now: " << this->getRC(j, i) << "=" << copy->getRC(i, j) << std::endl;
		};
	};
	return copy;
}
// Matrix* Matrix::transpose()
// {
// 	Matrix* copy = new Matrix(mbrColumns, mbrRows);
// 	for (int i = 0; i < copy->mbrRows; ++i)
// 	{
// 		for (int j = 0; j < copy->mbrColumns; ++j)
// 		{
// 			copy->setRC(i, j, this->getRC(j, i));
// 			//std::cout << "i:" << i << "j:" << j << "now: " << this->getRC(j, i) << "=" << copy->getRC(i, j) << std::endl;
// 		};
// 	};
// 	return copy;
// }

double Matrix::determinant() const
{
	double determinant = 0;
	if (mbrRows == 2 && mbrColumns == 2) determinant = mbrGrid[0][0] * mbrGrid[1][1] - mbrGrid[0][1] * mbrGrid[1][0];
	else
	{
		for (int i = 0; i < mbrColumns; ++i)
		{
			determinant += cofactor(0, i) * getRC(0, i);
		};
	};
	return determinant;
}
Matrix Matrix::submatrix(int row, int column) const
{
	Matrix sub = Matrix(mbrRows - 1, mbrColumns - 1);
	int subrow = 0;
	int subcol = 0;
	int i = 0;
	int j = 0;
	while (i < mbrRows)
	{
		if (i == row) { i += 1; }
		j = 0;
		subcol = 0;
		while (j < mbrColumns)
		{
			if (j == column) { j += 1; }
			sub.setRC(subrow, subcol, getRC(i, j));
			//std::cout << "i:" << subrow << "j:" << subcol << "now: " << this->getRC(i, j) << "=" << sub->getRC(subrow, subcol) << std::endl;
			j += 1;
			subcol += 1;
		}
		i += 1;
		subrow += 1;
	}
	return sub;
}
// Matrix* Matrix::submatrix(int row, int column) const
// {
// 	Matrix* sub = new Matrix(mbrRows - 1, mbrColumns - 1);
// 	int subrow = 0;
// 	int subcol = 0;
// 	int i = 0;
// 	int j = 0;
// 	while (i < mbrRows)
// 	{
// 		if (i == row) { i += 1; }
// 		j = 0;
// 		subcol = 0;
// 		while (j < mbrColumns)
// 		{
// 			if (j == column) { j += 1; }
// 			sub->setRC(subrow, subcol, this->getRC(i, j));
// 			//std::cout << "i:" << subrow << "j:" << subcol << "now: " << this->getRC(i, j) << "=" << sub->getRC(subrow, subcol) << std::endl;
// 			j += 1;
// 			subcol += 1;
// 		}
// 		i += 1;
// 		subrow += 1;
// 	}
// 	return sub;
// }

double Matrix::minor(int row, int column) const
{
	return submatrix(row, column).determinant();
}

double Matrix::cofactor(int row, int column) const
{
	return (row + column) % 2 == 0 ? this->minor(row, column) : -1 * this->minor(row, column);
}
Matrix Matrix::getInverse() const
{
	// std::cout << "Matrix::invert()" << std::endl;
	Matrix inverse = Matrix(mbrRows, mbrColumns);
	if (!checkInvertible()) return inverse;
	double dm = determinant();
	for (int i = 0; i < mbrRows; ++i)
	{
		for (int j = 0; j < mbrColumns; ++j)
		{
			double cf = cofactor(i, j);
			inverse.setRC(j, i, cf / dm);
			// std::cout << "j:" << j << "i:" << i << "now: " << cf << "/" << dm << "=" << inverse->getRC(j, i) << std::endl;
		};
	};
	return inverse;
}
// Matrix* Matrix::invert() const
// {
// 	// std::cout << "Matrix::invert()" << std::endl;
// 	Matrix* inverse = new Matrix(mbrRows, mbrColumns);
// 	if (!checkInvertible()) return inverse;
// 	double dm = this->determinant();
// 	for (int i = 0; i < this->mbrRows; ++i)
// 	{
// 		for (int j = 0; j < this->mbrColumns; ++j)
// 		{
// 			double cf = this->cofactor(i, j);
// 			inverse->setRC(j, i, cf / dm);
// 			// std::cout << "j:" << j << "i:" << i << "now: " << cf << "/" << dm << "=" << inverse->getRC(j, i) << std::endl;
// 		};
// 	};
// 	return inverse;
// }
Matrix Matrix::identity()
{
	Matrix identity = Matrix(mbrRows, mbrColumns);
	for (int i = 0; i < identity.mbrRows; ++i)
	{
		for (int j = 0; j < identity.mbrColumns; ++j)
		{
			i == j ? identity.mbrGrid[i][j] = 1 : identity.mbrGrid[i][j] = 0;
		};
	};
	return identity;
}
// Matrix* Matrix::identity()
// {
// 	Matrix* identity = new Matrix(mbrRows, mbrColumns);
// 	for (int i = 0; i < identity->mbrRows; ++i)
// 	{
// 		for (int j = 0; j < identity->mbrColumns; ++j)
// 		{
// 			i == j ? identity->mbrGrid[i][j] = 1 : identity->mbrGrid[i][j] = 0;
// 		};
// 	};
// 	return identity;
// }
Matrix Matrix::rotateX(double radians)
{
	XRotationMatrix rotate = XRotationMatrix(radians);
	return *this * rotate;
}
Matrix Matrix::rotateY(double radians)
{
	YRotationMatrix rotate = YRotationMatrix(radians);
	return *this * rotate;
}
Matrix Matrix::rotateZ(double radians)
{
	ZRotationMatrix rotate = ZRotationMatrix(radians);
	return *this * rotate;
}
Matrix Matrix::scale(int x, int y, int z)
{
	ScalingMatrix scale = ScalingMatrix(x,y,z);
	return *this * scale;
}
Matrix Matrix::translate(int x, int y, int z)
{
	TranslationMatrix translate = TranslationMatrix(x,y,z);
	return *this * translate;
}
Matrix Matrix::shear(double xy, double xz, double yx, double yz, double zx, double zy)
{
	ShearingMatrix shear = ShearingMatrix(xy, xz, yx, yz, zx, zy);
	return *this * shear;
}
// Matrix* Matrix::rotateX(double radians)
// {
// 	XRotationMatrix rotate = XRotationMatrix(radians);
// 	return *this * rotate;
// }
// Matrix* Matrix::rotateY(double radians)
// {
// 	YRotationMatrix rotate = YRotationMatrix(radians);
// 	return *this * rotate;
// }
// Matrix* Matrix::rotateZ(double radians)
// {
// 	ZRotationMatrix rotate = ZRotationMatrix(radians);
// 	return *this * rotate;
// }
// Matrix* Matrix::scale(int x, int y, int z)
// {
// 	ScalingMatrix scale = ScalingMatrix(x,y,z);
// 	return *this * scale;
// }
// Matrix* Matrix::translate(int x, int y, int z)
// {
// 	TranslationMatrix translate = TranslationMatrix(x,y,z);
// 	return *this * translate;
// }
// Matrix* Matrix::shear(double xy, double xz, double yx, double yz, double zx, double zy)
// {
// 	ShearingMatrix shear = ShearingMatrix(xy, xz, yx, yz, zx, zy);
// 	return *this * shear;
// }
void Matrix::renderConsole() const
{
	std::cout << "Matrix::renderConsole()" << std::endl;
	for (int i = 0; i < mbrRows; ++i)
	{
		std::cout << "[";
		for (int j = 0; j < mbrColumns; ++j)
		{
			std::cout << mbrGrid[i][j] << ", ";
		};
		std::cout << "]" << std::endl;
	};
}

IdentityMatrix::IdentityMatrix (int rows, int columns) : Matrix(rows = rows, columns = columns)
{
	for (int i = 0; i < mbrRows; ++i)
	{
		for (int j = 0; j < mbrColumns; ++j)
		{
			i == j ? this->mbrGrid[i][j] = 1 : this->mbrGrid[i][j] = 0;
		};
	};
}

TranslationMatrix::TranslationMatrix(double x, double y, double z) : Matrix(4, 4)
{
	this->mbrGrid[0][0] = 1;
	this->mbrGrid[0][3] = x;
	this->mbrGrid[1][3] = y;
	this->mbrGrid[1][1] = 1;
	this->mbrGrid[2][3] = z;
	this->mbrGrid[2][2] = 1;
	this->mbrGrid[3][3] = 1;
}

ScalingMatrix::ScalingMatrix(double x, double y, double z) : Matrix(4, 4)
{
	this->mbrGrid[0][0] = x;
	this->mbrGrid[1][1] = y;
	this->mbrGrid[2][2] = z;
	this->mbrGrid[3][3] = 1;
}

XRotationMatrix::XRotationMatrix(double radians) : Matrix(4, 4)
{
	this->mbrGrid[0][0] = 1;
	this->mbrGrid[1][1] = cos(radians);
	this->mbrGrid[1][2] = -sin(radians);
	this->mbrGrid[2][1] = sin(radians);
	this->mbrGrid[2][2] = cos(radians);
	this->mbrGrid[3][3] = 1;
}

YRotationMatrix::YRotationMatrix(double radians) : Matrix(4, 4)
{
	this->mbrGrid[0][0] = cos(radians);
	this->mbrGrid[0][2] = sin(radians);
	this->mbrGrid[1][1] = 1;
	this->mbrGrid[2][0] = -sin(radians);
	this->mbrGrid[2][2] = cos(radians);
	this->mbrGrid[3][3] = 1;
}

ZRotationMatrix::ZRotationMatrix(double radians) : Matrix(4, 4)
{
	this->mbrGrid[0][0] = cos(radians);
	this->mbrGrid[0][1] = -sin(radians);
	this->mbrGrid[1][0] = sin(radians);
	this->mbrGrid[1][1] = cos(radians);
	this->mbrGrid[2][2] = 1;
	this->mbrGrid[3][3] = 1;
}

ShearingMatrix::ShearingMatrix(double xy, double xz, double yx, double yz, double zx, double zy) : Matrix(4, 4)
{
	this->mbrGrid[0][0] = 1;
	this->mbrGrid[0][1] = xy;
	this->mbrGrid[0][2] = xz;
	this->mbrGrid[1][0] = yx;
	this->mbrGrid[1][1] = 1;
	this->mbrGrid[1][2] = yz;
	this->mbrGrid[2][0] = zx;
	this->mbrGrid[2][1] = zy;
	this->mbrGrid[2][2] = 1;
	this->mbrGrid[3][3] = 1;
}

ViewMatrix::ViewMatrix() : Matrix()
{
	for (int i = 0; i < mbrRows; ++i)
	{
		for (int j = 0; j < mbrColumns; ++j)
		{
			i == j ? this->mbrGrid[i][j] = 1 : this->mbrGrid[i][j] = 0;
		};
	};
}

ViewMatrix::ViewMatrix(Point start, Point end, Vector up) : Matrix()
{
	Vector varForward = (end - start).normalize();
	Vector varLeft = varForward.cross(up.normalize());
	Vector varUp = varLeft.cross(varForward);
	double varValues[] = {varLeft.mbrX, varLeft.mbrY, varLeft.mbrZ, 0, varUp.mbrX, varUp.mbrY, varUp.mbrZ, 0, -varForward.mbrX, -varForward.mbrY, -varForward.mbrZ, 0, 0, 0, 0, 1};
	Matrix varOrientation = Matrix(4,4, varValues);
	Matrix varResult = varOrientation * TranslationMatrix(-start.mbrX, -start.mbrY, -start.mbrZ);
	for (int i = 0; i < mbrRows; ++i)
	{
		for (int j = 0; j < mbrColumns; ++j)
		{
			this->mbrGrid[i][j] = varResult.mbrGrid[i][j];
			// std::cout << "addresses this:" << & grid[i][j] << ":other:" << &varResult->grid[i][j] << std::endl;
			// std::cout << "values this:" << grid[i][j] << ":other:" << varResult->grid[i][j] << std::endl;
		};
	};
}