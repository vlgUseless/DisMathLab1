#include <iostream>
#include <random>
#include <math.h>
#include "Additional.h"


int main()
{
    while (true) {
        multiset A, B;
        int n;
        
        while (1)
        {
            int mx_sz = log2(A.max_size());
            cout << "Enter the bit depth of the Universal set (it must be a positive integer number between 0 and " << mx_sz << "): ";
            cin >> n;
            if (cin.fail()) //returns true when input fails
            {
                cin.clear(); //use to clear error state of buffer

                //ignores rest of the line
                //after first error occurs

                //skips to the next line
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input." << endl;
                continue;

            }

            if (n < 0) {
                cout << "Invalid input. The bit depth must be a positive value." << endl;
                continue;
            }

            if (n > mx_sz) {
                cout << "Your device is only allow you to create 2^" << mx_sz << " elements. Please, try a smaller number." << endl;
                continue;
            }
            if (!cin.fail() and n >= 0 and n <= mx_sz)
                break;
        }
        cout << "Universal set: ";
        if (n == 0) {
            cout << "empty." << endl;

            cout << endl << "Multiset A: empty." << endl;
            cout << "Multiset B: empty." << endl;

            cout << endl << "Union: empty." << endl;

            cout << "Intersection: empty." << endl;

            cout << "Complement A: empty." << endl;
            cout << "Complement B: empty." << endl;

            cout << "AlgSum (A + B): empty." << endl;

            cout << "AlgDif (A - B): empty." << endl;
            cout << "AlgDif (B - A): empty." << endl;
           

            cout << "Diff (A \\ B): empty." << endl;
  
            cout << "Diff (B \\ A): empty." << endl;


            cout << "SymDiff: empty." << endl;


            continue;
        }
        int sz = 1 << n;
        multiset Uni(sz);
        Uni = grayCode(n);
        cout << endl;
        print(Uni);


        cout << "Enter the powers of the Multisets (it must be a positive integer numbers less than or equal " << sz << "): ";
        int a_pow = 0, b_pow = 0;
        cin >> a_pow >> b_pow;
        while (1)
        {
            if (cin.fail()) //returns true when input fails
            {
                cin.clear(); //use to clear error state of buffer

                //ignores rest of the line
                //after first error occurs

                //skips to the next line
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter the valid input: ";
                cin >> a_pow >> b_pow;
            }
     

            if (a_pow > sz or b_pow > sz or a_pow < 0 or b_pow < 0) {
                if (a_pow > sz or b_pow > sz) {
                    cout << "Both powers should be less than or equal " << sz << endl;
                }
                if (a_pow < 0 or b_pow < 0) {
                    cout << "Both powers should be a positive integers" << endl;
                }
                cout << "Please enter the valid input: ";
                cin >> a_pow >> b_pow;
            }

            if (!cin.fail() and (a_pow >= 0 and a_pow <= sz) and (b_pow >= 0 and b_pow <= sz))
                break;
        }
    

        cout << "Select the method for forming multisets (1 - manually, 2 - automatically): ";
        int method;
        cin >> method;
        while (1)
        {
            if (cin.fail() or (method != 1 and method != 2)) //returns true when input fails
            {
                cin.clear(); //use to clear error state of buffer

                //ignores rest of the line
                //after first error occurs

                //skips to the next line
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter the valid input: ";
                cin >> method;
            }

            if (!cin.fail() and (method == 1 or method == 2))
                break;
        }

        switch (method)
        {
        case 1: {
            cout << endl << "----------Manually filling multiset A----------" << endl;
            A = mfillMSET(Uni, a_pow);
            cout << endl << "----------Manually filling multiset B----------" << endl;
            B = mfillMSET(Uni, b_pow);
            break; }
        case 2: A = afillMSET(Uni, a_pow); B = afillMSET(Uni, b_pow); break;
        }
        cout << endl << "Multiset A:" << endl;
        print(A);
        cout << "Multiset B:" << endl;
        print(B);

        cout << endl << "Union:" << endl;
        print(Union(A, B)); // Объединение

        cout << "Intersection:" << endl;
        print(Intersection(A, B)); // Пересечение

        cout <<  "Complement A:" << endl;
        print(Complement(A, Uni)); // Дополнение множества A
        cout << "Complement B:" << endl;
        print(Complement(B, Uni)); // Дополнение множества B

        cout << "AlgSum (A + B):" << endl;
        print(AlgSum(A, B, Uni)); // Арифметическая сумма

        cout <<  "AlgDif (A - B):" << endl;
        print(AlgDif(A, B)); // Арифметическая разность A - B
        cout <<  "AlgDif (B - A):" << endl;
        print(AlgDif(B, A)); // Арифметическая разность B - A

        cout <<  "Diff (A \\ B):" << endl;
        print(Diff(A, B, Uni)); // Разность A \ B
        cout <<  "Diff (B \\ A):" << endl;
        print(Diff(B, A, Uni)); // Разность B \ A

        cout << "SymDiff:" << endl;
        print(SymDiff(A, B, Uni)); // Симметрическая разность
    }
}
