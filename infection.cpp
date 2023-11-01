#include "infection.h"

bool Graph::can_infect_all_bfs(std::vector<int> cur_state)
{
	std::queue<int> que;

	std::vector<int> infected_neigbours(this->max_vertex + 1, 0);
	std::vector<bool> used(this->max_vertex + 1, false);

	for(auto vertex: cur_state)
	{
		que.push(vertex);
		infected_neigbours[vertex] = 2;
		used[vertex] = true; //to vertex do not oush in que twice
		
	}

	

	while(!que.empty())
	{
		int cur_vertex = que.front();

		for(auto neigbour: this->neigbours[cur_vertex])
		{
			++infected_neigbours[neigbour];
			
			if(!used[neigbour] && infected_neigbours[neigbour] >= 2)
			{
				que.push(neigbour);
				used[neigbour] = true;
			}
		}

		
		que.pop();
	}



	for(int vertex = 1; vertex <= this->max_vertex; ++vertex)
	{
		if(infected_neigbours[vertex] < 2)
			return false;
	}

	return true;
}


void Graph::add_edge(int first_vertex, int second_vertex)
{
	neigbours[first_vertex].push_back(second_vertex);
	neigbours[second_vertex].push_back(first_vertex);
}




Graph* read_graph()
{
	Graph* graph = new Graph;
	std::cin >> graph->n_edges;

	int max_vertex = 0;
	std::vector<std::pair<int, int>> edges;

	for (size_t i = 0; i < graph->n_edges; ++i)
	{
		int first_vertex, second_vertex;

		std::cin >> first_vertex >> second_vertex;

		edges.push_back({first_vertex, second_vertex});

		max_vertex = std::max(max_vertex, std::max(first_vertex, second_vertex));
	}

	graph->max_vertex = max_vertex;

	graph->neigbours.resize(max_vertex + 1);
	graph->is_infected.resize(max_vertex + 1);

	for(int i = 1; i <= graph->is_infected.size(); i++) {
		graph->is_infected[i] = 0;
	}

	for(auto [first_vertex, second_vertex] : edges)
	{
		graph->add_edge(first_vertex, second_vertex);
	}

	return graph;
}

static double rnd_for_method()  //returns double from 0 to 1
{
	return double(rand() / RAND_MAX);
}

void Graph::delete_vertex(std::vector<int>& new_state, std::vector<int>& cur_state, std::vector<int>& answer, double temp)
{
	std::vector<int> cur_state_saved = cur_state;

	std::vector<bool> is_infected_saved = this->is_infected;

	int delete_vert = rnd() % cur_state.size();

	new_state.erase(new_state.begin() + delete_vert);
	this->is_infected[cur_state[delete_vert]] = false;
	

	bool is_corrrect = this->can_infect_all_bfs(new_state);
	size_t new_size = new_state.size(), cur_size = cur_state.size();

	if(is_corrrect && ((new_size < cur_size) || (rnd() < exp((new_size - cur_size) / temp))))
	{
		cur_state = new_state;
		if(answer.size() > cur_state.size())
			answer = cur_state;
	}
	else
	{
		this->is_infected = is_infected_saved;
		cur_state = cur_state_saved;
	}
}

void Graph::add_vertex(std::vector<int>& new_state, std::vector<int>& cur_state, std::vector<int>& answer, double temp)
{
	std::vector<bool> is_infected_saved = this->is_infected;
	std::vector<int> cur_state_saved = cur_state;

	std::vector<int> not_infected_vertexes;
	for(int vertex = 1; vertex <= this->max_vertex; ++vertex)
	{
		if(!(this->is_infected[vertex]))
		{
			not_infected_vertexes.push_back(vertex);
		}
	}




	int add_vert = rnd() % not_infected_vertexes.size(); 

	new_state.push_back(not_infected_vertexes[add_vert]);
	this->is_infected[not_infected_vertexes[add_vert]] = true;



	bool is_corrrect = this->can_infect_all_bfs(new_state);
	size_t new_size = new_state.size(), cur_size = cur_state.size();

	if(is_corrrect && ((new_size < cur_size) || (rnd() < exp((new_size - cur_size) / temp))))
	{
		cur_state = new_state;
		if(answer.size() > cur_state.size())
			answer = cur_state;
	}
	else
	{
		this->is_infected = is_infected_saved;
		cur_state = cur_state_saved;
	}
}


std::vector<int> Graph::simulated_annealing_method()
{
	std::vector<int> answer;
	std::vector<int> cur_state;

	for(int vertex = 1; vertex <= this->max_vertex; ++vertex)
	{
		cur_state.push_back(vertex);
		answer.push_back(vertex);
		this->is_infected[vertex] = true;
	}


	double temp = 1;
	std::vector<int> new_state;

	for(int cur_iter = 1; cur_iter < N_ITERS; ++cur_iter)
	{
		temp *= 0.99;
		new_state = cur_state;

		if(new_state.size() == this->max_vertex) // can only delete(has all vertexes now in new_state), so delete one random vertex
		{
			delete_vertex(new_state, cur_state, answer, temp);
			continue;
		}

		if(new_state.size() <= 1)
			return new_state;


		int operation = rnd() % 2;

		if(operation == 1)
		{
			delete_vertex(new_state, cur_state, answer, temp);
		}
		else
		{
			add_vertex(new_state, cur_state, answer, temp);
		}


	}

	return answer;
}



