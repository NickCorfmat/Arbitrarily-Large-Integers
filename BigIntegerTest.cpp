// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa6
// --------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>

#include "BigInteger.h"

using namespace std;

int main() {

    string s1 = "91287346670000043892345634563400005619187236478";
    string s2 = "-330293847502398475";
    string s3 = "9876545439000000345634560000000002000034565430000000006543654365346534";
    string s4 = "9876545439000000000000000100000000000006543654365346534";
    string s5 = "98765454390000034563456191872363456345619187236000456456345756780000065436543";
    string s6 = "9876545439000000000000000000000000000006543";

    BigInteger A = BigInteger(s1);
    BigInteger B = BigInteger(s2);
    BigInteger C = BigInteger(s3);
    BigInteger D = BigInteger(s4);
    BigInteger E = BigInteger(s5);
    BigInteger F = BigInteger(s6);

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    cout << "D = " << D << endl;
    cout << "E = " << E << endl;
    cout << "F = " << F << endl << endl;

    BigInteger sum1 = A + B;
    BigInteger difference1 = B - C;
    BigInteger product1 = C * D;

    cout << "A + B = " << sum1 << endl;
    cout << "B - C = " << difference1 << endl;
    cout << "C * D = " << product1 << endl << endl;

    BigInteger sum2 = B + C;
    BigInteger difference2 = C - D;
    BigInteger product2 = D * E;

    cout << "B + C = " << sum2 << endl;
    cout << "C - D = " << difference2 << endl;
    cout << "D * E = " << product2 << endl << endl;

    BigInteger sum3 = D + E;
    BigInteger difference3 = E - F;
    BigInteger product3 = E * F;

    cout << "D + E = " << sum3 << endl;
    cout << "E - F = " << difference3 << endl;
    cout << "E * F = " << product3 << endl << endl;

    BigInteger sum4 = F + A;
    BigInteger difference4 = A - B;
    BigInteger product4 = A * B;

    cout << "F + A = " << sum4 << endl;
    cout << "A - B = " << difference4 << endl;
    cout << "A * B = " << product4 << endl << endl;

    cout << "A < B : " << (A < B ? "true" : "false") << endl;
    cout << "A > B : " << (A > B ? "true" : "false") << endl;
    cout << "A == B: " << (A == B ? "true" : "false") << endl << endl;

    A += B;
    B -= C;
    C *= D;

    cout << "A += B: " << A << endl;
    cout << "B -= C: " << B << endl;
    cout << "C *= D: " << C << endl << endl;

    BigInteger sum5 = A + B;
    BigInteger difference5 = B - C;
    BigInteger product5 = C * D;

    cout << "A + B = " << sum5 << endl;
    cout << "B - C = " << difference5 << endl;
    cout << "C * D = " << product5 << endl << endl;

    BigInteger sum6 = D + E;
    BigInteger difference6 = E - F;
    BigInteger product6 = F * A;

    cout << "D + E = " << sum6 << endl;
    cout << "E - F = " << difference6 << endl;
    cout << "F * A = " << product6 << endl << endl;

    cout << "A < B : " << (A < B ? "true" : "false") << endl;
    cout << "B > C : " << (B > C ? "true" : "false") << endl;
    cout << "C == D: " << (C == D ? "true" : "false") << endl << endl;

    A += C;
    B -= D;
    C *= E;

    cout << "A += C: " << A << endl;
    cout << "B -= D: " << B << endl;
    cout << "C *= E: " << C << endl << endl;

    BigInteger sum7 = A + B;
    BigInteger difference7 = B - C;
    BigInteger product7 = C * D;

    cout << "A + B = " << sum7 << endl;
    cout << "B - C = " << difference7 << endl;
    cout << "C * D = " << product7 << endl << endl;

    cout << "A == B: " << (A == B ? "true" : "false") << endl;
    cout << "B <= C: " << (B <= C ? "true" : "false") << endl;
    cout << "C > D : " << (C > D ? "true" : "false") << endl << endl;

    // Test exceptions
    try {
        BigInteger X = BigInteger("");
    } catch (std::invalid_argument& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        BigInteger Y = BigInteger("+");
    } catch (std::invalid_argument& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        BigInteger Z = BigInteger("12329837492387492837492$4982379487293847");
    } catch (std::invalid_argument& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        BigInteger W = BigInteger("5298374902837409+82734098729287349827398");
    } catch (std::invalid_argument& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }

    return EXIT_SUCCESS;
}
