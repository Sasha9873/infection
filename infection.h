#ifndef INFECTION_H
#define INFECTION_H

	#include <iostream>
	#include <vector>
	#include <unordered_map>
	#include <queue>
	#include <chrono>
	#include <random>
	#include <algorithm>
	#include <math.h>

	static const int N_ITERS = 1e6;
	static std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());


	// numeration from 1
	class Graph{
	public:
		bool can_infect_all();
		void add_edge(int first_vertex, int second_vertex);
		std::vector<int> simulated_annealing_method();
		void add_vertex(std::vector<int>& new_state, std::vector<int>& cur_state, std::vector<int>& answer, double temp);
		void delete_vertex(std::vector<int>& new_state, std::vector<int>& cur_state, std::vector<int>& answer, double temp);
		bool can_infect_all_bfs(std::vector<int> cur_state);


		std::vector<std::vector<int>> neigbours;

		std::vector<bool> is_infected = {false};

		size_t n_edges = 0;
		size_t max_vertex = 0;
		Graph() = default;
		~Graph() = default;


	};

	Graph* read_graph();

#endif
