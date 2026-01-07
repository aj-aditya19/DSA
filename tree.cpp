#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <map>

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
map<int, vector<int>> top_view_map;
vector<int> top;

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

bool isIdentical(TreeNode *root1, TreeNode *root2)
{
    if (root1 == NULL || root2 == NULL)
    {
        return root1 == root2;
    }
    bool isLeft = isIdentical(root1->left, root2->left);
    bool isRight = isIdentical(root1->right, root2->right);

    return isLeft && isRight && root1->data == root2->data;
}

bool isSubTree(TreeNode *root1, TreeNode *root2)
{
    if (root1 == NULL || root2 == NULL)
    {
        return root1 == root2;
    }
    if (root1->data == root2->data && isIdentical(root1, root2))
    {
        return true;
    }
    return isSubTree(root1->left, root2) || isSubTree(root1->right, root2);
}

int Diameter(TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int left_d = Diameter(root->left);
    int right_d = Diameter(root->right);
    int curr_d = height(root->left) + height(root->right) + 1;
    return max(curr_d, max(left_d, right_d));
}

void top_view(TreeNode *root, int level)
{
    if (!root)
    {
        return;
    }
    top_view_map[level].push_back(root->data);
    top_view(root->left, level - 1);
    top_view(root->right, level + 1);
}
void print_top_view()
{
    for (auto it = top_view_map.begin(); it != top_view_map.end(); ++it)
    {
        cout << "" << it->first << ": ";
        for (int i = 0; i < it->second.size(); i++)
        {
            cout << it->second[i] << " ";
            if (i == 0)
            {
                top.push_back(it->second[i]);
            }
        }
        cout << endl;
    }
    cout << "Top View: ";
    for (int i = 0; i < top.size(); i++)
    {
        cout << top[i] << " ";
    }
    cout << endl;
}

void kth_level(TreeNode *root, int k)
{
    if (root == NULL)
    {
        return;
    }
    if (k == 1)
    {
        cout << root->data << " ";
    }
    kth_level(root->left, k - 1);
    kth_level(root->right, k - 1);
}

TreeNode *lowest_common_ancestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data == p->data || root->data == q->data)
    {
        return root;
    }
    TreeNode *leftLCA = lowest_common_ancestor(root->left, p, q);
    TreeNode *rightLCA = lowest_common_ancestor(root->left, p, q);

    if (leftLCA && rightLCA)
    {
        return root;
    }
    else if (leftLCA != NULL)
    {
        return leftLCA;
    }
    else
    {
        return rightLCA;
    }
}

TreeNode *postorderhelper(vector<int> pre, vector<int> in, int &preindex, int start, int end)
{
    if (start > end)
    {
        return NULL;
    }
    TreeNode *root = new TreeNode(pre[preindex++]);
    int index = 0;
    for (int i = start; i <= end; i++)
    {
        if (in[i] == root->data)
        {
            index = i;
            break;
        }
    }
    root->left = postorderhelper(pre, in, preindex, start, index - 1);
    root->right = postorderhelper(pre, in, preindex, index + 1, end);
    return root;
}
TreeNode *postorder(vector<int> pre, vector<int> in)
{
    int preindex = 0;
    return postorderhelper(pre, in, preindex, 0, in.size() - 1);
}

void functions_tree(TreeNode *root, TreeNode *root1)
{
    cout << "Height of Tree: " << height(root) << endl;
    for (auto it = sum_at_each_level.begin(); it != sum_at_each_level.end(); ++it)
    {
        cout << "Sum at level " << it->first << ": " << it->second << endl;
    }
    dfs(root, 1);

    cout << "Is Identical: " << isIdentical(root, root1) << endl; // 100-Identical-E

    cout << "Is SubTree: " << isSubTree(root, root1) << endl; // 573-Sum-E

    cout << "Diameter of Binary Tree: " << Diameter(root) << endl;

    top_view(root, 0);
    print_top_view();

    cout << "Kth-level: ";
    kth_level(root, 3);
    cout << endl;

    cout << "Lowest Common Ancestor: ";
    cout << lowest_common_ancestor(root, root, root); // 236-M

    vector<int> preorder = {1, 2, 5, 4, 3, 7, 6, 9, 8};
    vector<int> inorder = {1, 2, 5, 4, 3, 7, 6, 9, 8};
    TreeNode *post_tree = postorder(preorder, inorder);
    printTree(post_tree);
}

//--------------------------------Main-----------------------
int main()
{
    vector<int> vec = {1, 2, -1, 3, 4, 5, -1, -1, -1, -1, 6, 7, -1, -1, 8, 9, -1, -1, -1};
    vector<int> vec1 = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};
    idx = 0;
    TreeNode *root = buildTree(vec);
    TreeNode *root1 = buildTree(vec1);
    printTree(root);
    functions_tree(root, root1);
}