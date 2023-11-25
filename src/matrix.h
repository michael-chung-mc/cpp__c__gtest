#pragma once
#ifndef MATRIX_H
#define MATRIX_H

class Tuple;
class Point;
class Vector;
#include <string>
#include <memory>
#include <vector>

class Matrix {
public:
	std::vector<std::vector<double>> _fieldGrid;
	int _fieldRows;
	int _fieldColumns;
	Matrix();
	Matrix(int rows, int columns);
	Matrix(const Matrix& other);
	Matrix(Matrix &&argOther) noexcept;
	Matrix(Matrix *other);
	Matrix(int row, int column, double* values);
	~Matrix();
	Matrix& operator=(const Matrix &other);
	Matrix& operator=(const Matrix &&argOther) noexcept;
	bool operator==(const Matrix &other) const;
	// Matrix* operator*(const Matrix &other);
	Matrix operator*(const Matrix &other);
	Tuple operator*(const Tuple &other);
	Point operator*(const Point &other);
	Vector operator*(const Vector &other);
	bool checkInvertible() const;
	bool checkValid(int row, int column) const;
	bool checkEqual(const Matrix& other) const;
	double getRC(int row, int column) const;
	void setRC(int row, int column, double value);
	double determinant() const;
	double minor(int row, int column) const;
	double cofactor(int row, int column) const;
	Matrix transpose();
	Matrix submatrix(int row, int column) const;
	Matrix getInverse() const;
	Matrix identity();
	Matrix rotateX(double radians);
	Matrix rotateY(double radians);
	Matrix rotateZ(double radians);
	Matrix scale(int x, int y, int z);
	Matrix translate(int x, int y, int z);
	Matrix shear(double xy, double xz, double yx, double yz, double zx, double zy);
	// Matrix* transpose();
	// Matrix* submatrix(int row, int column) const;
	// Matrix* invert() const;
	// Matrix* identity();
	// Matrix* rotateX(double radians);
	// Matrix* rotateY(double radians);
	// Matrix* rotateZ(double radians);
	// Matrix* scale(int x, int y, int z);
	// Matrix* translate(int x, int y, int z);
	// Matrix* shear(double xy, double xz, double yx, double yz, double zx, double zy);
	void renderConsole() const;
};

class IdentityMatrix : public Matrix {
public:
	IdentityMatrix(int rows, int columns);
};

class TranslationMatrix : public Matrix {
public:
	TranslationMatrix(double x, double y, double z);
};

class ScalingMatrix : public Matrix {
public:
	ScalingMatrix(double x, double y, double z);
};

class XRotationMatrix : public Matrix {
public:
	XRotationMatrix(double radians);
};

class YRotationMatrix : public Matrix {
public:
	YRotationMatrix(double radians);
};

class ZRotationMatrix : public Matrix {
public:
	ZRotationMatrix(double radians);
};

class ShearingMatrix : public Matrix {
public:
	ShearingMatrix(double xy, double xz, double yx, double yz, double zx, double zy);
};

class ViewMatrix : public Matrix {
public:
	ViewMatrix();
	ViewMatrix(Point start, Point end, Vector up);
};

#endif