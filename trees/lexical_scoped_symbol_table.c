#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ScopeEntry {
    int scopeLvl;
    char type[7];
    struct ScopeEntry* next;
} ScopeEntry;

typedef struct BSTNode {
    char name[7];
    ScopeEntry* scopeStk;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct ScopeDeclList {
    BSTNode* node;
    struct ScopeDeclList* next;
} ScopeDeclList;

BSTNode* symbols = NULL;
int currScope = 0;
ScopeDeclList* newList[200002];

BSTNode* getOrInsertSymbol(BSTNode** root, char* name) {
    BSTNode** curr = root;
    
    while (*curr != NULL) {
        int cmp = strcmp(name, (*curr)->name);
        if (cmp == 0) {
            return *curr;
        } else if (cmp < 0) {
            curr = &((*curr)->left);
        } else {
            curr = &((*curr)->right);
        }
    }
    
    BSTNode* node = malloc(sizeof *node);
    strcpy(node->name, name);
    node->scopeStk = NULL;
    node->left = NULL;
    node->right = NULL;
    *curr = node;
    return node;
}

BSTNode* lookupSymbol(BSTNode* root, char* name) {
    while (root != NULL) {
        int cmp = strcmp(name, root->name);
        if (cmp == 0) {
            return root;
        } else if (cmp < 0) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return NULL;
}

int declVar(char* name, char* type) {
    BSTNode* node = getOrInsertSymbol(&symbols, name);
    
    if (node->scopeStk != NULL && node->scopeStk->scopeLvl == currScope) {
        return 0;
    }
    
    ScopeEntry* entry = malloc(sizeof *entry);
    entry->scopeLvl = currScope;
    strcpy(entry->type, type);
    entry->next = node->scopeStk;
    node->scopeStk = entry;
    
    ScopeDeclList* var = malloc(sizeof *var);
    var->node = node;
    var->next = newList[currScope];
    newList[currScope] = var;
    
    return 1;
}

char* findType(char* name) {
    BSTNode* node = lookupSymbol(symbols, name);
    if (node == NULL || node->scopeStk == NULL) {
        return NULL;
    }
    return node->scopeStk->type;
}

void enterBlock() {
    currScope++;
    newList[currScope] = NULL;
}

void exitBlock() {
    ScopeDeclList* var = newList[currScope];
    while (var != NULL) {
        BSTNode* node = var->node;
        if (node->scopeStk != NULL) {
            ScopeEntry* entry = node->scopeStk;
            node->scopeStk = entry->next;
            free(entry);
        }
        ScopeDeclList* next = var->next;
        free(var);
        var = next;
    }
    newList[currScope] = NULL;
    currScope--;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i <= 200001; i++) {
        newList[i] = NULL;
    }
    
    enterBlock();
    
    for (int i = 0; i < n; i++) {
        char cmd[8];
        scanf("%7s", cmd);
        
        if(strcmp(cmd, "{") == 0) {
            enterBlock();
        } else if (strcmp(cmd, "}") == 0) {
            exitBlock();
        } else if (strcmp(cmd, "DECLARE") == 0) {
            char name[7];
            char type[7];
            scanf("%6s", name);
            scanf("%6s", type);
            if (!declVar(name, type)) {
                printf("MULTIPLE DECLARATION\n");
                return 0;
            }
        } else if (strcmp(cmd, "TYPEOF") == 0) {
            char name[7];
            scanf("%6s", name);
            char* type = findType(name);
            if (type == NULL) {
                printf("UNDECLARED\n");
            } else {
                printf("%s\n", type);
            }
        }
    }
    
    return 0;
}
