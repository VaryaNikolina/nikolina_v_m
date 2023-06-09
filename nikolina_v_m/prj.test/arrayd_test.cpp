#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <arrayd/arrayd.hpp>

#include <doctest/doctest.h>

TEST_CASE("ARRAYD WORKING LIKE ARRAYT") {
	SUBCASE("A") {
		size_t size = 4;
		ArrayD b(size);
		SUBCASE("0") {
			CHECK(b[0] == 0);
		}
		b = b;
		b[2] = 2.2;
		SUBCASE("SIZE") {
			CHECK(b.ssize() == size);
		}
		SUBCASE("ARRAYD VALUES") {
			CHECK(b[2] == 2.2);
			CHECK(b[0] == 0.000000);
		}
		SUBCASE("CHANGE VALUES") {
			b[0] = 10.700;
			CHECK(b[0] == 10.700);
		}
	}
}
