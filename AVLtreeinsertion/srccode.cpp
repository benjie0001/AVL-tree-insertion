#include<iostream>

using namespace std;

class Node//implement an AVL tree node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;
};
 int max(int a, int b)//utility method to get maximum of two integers
    {
        if(a>b)
            return a;
        else
            return b;
    }
    int height(Node *N)
    {
        if (N==NULL)//empty node
        {
            return 0;
        }
        return N->height;//gives number of nodes that relates to the hieght of AVL tree
    }

    Node *newNode(int key)//allocates new node with given key and NULL left/right pointers
    {
        Node *node=new Node();
        node->key=key;
        node->left=NULL;
        node->right=NULL;
        node->height=1;

        return(node);
    }

    Node *rightRotate(Node *y)
    {
        Node *x=y->left;
        Node *Temp2=x->right;
        x->right=y;
        y->left=Temp2;

        //update heights
        y->height=max(height(y->left),height(y->right))+1;
        x->height=max(height(x->left),height(x->right))+1;

        return x;//returns new root

    }
    //rotate subtree rooted with x
    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *Temp2=y->left;
        //perform rotation
        y->left=x;
        x->right=Temp2;
        //update heights
        x->height=max(height(x->left),height(x->right))+1;
        y->height=max(height(y->left),height(y->right))+1;
        return y;//returns new root
    }

    int getBalance(Node *N)//get balance factor if node N
    {
        if(N==NULL)
            return 0;

        return height(N->left)-height(N->right);

    }

    Node *insert(Node* node,int key)
    {
         /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                        height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;

    }

    //function for preorder traversal of the tree
    void preOrder(Node*root)
    {
        if(root!=NULL)
        {
            cout<<root->key<<" ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

int main()
{
    Node *root=NULL;
    //insert values into the trr
    root= insert(root,10);
    root= insert(root,20);
    root= insert(root,25);
    root= insert(root,30);
    root= insert(root,40);
    root= insert(root,50);
    root= insert(root,69);

    cout<<" preorder traversal of the constructed AVL tree"<<endl;
    preOrder(root);
    return 0;
}
