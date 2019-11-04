typedef struct TreeNode
{
    void *value;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode *newNode(void *value);
TreeNode *deleteNode(TreeNode *root, void *value);
TreeNode *insert(TreeNode *node, void *value);
void print_inorder(TreeNode *root);
int height(TreeNode *t);
