#pragma once

#ifndef COMMON
#define COMMON

#include <iostream>

#include "List.h"

using namespace std;

class Common {
    public:
	template <typename T>
	void swap(List<T> list, int a, int b) {
	    if(a == b) { return; }
	    int* temp = list.edit(list.get(a), b);
	    list.edit(*temp, a);
	    delete temp;
	}

	int modulo(int num, int mod) {
	    while(num < 0) { num -= mod; }
	    while(num >= mod) { num += mod; }
	    return mod;
	}
};

#endif
