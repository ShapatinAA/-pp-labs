#include <iostream>
#include <string>
#include "bigint_vec.h"

BigInt::BigInt() :
	elem_(new short),
	sign_(0),
	size_(1) {
	if (elem_ == nullptr) {
		std::cout << "error in memory allocation";
		abort();
	}
	elem_[0] = 0;
}

//short& BigInt::operator[](int i) {
//	return elem_[i];
//}
//
//const short& BigInt::operator[](int i) const {
//	return elem_[i];
//}

BigInt::BigInt(int bigint_size, bool flag) :
	elem_(new short[bigint_size]),
	sign_(0),
	size_(bigint_size) {
	if (flag) elem_ = nullptr;
	if (elem_ == nullptr) {
		std::cout << "error in memory allocation";
		abort();
	}
	for (int i = 0; i < size_; i++) {
		elem_[i] = 0;
	}
}

BigInt::BigInt(int int_numb) :
	elem_(new short[(std::to_string(int_numb)).size()]),
	sign_(0),
	size_((std::to_string(int_numb)).size()) {
	if (elem_ == nullptr) {
		std::cout << "error in memory allocation";
		abort();
	}
	if (int_numb < 0) {
		sign_ = 1;
		--size_;
		for (int i = size_ - 1; i >= 0; i--) {
			elem_[i] = ((std::to_string(int_numb))[i+1]) - '0';
		}
		delete_leading_zeroes(*this);
	}
	else {
		for (int i = 0; i < size_; i++) {
			elem_[i] = ((std::to_string(int_numb))[i]) - '0';
		}
		delete_leading_zeroes(*this);
	}
}

BigInt::BigInt(std::string str_) :
	elem_(new short[str_.size()]),
	sign_(0),
	size_(str_.size())
{
	int str_size = (int)str_.size();
	if (!str_size) {
		std::cout << "invalid_argument";
		abort();
	}
	size_ = str_size;
	str_size--;
	while (str_size + 1) {
		if (str_[str_size] >= '0' && str_[str_size] <= '9') {
			elem_[str_size] = str_[str_size] - '0';
			str_size--;
		}
		else {
			if (str_size == 0 && size_ > 1) {
				BigInt new_numb(size_ - 1, 0);
				switch (str_[str_size])
				{
				case '-':
					size_--;
					for (int i = size_ - 1; i >= 0; i--) {
						new_numb.elem_[i] = elem_[i + 1];
					}
					*this = new_numb;
					sign_ = 1;
					str_size--;
					break;
				case '+':
					size_--;
					for (int i = size_ - 1; i >= 0; i--) {
						new_numb.elem_[i] = elem_[i + 1];
					}
					*this = new_numb;
					sign_ = 0;
					str_size--;
					break;
				default:
					std::cout << "invalid_argument";
					abort();
				}
			}
			else {
				std::cout << "invalid_argument";
				abort();
			}
		}
	}
	delete_leading_zeroes(*this);
	if (str_ == "-0") {
		BigInt new_numb("0");
		*this = new_numb;
	}
}

BigInt::BigInt(const BigInt& numb) :
	elem_(new short[numb.size_]),
	sign_(numb.sign_),
	size_(numb.size_) {
	if (elem_ == nullptr) {
		std::cout << "error in memory allocation";
		abort();
	}
	for (int i = 0; i < size_; i++) {
		elem_[i] = numb.elem_[i];
	}
}

BigInt::~BigInt() {
	delete[] elem_;
}

BigInt& BigInt::operator=(const BigInt& numb) {
	if (numb.elem_ == elem_) return (*this);
	delete[] elem_;
	short* res_elem = new short[numb.size_];
	if (res_elem == nullptr) {
		std::cout << "error in memory allocation";
		abort();
	}
	for (int i = numb.size_ - 1; i >= 0; i--) {
		res_elem[i] = numb.elem_[i];
	}
	elem_ = new short[numb.size_];
	for (int i = numb.size_ - 1; i >= 0; i--) {
		elem_[i] = res_elem[i];
	}
	size_ = numb.size_;
	sign_ = numb.sign_;
	return(*this);
}

void BigInt::delete_leading_zeroes(BigInt& numb) {
	int i = 0;
	bool allsign = numb.sign_;
	while (i < numb.size_ && numb.elem_[i] == 0) i++;
	if (i == numb.size_) {
		BigInt new_numb(1,0);
		numb = new_numb;
		numb.sign_ = allsign;
		return;
	}
	if (i != 0) {
		BigInt new_numb(numb.size_ - i,0);
		for (int j = 0; j < new_numb.size_; j++) {
			new_numb.elem_[j] = numb.elem_[i];
			i++;
		}
		numb = new_numb;
		numb.sign_ = allsign;
	}
}

BigInt BigInt::get_log2(const BigInt& numb) {
	BigInt new_numb("1");
	BigInt i("0");
	while (new_numb < numb) {
		new_numb *= 2;
		i++;
	}
	if (new_numb == numb) {
		return i;
	}
	else return (--i);
}

BigInt BigInt::operator~() const {
	if (size_ == 1 && sign_ && elem_[0] == (1)) {
		BigInt new_numb("0");
		return new_numb;
	}
	BigInt new_numb(size_,0);
	new_numb = *this;
	new_numb++;
	new_numb.sign_ = !sign_;
	return new_numb;
}

BigInt& BigInt::operator++() {
	if (!sign_) {
		int curr_pos = size_ - 1;
		elem_[curr_pos]++;
		while (curr_pos && (elem_[curr_pos] > 9)) {
			elem_[curr_pos] = 0;
			curr_pos--;
			elem_[curr_pos]++;
		}
		if (curr_pos == 0) {
			if (elem_[curr_pos] > 9) {
				elem_[curr_pos] = 0;
				BigInt new_numb(size_ + 1,0);
				for (curr_pos = size_; curr_pos > 0; curr_pos--) {
					new_numb.elem_[curr_pos] = elem_[curr_pos - 1];
				}
				new_numb.elem_[0] = 1;
				*this = new_numb;
				delete_leading_zeroes(*this);
				return *this;
			}
			else {
				delete_leading_zeroes(*this);
				return *this;
			}
		}
		else {
			delete_leading_zeroes(*this);
			return *this;
		}
	}
	else {
		if (size_ == 1 && elem_[0] == 1) {
			BigInt new_numb("0");
			*this = new_numb;
			return *this;
		}
		int curr_pos = size_-1;
		elem_[curr_pos]--;
		while (curr_pos && elem_[curr_pos] < 0) {
			elem_[curr_pos] = 9;
			curr_pos--;
			elem_[curr_pos]--;
		}
		if (curr_pos == 0) {
			if (elem_[curr_pos] < 0) {
				BigInt new_numb("-1");
				*this = new_numb;
				return *this;
			}
			else {
				if (elem_[curr_pos] == 0) {
					return *this;
				}
				else return *this;
			}
		}
		else return *this;
	}
}

const BigInt BigInt::operator++(int) {
	BigInt tmp = *this;
	++(*this);
	return tmp;
}

BigInt& BigInt::operator--() {
	if (sign_) {
		int curr_pos = size_ - 1;
		elem_[curr_pos]++;
		while (curr_pos && (elem_[curr_pos] > 9)) {
			elem_[curr_pos] = 0;
			curr_pos--;
			elem_[curr_pos]++;
		}
		if (curr_pos == 0) {
			if (elem_[curr_pos] > 9) {
				elem_[curr_pos] = 0;
				BigInt new_numb(size_ + 1,0);
				for (curr_pos = size_; curr_pos > 0; curr_pos--) {
					new_numb.elem_[curr_pos] = elem_[curr_pos - 1];
				}
				new_numb.elem_[0] = 1;
				*this = new_numb;
				return *this;
			}
			else {
				elem_[curr_pos]++;
				return *this;
			}
		}
		else {
			return *this;
		}
	}
	else {
		if (size_ == 1 && elem_[0] == 1) {
			BigInt new_numb("0");
			*this = new_numb;
			return *this;
		}
		int curr_pos = size_ - 1;
		elem_[curr_pos]--;
		while (curr_pos && elem_[curr_pos] < 0) {
			elem_[curr_pos] = 9;
			curr_pos--;
			elem_[curr_pos]--;
		}
		if (curr_pos == 0) {
			if (elem_[curr_pos] < 0) {
				BigInt new_numb("-1");
				*this = new_numb;
				return *this;
			}
			else {
				if (elem_[curr_pos] == 0) {
					delete_leading_zeroes(*this);
					return *this;
				}
				else return *this;
			}
		}
		else return *this;
	}
}

const BigInt BigInt::operator--(int) {
	BigInt tmp = *this;
	--(*this);
	return tmp;
}

BigInt& BigInt::operator+=(const BigInt& numb2) {
	BigInt zero_numb("0");
	if (*this == zero_numb) {
		*this = numb2;
		return *this;
	}
	else if (numb2 == zero_numb) return *this;
	if (!(sign_ ^ numb2.sign_)) {
		if (size_ > numb2.size_) {
			int i = numb2.size_ - 1;
			int j = size_ - 1;
			while (i >= 0) {
				elem_[j] += numb2.elem_[i];
				elem_[j - 1] += elem_[j] / 10;
				elem_[j] %= 10;
				i--;
				j--;
			}
			while (j > 0 && elem_[j] > 9) {
				elem_[j] %= 10;
				elem_[j - 1]++;
				j--;
			}
			if (j == 0 && elem_[j] > 9) {
				elem_[j] %= 10;
				BigInt new_numb(size_ + 1,0);
				for (int k = new_numb.size_; k > 0; k--) {
					new_numb.elem_[k] = elem_[k - 1];
				}
				new_numb.elem_[0] = 1;
				*this = new_numb;
			}
			return *this;
		}
		else {
			int i = numb2.size_ - 1;
			if (size_ < numb2.size_) {
				BigInt new_numb(numb2);
				new_numb += *this;
				*this = new_numb;
				return *this;
			}
			while (i > 0) {
				elem_[i] += numb2.elem_[i];
				elem_[i - 1] += (elem_[i] / 10);
				elem_[i] %= 10;
				i--;
			}

			elem_[i] += numb2.elem_[i];
			if (i == 0 && elem_[i] > 9) {
				elem_[i] %= 10;
				BigInt new_numb(size_ + 1,0);
				for (int k = new_numb.size_; k > 0; k--) {
					new_numb.elem_[k] = elem_[k - 1];
				}
				new_numb.elem_[0] = 1;
				*this = new_numb;
			}
			return *this;
		}
	}
	else {
		if (sign_ == 0) *this -= (-numb2);
		else {
			sign_ = !sign_;
			*this -= numb2;
			if (*this != zero_numb) sign_ = !sign_;
		}
		return *this;
	}
}

BigInt& BigInt::operator*=(const BigInt& numb2) {
	bool end_sign = sign_ ^ numb2.sign_;
	if ((size_ == 1 && elem_[0] == 0) || (numb2.size_ == 1 && numb2.elem_[0] == 0)) {
		BigInt new_numb("0");
		*this = new_numb;
		return *this;
	}
	BigInt new_numb(size_ + numb2.size_,0);
	if (size_ > numb2.size_) {
		for (int i = 0; i < numb2.size_; i++) {
			for (int j = size_-1; j >= 0; j--) {
				new_numb.elem_[j + numb2.size_ - i] += elem_[j] * numb2.elem_[numb2.size_ - 1 - i];
				new_numb.elem_[j + numb2.size_ - i - 1] += (new_numb.elem_[j + numb2.size_ - i] / 10);
				new_numb.elem_[j + numb2.size_ - i] %= 10;
			}
		}
		if (new_numb.elem_[0] == 0) {
			delete_leading_zeroes(new_numb);
		}
		*this = new_numb;
		sign_ = end_sign;
		return *this;
	}
	else {
		for (int i = 0; i < size_; i++) {
			for (int j = numb2.size_ - 1; j >= 0; j--) {
				new_numb.elem_[j + size_ - i] += numb2.elem_[j] * elem_[size_ - 1 - i];
				new_numb.elem_[j + size_ - i - 1] += (new_numb.elem_[j + size_ - i] / 10);
				new_numb.elem_[j + size_ - i] %= 10;
			}
		}
		if (new_numb.elem_[0] == 0) {
			delete_leading_zeroes(new_numb);
		}
		*this = new_numb;
		sign_ = end_sign;
		return *this;
	}
}

BigInt& BigInt::operator*=(const int& numb2) {
	std::string str_ = std::to_string(numb2);
	BigInt new_numb(str_);
	*this *= new_numb;
	return *this;
}

BigInt& BigInt::operator+=(const int& numb2) {
	std::string str_ = std::to_string(numb2);
	BigInt new_numb(str_);
	*this += new_numb;
	return *this;
}

BigInt& BigInt::operator-=(const int& numb2) {
	std::string str_ = std::to_string(numb2);
	BigInt new_numb(str_);
	*this -= new_numb;
	return *this;
}

BigInt& BigInt::operator/=(const int& numb2) {
	std::string str_ = std::to_string(numb2);
	BigInt new_numb(str_);
	*this /= new_numb;
	return *this;
}

BigInt& BigInt::operator%=(const int& numb2) {
	std::string str_ = std::to_string(numb2);
	BigInt new_numb(str_);
	*this %= new_numb;
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& numb2) {
	if (sign_ ^ numb2.sign_) {
		*this += (-numb2);
		return *this;
	}
	else {
		if (*this == numb2) {
			BigInt new_numb("0");
			*this = new_numb;
			return *this;
		}
		if (size_ > numb2.size_) {
			for (int i = 0; i < numb2.size_; i++) {
				elem_[size_ - 1 - i] -= numb2.elem_[numb2.size_ - 1 - i];
				if (elem_[size_ - 1 - i] < 0) {
					elem_[size_ - 2 - i]--;
					elem_[size_ - 1 - i] += 10;
				}
			}
			delete_leading_zeroes(*this);
			return *this;
		}
		else {
			if (numb2.size_ > size_) {
				BigInt new_numb(numb2);
				for (int i = 0; i < size_; i++) {
					new_numb.elem_[new_numb.size_ - 1 - i] -= elem_[size_ - 1 - i];
					if (new_numb.elem_[size_ - 1 - i] < 0) {
						new_numb.elem_[size_ - 2 - i]--;
						new_numb.elem_[size_ - 1 - i] += 10;
					}
				}
				*this = new_numb;
				sign_ = 1;
				delete_leading_zeroes(*this);
				return *this;
			}
			else {
				if (sign_) {
					if (*this < numb2) {
						for (int i = 0; i < numb2.size_; i++) {
							elem_[size_ - 1 - i] -= numb2.elem_[numb2.size_ - 1 - i];
							if (elem_[size_ - 1 - i] < 0) {
								elem_[size_ - 2 - i]--;
								elem_[size_ - 1 - i] += 10;
							}
						}
						delete_leading_zeroes(*this);
						return *this;
					}
					else {
						BigInt new_numb(numb2);
						for (int i = 0; i < size_; i++) {
							new_numb.elem_[new_numb.size_ - 1 - i] -= elem_[size_ - 1 - i];
							if (new_numb.elem_[size_ - 1 - i] < 0) {
								new_numb.elem_[size_ - 2 - i]--;
								new_numb.elem_[size_ - 1 - i] += 10;
							}
						}
						*this = new_numb;
						sign_ = 0;
						delete_leading_zeroes(*this);
						return *this;
					}
				}
				else {
					if (*this > numb2) {
						for (int i = 0; i < numb2.size_; i++) {
							elem_[size_ - 1 - i] -= numb2.elem_[numb2.size_ - 1 - i];
							if (elem_[size_ - 1 - i] < 0) {
								elem_[size_ - 2 - i]--;
								elem_[size_ - 1 - i] += 10;
							}
						}
						delete_leading_zeroes(*this);
						return *this;
					}
					else {
						BigInt new_numb(numb2);
						for (int i = 0; i < size_; i++) {
							new_numb.elem_[new_numb.size_ - 1 - i] -= elem_[size_ - 1 - i];
							if (new_numb.elem_[size_ - 1 - i] < 0) {
								new_numb.elem_[size_ - 2 - i]--;
								new_numb.elem_[size_ - 1 - i] += 10;
							}
						}
						*this = new_numb;
						sign_ = 1;
						delete_leading_zeroes(*this);
						return *this;
					}
				}
			}
		}
	}
}
bool BigInt::operator==(const BigInt& numb2) const { 
	if (size_ == numb2.size_ && sign_ == numb2.sign_) {
		for (int i = size_ - 1; i >= 0; i--) {
			if (elem_[i] != numb2.elem_[i]) return false;
		}
		return true;
	}
	return false;
}

BigInt& BigInt::operator/=(const BigInt& numb2) {
	BigInt copy_numb2(numb2);
	bool allsign = sign_ ^ numb2.sign_;
	sign_ = 0;
	copy_numb2.sign_ = 0;
	BigInt zero_numb("0");
	if (numb2 == zero_numb) {
		std::cout << "division by zero prohibited";
		return *this;
	}
	if (copy_numb2 > *this) {
		*this = zero_numb;
		return *this;	
	}
	++zero_numb;
	if (numb2 == zero_numb) {
		return *this;
	}
	zero_numb.sign_ = 1;
	if (numb2 == zero_numb) {
		sign_ = !sign_;
		return *this;
	}
	BigInt tmp;
	BigInt result_numb;
	int i = 0;
	while (i<size_) {
		for (; tmp < copy_numb2 && i < size_; i++) {
			result_numb *= 10;
			tmp *= 10;
			tmp.elem_[tmp.size_-1] = elem_[i];
		}
		BigInt rez_("1");
		while (tmp > (copy_numb2 * rez_)) {
			rez_++;
		}
		if (tmp != (copy_numb2 * rez_)) {
			rez_--;
		}
		result_numb += rez_;
		tmp -= copy_numb2 * rez_;
	}
	*this = result_numb;
	sign_ = allsign;
	return *this;
}

BigInt& BigInt::operator^=(const BigInt& numb) {
	BigInt zero_numb("0");
	if (*this == numb) {
		*this = zero_numb;
		return *this;
	}
	BigInt result_numb(1,0);
	BigInt numb2(numb);
	bool allsign = sign_ ^ numb.sign_;
	sign_ = 0;
	numb2.sign_ = 0;
	BigInt power_of_2("1");
	BigInt tmp("0");
	BigInt log2_of_this = get_log2(*this);
	if (*this > numb) {
		for (BigInt i("0"); i <= log2_of_this; i++) {
			tmp = (*this / power_of_2) + (numb2 / power_of_2);
			if (tmp.elem_[tmp.size_ - 1] % 2) result_numb += power_of_2;
			power_of_2 *= 2;
		}
	}
	else {
		numb2 ^= *this;
		*this = numb2;
		sign_ = allsign;
		if (size_ == 1 && elem_[0] == 0) {
			*this = zero_numb;
			return *this;
		}
		return *this;
	}
	result_numb.sign_ = allsign;
	*this = result_numb;
	if (size_ == 1 && elem_[0] == 0) {
		*this = zero_numb;
		return *this;
	}
	return *this;
}

BigInt& BigInt::operator%=(const BigInt& numb2) {
	if (*this == numb2) {
		BigInt zero_numb("0");
		*this = zero_numb;
		return *this;
	}
	BigInt zero_numb("0");
	if (numb2 == zero_numb) {
	std::cout << "division by zero prohibited";
	return *this;
	}
	if (numb2.size_ > size_) {
		return *this;
	}
	if (numb2.size_ == 1) {
		switch (numb2.elem_[0]) {
		case (1): 
			*this = zero_numb;
			return *this;
		case (2):
			if (!elem_[size_ - 1])	*this = zero_numb;
			else *this = (++zero_numb);
			return *this;
		}
	}
	sign_ = numb2.sign_;
	*this -= ((*this / numb2) * numb2);
	sign_ = 0;
	return *this;
}

BigInt& BigInt::operator&=(const BigInt&numb) {
	if (*this == numb) {
		return *this;
	}
	BigInt result_numb(1,0);
	BigInt numb2(numb);
	bool allsign = sign_ & numb.sign_;
	sign_ = 0;
	numb2.sign_ = 0;
	BigInt power_of_2("1");
	BigInt tmp1("0");
	BigInt tmp2("0");
	BigInt log2_of_this = get_log2(*this);
	if (*this > numb) {
		for (BigInt i("0"); i <= log2_of_this; i++) {
			tmp1 = (*this / power_of_2);
			tmp2 = (numb / power_of_2);
			if ((tmp1.elem_[tmp1.size_ - 1] % 2) && (tmp2.elem_[tmp2.size_ - 1] % 2)) result_numb += power_of_2;
			power_of_2 *= 2;
		}
	}
	else {
		numb2 &= *this;
		*this = numb2;
		sign_ = allsign;
		return *this;
	}
	result_numb.sign_ = allsign;
	*this = result_numb;
	return *this;
}

BigInt& BigInt::operator|=(const BigInt& numb) {
	BigInt result_numb(1, 0);
	BigInt numb2(numb);
	bool allsign = sign_ | numb.sign_;
	sign_ = 0;
	numb2.sign_ = 0;
	BigInt power_of_2("1");
	BigInt tmp1("0");
	BigInt tmp2("0");
	BigInt log2_of_this = get_log2(*this);
	if (*this > numb) {
		for (BigInt i("0"); i <= log2_of_this; i++) {
			tmp1 = (*this / power_of_2);
			tmp2 = (numb / power_of_2);
			if (((tmp1.elem_[tmp1.size_ - 1] % 2) 
				|| 
				(tmp2.elem_[tmp2.size_ - 1] % 2) 
				|| 
				((tmp1.elem_[tmp1.size_ - 1] % 2) * (tmp2.elem_[tmp2.size_ - 1] % 2)))
				% 2
				) result_numb += power_of_2;
			power_of_2 *= 2;
		}
	}
	else {
		numb2 |= *this;
		*this = numb2;
		sign_ = allsign;
		return *this;
	}
	result_numb.sign_ = allsign;
	*this = result_numb;
	return *this;
}

BigInt BigInt::operator+() const {
	return *this;
}

BigInt BigInt::operator-() const {
	BigInt new_numb = *this;
	BigInt zero_numb("0");
	if (new_numb == zero_numb) {
		return new_numb;
	}
	new_numb.sign_ = !new_numb.sign_;
	return new_numb;
}

bool BigInt::operator!=(const BigInt& numb) const {
	if (!((*this) == numb)) return true;
	else return false;
}

bool BigInt::operator<(const BigInt& numb) const {
	switch (sign_) {
	case (0): {
		switch (numb.sign_) {
		case (0): {
			switch (size_ < numb.size_) {
			case (1): return true;
			case (0): {
				switch (size_ == numb.size_) {
				case (0): return false;
				case (1): {
					for (int i = 0; i < size_; i++) {
						if (elem_[i] > numb.elem_[i]) return false;
						else if (elem_[i] < numb.elem_[i]) return true;
					}
					return false;
				}
				}
			}
			}
		case (1): return false;
		}
		}
	}
	case (1): {
		switch (numb.sign_) {
		case (0): return true;
		case (1): {
			switch (size_ < numb.size_) {
			case (1): return false;
			case (0): {
				switch (size_ == numb.size_) {
				case (0): return true;
				case (1): {
					for (int i = 0; i < size_; i++) {
						if (elem_[i] > numb.elem_[i]) return true;
						else if (elem_[i] < numb.elem_[i]) return false;
					}
					return false;
				}
				}
			}
			}
		}
		}
	}
	}
}

bool BigInt::operator>(const BigInt& numb) const { 
	if (!(*this < numb) && !(*this == numb)) return true;
	else return false;
}

bool BigInt::operator<=(const BigInt& numb) const {
	if (!(*this > numb)) return true;
	else return false;
}

bool BigInt::operator>=(const BigInt& numb) const {
	if (!(*this < numb)) return true;
	else return false;
}

BigInt::operator int() const {
	BigInt int_numb("1");
	for (int i = 1; i < 8 * sizeof(int); i++) {
		int_numb *= 2;
	}
	BigInt new_numb = *this;
	if (sign_) new_numb %= (++int_numb);
	else new_numb %= (int_numb);
	int result_numb = 0;
	for (int i = 0; i < new_numb.size_; i++) {
		result_numb *= 10;
		result_numb += new_numb.elem_[i];
	}
	if (sign_) result_numb = -result_numb;
	return result_numb;
}

BigInt::operator BigInt() const {
	std::string str_ = std::to_string(*this);
	BigInt new_numb(str_);
	return new_numb;
}

BigInt::operator std::string() const {
	std::string output_str;
	BigInt zero_numb("0");
	if (*this < zero_numb) {
		output_str += '-';
	}
	for (int i = 0; i < size_; i++) {
		output_str += (char)(elem_[i] + '0');
	}
	return output_str;
}

size_t BigInt::size() const {
	return (sizeof(short) * size_ + sizeof(bool) + sizeof(int));
}

BigInt operator*(const BigInt& numb1, const BigInt& numb2) {
	BigInt new_numb = numb1;
	new_numb *= numb2;
	return new_numb;
}

BigInt operator+(const BigInt& numb1, const BigInt& numb2) {
	BigInt new_numb = numb1;
	return new_numb += numb2;
}

BigInt operator/(const BigInt& numb1, const BigInt& numb2) {
	BigInt new_numb = numb1;
	return new_numb /= numb2;
}

BigInt operator-(const BigInt& numb1, const BigInt& numb2) {
	BigInt new_numb = numb1;
	return new_numb -= numb2;
}

BigInt operator^(const BigInt& numb1, const BigInt& numb2) {
	BigInt new_numb = numb1;
	return new_numb ^= numb2;
}

BigInt operator%(const BigInt& numb1, const BigInt& numb2) {
	BigInt new_numb = numb1;
	return new_numb %= numb2;
}

BigInt operator&(const BigInt& numb1, const BigInt& numb2) {
	BigInt new_numb = numb1;
	return new_numb &= numb2;
}

BigInt operator|(const BigInt& numb1, const BigInt& numb2) {
	BigInt new_numb = numb1;
	return new_numb |= numb2;
}

std::ostream& operator<<(std::ostream& o, const BigInt& i) {
	o << (std::string)(i);
	return o;
}
