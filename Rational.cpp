#include "Rational.h"

void Rational::Simplify()
{
	BigInteger nod = HOD(numerator, denuminator);
	numerator /= nod;
	denuminator /= nod;
}

BigInteger Rational::HOD(BigInteger a, BigInteger b) const
{
	if (a > b)
		std::swap(a, b);
	while (b)
	{
		BigInteger t = b;
		b = a % b;
		a = t;
	}
	return a;
}

bool Rational::isLess(const Rational& left_, const Rational& right_) const
{
	if (left_.sign < right_.sign)
		return true;
	if (left_.sign > right_.sign)
		return false;
	BigInteger left;
	BigInteger right;
	BigInteger nod_denuminator = HOD(left_.denuminator, right_.denuminator);
	left = left_.numerator * right_.denuminator / nod_denuminator;
	right = right_.numerator * left_.denuminator / nod_denuminator;
	bool answer = left < right;
	if (left_.sign == -1)
		answer = !answer;
	return answer;
}

Rational::Rational(int num, int denum)
{
	if (denum == 0)
		throw std::runtime_error ("incorrect denuminator in constructor rational int-int");
	if (num < 0 && denum > 0)
	{
		sign = -1;
		num *= -1;
	}
	if (num > 0 && denum < 0)
	{
		sign = -1;
		denum *= -1;
	}
	if (num < 0 && denum < 0)
	{
		sign = 1;
		denum *= -1;
		num *= -1;
	}
	numerator = BigInteger(num);
	denuminator = BigInteger(denum);
	Simplify();
}

Rational::Rational(BigInteger num, BigInteger denum)
{
	if (denum == 0)
		throw std::runtime_error("incorrect denuminator in constructor rational BigInt-BigInt");
	if (num < 0 && denum > 0)
	{
		sign = -1;
		num *= -1;
	}
	if (num > 0 && denum < 0)
	{
		sign = -1;
		denum *= -1;
	}
	if (num < 0 && denum < 0)
	{
		sign = 1;
		denum *= -1;
		num *= -1;
	}
	numerator = num;
	denuminator = denum;
	Simplify();
}

Rational Rational::operator-() const
{
	Rational result = *this;
	result.sign *= -1;
	return result;
}

Rational& Rational::operator+=(const Rational& right)
{
	BigInteger nod_denuminator = HOD(denuminator, right.denuminator);
	BigInteger l = numerator * right.denuminator / nod_denuminator;
	BigInteger r = right.numerator * denuminator / nod_denuminator;
	denuminator = denuminator * right.denuminator / nod_denuminator;
	if (sign == 1 && right.sign == 1)
		numerator = l + r;
	else if (sign == 1 && right.sign == -1)
		numerator = l - r;
	else if (sign == -1 && right.sign == 1)
		numerator = l - r;
	else if (sign == -1 && right.sign == -1)
	{
		numerator = l + r;
		sign = -1;
	}
	if (numerator < 0)
	{
		numerator *= (-1);
		sign *= -1;
	}
	Simplify();
	return *this;
}

Rational& Rational::operator-=(const Rational& right)
{
	BigInteger nod_denuminator = HOD(denuminator, right.denuminator);
	BigInteger l = numerator * right.denuminator / nod_denuminator;
	BigInteger r = right.numerator * denuminator / nod_denuminator;
	denuminator = denuminator * right.denuminator / nod_denuminator;
	if (sign == 1 && right.sign == 1)
		numerator = l - r;
	else if (sign == 1 && right.sign == -1)
		numerator = l + r;
	else if (sign == -1 && right.sign == 1)
	{
		numerator = l + r;
		sign = -1;
	}
	else if (sign == -1 && right.sign == -1)
		numerator = l - r;

	if (numerator < 0)
	{
		numerator *= (-1);
		sign *= -1;
	}
	Simplify();
	return *this;
}

Rational& Rational::operator*=(const Rational& right)
{
	numerator *= right.numerator;
	denuminator *= right.denuminator;
	sign *= right.sign;
	Simplify();
	return *this;
}

Rational& Rational::operator/=(const Rational& right)
{
	numerator *= right.denuminator;
	denuminator *= right.numerator;
	sign *= right.sign;
	Simplify();
	return *this;
}

std::string Rational::toString() const
{
	std::string num = numerator.toString();
	std::string den = denuminator.toString();
	std::string answer;
	if (sign == -1)
		answer.push_back('-');
	answer += num;
	if (denuminator == 1)
		return answer;
	answer += den;
	return answer;
}

std::string Rational::toString()
{
	Simplify();
	std::string num = numerator.toString();
	std::string den = denuminator.toString();
	std::string answer;
	if (sign == -1)
		answer.push_back('-');
	answer += num;
	if (denuminator == 1)
		return answer;
	answer += "/";
	answer += den;
	return answer;
}

std::string Rational::asDecimal(size_t precision) const
{
	BigInteger entire = (numerator - (numerator % denuminator)) / denuminator;
	std::string answer;
	if (sign == -1)
		answer.push_back('-');
	answer += entire.toString();
	if (precision == 0)
		return answer;


	std::string frac = (numerator % denuminator).toString();
	for (size_t i = 0; i < precision; ++i)
		frac += "0";
	BigInteger fraction(frac);
	fraction /= denuminator;
	answer.push_back('.');
	std::string str_fraction = fraction.toString();
	while (str_fraction.size() < precision)
		str_fraction.insert(str_fraction.begin(),'0');
	answer += str_fraction;
	return answer;
}

Rational::operator double() const
{
	std::string answer = asDecimal(16);
	return stod(answer);
}

void Rational::Print()
{
	if (sign == -1)
		std::cout << "-";
	std::cout << numerator;
	if (denuminator == 1)
		return;
	std::cout << "/";
	std::cout << denuminator;
}

Rational operator+(const Rational& left, const Rational& right)
{
	Rational result = left;
	result += right;
	return result;
}

Rational operator-(const Rational& left, const Rational& right)
{
	Rational result = left;
	result -= right;
	return result;
}

Rational operator*(const Rational& left, const Rational& right)
{
	Rational result = left;
	result *= right;
	return result;
}

Rational operator/(const Rational& left, const Rational& right)
{
	Rational result = left;
	result /= right;
	return result;
}

bool operator==(const Rational& left, const Rational& right)
{
	if (left.denuminator == right.denuminator && left.numerator == right.numerator)
		return true;
	return false;
}

bool operator!=(const Rational& left, const Rational& right)
{
	return !(left == right);
}

bool operator<(const Rational& left, const Rational& right)
{
	return left.isLess(left, right);
}

bool operator>(const Rational& left, const Rational& right)
{
	return left.isLess(right, left);
}

bool operator<=(const Rational& left, const Rational& right)
{
	return (left.isLess(left, right) || left == right);
}

bool operator>=(const Rational& left, const Rational& right)
{
	return (left.isLess(right, left) || left == right);
}