typedef struct TreeNode
{
    char *value;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode *newNode(char *value);
TreeNode *deleteNode(TreeNode *root, char *value);
TreeNode *insert(TreeNode *node, char *value);
void print_inorder(TreeNode *root);
int height(TreeNode *t);

int int_greater(int i1, int i2);