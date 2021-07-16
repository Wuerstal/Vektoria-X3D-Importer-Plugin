/*
Template-Klasse zum speichern zweier unabhängiger Datentypen.
*/

#pragma once

template <class T1, class T2>
class Pair
{
	T1 a;
	T2 b;
public:
	T1 getA() {
		return a;
	}
	T2 getB() {
		return b;
	}

	void setA(T1 x) {
		a = x;
	}

	void setB(T2 x) {
		b = x;
	}

	void setAB(T1 x, T2 y) {
		a = x;
		b = y;
	}
};
