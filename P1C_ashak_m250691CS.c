#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 100

struct Reward {
    char pname[21];
    char pmobile[11];
    int tcount;
    int totalFare;
    int totalDisc;
    struct Reward* left;
    struct Reward* right;
    struct Reward* parent;
};

struct Graph {
    char nodes[MAXN][30];
    int adj[MAXN][MAXN];
    int sz;
};

int getIndex(struct Graph* g, char* node) {
    for (int i = 0; i < g->sz; i++) {
        if (strcmp(g->nodes[i], node) == 0) return i;
    }
    strcpy(g->nodes[g->sz], node);
    g->sz++;
    return g->sz - 1;
}

int findIndex(struct Graph* g, char* node) {
    for (int i = 0; i < g->sz; i++) {
        if (strcmp(g->nodes[i], node) == 0) return i;
    }
    return -1; // no new insert
}


void addEdge(struct Graph* g, char* src, char* dst) {
    int u = getIndex(g, src);
    int v = getIndex(g, dst);
    g->adj[u][v] = g->adj[v][u] = 1;
}


int shortestPath(struct Graph* g, char* src, char* dst) {
    int s = getIndex(g, src);
    int d = getIndex(g, dst);
   // int s = findIndex(g, src);   // ✅ no insertion
   // int d = findIndex(g, dst);
    if (s == -1 || d == -1) return -1;
    int vis[MAXN] = {0}, dist[MAXN];
    for (int i = 0; i < MAXN; i++) dist[i] = -1;

    int q[MAXN], front = 0, rear = 0;
    q[rear++] = s;
    vis[s] = 1;
    dist[s] = 1;

    while (front < rear) {
        int u = q[front++];
        if (u == d) return dist[u];
        for (int v = 0; v < g->sz; v++) {
            if (g->adj[u][v] && !vis[v]) {
                vis[v] = 1;
                dist[v] = dist[u] + 1;
                q[rear++] = v;
            }
        }
    }
    return -1;
}

//bool validMobile(char *m) {
   // if (strlen(m) != 10) return false;
   // for (int i = 0; i < 10; i++) {
   //     if (!isdigit(m[i])) return false;
   // }
  //  return true;
//}

struct Reward* newReward(char* pname, char* pmobile, int fare, int disc) {
    struct Reward* node = (struct Reward*)malloc(sizeof(struct Reward));
    strcpy(node->pname, pname);
    strcpy(node->pmobile, pmobile);
    node->tcount = 1;
    node->totalFare = fare;
    node->totalDisc = disc;
    node->left = node->right = node->parent = NULL;
    return node;
}

struct Reward* addPassenger(struct Reward* root, char* pname, char* pmobile,
                            int fare, int disc, int* err) {
    if (disc >= fare) { *err = -1; return root; }
    if (strlen(pmobile) != 10) { *err = -1; return root; }
    if (root == NULL) {
        *err = 0;
        return newReward(pname, pmobile, fare, disc);
    }

    int cmp = strcmp(pname, root->pname);
    if (cmp == 0 && strcmp(pmobile, root->pmobile) == 0) {
        root->tcount++;
        root->totalFare += fare;
        root->totalDisc += disc;
        *err = 0;
    }
    else if (cmp < 0) {
        struct Reward* lch = addPassenger(root->left, pname, pmobile, fare, disc, err);
        root->left = lch;
        if (lch) lch->parent = root;
    }
    else {
        struct Reward* rch = addPassenger(root->right, pname, pmobile, fare, disc, err);
        root->right = rch;
        if (rch) rch->parent = root;
    }
    return root;
}

void inorderPrint(struct Reward* root, int* flag) {
    if (!root) return;
    inorderPrint(root->left, flag);
    if (*flag) printf(",");
    //printf("%s(%s)", root->pname, root->pmobile); // distinguish duplicates if name is duplicated
    printf("%s", root->pname);
    *flag = 1;
    inorderPrint(root->right, flag);
}

void showPassengers(struct Reward* root) {
    if (!root) {
        printf("-1\n");
        return;
    }

    int f = 0;
    inorderPrint(root, &f);
    printf("\n");
}

int isEligible(struct Reward* root, char* pname, char* pmobile) {
    if (!root) return 0;
    int cmp = strcmp(pname, root->pname);
    if (cmp == 0 && strcmp(pmobile, root->pmobile) == 0) {
        if (root->tcount > 0 && root->totalDisc < 700) return 1;
        else return -1;
    }
    else if (cmp < 0) return isEligible(root->left, pname, pmobile);
    else return isEligible(root->right, pname, pmobile);
}

struct Reward* better(struct Reward* a, struct Reward* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->tcount > b->tcount) return a;
    if (a->tcount < b->tcount) return b;
    if (a->totalDisc > b->totalDisc) return a;
    if (a->totalDisc < b->totalDisc) return b;
    return (strcmp(a->pname, b->pname) <= 0) ? a : b; // tie-break by name
}

struct Reward* topTraveler(struct Reward* root) {
    if (!root) return NULL;
    struct Reward* lbest = topTraveler(root->left);
    struct Reward* rbest = topTraveler(root->right);
    struct Reward* best = root;
    //best = better(best, lbest);   // ✅ use helper
    //best = better(best, rbest);
    if (lbest &&
        (lbest->tcount > best->tcount ||
         (lbest->tcount == best->tcount && lbest->totalDisc > best->totalDisc))) {
        best = lbest;
    }
    if (rbest &&
        (rbest->tcount > best->tcount ||
         (rbest->tcount == best->tcount && rbest->totalDisc > best->totalDisc))) {
        best = rbest;
    }
    return best;
}

int main() {
    struct Reward* root = NULL;
    struct Graph g;
    g.sz = 0;
    memset(g.adj, 0, sizeof(g.adj));  //make each value in the table 0

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char pname[21], pmobile[11];
        int fare, disc;
        scanf(" %[^,],%[^,],%d,%d", pname, pmobile, &fare, &disc);
        int err = 0;
        root = addPassenger(root, pname, pmobile, fare, disc, &err);
        if (err == -1) printf("-1\n");
    }

    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        char src[30], dst[30];
        scanf(" %[^,],%s", src, dst);
        addEdge(&g, src, dst);
    }

    char op;
    while (1) {
        scanf(" %c", &op);

        if (op == 't') {
            printf("program terminated\n");
            return 0;
        }
        else if (op == 'a') {
            char pname[21], pmobile[11];
            int fare, disc;
            scanf(" %[^,],%[^,],%d,%d", pname, pmobile, &fare, &disc);
            int err = 0;
            root = addPassenger(root, pname, pmobile, fare, disc, &err);
            if (err == -1) printf("-1\n");
        }
        else if (op == 'p') {
            showPassengers(root);
        }
        else if (op == 'e') {
            char pname[21], pmobile[11];
            scanf(" %[^,],%s", pname, pmobile);
            int res = isEligible(root, pname, pmobile);
            printf("%d\n", res);
        }
        else if (op == 'm') {
            struct Reward* top = topTraveler(root);
            if (top) printf("%d,%d\n", top->tcount, top->totalDisc);
            //else printf("-1\n");
        }
        else if (op == 'g') {
            char src[30], dst[30];
            scanf(" %[^,],%s", src, dst);
            int len = shortestPath(&g, src, dst);
            printf("%d\n", len);
        }
        else {
            printf("-1\n");
        }
    }

    return 0;
}
