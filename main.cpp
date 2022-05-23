#include<iostream>
#include<queue>
#include<vector>
#define GRAPH std::vector<std::vector<int>>
void print(GRAPH graph) {
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.size(); j++)
			std::cout << graph[i][j] << " ";
		std::cout << "\n";
	}

}
void randomFill(GRAPH& graph,int percent) {
	for (int i = 0; i < graph.size(); i++) {
		for (int j = i + 1; j < graph.size(); j++) {
			graph[i][j] = ((std::rand() % 100) < percent) ? 1 : 0;
			graph[j][i] = graph[i][j];
			if (i == j) graph[i][j] == 0;
		}

	}
}
bool finded(std::vector<int> labelled,int elem) {
	for (int i = 0; i < labelled.size(); i++)if (labelled[i] == elem) return true;
	return false;
}
std::vector<int> findNeighbour(GRAPH graph, int elem, std::vector<int> labelled) {
	std::vector<int> neigh;
	for (int i = 0; i < graph.size(); i++) {
		if (graph[elem][i] == 1 && !finded(labelled,i)) neigh.push_back(i);
	}
	return neigh;
}

std::vector<int> searchInWidth(GRAPH graph, int start, int end) {
	std::vector<int> labelled;
	std::queue<int> result;
	int current;
	result.push(start);


	while (!finded(labelled, end) && labelled.size() != graph.size()) {
		if (!result.empty())
			current = result.front();
		result.pop();
		labelled.push_back(current);
		std::vector<int> neigh = findNeighbour(graph, current, labelled);
		if (finded(neigh, end)) {
			labelled.push_back(end);
			return labelled;
		}

		for (int i = 0; i < neigh.size(); i++) {
			result.push(neigh[i]);
		}
		if (finded(labelled, end)) return labelled;

		if (result.empty()) return std::vector<int>(0);
	}
	
	if (!finded(labelled, end)) {
		labelled = std::vector<int>(0);
	}
	return labelled;
}


int main() {
	std::srand(std::time(0));
	int size,start,end;
	GRAPH graph;
	std::cout << "Graph size:";
	std::cin >> size;
	graph.resize(size);
	for (int i = 0; i < size; i++)graph[i].resize(size);
	//random fill
	randomFill(graph, 20);
	print(graph);
	std::cin >> start >> end;
	std::vector<int> result = searchInWidth(graph,start,end);
	for (int i = 0; i < result.size(); i++) { std::cout << result[i]; if (i != result.size() - 1)std::cout << "->"; };


	return 0;
}

