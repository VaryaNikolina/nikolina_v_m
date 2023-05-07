#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.hpp>

#include <sstream>

TEST_CASE("[rational] - Rational ctor") {
    CHECK(Rational() == Rational(0, 1));
    CHECK(Rational(3) == Rational(3, 1));
    CHECK(Rational(-3) == Rational(-3, 1));
    CHECK(Rational(10, 6) == Rational(5, 3));
    CHECK(Rational(-10, 6) == Rational(-5, 3));
    CHECK(Rational(10, -6) == Rational(-5, 3));
    CHECK(Rational(-10, -6) == Rational(5, 3));
    CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("[rational] - Rational add") {
    CHECK(Rational(3, 2) + Rational(5, 7) == Rational(31, 14));
    CHECK(Rational(5, 7) + Rational(3, 2) == Rational(31, 14));
    CHECK(Rational() + Rational() == Rational());
    CHECK(Rational() + Rational(29, 41) == Rational(29, 41));
    CHECK(Rational(5, 1) + Rational(3, 2) == Rational(13, 2));
}

TEST_CASE("[rational] - Rational subtract") {
    CHECK(Rational(31, 14) - Rational(5, 7) == Rational(3, 2));
    CHECK(Rational(25, 7) - Rational(2, 9) == Rational(211, 63));
    CHECK(Rational(2, 3) - Rational(7, 4) == Rational(-13, 12));
}

TEST_CASE("[rational] - Rational division") {
    CHECK(Rational(5, 2) / Rational(5, 2) == Rational(1, 1));
    CHECK(Rational(3, 2) / Rational(9, 8) == Rational(4, 3));
    CHECK_THROWS(Rational(3, 2) / Rational(5, 0));
}

TEST_CASE("/=") {
    Rational a = Rational(3, 4);
    a /= a;
    CHECK(a == Rational(1));
}

TEST_CASE("*=") {
    Rational a = Rational(3, 4);
    a *= a;
    CHECK(a == Rational(9, 16));
}

TEST_CASE("-=") {
    Rational a = Rational(3, 4);
    a -= a;
    CHECK(a == Rational(0));
}

TEST_CASE("+=") {
    Rational a = Rational(3, 4);
    a += a;
    CHECK(a == Rational(3, 2));
}

TEST_CASE("[rational] - Rational minus") {
    CHECK(-Rational() == Rational());
    CHECK(Rational(-5, 3) == -Rational(5, 3));
    CHECK(Rational(25, 7) == -(-(Rational(25, 7))));
    CHECK(Rational(29, 41) == -Rational(-29, 41));
}


TEST_CASE("checking throw") {
    Rational zero = Rational(0);
    Rational half = Rational(1, 2);
    CHECK(Rational(4, 5) < Rational(5, 6));
    CHECK(Rational(0, 3) == Rational(0));

    CHECK(!Rational(0, 123));
    CHECK(Rational(1));

    CHECK(Rational(0, -1) / Rational(INT_MAX) == Rational(0));
    CHECK(Rational(1, 2) == half);
    CHECK(Rational(1, -2) == -half);
    CHECK(Rational(-1, 2) == -half);
    CHECK(Rational(-1, -2) == half);
    CHECK(Rational(-2, -4) == half);

    CHECK(Rational(-0, -4) == zero);
    CHECK(Rational(0, -1) == zero);
    CHECK(Rational(0, 4) == zero);
    CHECK(Rational(-0) == zero);

    CHECK_THROWS(Rational(1, 0));
    CHECK_THROWS(Rational(1) / Rational(0));
    CHECK_THROWS(Rational(0, -0));
}

TEST_CASE("[rational] - I/O") {

    SUBCASE("Output") {

        std::stringstream sstrm;

        SUBCASE("Simple") {
            sstrm << Rational(23, 7);
            CHECK(sstrm.str() == "23/7");
        }

        sstrm.clear();

        SUBCASE("Default constructor") {
            sstrm << Rational();
            CHECK(sstrm.str() == "0/1");
        }

        sstrm.clear();


        SUBCASE("Negative") {
            sstrm << -Rational(3, 8);
            CHECK(sstrm.str() == "-3/8");
        }

        sstrm.clear();

        SUBCASE("Negative with reduce") {
            sstrm << Rational(-8, 2);
            CHECK(sstrm.str() == "-4/1");
        }

    }

    SUBCASE("Correct inputs") {

        Rational r;
        std::stringstream sstrm;

        SUBCASE("Simple") {
            sstrm.str("2/3");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::eofbit);
            CHECK(r == Rational(2, 3));
        }

        sstrm.clear();

        SUBCASE("Input with reducing") {
            sstrm.str("36/48");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::eofbit);
            CHECK(r == Rational(3, 4));
        }

        sstrm.clear();

        SUBCASE("Negative input") {
            sstrm.str("-8/7");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::eofbit);
            CHECK(r == Rational(-8, 7));
        }
    }

    SUBCASE("Correct inputs with extra spaces on begin and trash on end") {

        Rational r, r1, r2, r3, r4;
        std::stringstream sstrm;

        SUBCASE("Extra spaces on begin") {
            sstrm.str(" 1/3");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::eofbit);
            CHECK(r == Rational(1, 3));
        }

        sstrm.clear();

        SUBCASE("Extra extra spaces on begin") {
            sstrm.str("   -3/4");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::eofbit);
            CHECK(r == Rational(-3, 4));
        }

        sstrm.clear();

        SUBCASE("Extra spaces on both ends") {
            sstrm.str(" 5/9  ");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::goodbit);
            CHECK(r == Rational(5, 9));
        }

        sstrm.clear();

        SUBCASE("Extra spaces on both ends and negative number") {
            sstrm.str(" -3/9  ");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::goodbit);
            CHECK(r == Rational(-1, 3));
        }

        sstrm.clear();

        SUBCASE("Extra spaces on begin and trash on end") {
            sstrm.str(" 23/9abc");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::goodbit);
            CHECK(r == Rational(23, 9));
        }

        sstrm.clear();

        SUBCASE("Extra spaces on end") {
            sstrm.str("3/7 ");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::goodbit);
            CHECK(r == Rational(3, 7));
        }

        sstrm.clear();

        SUBCASE("Trash on end") {
            sstrm.str("9/2&");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::goodbit);
            CHECK(r == Rational(9, 2));
        }

        sstrm.clear();

        SUBCASE("Spaces") {
            sstrm.str("1/2 3/4 5/6");
            sstrm >> r1 >> r2 >> r3;
            CHECK(sstrm.rdstate() == std::ios_base::eofbit);
            CHECK(r1 == Rational(1, 2));
            CHECK(r2 == Rational(3, 4));
            CHECK(r3 == Rational(5, 6));
        }

        sstrm.clear();

        SUBCASE("Several rationals in one string with many ws") {
            sstrm.str("  1/2  3/4   5/6 ");
            sstrm >> r1 >> r2 >> r3;
            CHECK(sstrm.rdstate() == std::ios_base::goodbit);
            CHECK(r1 == Rational(1, 2));
            CHECK(r2 == Rational(3, 4));
            CHECK(r3 == Rational(5, 6));
        }

        sstrm.clear();

        SUBCASE("Several rationals in one string with symbols") {
            sstrm.str("1/3 3/7 5/4a");
            sstrm >> r1 >> r2 >> r3;
            CHECK(sstrm.rdstate() == std::ios_base::goodbit);
            CHECK(r1 == Rational(1, 3));
            CHECK(r2 == Rational(3, 7));
            CHECK(r3 == Rational(5, 4));
        }
    }

    SUBCASE("Uncorrect inputs") {
        Rational r, r1, r2, r3;
        std::stringstream sstrm;

        SUBCASE("Trash") {
            sstrm.str("kek");
            sstrm >> r;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }

        sstrm.clear();

        SUBCASE("Simple") {
            sstrm.str("3");
            sstrm >> r;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }

        sstrm.clear();

        SUBCASE("Bad delimiter") {
            sstrm.str("5\\3");
            sstrm >> r;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }

        sstrm.clear();

        SUBCASE("Numerator is trash") {
            sstrm.str("a/3");
            sstrm >> r;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }

        sstrm.clear();

        SUBCASE("Trash in numerator") {
            sstrm.str("a3/2");
            sstrm >> r;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }

        sstrm.clear();

        SUBCASE("Denominator is trash") {
            sstrm.str("3/*");
            sstrm >> r;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }

        sstrm.clear();

        SUBCASE("Spaces between 1") {
            sstrm.str("3 /2");
            sstrm >> r;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }

        sstrm.clear();

        SUBCASE("Spaces between 2") {
            sstrm.str("3/ 2");
            sstrm >> r;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }

        sstrm.clear();

        SUBCASE("Spaces between 3") {
            sstrm.str("3 / 2");
            sstrm >> r;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }

        sstrm.clear();

        SUBCASE("Denominator is negative") {
            sstrm.str("3/-2");
            sstrm >> r;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }

        sstrm.clear();

        SUBCASE("Several rationals in one string with symbol") {
            sstrm.str("1/3 a 3/7 5/4");
            sstrm >> r1 >> r2 >> r3;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }

        sstrm.clear();

        SUBCASE("Several rationals in one string without symbol") {
            sstrm.str("1/3  3/7 5/4");
            sstrm >> r1 >> r2 >> r3;
            CHECK(r3 == Rational(5, 4));
        }

        sstrm.clear();

        SUBCASE("Several rationals in one string with symbols before") {
            sstrm.str("1/3 a3/7 5/4");
            sstrm >> r1 >> r2 >> r3;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }

        sstrm.clear();

        SUBCASE("den 0") {
            sstrm.str("3/0");
            sstrm >> r;
            CHECK(sstrm.fail());
            CHECK(!sstrm.bad());
        }
    }
    

}