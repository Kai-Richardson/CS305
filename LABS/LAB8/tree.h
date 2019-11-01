/* CS 305
 * Tree code
 * Tammy VanDeGrift
 * tree.h 
 */

/* data structure definitions for binary tree */
typedef int TreeData;  // can change type with
                       // primitive or struct type

typedef struct TreeNodeTag TreeNode;

struct TreeNodeTag {
  TreeData value;    // value stored in node
  TreeNode * left;   // left child
  TreeNode * right;  // right child
};

typedef TreeNode * TreeNodePtr; // how textbook defines type if you
                                // prefer to use TreeNodePtr as a type
                                // instead of TreeNode *

/* function prototypes */
TreeNode * createTree(TreeData a[], int size);
void insert(TreeData d, TreeNode ** tptr);
void insertR(TreeData d, TreeNode **tptr);
void delete(TreeData d, TreeNode ** tptr);
int size(TreeNode * t);
void preorder(TreeNode * t);
void inorder(TreeNode * t);
int numLeaves(TreeNode * t);
int sum(TreeNode * t);
void freeTree(TreeNode ** t);
TreeData findMin(TreeNode * t);
void print(TreeNode * t);

/* prototypes for lab exercises */
int height(TreeNode * t); // lab exercise
void postorder(TreeNode * t); // lab exercise
TreeNode * find(TreeData d, TreeNode * t);  // lab exercise
TreeData findMax(TreeNode * t); // lab exercise
