#include "rational.hpp"

Rational::Rational(int num, int den) {
    num_ = num;
    den_ = den;
    if (den_ == 0) {
        throw "Denominator can't be zero";
    }
    Normalise();
}


void Rational::Normalise() {
    if (num_ < 0 && den_ < 0) {
        num_ = std::abs(num_);
        den_ = std::abs(den_);
    } else if (den_ < 0){
        num_ *= -1;
        den_ = std::abs(den_);
    }
    int g = gcd(std::abs(num_), std::abs(den_));
    num_ /= g;
    den_ /= g;
}

Rational::Rational(const Rational& other) {
    num_ = other.num();
    den_ = other.den();
}

Rational Rational::operator+(const Rational& rhs) noexcept{
    int den = den() * rhs.den();
    int num = num() * rhs.den() + rhs.num() * den();
    return Rational(num, den);
}

Rational Rational::operator-(const Rational& rhs) noexcept {
    int den = den() * rhs.den();
    int num = num() * rhs.den() - rhs.num() * den();
    return Rational(num, den);
}

Rational Rational::operator*(const Rational& rhs) noexcept {
    int den = den() * rhs.den();
    int num = num() * rhs.num();
    return Rational(num, den);
}

Rational Rational::operator/(const Rational& rhs) {
    int den = den() * ((rhs.num() < 0) ? rhs.num() * -1 : rhs.num());
    int num = num() * ((rhs.num() < 0) ? rhs.den() * -1 : rhs.den());
    return Rational(num, den);
}

Rational& Rational::operator+=(const Rational& rhs) { return *this = *this + rhs; }
Rational& Rational::operator-=(const Rational& rhs) { return *this = *this - rhs; }
Rational& Rational::operator*=(const Rational& rhs) { return *this = *this * rhs; }
Rational& Rational::operator/=(const Rational& rhs) { return *this = *this / rhs; }

Rational& Rational::operator=(const Rational& rhs) {
    num_ = rhs.num();
    den_ = rhs.den();
    return *this;
}

Rational Rational::operator-() const { return Rational(-num(), den()); }
Rational Rational::operator+() const { return Rational(num(), den()); }

Rational Rational::operator++(int) {
    Rational tmp(*this);
    *this += 1;
    return tmp;
}

Rational& Rational::operator++() {
    return *this += Rational(1);
}

Rational Rational::operator--(int) {
    Rational tmp(*this);
    *this -= 1;
    return tmp;
}

Rational& Rational::operator--() {
    return *this -= Rational(1);
}

bool Rational::operator==(const Rational& rhs) const noexcept { return (num() == rhs.num() && den() == rhs.den()); }
bool Rational::operator!=(const Rational& rhs) const noexcept { return (num() != rhs.num() || den() != rhs.den()); }
bool Rational::operator>=(const Rational& rhs) const noexcept { return (num() * rhs.den() >= rhs.num() * den()); }
bool Rational::operator<=(const Rational& rhs) const noexcept { return (num() * rhs.den() <= rhs.num() * den()); }
bool Rational::operator>(const Rational& rhs) const noexcept { return (num() * rhs.den() > rhs.num() * den()); }
bool Rational::operator<(const Rational& rhs) const noexcept { return (num() * rhs.den() < rhs.num() * den()); }

Rational operator+(int lhs, const Rational& rhs) { return Rational(lhs) + rhs; }
Rational operator-(int lhs, const Rational& rhs) { return Rational(lhs) - rhs; }
Rational operator*(int lhs, const Rational& rhs) { return Rational(lhs) * rhs; }
Rational operator/(int lhs, const Rational& rhs) { return Rational(lhs) / rhs; }

std::ostream& operator<<(std::ostream& basicOstream, const Rational& rhs) {
    return basicOstream << rhs.AsString();
}

std::istream& operator>>(std::istream& , Rational& rhs) {
    int a, b;
    basicIstream >> a >> b;
    rhs = Rational(a, b);
    return basicIstream;
}
