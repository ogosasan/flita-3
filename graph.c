#include "gra
ph.h"

void dfs(struct graph* g, int v, int visited[]) {
    visited[v] = 1;
    for (int i = 0; i < g->num_nodes; i++) {
        if (g->nodes[v][i] && !visited[i]) {
            dfs(g, i, visited);
        }
    }
}

int is_connected(struct graph* g) {
    int visited[MAX_NODES] = {0};
    dfs(g, 0, visited);
    for (int i = 0; i < g->num_nodes; i++) {
        if (!visited[i]) {
            return 0;
        }
    }
    return 1;
}

void read_graph(FILE* file, struct graph* g) {
    char line[256];
    int row = 0;

    while (fgets(line, sizeof(line), file)) {
        int col = 0;
        char* token = strtok(line, " ");
        while (token) {
            int value = atoi(token);
            g->nodes[row][col++] = value;
            if (col-1 <= row) {
                g->nodes[col-1][row] = value;
            }
            token = strtok(NULL, " ");
        }
        row++;
    }

    g->num_nodes = row;
}

void write_dot(FILE* file, struct graph* g) {
    fprintf(file, "digraph G {\n");
    for (int i = 0; i < g->num_nodes; i++) {
        fprintf(file, "  %d;\n", i);
    }
    for (int i = 0; i < g->num_nodes; i++) {
        for (int j = i; j < g->num_nodes; j++) {
            if (g->nodes[i][j]) {
                fprintf(file, "  %d -> %d [dir=none, label=%d];\n", i, j, g->nodes[i][j]);
            }
        }
    }
    fprintf(file, "}\n");
}