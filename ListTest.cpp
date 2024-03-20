// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa6
// --------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

using namespace std;

int main() {
   List A, B, C;

   cout << "Testing List ADT" << endl;

   for (int i = 1; i <= 10; i++) {
      A.insertAfter(i * 2);
      B.insertBefore(i * 3);
      C.insertAfter(i * 4);
   }

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;

   cout << "A.length() = 0?" << (A.length()==0 ? "true" : "false") << endl;
   cout << "B.length() = 0?" << (B.length()==0 ? "true" : "false") << endl;
   cout << "C.length() = 0?" << (C.length()==0 ? "true" : "false") << endl;
   cout << endl;

   A.moveFront();
   B.moveBack();
   C.moveNext();
   cout << "A.position() = " << A.position() << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << endl;

   cout << "A.peekNext() = " << A.peekNext() << endl;
   cout << "B.peekPrev() = " << B.peekPrev() << endl;
   cout << "C.peekNext() = " << C.peekNext() << endl;
   cout << endl;

   A.moveNext();
   B.movePrev();
   C.moveNext();
   cout << "A.position() = " << A.position() << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << endl;

   cout << "A.findNext(6) = " << A.findNext(6) << endl;
   cout << "B.findPrev(9) = " << B.findPrev(9) << endl;
   cout << "C.findNext(12) = " << C.findNext(12) << endl;
   cout << endl;

   cout << "A.length() = " << A.length() << endl;
   cout << "B.length() = " << B.length() << endl;
   cout << "C.length() = " << C.length() << endl;
   cout << endl;

   List D = A.concat(B).concat(C);
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   D.moveBack();
   cout << "D.eraseBefore()" << endl;
   D.eraseBefore();
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   D.moveFront();
   cout << "D.eraseAfter()" << endl;
   D.eraseAfter();
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;
   cout << "D.front() = " << D.front() << endl;
   cout << "D.back() = " << D.back() << endl;
   cout << endl;

   cout << "D.moveNext() = " << D.moveNext() << endl;
   cout << "D.movePrev() = " << D.movePrev() << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   cout << "D.setAfter(15)" << endl;
   D.setAfter(15);
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   D.moveBack();
   cout << "D.setBefore(20)" << endl;
   D.setBefore(20);
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   cout << "D.cleanup()" << endl;
   D.cleanup();
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   List E;
   E = D;
   cout << "E = " << E << endl;
   cout << "E.position() = " << E.position() << endl;
   cout << endl;

   cout << "E == D is " << (E == D ? "true" : "false") << endl;
   cout << endl;

   cout << "E.insertAfter(25)" << endl;
   E.insertAfter(25);
   cout << "E = " << E << endl;
   cout << "E.position() = " << E.position() << endl;
   cout << endl;

   cout << "E.insertBefore(30)" << endl;
   E.insertBefore(30);
   cout << "E = " << E << endl;
   cout << "E.position() = " << E.position() << endl;
   cout << endl;

   cout << "E.eraseAfter()" << endl;
   E.eraseAfter();
   cout << "E = " << E << endl;
   cout << "E.position() = " << E.position() << endl;
   cout << endl;

   cout << "E.eraseBefore()" << endl;
   E.eraseBefore();
   cout << "E = " << E << endl;
   cout << "E.position() = " << E.position() << endl;
   cout << endl;

   cout << "E.clear()" << endl;
   E.clear();
   cout << "E = " << E << endl;
   cout << "E.position() = " << E.position() << endl;
   cout << endl;

   cout << "Testing exceptions:" << endl;

   cout << "E.front(): ";
   try {
      E.front();
   } catch (std::length_error& e) {
      cout << e.what() << endl;
   }

   cout << "E.back(): ";
   try {
      E.back();
   } catch (std::length_error& e) {
      cout << e.what() << endl;
   }

   cout << "E.moveFront(): ";
   try {
      E.moveFront();
   } catch (std::range_error& e) {
      cout << e.what() << endl;
   }

   cout << "E.moveBack(): ";
   try {
      E.moveBack();
   } catch (std::range_error& e) {
      cout << e.what() << endl;
   }
   cout << "E.movePrev(): ";
   try {
      E.movePrev();
   } catch (std::range_error& e) {
      cout << e.what() << endl;
   }

   cout << "E.moveNext(): ";
   try {
      E.moveNext();
   } catch (std::range_error& e) {
      cout << e.what() << endl;
   }

   cout << "E.setBefore(10): ";
   try {
      E.setBefore(10);
   } catch (std::range_error& e) {
      cout << e.what() << endl;
   }

   cout << "E.setAfter(10): ";
   try {
      E.setAfter(10);
   } catch (std::range_error& e) {
      cout << e.what() << endl;
   }

   cout << "E.eraseBefore(): ";
   try {
      E.eraseBefore();
   } catch (std::range_error& e) {
      cout << e.what() << endl;
   }

   cout << "E.eraseAfter(): ";
   try {
      E.eraseAfter();
   } catch (std::range_error& e) {
      cout << e.what() << endl;
   }

   cout << endl;

   cout << "Testing copy constructor:" << endl;
   List F(D);
   cout << "F = " << F << endl;
   cout << "F.position() = " << F.position() << endl;
   cout << "F == D is " << (F == D ? "true" : "false") << endl;

   cout << endl;

   cout << "Testing assignment operator:" << endl;
   List G;
   G = D;
   cout << "G = " << G << endl;
   cout << "G.position() = " << G.position() << endl;
   cout << "G == D is " << (G == D ? "true" : "false") << endl;

   cout << endl;

   cout << "All tests completed." << endl;

   return EXIT_SUCCESS;
}


