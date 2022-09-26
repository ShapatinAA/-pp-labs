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
		for (int i = 0; i < size_; ++i) {
			elem_[i] = 0;
		}
}

BigInt::BigInt(std::string str_) {
	int str_size = str_.size();
	if (!str_size) {
		std::cout << "invalid_argument";
		abort();
	}
	short* elem_(new short[str_size]);
	sign_ = 0;
	size_ = str_size - 1;
	str_size--;
	while (str_size + 1) {
		if (str_[str_size] >= '0' && str_[str_size] <= '9') {
			elem_[str_size] = str_[str_size] - '0';
			str_size--;
		}
		else {
			if (str_size == 0) {
				switch (elem_[str_size])
				{
				case '-':
					sign_ = 1;
					size_ = str_.size() - 1;
					break;
				case '+':
					sign_ = 0;
					size_ = str_.size() - 1;
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
	BigInt buf(size_);
	for (int i = 0; i < size_; i++) {
		buf.elem_[i] = ~elem_[i];
	}
	buf.sign_ = ~sign_;
	return buf;
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
				return (new_numb);
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
				BigInt new_numb(size_ - 1);
				for (curr_pos = size_ - 2; curr_pos >= 0; curr_pos--) {
					new_numb.elem_[curr_pos] = elem_[curr_pos];
				}
				*this = new_numb;
				return (*this);
			}
		}
	}
}

const BigInt& BigInt::operator++(int) const {
	BigInt tmp = *this;
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
			*this(new_numb);
			return (new_numb);
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

BigInt& BigInt::operator--() {
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
			return (new_numb);
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
