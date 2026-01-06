#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <unordered_map>

using namespace std;

//---------------------------Values--------------------------------
class TreeNode
{
public:
    int data;
    TreeNode *left, *right;

    TreeNode(int val)
    {
        data = val;
        left = right = NULL;
    }
};

int idx = 0;
unordered_map<int, int> sum_at_each_level;
unordered_map<int, vector<int>> value_at_level;
unordered_map<int, long long> sum;

//----------------------------------------------------------------------

//----------------------------Creating Tree---------------------
TreeNode *buildTreeHelper(vector<int> &vec)
{
    if (idx >= vec.size() || vec[idx] == -1)
    {
        idx++;
        return NULL;
    }
    TreeNode *root = new TreeNode(vec[idx]);
    idx++;
    root->left = buildTreeHelper(vec);
    root->right = buildTreeHelper(vec);

    return root;
}
TreeNode *buildTree(vector<int> vec)
{
    return buildTreeHelper(vec);
}
//----------------------------------------------------------

//------------------------------Printing TreeNode--------
void printInorder(TreeNode *root)
{
    if (!root)
    {
        return;
    }
    printInorder(root->left);
    cout << root->data << " ";
    printInorder(root->right);
}
void printPostorder(TreeNode *root)
{
    if (!root)
    {
        return;
    }
    printInorder(root->left);
    printInorder(root->right);
    cout << root->data << " ";
}
void printPreorder(TreeNode *root)
{
    if (!root)
    {
        return;
    }
    cout << root->data << " ";
    printInorder(root->left);
    printInorder(root->right);
}
void printTree(TreeNode *root)
{

    cout << "Pre-order: ";
    printPreorder(root);
    cout << endl;
    cout << "Inorder: ";
    printInorder(root);
    cout << endl;
    cout << "Post-order: ";
    printPostorder(root);
    cout << endl;
}

//----------------------------Functions-------------------------------
int height(TreeNode *root)
{
    if (!root)
    {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    int height = max(leftHeight, rightHeight) + 1;
    sum_at_each_level[height] += root->data;
    return height;
}

void dfs(TreeNode *root, int level)
{
    if (!root)
    {
        return;
    }
    sum[level] += root->data;
    dfs(root->left, level + 1);
    dfs(root->right, level + 1);
}

void functions_tree(TreeNode *root)
{
    cout << "Height of Tree: " << height(root) << endl;
    for (auto it = sum_at_each_level.begin(); it != sum_at_each_level.end(); ++it)
    {
        cout << "Sum at level " << it->first << ": " << it->second << endl;
    }
    dfs(root, 1);
}

//--------------------------------Main-----------------------
int main()
{
    vector<int> vec = {1, 2, -1, 3, 4, 5, -1, -1, -1, -1, 6, 7, -1, -1, 8, 9, -1, -1, -1};
    idx = 0;
    TreeNode *root = buildTree(vec);
    printTree(root);
    functions_tree(root);
}