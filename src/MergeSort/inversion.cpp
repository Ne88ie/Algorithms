// Первая строка ввода содержит число n (1≤n≤105), вторая — массив A[1…n], содержащий натуральные числа, не
// превосходящих 109. Необходимо посчитать число пар индексов 1≤i<j≤n, для которых A[i]>A[j]. (Такая пара элементов
// называются инверсией массива. Количество инверсий в массиве является в некотором смысле его мерой
// неупорядоченности: например, в упорядоченном по неубыванию массиве инверсий нет вообще, а массиве, упорядоченном
// по убыванию, инверсию образуют каждые два элемента.)

// Sample Input:
// 5
// 2 3 9 2 9
// Sample Output:
// 2

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<unsigned> v;
long long count_inversion = 0;

void merge(size_t const beg, size_t const end)
{	
	vector<unsigned> buffer;
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
			
			v[i] = buffer[p];
			count_inversion += r/2 - l;
			++p; 	
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
		unsigned x;
		cin >> x;
		v.push_back(x);
	}  

	merge_sort(0, n);

	cout << count_inversion << endl;
	return 0;
}
