#include "infection.h"

int main()
{
	Graph* graph = read_graph();


	std::vector answer = graph->simulated_annealing_method();

	std::cout << answer.size() << "\n";

	for(auto vertex : answer)
		std::cout << vertex << " ";

	delete(graph);
	graph = nullptr;

	return 0;
}