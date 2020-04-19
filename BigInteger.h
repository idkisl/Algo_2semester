#pragma once
#include <iostream>
#include <vector>
#include <string>

class BigInteger
{
	static const unsigned int BASE = 1000000000;
	static const unsigned int number_size = 9;
	std::vector<unsigned int> number;
	int sign = 1; // +1 or -1
	bool isLess(const std::vector<unsigned int>& left, const std::vector<unsigned int>& right) const;
	BigInteger Karatsuba(const BigInteger& left, const BigInteger& right) const;
	BigInteger GetHalfNumber(unsigned int size, bool is_left) const;
	BigInteger Partition(const BigInteger& dividend, const BigInteger& divisor) const;
	std::pair<BigInteger, BigInteger> DivisorSearch(const BigInteger& did, const BigInteger& dis) const;
public:
	BigInteger(const std::string& str);
	BigInteger();
	BigInteger(int construct_number);
	BigInteger(unsigned int construct_number);
	BigInteger(uint64_t construct_number);
	explicit operator bool() const;
	explicit operator std::string() const;
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

	friend bool operator<(const BigInteger& left, const BigInteger& right);
	friend bool operator>(const BigInteger& left, const BigInteger& right);
	friend bool operator==(const BigInteger& left, const BigInteger& right);
	friend bool operator!=(const BigInteger& left, const BigInteger& right);
	friend bool operator<=(const BigInteger& left, const BigInteger& right);
	friend bool operator>=(const BigInteger& left, const BigInteger& right);
};
