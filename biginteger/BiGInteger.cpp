#include "BigInteger.h"

bool BigInteger::isLess(const std::vector<unsigned int>& left, const std::vector<unsigned int>& right) const
{
	unsigned int l_size = left.size();
	unsigned int r_size = right.size();
	//проверка на незначащие нули
	if (l_size > 0)
		for (unsigned int i = left.size() - 1; i > 0; --i)
		{
			if (left[i] == 0)
			{
				--l_size;
				continue;
			}
			break;
		}
	if (r_size > 0)
		for (unsigned i = right.size() - 1; i > 0; --i)
		{
			if (right[i] == 0)
			{
				--r_size;
				continue;
			}
			break;
		}
	if (l_size < r_size)
		return true;
	if (l_size > r_size)
		return false;
	for (int i = l_size - 1; i >= 0; --i) // l_size
	{
		if (left[i] < right[i])
			return true;
		if (left[i] > right[i])
			return false;
	}
	return false;
}

BigInteger BigInteger::Karatsuba(const BigInteger& X, const BigInteger& Y) const
{
	unsigned int n = (X.number.size() > Y.number.size() ? X.number.size() : Y.number.size());
	if (n == 1)
	{
		uint64_t res = static_cast<uint64_t>(X.number[0]) * static_cast<uint64_t>(Y.number[0]);
		BigInteger result(res);
		return result;
	}
	if (X.number.size() > (n / 2) * 2 || Y.number.size() > (n / 2) * 2)
		++n;
	BigInteger X_r = X.GetHalfNumber(n / 2, false);
	BigInteger X_l = X.GetHalfNumber(n / 2, true);
	BigInteger Y_l = Y.GetHalfNumber(n / 2, true);
	BigInteger Y_r = Y.GetHalfNumber(n / 2, false);
	BigInteger Prod1 = Karatsuba(X_l, Y_l);
	BigInteger Prod2 = Karatsuba(X_r, Y_r);
	BigInteger Prod3 = Karatsuba(X_l + X_r, Y_l + Y_r);
	BigInteger Sum = Prod3;
	Sum -= Prod1;
	Sum -= Prod2;
	//вернуть Prod1 * 10 ^ n + (Prod3 - Prod1 - Prod2) * 10 ^ (n / 2) + Prod2
	BigInteger answer;
	unsigned int max = n + Prod1.number.size();
	if (max < n / 2 + Sum.number.size())
		max = Sum.number.size() + n / 2;
	if (max < Prod2.number.size())
		max = Prod2.number.size();
	++max;

	for (unsigned int i = 0; i < max; ++i)
		answer.number.push_back(0);

	for (unsigned int i = 0; i < n / 2; ++i)
	{
		if (i < Prod2.number.size())
			answer.number[i] = Prod2.number[i];
	}
	BigInteger after_prod_1;
	unsigned int end_size = (Prod2.number.size() > n / 2 ? Prod2.number.size() - n / 2 : 0);
	for (int i = 0; i < end_size; ++i)
	{
		after_prod_1.number.push_back(0);
	}
	for (unsigned int i = n / 2; i < Prod2.number.size(); ++i)
		after_prod_1.number[i - n / 2] = Prod2.number[i];
	Sum += after_prod_1; // остаток от предыдущего раздяра

	for (unsigned int i = 0; i < n / 2; ++i)
	{
		if (i < Sum.number.size())
			answer.number[i + n / 2] += Sum.number[i];
	}
	BigInteger after_sum;
	end_size = (Sum.number.size() > n / 2 ? Sum.number.size() - n / 2 : 0);
	for (unsigned int i = 0; i < end_size; ++i)
	{
		after_sum.number.push_back(0);
	}
	for (unsigned int i = n / 2; i < Sum.number.size(); ++i)
		after_sum.number[i - n / 2] = Sum.number[i];
	Prod1 += after_sum; // остаток от предыдущего раздяра

	for (unsigned int i = 0; i < Prod1.number.size(); ++i)
	{
		answer.number[i + n] += Prod1.number[i];
	}
	end_size = (answer.number.size() > 0 ? answer.number.size() - 1 : 0);
	for (unsigned int i = end_size; i > 0; --i)
	{
		if (answer.number[i] == 0)
		{
			answer.number.pop_back();
		}
		else
		{
			break;
		}
	}
	answer.sign *= answer.sign;
	return answer;
}

BigInteger BigInteger::GetHalfNumber(unsigned int size, bool is_left) const
{
	if (size * 2 < number.size())
	{
		throw std::runtime_error("Incorrect size_GetHalfNumber");
	}
	unsigned int start_index;
	unsigned int end_index;

	if (is_left)
	{
		if (size >= number.size())
			return BigInteger("0");
		start_index = size;
		end_index = number.size();
	}
	else
	{
		if (size >= number.size())
			return *this;
		start_index = 0;
		end_index = size;
	}
	BigInteger result;
	for (unsigned int i = start_index; i < end_index; ++i)
	{
		result.number.push_back(number[i]);
	}
	return result;
}

BigInteger BigInteger::Partition(const BigInteger& dividend, const BigInteger& divisor_) const
{
	if (divisor_ * divisor_.sign == 1)
		return dividend * divisor_.sign;
	if (dividend * dividend.sign < divisor_ * divisor_.sign)
		return 0;
	BigInteger divisor = divisor_;
	divisor.sign = 1;
	BigInteger suffix_dividened;
	BigInteger current;

	std::string str_answer;
	
	for (int i = int(dividend.number.size()) - 1; i >= 0 ; --i)
	{
		suffix_dividened.number.insert(suffix_dividened.number.begin(), dividend.number[i]);
		if (suffix_dividened < divisor)
		{
			if (!str_answer.empty())
				for (unsigned int m = 0; m < number_size; ++m)
					str_answer += '0';
			continue;
		}
		unsigned int end_index = (suffix_dividened.number.size() > 0 ? suffix_dividened.number.size() - 1 : 0);
		for (int k = end_index; k > 0; --k)
		{
			if (suffix_dividened.number[k] == 0)
			{
				suffix_dividened.number.pop_back();
				continue;
			}
			break;
		}
		auto res = DivisorSearch(suffix_dividened, divisor); // возвращает частное и остаток от деления соответственно

		str_answer += res.first.toString();
		suffix_dividened = res.second;
	}
	BigInteger answer(str_answer);
	answer.sign = divisor_.sign * dividend.sign;
	return answer;
}

std::pair<BigInteger, BigInteger> BigInteger::DivisorSearch(const BigInteger& did, const BigInteger& dis) const
{
	BigInteger current = dis;
	unsigned int left = 0;
	unsigned int right = BASE * 3;
	unsigned int middle;
	while (true)
	{
		middle = (left + right);
		middle /= 2;
		current = dis * middle;
		if (current <= did && (current + dis) > did)
		{
			break;
		}
		if (current > did)
		{
			right = middle;
			continue;
		}
		if (current <= did)
		{
			left = middle;
			continue;
		}
	}

	return std::make_pair(middle, did - current); //частное и остаток от деления соответственно
}

BigInteger::BigInteger(const std::string& str)
{
	if (str.empty())
	{
		return;
	}
	int index_start_of_number = 0;
	if (str[0] == '-')
	{
		sign = -1;
		index_start_of_number = 1;
	}
	else if (str[0] == '+')
	{
		sign = 1;
		index_start_of_number = 1;
	}
	else
	{
		sign = 1;
	}

	unsigned int size = str.size();
	unsigned int current = 0;
	for (int i = int(size - 1); i >= int(index_start_of_number); i -= number_size)
	{
		int start_index = ((i < int(number_size)) ? index_start_of_number : i - number_size + 1);
		current = 0;
		for (int j = start_index; j <= i; ++j)
		{
			current *= 10;
			current += (str[j] - '0');
		}
		number.push_back(current);
	}
	if (number.size() == 1 && number[0] == 0)
		sign = 1;
}

BigInteger::BigInteger() {}

BigInteger::BigInteger(int construct_number)
{
	if (construct_number < 0)
	{
		construct_number *= -1;
		sign = -1;
	}
	do
	{
		number.push_back(construct_number % BASE);
		construct_number /= BASE;
	} while (construct_number != 0);
}

BigInteger::BigInteger(unsigned int construct_number)
{
	sign = 1;
	do
	{
		number.push_back(construct_number % BASE);
		construct_number /= BASE;
	} while (construct_number != 0);
}

BigInteger::BigInteger(uint64_t construct_number)
{
	sign = 1;
	do
	{
		number.push_back(construct_number % BASE);
		construct_number /= BASE;
	} while (construct_number != 0);
}

BigInteger::operator bool() const 
{
	return ((number.size() == 1 && (number[0] == 0)) ? false : true);
}

BigInteger::operator std::string() const
{
	std::string  reverse_number= "";
	for (unsigned int i = 0; i < number.size(); ++i)
	{
		int current = number[i];
		for (unsigned int j = 0; j < number_size; ++j)
		{
			std::string c = std::to_string(current % 10);
			current /= 10;
			reverse_number += c;
		}
	}
	std::string str_number = "";
	if (sign == -1)
		str_number.push_back('-');

	bool flag = false;
	for (int i = int(reverse_number.size() - 1); i >= 0; --i)
	{
		if (!flag && reverse_number[i] != '0')
			flag = true;
		if (flag)
			str_number.push_back(reverse_number[i]);
	}
	if (str_number.empty() || (str_number.size() == 1 && str_number[0] == '-'))
	{
		str_number.clear();
		str_number.push_back('0');
	}
	return str_number;
}

std::string BigInteger::toString() const
{
	return std::string(*this);
}

BigInteger BigInteger::operator-() const
{
	BigInteger result = *this;
	if (result.number.size() == 1 && result.number[0] == 0)
		return result;
	result.sign *= -1;
	return result;
}

BigInteger& BigInteger::operator++()
{
	if (sign == -1)
	{
		sign = 1;
		--(*this);
		sign = -1;
		if (number.size() == 1 && number[0] == 0)
			sign = 1;
		return *this;
	}
	unsigned int next_mod = 1;
	unsigned int current;
	for (unsigned int i = 0; i < number.size(); ++i)
	{
		current = number[i] + next_mod;
		next_mod = (current - current % BASE) / BASE;
		current %= BASE;
		number[i] = current;
		if (next_mod == 0)
			return *this;
	}
	if (next_mod != 0)
		number.push_back(next_mod);
	return *this;
}

BigInteger& BigInteger::operator--()
{
	if (sign == -1)
	{
		sign = 1;
		++(*this);
		sign = -1;
		return *this;
	}
	int take_from_next = 1;
	for (unsigned int i = 0; i < number.size(); ++i)
	{
		if (int(number[i]) < take_from_next)
		{
			take_from_next = 1;
			number[i] += (BASE - take_from_next);
		}
		else
		{
			number[i] -= take_from_next;
			return *this;
		}
	}
	if (take_from_next != 0)
	{
		number.clear();
		sign *= -1;
		number.push_back(1);
	}
	return *this;
}

BigInteger BigInteger::operator++(int)
{
	BigInteger result = *this;
	++(*this);
	return result;
}

BigInteger BigInteger::operator--(int)
{
	BigInteger result = *this;
	--(*this);
	return result;
}

BigInteger& BigInteger::operator+=(const BigInteger& right)
{
	if (sign * right.sign == 1)
	{
		//предположим, что *this и right одинаковые по знаку 
		unsigned int next_mod = 0;
		unsigned int current;
		unsigned int max_index = number.size() > right.number.size() ? number.size() : right.number.size();
		for (unsigned int i = 0; i < max_index; ++i)
		{
			unsigned int a = (i >= number.size()) ? 0 : number[i];
			unsigned int b = (i >= right.number.size()) ? 0 : right.number[i];
			current = a + b + next_mod;
			next_mod = (current - current % BASE) / BASE;
			current %= BASE;
			if (i < number.size())
				number[i] = current;
			else
				number.push_back(current);
		}

		if (next_mod > 0)
			number.push_back(next_mod);
		return *this;
	}
	if (sign == -1)
	{
		sign = 1;
		if (*this < right)
		{
			*this -= right;
			sign *= -1;
			return *this;
		}
		*this -= right;
		sign = -1;
		return *this;
	}
	if (right.sign == -1)
	{
		BigInteger new_right = right;
		new_right.sign = 1;
		*this -= new_right;
		return *this;
	}
	return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& right) 
{
	if (*this == right)
	{
		number.clear();
		number.push_back(0);
		sign = 1;
		return *this;
	}
	if (sign * right.sign == 1 && ((sign == 1 && *this > right) || (sign == -1 && *this < right)))
	{
		//предположим, что *this больше right по модулю
		unsigned int take_from_next = 0;
		int minus_current;
		for (unsigned int i = 0; i < number.size(); ++i)
		{
			minus_current = (i < right.number.size() ? (take_from_next + right.number[i]) : take_from_next);

			if (int(number[i]) < minus_current)
			{
				number[i] += BASE;
				number[i] -= minus_current;
				take_from_next = 1;
			}
			else
			{
				number[i] -= minus_current;
				take_from_next = 0;
			}
		}

		for (int i = int(number.size() - 1); i >= 0; --i)
		{
			if (number[i] == 0)
			{
				number.pop_back();
			}
			else
			{
				break;
			}
		}
		return *this;
	}
	if (sign * right.sign == 1 && (sign == -1 && *this > right))
	{
		BigInteger new_right = right;
		new_right.sign = 1;
		*this += new_right;
		return *this;
	}
	if (sign * right.sign == 1 && (sign == 1 && *this < right))
	{
		BigInteger new_right = right;
		new_right -= *this;
		*this = new_right;
		sign = -1;
		return *this;
	}
	if (sign * right.sign == -1 && right.sign == -1)
	{
		BigInteger new_right = right;
		new_right.sign = 1;
		*this += new_right;
		return *this;
	}
	//if (sign * right.sign == -1 && sign == -1)
	sign = 1;
	*this += right;
	sign = -1;
	return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& right)
{
	*this = Partition(*this, right);
	return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& right)
{
	*this = *this - (*this / right) * right;
	return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& right)
{
	int signum = sign * right.sign;
	*this = Karatsuba(*this, right);
	sign = signum;
	for (int i = int(number.size() - 1); i > 0; --i)
	{
		if (number[i] != 0)
			break;
		number.pop_back();
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& big_int)
{
	std::string number = std::string(big_int);
	out << number;
	return out;
}

std::istream& operator>>(std::istream& in, BigInteger& big_int)
{
	std::string number;
	in >> number;
	BigInteger new_big_int(number);
	big_int = new_big_int;
	return in;
}

BigInteger operator%(const BigInteger& left, const BigInteger& right)
{
	BigInteger result = left - (left / right) * right * left.sign;
	return result;
}

BigInteger operator/(const BigInteger& left, const BigInteger& right)
{
	return left.Partition(left, right);
}

BigInteger operator*(const BigInteger& left, const BigInteger& right)
{
	BigInteger result = left;
	result *= right;
	return result;
}

BigInteger operator+(const BigInteger& left, const BigInteger& right)
{
	BigInteger result = left;
	result += right;
	return result;
}

BigInteger operator-(const BigInteger& left, const BigInteger& right)
{
	BigInteger result = left;
	result -= right;
	return result;
}

bool operator<(const BigInteger& left, const BigInteger& right)
{
	if (left.sign < right.sign)
		return true;
	if (left.sign > right.sign)
		return false;
	bool answer = left.isLess(left.number, right.number);
	return left.sign == 1 ? answer : !answer;
}

bool operator>(const BigInteger& left, const BigInteger& right)
{
	if (left.sign > right.sign)
		return true;
	if (left.sign < right.sign)
		return false;
	bool answer = left.isLess(right.number, left.number);
	return left.sign == 1 ? answer : !answer;
}

bool operator==(const BigInteger& left, const BigInteger& right)
{
	if (left.sign != right.sign)
		return false;
	return (!left.isLess(right.number, left.number) && !left.isLess(left.number, right.number));
}

bool operator!=(const BigInteger& left, const BigInteger& right)
{
	if (left.sign != right.sign)
		return true;
	return (left.isLess(right.number, left.number) || left.isLess(left.number, right.number));
}

bool operator<=(const BigInteger& left, const BigInteger& right)
{
	if (left.sign < right.sign)
		return true;
	if (left.sign > right.sign)
		return false;
	bool left_compare = left.isLess(left.number, right.number);
	bool right_compare = left.isLess(right.number, left.number);
	if (left.sign == -1)
	{
		left_compare = !left_compare;
		right_compare = !right_compare;
	}
	return left_compare || (!right_compare && !left_compare);
}

bool operator>=(const BigInteger& left, const BigInteger& right)
{
	if (left.sign > right.sign)
		return true;
	if (left.sign < right.sign)
		return false;
	bool left_compare = left.isLess(left.number, right.number);
	bool right_compare = left.isLess(right.number, left.number);
	if (left.sign == -1)
	{
		left_compare = !left_compare;
		right_compare = !right_compare;
	}
	return right_compare || (!right_compare && !left_compare);
}