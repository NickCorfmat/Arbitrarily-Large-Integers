// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa6
// --------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>
#include <exception>

#include "List.h"

/*** Constructors-Destructors ***/

List::Node::Node(ListElement x) {
	data = x;
	next = nullptr;
	prev = nullptr;
}

List::List() {
	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

List::List(const List &L) {
	frontDummy = new Node(0);
        backDummy = new Node(0);
	frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
        beforeCursor = frontDummy;
        afterCursor = backDummy;
        pos_cursor = 0;
        num_elements = 0;

	Node* N = L.frontDummy->next;

	while (N != L.backDummy) {
		this->insertBefore(N->data);
		N = N->next;
	}

	this->moveFront();
}

List::~List() {
	clear();
	delete frontDummy;
	delete backDummy;
}

int List::length() const {
	return num_elements;
}

ListElement List::front() const {
	if (num_elements <= 0) {
		throw std::length_error("Error: Calling front() on empty List");
	}

	return frontDummy->next->data;
}

ListElement List::back() const {
        if (num_elements <= 0) {
                throw std::length_error("Error: Calling back() on empty List");
	}

        return backDummy->prev->data;
}

int List::position() const {
	return pos_cursor;
}

ListElement List::peekNext() const {
	if (pos_cursor >= num_elements) {
		throw std::range_error("Error: Calling peekNext() on invalid position");
	}

	return afterCursor->data;
}

ListElement List::peekPrev() const {
	if (pos_cursor <= 0) {
                throw std::range_error("Error: Calling peekPrev() on invalid position");
	}

        return beforeCursor->data;
}

/*** Manipulation Procedures ***/

void List::clear() {
	while (num_elements > 0) {
		moveFront();
		eraseAfter();
	}
}

void List::moveFront() {
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;

	pos_cursor = 0;
}

void List::moveBack() {
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;

	pos_cursor = num_elements;
}

ListElement List::moveNext() {
	if (pos_cursor >= num_elements) {
		throw std::range_error("Error: Calling moveNext() on invalid cursor position");
	}

	beforeCursor = afterCursor;
	beforeCursor->next = afterCursor->next;
	afterCursor->next->prev = beforeCursor;
	afterCursor = afterCursor->next;

	pos_cursor++;

	return beforeCursor->data;
}

ListElement List::movePrev() {
        if (pos_cursor <= 0) {
                throw std::range_error("Error: Calling movePrev() on invalid cursor position");
	}

        afterCursor = beforeCursor;
        afterCursor->prev = beforeCursor->prev;
        beforeCursor->prev->next = afterCursor;
        beforeCursor = beforeCursor->prev;

        pos_cursor--;

        return afterCursor->data;
}

void List::insertBefore(ListElement x) {
	Node* N = new Node(x);

        N->prev = beforeCursor;
        N->next = afterCursor;
	beforeCursor->next = N;
        afterCursor->prev = N;
	beforeCursor = N;
	
	pos_cursor++;
	num_elements++;
}

void List::insertAfter(ListElement x) {
	Node* N = new Node(x);

	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	afterCursor = N;

        num_elements++;
}

void List::setAfter(ListElement x) {
	if (pos_cursor >= num_elements) {
		throw std::range_error("Error: Calling setAfter() on invalid cursor position");
	}

	afterCursor->data = x;
}

void List::setBefore(ListElement x) {
	if (pos_cursor <= 0) {
                throw std::range_error("Error: Calling setBefore() on invalid cursor position");
        }

        beforeCursor->data = x;
}

void List::eraseAfter() {
        if (pos_cursor >= num_elements) {
                throw std::range_error("Error: Calling eraseAfter() on invalid cursor position");
        }

	beforeCursor->next = afterCursor->next;
	afterCursor->next->prev = beforeCursor;
	Node* N = afterCursor;
	afterCursor = beforeCursor->next;

	delete N;

	num_elements--;
}

void List::eraseBefore() {
        if (pos_cursor <= 0) {
                throw std::range_error("Error: Calling eraseAfter() on invalid cursor position");
        }

        afterCursor->prev = beforeCursor->prev;
        beforeCursor->prev->next = afterCursor;
	Node* N = beforeCursor;
        beforeCursor = afterCursor->prev;

        delete N;

	pos_cursor--;
        num_elements--;
}

/*** Other Functions ***/

int List::findNext(ListElement x) {
	Node* N = afterCursor;
	int pos = pos_cursor + 1;

	while (N != backDummy) {
		if (N->data == x) {
			beforeCursor = N;
			afterCursor = N->next;
			pos_cursor = pos;

			return pos_cursor;
		}

		N = N->next;
		pos++;
	}

	beforeCursor = backDummy->prev;
	afterCursor = backDummy;
	pos_cursor = num_elements;

	return -1;
}

int List::findPrev(ListElement x) {
	Node* N = beforeCursor;
	int pos = pos_cursor - 1;

	while (N != frontDummy) {
                if (N->data == x) {
                        beforeCursor = N->prev;
			afterCursor = N;
                        pos_cursor = pos;

                        return pos_cursor;
                }

                N = N->prev;
		pos--;
        }

	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
        pos_cursor = 0;

        return -1;
}

void List::cleanup() {
	if (num_elements <= 1) {
		return;
	}
	
	Node* current = frontDummy->next;

	while (current != backDummy) {
		Node* iter = current->next;

		while (iter != backDummy) {
			if (current->data == iter->data) {
				if (iter == beforeCursor) {
					beforeCursor = iter->prev;
				} else if (iter == afterCursor) {
					afterCursor = iter->next;
				}

				iter->prev->next = iter->next;
				iter->next->prev = iter->prev;
				delete iter;
				iter = current->next;
				num_elements--;

			} else {
				iter = iter->next;
			}
		}

		current = current->next;
	}

	if (pos_cursor != 0) {
		ListElement x = peekPrev();
		moveFront();
		findNext(x);
	}
}

List List::concat(const List &L) const {
	List C;
	Node* N = this->backDummy->prev;
	Node* M = L.backDummy->prev;

	while (M != L.frontDummy) {
		C.insertAfter(M->data);
		M = M->prev;
	}

	while (N != this->frontDummy) {
		C.insertAfter(N->data);
		N = N->prev;
	}

	C.moveFront();

	return C;
}

std::string List::to_string() const {
	Node* N = nullptr;
	std::string s = "(";

	for (N = frontDummy->next; N !=backDummy; N = N->next) {
		s += std::to_string(N->data) + (N==backDummy->prev? "" : ", ");		
	}

	return s + ")";
}

bool List::equals(const List &R) const {
	bool eq = false;

	eq = (this->num_elements == R.num_elements);

	Node* N = this->frontDummy;
	Node* M = R.frontDummy;

	while (eq && N != this->backDummy) {
		eq = (N->data==M->data);
		N = N->next;
		M = M->next;
	}

	return eq;
}

/*** Overriden Operators ***/

std::ostream& operator<<( std::ostream& stream, const List& L) {
	return stream << L.to_string();
}

bool operator==( const List& A, const List& B) {
	return A.equals(B);
}

List& List::operator=( const List& L) {
	if (this != &L) {
		List temp = L;

		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(num_elements, temp.num_elements);
		std::swap(pos_cursor, temp.pos_cursor);
	}

	return *this;
}
