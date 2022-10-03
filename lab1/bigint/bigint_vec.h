#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H
#endif
#include <string>

class BigInt {

private:

    short* elem_;
    bool sign_;
    int size_;

public:

    BigInt();
    BigInt(int);
    BigInt(std::string); // бросать исключение std::invalid_argument при ошибке
    BigInt(const BigInt&);
    ~BigInt();

    //short& operator[](int);
    //const short& operator[](int) const;

    BigInt& operator=(const BigInt&);  //возможно присваивание самому себе!

    BigInt get_log2(const BigInt&);

    BigInt operator~() const;
    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator^=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    BigInt& BigInt::operator*=(const int& numb2);
    BigInt& BigInt::operator+=(const int& numb2);
    BigInt& BigInt::operator-=(const int& numb2);
    BigInt& BigInt::operator/=(const int& numb2);
    BigInt& BigInt::operator%=(const int& numb2);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator int() const;
    operator std::string() const;
    operator BigInt() const;

    size_t size() const;  // size in bytes

    void delete_leading_zeroes(BigInt&);
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream& o, const BigInt& i);

