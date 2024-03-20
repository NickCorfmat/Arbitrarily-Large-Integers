// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa6
// -------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <stdexcept>

#include "BigInteger.h"

/*** Global Constants ***/

const int power = 9;
const ListElement base = 10;

/*** Constructors-Destructors ***/

BigInteger::BigInteger() {
	signum = 0;
}

BigInteger::BigInteger(long x) {
	if (x > 0) {
		signum = 1;
	} else if (x < 0) {
		signum = -1;
	} else {
		signum = 0;
	}

	// Calculate b = base^power
	long b = 1;

	for (int i = 0; i < power; i++) {
		b *= base;
	}

	while (x > 0) {
		digits.insertBefore(x % base);
		x = x / b;
	}
}

BigInteger::BigInteger(std::string s) {

	// Check if string is empty
	if (s.empty()) {
		throw std::invalid_argument("Constructor: empty string");
	}

	// Create a clean version of input string
	std::string num = s;

	// Check for optional + or - sign
	if (s[0] == '+' || s[0] == '-') {
		num = num.substr(1);
	}
	
	// Check if string contains only numbers
	for (char c : num) {
		if (c < '0' || c > '9') {
			throw std::invalid_argument("Constructor: non-numeric string");
		}
	}

	// Delete all unnecessary leading zeros
	while (num[0] == '0') {
		num = num.substr(1);
	}

	// Determine sign of BigInteger
	int length = num.length();

        if (s[0] == '-') {
                signum = -1;
        } else if ((num[0] != '0' && length > 0) || s[0] == '+') {
                signum = 1;
        } else {
                signum = 0;
	}

	std::string segment;

	// Split string into size, power, and append digits to list
	for (int i = length - 1; i >= 0; i--) {
		segment = num[i] + segment;

		if ((length - i) % power == 0) {
			digits.insertAfter(std::stoi(segment));
			segment = "";
		}
	}

	// Append remaining digits
	if (!segment.empty()) {
		digits.insertAfter(std::stoi(segment));
	}
}

BigInteger::BigInteger(const BigInteger& N) {
	signum = N.signum;
	digits = N.digits;
}

/*** Access Functions ***/

int BigInteger::sign() const {
	return signum;
}

int BigInteger::compare(const BigInteger& N) const {
	if (signum < N.signum) {
		return -1;
	} else if (signum > N.signum) {
		return 1;
	}

	if (digits.length() < N.digits.length()) {
		return -signum;
	} else if (digits.length() > N.digits.length()) {
		return signum;
	}

	// Both lengths are equal, make copies of both lists, and iterate through digits
	List A = digits;
	List B = N.digits;
	
	A.moveFront();
	B.moveFront();

	while (A.position() < A.length() && B.position() < B.length()) {
		long num1 = A.moveNext();
		long num2 = B.moveNext();

		if (num1 < num2) {
			return -signum;
		} else if (num1 > num2) {
			return signum;
		}
	}

	return 0;
}

void BigInteger::makeZero() {
	signum = 0;
	digits.clear();
}

void BigInteger::negate() {
	if (signum != 0) {
		signum = -signum;
	}
}

BigInteger BigInteger::add(const BigInteger& N) const {

	// Check if either number is zero
	if (signum == 0) {
		return N;
	} else if (N.signum == 0) {
		return *this;
	}

	BigInteger sum;

	List A = digits;
	List B = N.digits;

	// Calculate b = base^power
	int b = 1;

	for (int i = 0; i < power; i++) {
		b *= base;
	}

	if (signum == N.signum) {
		// Adding either two positives or two negatives
		sum.signum = signum;

		long carry = 0;

		A.moveBack();
		B.moveBack();

		while (A.position() > 0 || B.position() > 0 || carry != 0) {
			long d1 = A.position() > 0 ? A.movePrev() : 0;
			long d2 = B.position() > 0 ? B.movePrev() : 0;

			long total = d1 + d2 + carry;
			carry = total / b;
			total %= b;

			sum.digits.insertAfter(total);
		}

		return sum;
	} else {
		// Adding positive and negative
		const BigInteger& B = signum == 1 ? *this : N;
		const BigInteger& S = signum == 1 ? N : *this;

		BigInteger negS = S;
		negS.negate();

		int cmp = B.compare(negS);

		if (cmp != 0) {
			sum = B.sub(negS);
			sum.signum = cmp > 0 ? 1 : -1;
		}

                return sum;
	}
}

BigInteger BigInteger::sub(const BigInteger& N) const {

	// Check if either number is zero
	if (signum == 0) {
		BigInteger negN = N;
		negN.negate();
		return negN;
	} else if (N.signum == 0) {
		return *this;
	}

	BigInteger diff;
	
	// Calculate b = base^power
	int b = 1;
	
	for (int i = 0; i < power; i++) {
		b *= base;
	}

	if (signum == N.signum) {
		int cmp = compare(N);

		// Return zero if both numbers are equal
                if (cmp == 0) {
                        return diff;
                }

		// Special case if subtracting two negatives
		if (signum == -1) {
			const BigInteger& A = *this;
			const BigInteger& B = N;

			BigInteger X = A;
			BigInteger Y = B;

			X.negate();
			Y.negate();

			cmp = X.compare(Y);
			int sign = cmp > 0 ? -1 : 1;

			diff = X.sub(Y);
			diff.signum = sign;
		} else {

			// Subtracting two positives
			List A = cmp > 0 ? digits : N.digits;
			List B = cmp > 0 ? N.digits : digits;
		
			diff.signum = cmp > 0 ? 1 : -1;

                	long borrow = 0;

                	A.moveBack();
                	B.moveBack();

                	while (A.position() > 0 || B.position() > 0) {
                        	long d1 = A.position() > 0 ? A.movePrev() : 0;
                        	long d2 = B.position() > 0 ? B.movePrev() : 0;

                        	long total = d1 - d2 - borrow;
			
				if (total < 0) {
					borrow = 1;
					total = (b - (total * -1)) % b;
				} else {
					borrow = 0;
				}

				diff.digits.insertAfter(total);
                	}

			// Clean up front of list
			if (diff.digits.front() == 0) {
				diff.digits.moveFront();
				diff.digits.eraseAfter();
			}
		}

		return diff;
	} else {
		// Subtracting positive and negative
		int sign = signum;

		const BigInteger& B = signum == 1 ? *this : N;
                const BigInteger& S = signum == 1 ? N : *this;

                BigInteger negS = S;
                negS.negate();

                diff = B.add(negS);
		diff.signum = sign;

                return diff;
	}
}

BigInteger BigInteger::mult(const BigInteger& N) const {
	BigInteger prod;

	if (signum == 0 || N.signum == 0) {
		return prod;
	}

	int sign = signum * N.signum;

	// A = smaller int, B = larger int
	int cmp = compare(N);
	
	List A = cmp > 0 ? N.digits : digits;
	List B = cmp > 0 ? digits : N.digits;

	A.moveBack();

	int pos1 = 0;

	while (A.position() > 0) {
		B.moveBack();

		long d1 = A.movePrev();
		int pos2 = 0;

		while (B.position() > 0) {
			long d2 = B.movePrev();
			long total = d1 * d2;

			std::string num = std::to_string(total) + std::string((pos1 + pos2) * power, '0');

			BigInteger B = BigInteger(num);
			prod = prod.add(B);

			pos2++;
		}

		pos1++;
	}

	prod.signum = sign;

	return prod;
}

/*** Other Functions ***/

std::string BigInteger::to_string() {
	std::string s = "";

	if (signum == 0 || digits.length() == 0) {
		return "0";	
	} else if (signum == -1) {
		s += '-';
	}

	digits.moveFront();
	s += std::to_string(digits.moveNext());

	for (int i = 1; i < digits.length(); i++) {
		std::string num = std::to_string(digits.moveNext());
		s += std::string((power - num.length()), '0') + num;
	}

	return s;
}

/*** Overidden Operators ***/

std::ostream& operator<<( std::ostream& stream, BigInteger N) {
	return stream << N.to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ) {
	return A.compare(B) == 0;
}

bool operator<( const BigInteger& A, const BigInteger& B ) {
	return A.compare(B) < 0;
}

bool operator<=( const BigInteger& A, const BigInteger& B ) {
	return A.compare(B) <= 0;
}

bool operator>( const BigInteger& A, const BigInteger& B ) {
	return A.compare(B) > 0;
}

bool operator>=( const BigInteger& A, const BigInteger& B ) {
	return A.compare(B) >= 0;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
	return A.add(B);
}

BigInteger operator+=(BigInteger& A, const BigInteger& B ) {
	A = A.add(B);
	return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
	return A.sub(B);
}

BigInteger operator-=(BigInteger& A, const BigInteger& B ) {
	A = A.sub(B);
	return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
	return A.mult(B);
}

BigInteger operator*=(BigInteger& A, const BigInteger& B ) {
	A = A.mult(B);
	return A;
}
