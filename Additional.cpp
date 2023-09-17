#include "Additional.h"
#include <iostream>
#include <random>

// Integer element of vector to its binary notation
string DecToBin(int elem, int n)
{
	string bin;
	while (elem > 0) {
		bin = to_string(elem % 2) + bin;
		elem = elem / 2;
	}

	while (bin.length() < n) {
		bin = "0" + bin;
	}

	return bin;
}

void print(const multiset& arr)
{
	cout << "Multiset contains next items: ";
	for (int i = 0; i < arr.size(); i++) {
		cout << "(" << arr[i].first << ";" << arr[i].second << "), ";
	}
	cout << endl << endl;
}


int contains(const multiset& MSET, pair<string, int> elem) {
	// Считаем, что элемента в множестве нет
	// P.S. под элементов понимается не целая пара значение-кратность, а только значение
	int ind = -1;
	// Ищем elem среди элементов MSET
	for (int i = 0; i < MSET.size(); i++) {
		if (MSET[i].first == elem.first) {
			ind = i; // Если нашли, то запоминаем индекс
			break;
		}
	}
	return ind;
}

// Автоматическое заполнение мультимножества
multiset afillMSET(const multiset& U, int power) {
	srand(rand());
	multiset MSET;

	// Пока не заполним мультимножество на заданное кол-во элементов
	while (MSET.size() < power) {
		// Берём случайный элемент из Universal
		pair<string, int> elem = U[rand() % U.size()]; 
		
		// Если MSET не содержит elem
		if (contains(MSET, elem) == -1) { 
			// Добавляем этот элемент, выбирая случайно кратность
			MSET.push_back(make_pair(elem.first, rand() % elem.second));
		}
	}
	return MSET;
}

// Ручное заполнение мультимножества
multiset mfillMSET(const multiset& U, int power) {
	multiset MSET;
	
	for (int i = 0; i < power;) {
		int mult;
		string val;

		cout << endl << "Enter the value of the Multiset element and its multiplicity (value must be one of the elements in Universal set; multiplicity must be a non-negative integer): ";
		cin >> val >> mult;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a valid integer for multiplicity." << endl;
			continue;
		}

		bool found = false;
		for (const auto& element : U) {
			if (element.first == val && mult >= 0) {
				found = true;
				break;
			}
		}

		if (!found) {
			cout << "Invalid input. ";
			if (mult < 0) {
				cout << "Multiplicity must be a non-negative integer. ";
			}
			cout << "Please enter a valid value from Universal set and non-negative integer for multiplicity." << endl;
			continue;
		}

		found = false;
		for (const auto& element : MSET) {
			if (element.first == val) {
				found = true;
				break;
			}
		}

		if (found) {
			cout << "The element is already in the multiset. Please try again." << endl;
			continue;
		}

		MSET.push_back(make_pair(val, mult));
		// Увеличиваем счетчик только при успешном добавлении элемента
		i++; 
	}

	return MSET;
}

multiset Union(const multiset& A, const multiset& B) {
	multiset ans = A;

	for (int i = 0; i < B.size(); i++) {
		int ind = contains(ans, B[i]); // Индекс элемента B[i] в векторе ans
		if (ind == -1) { // Если элемента нет в ans
			ans.push_back(B[i]); // Добавляем его
		}
		else { // Если элемент есть в ans
			// Берём максимальную кратность
			if (ans[ind].second < B[i].second) {
				ans[ind].second = B[i].second; 
			}
		}
	}
	return ans;
}

multiset Intersection(const multiset& A, const multiset& B) {
	multiset ans;

	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < B.size(); j++) {
			if (A[i].first == B[j].first) {
				int min_mult = A[i].second;
				if (B[j].second < min_mult) {
					min_mult = B[j].second;
				}
				ans.push_back(make_pair(A[i].first, min_mult));
			}
		}
	}
	return ans;
}

// Операция "Дополнение"
multiset Complement(const multiset& A, const multiset& U) {
	multiset ans;
	for (int i = 0; i < A.size(); i++) {
		int ind = contains(U, A[i]);
		ans.push_back(make_pair(A[i].first, U[ind].second - A[i].second));
	}
	
	return ans;
}

// Операция "Арифметическая сумма"
multiset AlgSum(const multiset& A, const multiset& B, const multiset& U) {
	multiset ans;
	
	// Добавляем элементы из мультимножества A
	for (int i = 0; i < A.size(); i++) {
		int indB = contains(B, A[i]);
		int indU = contains(U, A[i]);
		// Если элемент есть в мультимножестве B
		if (indB != -1) { 
			if ((A[i].second + B[indB].second) < U[indU].second) {
				ans.push_back(make_pair(A[i].first, A[i].second + \
					B[indB].second));
			}
			else {
				ans.push_back(make_pair(A[i].first, U[indU].second));
			}
		}
		// Если элемента нет в мультимножестве B
		else {
			ans.push_back(A[i]);
		}
	}

	// Добавляем элементы из мультимножества B
	for (int i = 0; i < B.size(); i++) {
		int indA = contains(A, B[i]);
		// Если элемента нет в мультимножестве A
		if (indA == -1) {
			ans.push_back(B[i]);
		}
	}
	return ans;
}

// Операция "Арифметическая разность"
multiset AlgDif(const multiset& A, const multiset& B) {
	multiset ans;

	// Добавляем элементы из мультимножества A
	for (int i = 0; i < A.size(); i++) {
		int indB = contains(B, A[i]);
		// Если элемент есть в мультимножестве B
		if (indB != -1) {
			if ((A[i].second - B[indB].second) > 0) {
				ans.push_back(make_pair(A[i].first, A[i].second - \
					B[indB].second));
			}
			else {
				ans.push_back(make_pair(A[i].first, 0));
			}
		}
		// Если элемента нет в мультимножестве B
		else {
			ans.push_back(A[i]);
		}
	}
	// Добавляем элементы из мультимножества B
	for (int i = 0; i < B.size(); i++) {
		int indA = contains(A, B[i]);
		// Если элемента нет в мультимножестве A
		if (indA == -1) {
			ans.push_back(make_pair(B[i].first, 0));
		}
	}
	return ans;
}

multiset Diff(const multiset& A, const multiset& B, const multiset& U) {
	return Intersection(A, Complement(B, U));
}

multiset SymDiff(const multiset& A,const multiset& B, const multiset& U) {
	return Diff(Union(A,B), Intersection(A, B), U);
}
