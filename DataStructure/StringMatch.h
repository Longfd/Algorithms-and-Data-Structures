#pragma once
// String Match algorithm

#include <iostream>

using namespace std;

void StringMatchTest();

// Following program is a C++ implementation of Rabin-Karp Algorithm given in the CLRS book

/*
	pat -> pattern
	txt -> text	
	q	-> A prime number

	Rehashing is done using the following formula:
	hash(txt[s+1...s+m]) = d*(hash(txt[s...s+m-1]) - txt[s]*h) + txt[s+m] % q
	hash(txt[s...s+m-1]): hash value at shift s
	hash(txt[s+1...s+m]): hash value at shift s+1
	txt[s]: the digit of the first character of slide window at shift s
	txt[s+m]: the digit of the last character of slide window at shift s+1
	d: number of characters in the alphabet, this case, d = 256
	h: pow(d, m-1) -> d^(m-1)
	q: A prime number, inorder to avoid the number of hash is too large

	For example pattern length is 3 and string is "23456"
	You compute the value of first window (which is "234") as 234.
	How will you compute value of next window "345"? You will do (234 - 2*100)*10 + 5 and get 345.
*/
void RK_Search(char pat[], char txt[], int q);
