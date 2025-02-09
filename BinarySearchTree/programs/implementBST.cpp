#include <iostream>
#include <queue>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

Node* insertIntoBST(Node *root, int data) {
    if (root == NULL)
    {
        root = new Node(data);
        return root;
    }

    // its not the first node
    if (data > root->data)
    {
        root->right = insertIntoBST(root->right, data);
    }
    else
    {
        root->left = insertIntoBST(root->left, data);
    }

    return root;
}

void createBST(Node* &root)
{
    cout << "Enter Data : ";
    int data;
    cin >> data;

    while (data != -1)
    {
        root = insertIntoBST(root, data);
        cout << "Enter data : ";
        cin >> data;
    }
}

void levelOrderTraversal(Node *root)
{
    queue<Node*> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty())
    {
        Node* temp = q.front();
        q.pop();

        if (temp == NULL)
        {
            cout << endl;
            if (!q.empty())
            {
                q.push(NULL);
            }
        }
        else
        {
            cout << temp->data << " ";
            if (temp->left != NULL)
            {
                q.push(temp->left);
            }
            if (temp->right != NULL)
            {
                q.push(temp->right);
            }
        }
    }
}

// preorder
void preorder(Node* root) {
    if(root == NULL) {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// inorder
void inorder(Node* root) {
    if(root == NULL) {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// postorder
void postorder(Node* root) {
    if(root == NULL) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// min value
Node* findMinValueNode(Node* root) {
    if(root == NULL) {
        return NULL;
    }
    Node* temp = root;

    while(temp->left != NULL) {
        temp = temp->left;
    }

    return temp;
}

// max value
Node* findMaxValueNode(Node* root) {
    if(root == NULL) {
        return NULL;
    }
    Node* temp = root;

    while(temp->right != NULL) {
        temp = temp->right;
    }

    return temp;
}

Node* deleteFromBST(Node* root, int target) {
    // find the target node
    // and delete the target

    if(root == NULL) {
        return  NULL;
    }

    if(target == root->data) {
        // target found delete now
        // 4 cases

        if(root->left == NULL && root->right == NULL) {
            // 1st case -> leaf node
            delete root;
            return NULL;
        }
        else if(root->left != NULL && root->right == NULL) {
            // 2nd case -> left non-NULL and right NULL 
            Node* childSubtree = root->left;
            delete root;
            return childSubtree;
        }
        else if(root->left == NULL && root->right != NULL) {
            // 3rd case -> left NULL and right  non-NULL
            Node* childSubtree = root->right;
            delete root;
            return childSubtree;
        }
        else {
            // 4rth case -> left non-NULL and right non-NULL
            // step1 : bring maximum node from left subtree
            Node* leftMaxi = findMaxValueNode(root->left);
            // step2 : replacement
            root->data = leftMaxi->data;
            // step3 : delete leftMaxi node 
            root->left = deleteFromBST(root->left, leftMaxi->data);
            return root;
        }
    }
    else if(target < root->data) {
        // go to left size of the root
        root->left = deleteFromBST(root->left, target);
    } else {
        // go to right side of the root
        root->right = deleteFromBST(root->right, target);
    }

    return root;
}

// Lakshya Bhaiya Approach
class Solution {
public:
    Node* deleteNode(Node* root, int key) {
        if(!root) return 0;
        if(root->data == key) {
            if(!root->left && !root->right) {
                // case 1: leaf node  
                delete root;
                return 0;
            }
            else if(!root->left) {
                // case 2: root->left = null, root->right != null
                auto temp = root;
                root = root->right;
                delete temp;
                return root;
            }
            else if(!root->right) {
                // case 3: root->left != NULL, root->right = NULL 
                auto temp = root;
                root = root->left;
                delete temp;
                return root;
            }
           else {
#if 0
//                 case 4: root->left == NULL, root->right == NULL 
//                 find minimum of right subtree  
//                 auto rscan = root->right;
//                 while(rscan->left) 
//                     rscan = rscan->left;
//                 rscan->left = root->left;
//                 auto temp = root;
//                 root = root->right;
//                 delete temp;
//                 return root; 
#endif
                // case 4: root->left != NULL, root->right != NULL
                // find maximum element from left subtree
                auto lscan = root->left;
                while(lscan->right)
                    lscan = lscan->right;
                lscan->right = root->right;
                auto temp = root;
                root = root->left;
                delete temp;
                return root;
            }
        }
        if(key < root->data)
            root->left = deleteNode(root->left, key);
        else
            root->right = deleteNode(root->right, key);
        return root;
    }
};

int main()
{
    Node *root = NULL;
    createBST(root);
    
    cout << endl << "Level Order Traversal : "<< endl;
    levelOrderTraversal(root);

    int target;
    cout << "Enter the value of target : ";
    cin >> target;

    while(target != -1) {
        root = deleteFromBST(root, target);
        cout << endl <<"Printing level order traversal"<< endl;
        levelOrderTraversal(root);

        cout << "Enter the value of target : ";
        cin >> target;
    }

    // Node* minNode = findMinValueNode(root);
    // if(minNode == NULL) {
    //     cout << "Entire tree in NULL, No such value exist." << endl;
    // } else {
    //     cout << "Min value node is : " << minNode->data << endl;
    // }

    // cout << endl << "Pre-Order Traversal : "<< endl;
    // preorder(root);
    // cout << endl << "In-Order Traversal : "<< endl;
    // inorder(root);
    // cout << endl << "Post-Order Traversal : "<< endl;
    // postorder(root);

    return 0;
}