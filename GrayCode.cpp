#include "Additional.h"
#include <algorithm>
#include <random>

// Gray code main function
multiset grayCode(int n) {
    srand(time(NULL));
    multiset ans(1 << n); // (1 << n) = 2**n

    for (int i = 0; i < (1 << n); i++) {
        ans[i] = make_pair(DecToBin(i ^ (i >> 1), n), (rand() % 20) + 1);
        /*
        * (i >> 1) = i / 2 - ����������, ����� ��� ���������� �������������
        * (rand() % 20) + 1 - ��������� ������� ����� ��������� �������
        �������� � �������� �� 1 �� 20
        */
    }

    std::sort(ans.begin(), ans.end());
    return ans;
}