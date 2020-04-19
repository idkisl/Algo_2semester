#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class BigInteger
{
	static const unsigned int BASE = 1000000000;
	static const unsigned int number_size = 9;
	std::vector<unsigned int> number;
	int sign = 1; // +1 or -1
	BigInteger Karatsuba(const BigInteger& left, const BigInteger& right) const;
	BigInteger GetHalfNumber(unsigned int size, bool is_left) const;
	BigInteger Partition(const BigInteger& dividend, const BigInteger& divisor) const;
	std::pair<BigInteger, BigInteger> DivisorSearch(const BigInteger& did, const BigInteger& dis) const;
	explicit operator std::string() const;
public:
	explicit BigInteger(const std::string& str);
	explicit BigInteger() = default;
	BigInteger(int construct_number); // тут не должно быть explicit, иначе все ломаетс€, преодразовани€ из int могут быть не€вными
	explicit BigInteger(unsigned int construct_number);
	explicit BigInteger(uint64_t construct_number);
	explicit operator bool() const;
	std::string toString() const;
	BigInteger operator-() const; // унарный минус
	BigInteger& operator++(); // префиксный инкремент
	BigInteger& operator--(); // префиксный декремент
	BigInteger operator++(int); // постфиксный инкремент
	BigInteger operator--(int); // постфиксный декремент
	BigInteger& operator+=(const BigInteger& right);
	BigInteger& operator-=(const BigInteger& right);
	BigInteger& operator/=(const BigInteger& right);
	BigInteger& operator%=(const BigInteger& right);
	BigInteger& operator*=(const BigInteger& right);

	friend std::ostream& operator<<(std::ostream& out, const BigInteger& big_int);
	friend std::istream& operator>>(std::istream& in, BigInteger& big_int);
	friend BigInteger operator%(const BigInteger& left, const BigInteger& right);
	friend BigInteger operator/(const BigInteger& left, const BigInteger& right);
	friend BigInteger operator*(const BigInteger& left, const BigInteger& right);
	friend BigInteger operator+(const BigInteger& left, const BigInteger& right);
	friend BigInteger operator-(const BigInteger& left, const BigInteger& right);

	friend bool isLess(const BigInteger& left, const BigInteger& right);
	friend bool operator<(const BigInteger& left, const BigInteger& right);
	friend bool operator>(const BigInteger& left, const BigInteger& right);
	friend bool operator==(const BigInteger& left, const BigInteger& right);
	friend bool operator!=(const BigInteger& left, const BigInteger& right);
	friend bool operator<=(const BigInteger& left, const BigInteger& right);
	friend bool operator>=(const BigInteger& left, const BigInteger& right);
};