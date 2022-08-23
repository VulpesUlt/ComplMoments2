#include <iostream>
#include <utility>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>


using namespace std;

// Task 1 ===========================================

template <typename T>
void Swap(T*& onePtr,T*& twoPtr)
{
	T* tempPtr = twoPtr;
	twoPtr = onePtr;
	onePtr = tempPtr;
}

// Task 2 ===========================================

template <typename T>
void SortPointers (vector<T*>& vect)
{
	sort(vect.begin(), vect.end(), [](T*& onePtr, T*& twoPtr) {return *onePtr < *twoPtr; });
}

template <typename T>
void printVect(vector<T*>& vect)
{
	for (T* iter : vect)
	{
		cout << *iter << " ";
	}
	cout << endl;
}

// Task 3 ===========================================

class Book
{
public:
	Book() { book_m = "Empty"; }
	Book(ifstream& file)
	{
		while (!file.eof())
		{
			book_m.push_back(file.get());
		}
	}

	void print()
	{
		setlocale(LC_ALL, "Russian");
		cout << endl << book_m << endl;
	}

	const int count_if_find()
	{
		string vowels = "àóîûýÿþ¸èåÀÓÎÛÝßÞ¨ÈÅ";
		return count_if(book_m.begin(), book_m.end(),[&vowels](char ch) {return vowels.find(ch) != string::npos;});
	}

	const int count_if_for()
	{
		string vowels = "àóîûýÿþ¸èåÀÓÎÛÝßÞ¨ÈÅ";
		return count_if(book_m.begin(), book_m.end(),[&vowels](char ch)
			{
				for (auto it : vowels)
				{
					if (it == ch)
						return true;
				}
				return false;
			});
	}

	const int count_for_find()
	{
		string vowels = "àóîûýÿþ¸èåÀÓÎÛÝßÞ¨ÈÅ";
		int result(0);
		for (auto it : book_m)
		{
			if (vowels.find(it) != string::npos)
				result++;
		}
		return result;
	}

	const int count_for_for()
	{
		string vowels = "àóîûýÿþ¸èåÀÓÎÛÝßÞ¨ÈÅ";
		int result(0);
		for (auto itBook : book_m)
		{
			for (auto itVow : vowels)
			{
				if (itBook == itVow)
					result++;
			}
		}
		return result;
	}


private:
	string book_m;
};

int main()
{
	// Task 1 ===========================================

	int a = 5;
	int b = 10;
	int* aPtr = &a;
	int* bPtr = &b;
	
	cout << "Task 1" << endl;
	cout << "Before swap: " << "a = " << setw(3) << *aPtr << " | b = " << *bPtr << endl;
	Swap(aPtr, bPtr);
	cout << "After swap:  " << "a = " << setw(3) << *aPtr << " | b = " << *bPtr << endl;

	// Task 2 ===========================================
	cout << endl << "Task 2" << endl;

	const int VECTSIZE = 10;
	vector<int*> vect;
	for (int i = 0; i < VECTSIZE; i++)
	{
		vect.push_back(new int);
		*vect[i] = rand();
	}
	cout << "Before sort: ";
	printVect(vect);
	SortPointers(vect);
	cout << "After sort: ";
	printVect(vect);

	// Task 3 ===========================================
	cout << endl << "Task 3" << endl;

	setlocale(LC_ALL, "Russian");
	ifstream file("voyna-i-mir-tom-1.txt");

	if (file.is_open()) { cout << "File was opened " << endl; }
	else { return 1; }

	Book book(file);
	//book.print();

	auto start = chrono::steady_clock::now();
	book.count_if_find();
	auto stop = chrono::steady_clock::now();
	chrono::duration<double> seconds = stop - start;
	cout << "count_if + find duration: " << seconds.count() << endl;
	
	start = chrono::steady_clock::now();
	book.count_if_for();
	stop = chrono::steady_clock::now();
	seconds = stop - start;
	cout << "count_if + for duration: " << seconds.count() << endl;
	
	start = chrono::steady_clock::now();
	book.count_for_find();
	stop = chrono::steady_clock::now();
	seconds = stop - start;
	cout << "for + find duration: " << seconds.count() << endl;

	start = chrono::steady_clock::now();
	book.count_for_for();
	stop = chrono::steady_clock::now();
	seconds = stop - start;
	cout << "for + for: " << seconds.count() << endl;

	return 0;
}