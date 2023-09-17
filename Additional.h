#pragma once
#include <vector>
#include <string>
using namespace std;
typedef vector<pair<string, int>> multiset;

multiset grayCode(int n);

string DecToBin(int elem, int n);

multiset afillMSET(const multiset& U, int power);
multiset mfillMSET(const multiset& U, int power);

int contains(const multiset& MSET, pair<string, int> elem);

void print(const multiset& arr);


multiset Union(const multiset& A, const multiset& B);
multiset Intersection(const multiset& A, const multiset& B);
multiset Complement(const multiset& A, const multiset& U);
multiset AlgSum(const multiset& A, const multiset& B, const multiset& U);
multiset AlgDif(const multiset& A, const multiset& B);
multiset Diff(const multiset& A, const multiset& B, const multiset& U);
multiset SymDiff(const multiset& A, const multiset& B, const multiset& U);