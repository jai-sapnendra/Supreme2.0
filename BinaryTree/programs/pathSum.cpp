#include<iostream>
#include<vector>
using namespace std;

class TreeNode{
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

bool solve(TreeNode* root, int targetSum, int sum) {
    // base case
    if(root == NULL) return false;

    sum += root->data;
    if(root->left == NULL && root->right == NULL) {
        // I am standing at leaf node
        // verify answer
        if(sum == targetSum) return true;
        else return false;
    }

    bool leftAns = solve(root->left, targetSum, sum);
    bool rightAns = solve(root->right, targetSum, sum);

    return leftAns || rightAns;
}

bool hasPathSum(TreeNode* root, int targetSum) {
    int sum = 0;
    bool ans = solve(root, targetSum, sum);
    return ans;
}

int main() {

    return 0;
}