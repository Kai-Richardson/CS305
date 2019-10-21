typedef struct LLNode Node;
struct LLNode {
	int data;
	Node* next;
} LLNode;

void printAndFree(Node * list) {

	if (list  == NULL) return;
	printf("%d\n", list->data);
	printAndFree(list);
	free(list);
	}
}

void InsertInOrder (DLList* list, DLList* node) {
	
}

