#pragma once

#ifndef NODE
#define NODE

#include <iostream>

using namespace std;

template <typename T>
class Node {
    public:
		T data;
		Node* next;

		Node() {
			data = NULL;
			next = NULL;
		}

		Node(T Data) {
			data = Data;
			next = NULL;
		}

		Node(T Data, Node<T>* Next) {
			data = Data;
			next = Next;
		}
};

#endif
