// Задача: дано натуральное число 1≤n≤105 и массив целых чисел A[1…n], не превосходящих по модулю 109. Необходимо
// вывести True, если в массиве A есть число, встречающееся строго больше n/2 раз, и False в противном случае.
// Sample Input:
// 5
// 2 3 9 2 2
// Sample Output:
// True
// Memory Limit: 256 MB
// Time Limit: 5 seconds

// Заметка: есть однопроходное решение http://logic.pdmi.ras.ru/csclub/sites/default/files/lection.1.pdf

#include <iostream>
#include <vector>
#include <utility>

using namespace std;
vector<int> v;

void merge(size_t const beg, size_t const end)
{	
	vector<int> buffer;
	for (size_t i = beg; i < end; ++i)
	{
		buffer.push_back(v[i]);
	}
	size_t l = 0;
	size_t r = end - beg;
	size_t p = r/2;
	for (size_t i = beg; i < end; ++i) 
	{
		if (l == r/2)
		{
			while (i < end)
			{
				v[i++] = buffer[p++];
			}
		}
		else if (p == r)
		{
			while (i < end)
			{
				v[i++] = buffer[l++];
			}
		}
		else if (buffer[p] < buffer[l])
		{
			v[i] = buffer[p++];
		}
		else 
		{
			v[i] = buffer[l++];
		}
	}
}

void merge_sort(size_t beg, size_t end)
{
	if (end - beg < 2) return;
	size_t mid = (end - beg) / 2 + beg;
	merge_sort(beg, mid);
	merge_sort(mid, end);
	merge(beg, end);
}

int main()
{	
	size_t n;
	cin >> n;

	for (size_t i = 0; i < n; ++i)
	{	
		int x;
		cin >> x;
		v.push_back(x);
	}  

	merge_sort(0, n);

	size_t m = n/2;
	for (size_t i = 0; i < n - m; ++i)
	{	
		if (v[i] == v[i + m])
		{
			cout << "True\n";
			return 0;
		}
	}
	cout << "False\n";
	return 0;
}
