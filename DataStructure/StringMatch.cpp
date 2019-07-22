#include "StringMatch.h"

// d is the number of character in the input alphabet
#define d 256

void RK_Search(char pat[], char txt[], int q)
{
	int M = strlen(pat);
	int N = strlen(txt);
	int i, j;
	int	p = 0; // hash value for pattern
	int t = 0; // hash value for text
	int h = 1;

	// The value of h should be "pow(d, M-1)%q", pow: the power of exponent
	for (i = 0; i < M - 1; i++)
		h = (h * d) % q;

	// calculate the hash value of pattern and first window of text
	for (i = 0; i < M; i++)
	{
		p = (d * p + pat[i]) % q;
		t = (d * t + txt[i]) % q;
	}

	// slide the pattern over text one by one
	for (i = 0; i <= N - M; i++)
	{
		// check the value of current window of text and pattern
		// if the hash values match then only check foe characters one by one
		if (p == t)
		{
			// check for characters one by one
			for (j = 0; j < M && txt[i + j] == pat[j]; j++)
				;

			// if p == t and pat[0...M-1] = txt[i...i+M-1] 
			if (j == M)
				cout << "Pattern found at index:" << i << endl;
		}

		// calculate hash value for next window of text
		// Remove leading digit add trailing digit
		if (i < N - M)
		{
			t = (d*(t - txt[i] * h) + txt[i + M]) % q;
			// we might get negative value of t, converting it to positive
			if (t < 0)
				t += q;
		}
	}
}

void StringMatchTest()
{
	char txt[] = "GEEKS FOR GEEKS";
	char pat[] = "GEEK";
	int q = 101;
	RK_Search(pat, txt, q);
}
