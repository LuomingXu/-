#include <iostream>
#include <codecvt>
using namespace std;
typedef  int type;

//二分查找
int binary_serach(int* array, const int key)
{
	int high = 20;
	int low = 1;
	int mid = 0;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key == array[mid])
			return mid;
		if (key < array[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}

	return -1;
}

typedef struct bi_tree_node
{
	type data;
	struct bi_tree_node *lchild, *rchild;
}bi_tree_node, *bi_tree;

void create_bi_tree(bi_tree *T)
{
	type ch;
	std::cin >> ch;
	if (ch == 0)
		*T = nullptr;
	else
	{
		*T = bi_tree(malloc(sizeof(bi_tree_node)));//C++的函数转化风格??
		
		(*T)->data = ch;
		create_bi_tree(&(*T)->lchild);
		create_bi_tree(&(*T)->rchild);
	}
}

bi_tree search_in_bi_tree(const bi_tree T, const type target, int* position, int* count)
{
	if (T == nullptr)
		return nullptr;
	(*count)++;
	if (T->data == target)
		return T;
	(*position)++;//也不知道为什么, 随便一试, 发现在此处++就是前序的位置...
	auto left = search_in_bi_tree(T->lchild, target, position, count);
	(*count)++;
	if (left != nullptr && left->data == target)
		return left;
	auto right = search_in_bi_tree(T->rchild, target, position, count);
	(*count)++;
	if (right != nullptr && right->data == target)
		return right;

	return nullptr;
}

bi_tree search_in_bi_tree(const bi_tree T, const type target)
{
	if (T == nullptr)
		return nullptr;
	if (T->data == target)
		return T;
	auto left = search_in_bi_tree(T->lchild, target);
	if (left != nullptr && left->data == target)
		return left;
	auto right = search_in_bi_tree(T->rchild, target);
	if (right != nullptr && right->data == target)
		return right;

	return nullptr;
}
//
//bi_tree left_search_in_bi_tree(const bi_tree T, const type target)
//{
//	if (T == nullptr)
//		return nullptr;
//	if (T->data < target)
//		return T;
//	auto left = left_search_in_bi_tree(T->lchild, target);
//	if (left != nullptr && left->data < target)
//		return left;
//	auto right = left_search_in_bi_tree(T->rchild, target);
//	if (right != nullptr && right->data < target)
//		return right;
//
//	return nullptr;
//}
//bi_tree right_search_in_bi_tree(const bi_tree T, const type target)
//{
//	if (T == nullptr)
//		return nullptr;
//	if (T->data > target)
//		return T;
//	auto left = right_search_in_bi_tree(T->lchild, target);
//	if (left != nullptr && left->data > target)
//		return left;
//	auto right = right_search_in_bi_tree(T->rchild, target);
//	if (right != nullptr && right->data > target)
//		return right;
//
//	return nullptr;
//}

//bool search_in_bi_tree(const bi_tree t, const type key, bi_tree f, bi_tree &p)
//{
//	if (t == nullptr)
//	{
//		p = f; return false;
//	}
//	if (t->data== key)
//	{
//		p = t; return true;
//	}
//	if (key < t->data)
//		return search_in_bi_tree(t->lchild, key, t, p);
//	else
//		return search_in_bi_tree(t->rchild, key, t, p);
//}
//bool insert_in_bi_tree(bi_tree &t,type e)
//{
//	if (!search_in_bi_tree(t,e,nullptr,p))
//	{
//		
//	}
//}
void pre_order_traverse(const bi_tree T)
{
	if (T == nullptr)
		return;
	std::cout << T->data << " ";
	pre_order_traverse(T->lchild);
	pre_order_traverse(T->rchild);
}
void in_order_traverse(const bi_tree T)
{
	if (T == nullptr)
		return;
	in_order_traverse(T->lchild);
	std::cout << T->data << " ";
	in_order_traverse(T->rchild);
}

void bi_tree_array(const bi_tree T, type* array, int* i)
{
	if (T == nullptr)
		return;
	bi_tree_array(T->lchild, array, i);
	array[(*i)++] = T->data;
	bi_tree_array(T->rchild, array, i);
}

int main(int argc, char* argv[])
{
	//二分法查找
	int order_table[20] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
	int key = 0;
	std::cout << "Please input the key which you want to search :";
	std::cin >> key;
	std::cout << binary_serach(order_table, key) << endl;

	//构建二叉排序树
	bi_tree tree = nullptr;
	std::cout << "请以前序遍历的方式输入二叉树 :" << endl;
	create_bi_tree(&tree);
	std::cout << "前序遍历：" << endl; pre_order_traverse(tree); std::cout << endl;
	std::cout << "中序遍历: " << endl; in_order_traverse(tree); std::cout << endl;
	
	//在二叉排序树中查找
	type temp; bi_tree search = nullptr; int position = 1; int count = 0;//初始位置: 1; 初始比较次数: 0
	std::cout << "请输入所求的: " << endl;
	std::cin >> temp;
	search = search_in_bi_tree(tree, temp, &position,&count);
	if (search != nullptr)
		std::cout << search->data << "  前序遍历第" << position << "个  比较" << count << "次" << endl;
	else
	{
		std::cout << "\"" << temp << "\" is not exist in this bi_tree..." << endl ;
		//在树中插入
		type array[20]; int length = 0;
		bi_tree left = nullptr; bi_tree right = nullptr;
		bi_tree_array(tree, array, &length);

		for (int i = 0; i < length; i++)
			if (temp < array[i])
			{
				left = search_in_bi_tree(tree, array[i - 1]);
				right = search_in_bi_tree(tree, array[i]);
				break;
			}

		const auto the_insert = bi_tree(malloc(sizeof(bi_tree_node)));
		the_insert->data = temp; the_insert->lchild = nullptr; the_insert->rchild = nullptr;

		if (left->rchild == nullptr)
			left->rchild = the_insert;
		else
			right->lchild = the_insert;

		std::cout << "This NUMBER has inserted into this bi_tree" << endl;
		std::cout << "中序遍历: " << endl; in_order_traverse(tree); std::cout << endl;
	}

	std::cout << "Please input any key to exit..." << endl;
	getchar();
	getchar();

	return 0;
}
