#include <iostream>
#include <vector>

using namespace std;

struct vertex {
	int id;
	int scc = -1;
	int d = 0;
	int color = 0; //white = 0, gray = 1, black = 2
	vertex pi;
	int f = 0;
};

struct Graph {
	int vertices;
	vector<vertex> vertexVect;
	int edgeNum;
	vector< vector<vertex> > edges;
	Graph(int vertNum) {
		vertices = vertNum;
		for (int i = 0; i < vertices; i++) {
			vertexVect[i].id = i;
		}
	}
	void edge(int vertex1, int vertex2) {
		vertex v;
		vector<vertex> temp;
		v.id = vertex1;
		temp.push_back(v);
		v.id = vertex2;
		temp.push_back(v);
		edges.push_back(temp);
	}
	Graph transpose() {
		Graph t(vertices);
		int j = 0;
		vector<vertex> temp;
		for (int i = 0; i < edgeNum; i++) {
			for (j = 2; j > 0; j--) {
				temp.push_back(edges[i][j-1]);
			}
			t.edges.push_back(temp);
		}
		return t;
	}
	
};

void DFS (&Graph G) {
	for (int i = 0; i < G->vertices; i++){
		G->vertexVect[i].color = 0;
		G->vertexVect[i].pi = -1;
	}
	int time = 0;
	for (int i = 0; i < G->vertices; i++) {
		if (G->vertexVect[i].color == 0) {
			vertex u = G->vertexVect[i];
			DFSVisit(G, u, time);
		}
	}
}

void DFSVisit (&Graph G, &vertex u, int time) {
	cout << u->id << endl;
	int time2 = time + 1;
	u->d = time2;
	u->color = 1;
	for (int i = 0; i < G->edgeNum; i++) {
		if (G->edges[i][0] == u) {
			vertex v = G->edges[i][1];
			if (v.color == 0) {
				v.pi = u;
				DFSVisit (G, v, time2);
			}
		}
	}
	u->color = 2;
	time2++;
	u->f = time2;
}

void sort (&Graph G) {
	vector<vertex> temp;
	vertex max;
	for (int j = 0; j < G->vertices; j++) {
		int MaxInt = 0;
		int MaxVer = 0;
		for (int i = 0; i < G->vertices; i++) {
			if (G->vertexVect[i].f > MaxInt) {
				MaxVer = i;
				MaxInt = G->vertexVect[i].f;
				max = G->vertexVect[i];
			}
		}
		temp.push_back(max);
		G->vertexVect.erase(G->vertexVect.begin()+i);
	}
	G->vertexVect = temp;
}

int main() {
	int input1;
	int input2;
	int vert1;
	int vert2;
	cin >> input1;
	Graph G(input1);
	cin >> input2;
	for (int i = 0; i < input2; i++) {
		cin >> vert1;
		cin >> vert2;
		G.edge(vert1, vert2);
	}
	DFS(G);
	Graph T = G.transpose();
	sort(T);
	DFS(T);
}















