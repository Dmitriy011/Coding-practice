#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

//* n - количество вершин

// min, max — допустимый диапазон значений для текущего поддерева: [min; max)
void Convert_preorderToPostorder(std::vector<int>& preorder, int min, int max, size_t& curr_i)
{
    if (curr_i == preorder.size())
        return;
    
    if (preorder[curr_i] < min)
        return;
   
    if (preorder[curr_i] >= max)
        return;

    int tmp_root = preorder[curr_i];
    ++curr_i;

    Convert_preorderToPostorder(preorder, min, tmp_root, curr_i);
    Convert_preorderToPostorder(preorder, tmp_root, max, curr_i);

    std::cout << tmp_root << " ";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

// ========= 1. Считывание задачи ========= //
    size_t n;

    std::cin >> n;
    if (n == 0)
        return 0;

    std::vector<int> keys_arr(n);

    // Preorder обход (корень → левое поддерево → правое).
    for (size_t i = 0; i < n; ++i)
        std::cin >> keys_arr[i];

// ========= 2. Решение задачи + Вывод ответа postorder (левое → правое → корень) ========= //
    size_t tmp_index = 0;
    Convert_preorderToPostorder(keys_arr, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), tmp_index);

    std::sort(keys_arr.begin(), keys_arr.end());

// ========= 3. Вывод ответа inorder (левое → корень → правое). ========= //
    // inorder = отсортированный порядок ключей.
    std::cout << '\n';
    for (size_t i = 0; i < n; ++i)
        std::cout << keys_arr[i] << " ";
    std::cout << "\n";

    return 0;
}
