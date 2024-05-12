#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#ifndef operators
#define operators
using namespace std;


bool operator == (const tm & x, const tm & y);
bool operator < (const tm & x, const tm & y);
ostream & operator << (ostream & os, const tm & x);

bool operator >= (const tm & x, const tm & y);
bool operator <= (const tm & x, const tm & y);

#endif



