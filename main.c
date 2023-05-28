#include "graph.h"

int main(int argc, char *argv[]) {
    struct graph g = {0};
    if(argc != 3){
        puts("Error input! Enter path to file.");
        return 1;
    }
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error. Unable to open file.\n");
        return 1;
    }
    read_graph(file, &g);
    fclose(file);

    if (is_connected(&g)) {
        puts("Graph is connected");
    } else{
        puts("Graph is disconnected");
    }

    file = fopen(argv[2], "w");
    if (file == NULL) {
        fprintf(stderr, "Error. Unable to open file.\n");
        return 1;
    }
    write_dot(file, &g);
    fclose(file);
    system("dot -Tpng graph.dot -o graph.png");
    return 0;
}