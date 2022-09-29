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
	elem_ = 0;
}


BigInt::BigInt(int size) :
	elem_(new short[size]),
	sign_(0),
	size_(size) {
	if (elem_ == nullptr) {
		std::cout << "error in memory allocation";
		abort();
	}
		for (int i = 0; i < size_; i++) {
			elem_[i] = 0;
		}
}

BigInt::BigInt(std::string str_) {
	int str_size = (int)str_.size();
	if (!str_size) {
		std::cout << "invalid_argument";
		abort();
	}
	short* elem_(new short[str_size]);
	sign_ = 0;
	size_ = str_size;
	str_size--;
	while (str_size + 1) {
		if (str_[str_size] >= '0' && str_[str_size] <= '9') {
			elem_[str_size] = str_[str_size] - '0';
			str_size--;
		}
		else {
			if (str_size == 0 && size_ > 1) {
				switch (str_[str_size])
				{
				case '-':
					sign_ = 1;
					size_--;
					break;
				case '+':
					size_--;
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
	short* elem = new short[numb.size_];
	if (elem_ == nullptr) {
		std::cout << "error in memory allocation";
		abort();
	}
	for (int i = size_; i > 0; i--) {
		elem_[i] = numb.elem_[i];
	}
	size_ = numb.size_;
	sign_ = numb.sign_;
	return(*this);
}

BigInt BigInt::operator~() const {
	BigInt new_numb(size_);
	new_numb = (*this);
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
				BigInt new_numb(size_ + 1);
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
		int curr_pos = size_-1;
		elem_[curr_pos]--;
		while (curr_pos && elem_[curr_pos] < 0) {
			elem_[curr_pos] = 9;
			curr_pos--;
			elem_[curr_pos]--;
		}
		if (curr_pos == 0) {
			if (elem_[curr_pos] < 0) {
				BigInt new_numb("1");
				*this = new_numb;
				return *this;
			}
			else {
				if (elem_[curr_pos] == 0) {
					BigInt new_numb(size_ - 1);
					for (curr_pos = size_ - 2; curr_pos >= 0; curr_pos--) {
						new_numb.elem_[curr_pos] = elem_[curr_pos + 1];
					}
					*this = new_numb;
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
				BigInt new_numb(size_ + 1);
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
					BigInt new_numb(size_ - 1);
					for (curr_pos = size_ - 2; curr_pos >= 0; curr_pos--) {
						new_numb.elem_[curr_pos] = elem_[curr_pos + 1];
					}
					*this = new_numb;
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
	if (!(sign_ ^ numb2.sign_)) {
		if (size_ > numb2.size_) {
			int i = numb2.size_ - 1;
			int j = size_ - 1;
			short integ = 0;
			while (i >= 0) {
				elem_[j] = (elem_[j] + numb2.elem_[i]) % 10;
				integ = (elem_[j] + numb2.elem_[i]) / 10;
				elem_[j - 1] += integ;
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
				BigInt new_numb(size_ + 1);
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
				int j = size_ - 1;
				BigInt new_numb(numb2.size);
				for (; j >= 0; j--) new_numb.elem_[j] = elem_[j];
				*this = new_numb;
			}
			short integ = 0;
			while (i > 0) {
				elem_[i] = (elem_[i] + numb2.elem_[i]) % 10;
				integ = (elem_[i] + numb2.elem_[i]) / 10;
				elem_[i - 1] += integ;
				i--;
			}
			if (i == 0 && elem_[i] > 9) {
				elem_[i] %= 10;
				BigInt new_numb(size_ + 1);
				for (int k = new_numb.size_; k > 0; k--) {
					new_numb.elem_[k] = elem_[k - 1];
				}
				new_numb.elem_[0] = 1;
				*this = new_numb;
			}
			return *this;
		}
	}
	else *this -= numb2;
}

BigInt& BigInt::operator*=(const BigInt& numb2) {
	bool end_sign = sign_ ^ numb2.sign_;
	BigInt new_numb(size_ + numb2.size_ - 1);
	if (size_ > numb2.size_) {
		for (int i = 0; i < numb2.size_; i--) {
			for (int j = size_-1; j >= 0; j--) {
				new_numb.elem_[j + i] = elem_[j] * numb2.elem_[numb2.size_ - 1 - i];
				new_numb.elem_[j + i + 1] += (new_numb.elem_[j + i] / 10);
				new_numb.elem_[j + i] %= 10;
			}
		}
		if (new_numb.elem_[0] == 0) {
			BigInt new_numb2(new_numb.size_ - 1);
			for (int i = new_numb.size_ - 1; i > 0; i--) {
				new_numb2.elem_[i] = new_numb.elem_[i];
			}
			*this = new_numb2;
		}
		*this = new_numb;
		sign_ = end_sign;
		return *this;
	}
	else {
		for (int i = 0; i < size_; i--) {
			for (int j = numb2.size_ - 1; j >= 0; j--) {
				new_numb.elem_[j + i] = numb2.elem_[j] * elem_[size_ - 1 - i];
				new_numb.elem_[j + i + 1] += (new_numb.elem_[j + i] / 10);
				new_numb.elem_[j + i] %= 10;
			}
		}
		if (new_numb.elem_[0] == 0) {
			BigInt new_numb2(new_numb.size_ - 1);
			for (int i = new_numb.size_ - 1; i > 0; i--) {
				new_numb2.elem_[i] = new_numb.elem_[i];
			}
			*this = new_numb2;
		}
		*this = new_numb;
		sign_ = end_sign;
		return *this;
	}
}



