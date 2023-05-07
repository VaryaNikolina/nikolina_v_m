#include <rational/rational.hpp>

#include <iosfwd>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <numeric>

int32_t gcd(int32_t a, int32_t b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

Rational::Rational(int32_t num) noexcept : num_(num), den_(1) {};

Rational::Rational(int32_t num, int32_t denom) {
    if (denom == 0)
        throw "Deminator is not correct: \n";
    else {
        num_ = num;
        den_ = denom;
    }
    normalize();
};


Rational Rational::operator-() const noexcept {
    return Rational(num_*(-1), den_);
};
Rational::operator bool() const noexcept {
    if (num_ == 0) return false;
    return true;
};

bool Rational::operator==(const Rational& rhs) const noexcept {
    return num_ * rhs.denom() - rhs.num() * den_ == 0;
}
bool Rational::operator!=(const Rational& rhs) const noexcept {
    return !(num_ * rhs.denom() - rhs.num() * den_ == 0);
};
bool Rational::operator>(const Rational& rhs) const noexcept {
    return num_ * rhs.denom() - rhs.num() * den_ > 0;
};
bool Rational::operator<(const Rational& rhs) const noexcept {
    return num_ * rhs.denom() - rhs.num() * den_ < 0;
};
bool Rational::operator>=(const Rational& rhs) const noexcept {
    return num_ * rhs.denom() - rhs.num() * den_ >= 0;
};
bool Rational::operator<=(const Rational& rhs) const noexcept {
    return num_ * rhs.denom() - rhs.num() * den_ <= 0;
};

Rational& Rational::operator*=(const Rational& rhs) noexcept {
    num_ *= rhs.num();
    den_ *= rhs.denom();
    normalize();
    return *this;
};
Rational& Rational::operator+=(const Rational& rhs) noexcept {
    num_ = num_ * rhs.denom() + rhs.num() * den_;
    den_ *= rhs.denom();
    normalize();
    return *this;
};


Rational& Rational::operator-=(const Rational& rhs) noexcept {
    num_ = num_ * rhs.denom() - rhs.num() * den_;
    den_ *= rhs.denom();
    normalize();
    return *this;
};

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.num_ != 0) {
        int32_t tmp = rhs.num();
        num_ *= rhs.denom();
        den_ *= tmp;
        normalize();
        return *this;
    }
    else {
        throw "Deminator is not correct: \n";
    }
};

void Rational::normalize() noexcept {
    if (num() * 1ll * denom() < 0) {
        num_ = -abs(num());
        den_ = abs(denom());
    }
    else {
        num_ = abs(num());
        den_ = abs(denom());
    }

    if (num_ == 0) {
        den_ = 1;
    }
    else {
        int32_t gcd = std::gcd(std::abs(num()), denom());
        num_ /= gcd;
        den_ /= gcd;
    }
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept {
    return rhs.write_to(ostrm);
}
std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
    return rhs.read_from(istrm);
}


std::ostream& Rational::write_to(std::ostream& ostrm) const noexcept {
    ostrm << num_ << delimiter_ << den_;
    return ostrm;
};
std::istream& Rational::read_from(std::istream& istrm) noexcept {
    int32_t num;
    char delimiter;
    int32_t den;

    istrm >> std::ws >> num >> std::noskipws >> delimiter >> den;
    if (istrm.eof() || istrm.good()) {
        if (Rational::delimiter_ == delimiter && den > 0) {
            *this = Rational(num, den);
        }
        else {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
};