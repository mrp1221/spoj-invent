// SPOJ Username: sangwidge
// SPOJ Status: https://www.spoj.com/status/INVENT,sangwidge/

#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef struct e {
    int from;
    int to;
    int weight;
} Edge;

typedef struct n {
    int n;
    int rank = 1;
} Node;

// Find parent function
Node set_find(Node parents[], Node node) {
    if (parents[node.n].n == node.n) {
        return parents[node.n];
    };
    return parents[node.n] = set_find(parents, parents[node.n]);
}

// Union sets function
void set_union(Node parents[], Node x, Node y) {
    if (x.rank > y.rank) {
        parents[y.n].n = x.n;
        parents[x.n].rank += y.rank;
        parents[y.n].rank = x.rank;
    } else {
    	/*if (parents[x.n].rank == parents[y.n].rank) {
    		parents[y.n].rank++;
    	}*/
        parents[x.n].n = y.n;
        parents[y.n].rank += x.rank;
        parents[x.n].rank = y.rank;
    }
}

// Comparator for sort function
bool compare_weight(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}


int main(void) {
	// your code goes here
    Edge edges[15001];
    Node nodes[15001];
    Edge curr;
    int tests, num_nodes, i, j;
    long sum, new_edges, new_weights;
    Node parent1, parent2;
    bool first = true;

    cin >> tests;
    for (i=0; i<tests; i++) {
        sum = 0;
        cin >> num_nodes;
        if (!first) {
		    for (j=0; j <= num_nodes; j++) {
				nodes[j].rank = 1;
		    }
        }
        first = false;
        for (j=0; j < num_nodes-1; j++) {
            scanf("%d %d %d", &edges[j].from, &edges[j].to, &edges[j].weight);
            nodes[edges[j].from].n = edges[j].from;
            nodes[edges[j].to].n = edges[j].to;
        }
        sort(edges, edges+(num_nodes - 1), compare_weight);
        for (j=0; j < num_nodes-1; j++) {
        	curr = edges[j];
            sum += curr.weight;

            parent1 = set_find(nodes, nodes[curr.from]);
            parent2 = set_find(nodes, nodes[curr.to]);
            
            new_edges = (parent1.rank * parent2.rank) - 1;
	        new_weights = (new_edges * (curr.weight + 1));
	        sum += new_weights;
            
	        set_union(nodes, parent1, parent2);
        }
        cout << sum << endl;
    }

    return 0;
}