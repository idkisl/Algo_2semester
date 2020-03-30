#pragma once
#include "BigInteger.h"
#include <iostream>
#include <vector>
#include <string>

class Rational
{
	BigInteger numerator;
	BigInteger denuminator;
	int sign = 1;
	void Simplify();
	BigInteger HOD(BigInteger a, BigInteger b) const;
	bool isLess(const Rational& left, const Rational& right) const;
public:
	Rational(int num, int denum = 1);
	Rational(BigInteger num, BigInteger denum = 1);
	Rational() {}
	Rational operator-() const; // унарный минус
	Rational& operator+=(const Rational& right);
	Rational& operator-=(const Rational& right);
	Rational& operator*=(const Rational& right);
	Rational& operator/=(const Rational& right);
	std::string toString() const;
	std::string toString();
	std::string asDecimal(size_t precision = 0) const;
	explicit operator double() const;
	void Print();

	friend Rational operator+(const Rational& left, const Rational& right);
	friend Rational operator-(const Rational& left, const Rational& right);
	friend Rational operator*(const Rational& left, const Rational& right);
	friend Rational operator/(const Rational& left, const Rational& right);
	friend bool operator==(const Rational& left, const Rational& right);
	friend bool operator!=(const Rational& left, const Rational& right);
	friend bool operator<(const Rational& left, const Rational& right);
	friend bool operator>(const Rational& left, const Rational& right);
	friend bool operator<=(const Rational& left, const Rational& right);
	friend bool operator>=(const Rational& left, const Rational& right);
};