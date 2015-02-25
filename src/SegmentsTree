// Задача: реализовать дерево отрезков. В первой строке входа даны два числа n и m (1≤n,m≤105), во второй 
//  строке — n целых чисел, задающих начальные значения массива. Далее даны m строк вида Set I X, где I — номер
// позиции, а X — новое значение, или Min L R, где L и R — левая и правая границы отрезка. Для каждой операции Min
// программа должна вывести минимальное значение на отрезке от L до R. Позиции нумеруются от единицы до n, все
// значения — натуральные числа, не превышающие 109.

// Sample Input:
// 5 7
// 1 2 3 4 5
// Min 1 5
// Set 1 8
// Min 1 5
// Min 1 1
// Min 1 3
// Set 3 1
// Min 2 4
// Sample Output:
// 1
// 2
// 8
// 2
// 1
// Memory Limit: 256 MB
// Time Limit: 5 seconds

#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

const unsigned INFINITY = 1e9 + 1;

class segment_tree
{
	struct node
	{
		unsigned value;
		size_t left;
		size_t right;
		node(unsigned v = INFINITY, size_t l = 0, size_t r = 0)
			: value(v)
			, left(l)
			, right(r)
		{

		}
	};

	vector<node> tree;

	void make()
	{
		for (size_t i = tree.size()/2 - 1; i < tree.size()/2; --i)
		{
			tree[i].value = min(tree[i * 2 + 1].value, tree[i * 2 + 2].value);
			tree[i].left = tree[i * 2 + 1].left;
			tree[i].right = tree[i * 2 + 2].right;
		}
	}

	size_t get_bit_degree(size_t size) const
	{
		size_t degree = 0;
		while (size != 0 )
		{
			size >>= 1;
			++degree;
		} 
		return degree;
	}

	size_t get_parent(size_t child)
	{	
		return (child - 1)/2;
	}

	unsigned min_under_node(size_t ind_node, size_t l, size_t r)
	{
		if (l == tree[ind_node].left && r == tree[ind_node].right)
		{
			return tree[ind_node].value;
		}
		size_t mid = (tree[ind_node].left + tree[ind_node].right)/2;
		if (r <= mid)
		{
			return min_under_node(ind_node * 2 + 1, l, r);
		}
		else if (l > mid)
		{
			return min_under_node(ind_node * 2 + 2, l, r);
		}
		else
		{
			return min(min_under_node(ind_node * 2 + 1, l, mid),
			           min_under_node(ind_node * 2 + 2, mid + 1, r));
		}
	}

public:
	segment_tree(vector<unsigned> const & v)
	{
		size_t bit_gegree = 1 << get_bit_degree(v.size());
		size_t size_tree = 2 * bit_gegree - 1;
		tree.assign(size_tree, node());
		size_t i = 0;
		while(i < v.size())
		{
			tree[bit_gegree - 1 + i] = node(v[i], i, i);
			++i;
		}
		while(i <= size_tree/2)
		{
			tree[bit_gegree - 1 + i] = node(0, i, i);
			++i;
		}
		make();
	}

	unsigned get_min(size_t l, size_t r)
	{
		return min_under_node(0, l, r);
	}

	void set(size_t index, unsigned value)
	{
	
		size_t index_now = index + tree.size()/2;
		tree[index_now].value = value;
		size_t parent = get_parent(index_now);
		while (parent != 0)
		{
			size_t sib = index_now & 1 ? index_now + 1 : index_now - 1;
			if (tree[index_now].value < tree[sib].value)
			{
				tree[parent].value = tree[index_now].value;	
			}
			else if (tree[parent].value != tree[sib].value)
			{
				tree[parent].value = tree[sib].value;
			}
			else 
			{
				return;
			}
			index_now = parent;
			parent = get_parent(index_now);
		}
		tree[0].value = min(tree[1].value, tree[2].value);
	}

	// void print()
	// {
	// 	for (size_t i = 0; i < tree.size(); ++i)
	// 	{	
	// 		size_t degree = get_bit_degree(i);
	// 		size_t now = 1 << degree;
	// 		if (i + 1 == now)
	// 		{
	// 			cout << endl;
	// 		}
	// 		cout << ((tree[i].value == INFINITY) ? 0 : tree[i].value) <<
	// 		 "(" << tree[i].left << ':' << tree[i].right << ")   ";
	// 	}
	// 	cout << "\n-------------------\n";
	// }
};


int main()
{
	size_t n, m;
	cin	>> n >> m;

	vector<unsigned> v;

	for (size_t i = 0; i < n; ++i)
	{	
		unsigned x;
		cin >> x;
		v.push_back(x);
	}

	segment_tree t(v);
	
	for (size_t i = 0; i < m; ++i)
	{
		string s;
		cin >> s;
		size_t l, r;
		unsigned val;
		if (s == "Min")
		{
			// t.print();
			cin >> l >> r;
			cout << t.get_min(l - 1, r - 1) << endl;
		}
		else
		{	
			cin >> l >> val;
			t.set(l - 1, val);
			// t.print();
		}
	}
}
