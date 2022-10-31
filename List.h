#pragma once

#ifndef LIST
#define LIST

#include <iostream>

#include "Node.h"

using namespace std;

template <typename T>
class List {
    public:
		Node<T>* head;
		int size;

		List() {
			head = NULL;
			size = 0;
		}

		int getSize() {
			return size;
		}

		T get(int key) {
			if(key < 0 || key >= size) {
				cout << "Cannot access nodes outside the bounds of the list" << endl;
			}

			Node<T>* curr = head;
			for(int i = 0; i < key; i++) {
				curr = curr->next;
			}
			return curr->data;
		}

		void print() {
			Node<T>* curr = head;
			for(int i = 0; i < size; i++) {
				std::cout << curr->data;
				if(i != size - 1) {
					std::cout << ", ";
				}
				curr = curr->next;
			}
			std::cout << std::endl;
		}

		void push(T Data) {
			if(size == 0) {
				head = new Node<T>(Data);
			} else {
				Node<T>* curr = head;
				while(curr->next != NULL) {
					curr = curr->next;
				}
				curr->next = new Node<T>(Data);
			}
			size++;
		}

		void insert(T Data, int key) {
			if(key < 0 || key >= size) {
				cout << "Cannot insert a node outside of the bounds of the list" << endl;
			}

			if(key == 0) {
				Node<T>* node = new Node<T>(Data, head);
				head = node;
			} else {
				Node<T>* curr = head;
				for(int i = 0; i < key - 1; i++) {
					curr = curr->next;
				}
				Node<T>* node = new Node<T>(Data, curr->next);
				curr->next = node;
			}
			size++;
		}

		T edit(T newData, int key) {
			if(key < 0 || key >= size) {
				cout << "Cannot edit a node that is outside the bounds of the list" << endl;
			}

			T temp = 0;
			Node<T>* curr = head;
			for(int i = 0; i < key; i++) {
				curr = curr->next;
			}
			temp = curr->data;
			curr->data = newData;

			return temp;
		}

		T remove(int key) {
			if(key < 0 || key >= size) {
				cout << "Cannot remove a node that is outside the bounds of the list" << endl;
			}

			T temp = 0;
			if(key == 0) {
				Node<T>* node = head;
				head = head->next;
				temp = node->data;
				delete node;
			} else {
				Node<T>* curr = head;
				for(int i = 0; i < key - 1; i++) {
					curr = curr->next;
				}
				Node<T>* node = curr->next;
				curr->next = node->next;
				temp = node->data;
				delete node;
			}

			size--;
			return temp;
		}
};

#endif
