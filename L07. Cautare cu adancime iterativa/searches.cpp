/**
 L07. Cautare limitata in adancime
 Pornind de la programul rezolvat în L06 (cautare limitata in adancime),
 implementati in continuare o cautare cu adancime iterativa. Pastrati in acelasi
 program si celelalte cautari (latime, adancime, cost uniform, cautare limitata
 in adancime) pentru a putea compara rutele gasite.

 Instructiuni legate de cautarea cu adancime iterativa:
 1. Programul se bazeaza pe cautarea cu adancime limitata. Este apelata o metoda
 cu adancime limitata cu limita 1, 2, 3 etc pana ori se ajunge la solutie, ori
 se goleste complet lista de noduri.
 2. Fireste, aceasta cautare nu trebuie sa afiseze ca nu are solutie pentru
 fiecare limita ce este prea mica.
 3. Se afiseaza la final ce limita a fost necesara pentru a se gasi solutia.
*/
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

#pragma region Setup
// prototipuri de functii
void breadth_first_search(int, int, float&, int&);
bool depth_first_search(int, int, float&, int&, int = 0);
void uniform_cost_search(int, int, float&, int&);
void get_city_id(int*);
float get_speed(float);
void print_problem();
string get_steps(string&, int, int[], int[], int);
string get_formatted_time(float);
void print_results(int, int, int[], int, int[], float = 0);

// variabile globale
string city_names[] = {"Arad",			 "Zerind",	"Oradea",	"Timisoara",
					   "Lugoj",			 "Mehadia", "Drobeta",	"Craiova",
					   "Ramnicu Valcea", "Sibiu",	"Fagaras",	"Pitesti",
					   "Bucuresti",		 "Giurgiu", "Urziceni", "Harsova",
					   "Eforie",		 "Vaslui",	"Iasi",		"Neamt"};
const int count = sizeof(city_names) / sizeof(city_names[0]);
// matricea de adiacenta dupa distanta
int distances[][count] = {
	{0, 75, 0, 118, 0, 0, 0, 0, 0, 140, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{75, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 71, 0, 0, 0, 0, 0, 0, 0, 151, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{118, 0, 0, 0, 111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 111, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 70, 0, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 75, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 120, 0, 146, 0, 0, 138, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 146, 0, 80, 0, 97, 0, 0, 0, 0, 0, 0, 0, 0},
	{140, 0, 151, 0, 0, 0, 0, 0, 80, 0, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 211, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 138, 97, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 211, 101, 0, 90, 85, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 85, 0, 0, 98, 0, 142, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 98, 0, 86, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 86, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 142, 0, 0, 0, 92, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 92, 0, 87},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 87, 0}};
// matricea de adiacenta dupa trafic
// FIXME: segmentul Ramnicu Valcea - Pitesti are valoarea 1300, setata arbitrar,
// in lipsa unei valori in enuntul problemei (harta)
int traffic[][count] = {
	{0, 800, 0, 1100, 0, 0, 0, 0, 0, 1200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{800, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 700, 0, 0, 0, 0, 0, 0, 0, 2500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1100, 0, 0, 0, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1000, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 400, 0, 600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 600, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 900, 0, 1300, 0, 0, 1600, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1300, 0, 800, 0, 1300, 0, 0, 0, 0, 0, 0, 0, 0},
	{1200, 0, 2500, 0, 0, 0, 0, 0, 1300, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 1200, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1600, 800, 0, 0, 0, 1000, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1200, 1000, 0, 400, 700, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 700, 0, 0, 900, 0, 1400, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 300, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 300, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1400, 0, 0, 0, 1200, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1200, 0, 700},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 700, 0}};
bool display_steps = false;	 // setare: afiseaza pasii intermediari
string separator =
	"\n************************************************************\n";
#pragma endregion Setup

/**
 @brief Entry point
 @param argc numar de argumente introduse
 @param *argv[] pointer la un array de caractere, fiecare element este un
 argument introdus
 @arg -d seteaza display_steps ca true
*/
int main(int argc, char* argv[]) {
	// parsarea argumentelor cu care este pornita aplicatia
	for (int i = 1; i < argc; ++i) {
		string arg = argv[i];
		if (arg == "-d") {
			display_steps = true;
		}
	}

	int start;
	int finish;
	float time_bfs;
	int cost_bfs;
	float time_dfs;
	int cost_dfs;
	float time_dfsl;
	int cost_dfsl;
	float time_ucs;
	int cost_ucs;
	int depth_constraint = 1;  // FIXME: magic number
							   // care ar trebui controlat de utilizator

	print_problem();

	// input loop pentru a putea incerca diferite combinatii de orase,
	// fara a restarta aplicatia si fara a le hardcoda
	while (true) {
		cout << "\n\nScrie id-ul orasului de plecare: ";
		get_city_id(&start);
		cout << "Plecare: " << city_names[start];

		cout << "\n\nScrie id-ul orasului de sosire: ";
		get_city_id(&finish);
		cout << "Sosire: " << city_names[finish];

		breadth_first_search(start, finish, time_bfs, cost_bfs);
		uniform_cost_search(start, finish, time_ucs, cost_ucs);
		depth_first_search(start, finish, time_dfs, cost_dfs);

		bool exit_flag = false;
		while (!exit_flag && depth_constraint <= count) {
			if (depth_first_search(start, finish, time_dfsl, cost_dfsl,
								   depth_constraint)) {
				exit_flag = true;  // break ar face sa nu mai apara sumarul

				cout << "\n\nSumar:" << separator;
				cout << "BFS  : " << std::right << setw(4) << cost_bfs << " km"
					 << setw(10) << get_formatted_time(time_bfs) << '\n';
				cout << "UCS  : " << setw(4) << cost_ucs << " km" << setw(10)
					 << get_formatted_time(time_ucs) << '\n';
				cout << "DFS  : " << setw(4) << cost_dfs << " km" << setw(10)
					 << get_formatted_time(time_dfs) << '\n';
				cout << "DFSL" << depth_constraint << ": " << setw(4)
					 << cost_dfsl << " km" << setw(10)
					 << get_formatted_time(time_dfsl) << '\n';

				cout << separator;
			}
			depth_constraint++;
		}

		// reseteaza variabilele pentru urmatorul input
		depth_constraint = 1;
		time_bfs = 0;
		cost_bfs = 0;
		time_dfs = 0;
		cost_dfs = 0;
		time_dfsl = 0;
		cost_dfsl = 0;
		time_ucs = 0;
		cost_ucs = 0;
	}

	return 0;
}

#pragma region Algorithms
/**
 @brief Implementare a algoritmului de cautare in latime (BFS - breadth-first
 search)
 @param start_node punct de plecare (index din city_names, definita global)
 @param finish_node punct de sosire (idem)
 @param time
 @param cost
*/
void breadth_first_search(int start_node, int finish_node, float& time,
						  int& cost) {
	int frontier[count] = {start_node};	 // noduri de explorat
	int node_count = 1;					 // numar de noduri de explorat
	bool explored[count] = {false};		 // noduri explorate
	explored[start_node] = true;		 // marcheaza start ca explorat
	int parent_nodes[count] = {0};		 // noduri-parinte
	bool found = false;
	int costs[count] = {0};
	int step = 1;				 // contor pentru afisarea pasilor
	string recorded_steps = "";	 // contine pasii inregistrati

	while (!found && node_count > 0) {
		// primul element din frontiera devine nodul curent
		int current_node = frontier[0];
		int current_cost = costs[current_node];

		// inregistreza pasii
		get_steps(recorded_steps, step, frontier, costs, node_count);
		step++;

		// elimina primul element din frontiera (pop)
		// deplaseaza continutul in uz al frontierei cu un element spre stanga
		for (int i = 0; i < node_count - 1; i++) {
			frontier[i] = frontier[i + 1];
		}
		node_count--;  // actualizeaza numarul de noduri de explorat

		// verifica daca nodul curent este tinta
		if (current_node == finish_node) {
			found = true;
		} else {
			// itereaza in linia din matricea de adiacenta,
			// corespunzatoare nodului curent pentru a gasi nodurile succesoare
			for (int i = 0; i < count; i++) {
				if ((distances[current_node][i] != 0) && !explored[i]) {
					frontier[node_count] = i;  // evitam frontier[node_count++]
					// (si alte expresii similare) pentru ca poate duce la erori
					// de intelegere a codului
					costs[i] = current_cost + distances[current_node][i];
					node_count++;  // actualizeaza numarul de noduri de explorat
					explored[i] = true;	 // marcheaza nodul succesor ca explorat
					parent_nodes[i] = current_node;
				}
			}
		}
	}

	// afiseaza denumirea algoritmului
	cout << "\n\nCautare in latime (Breadth-First Search)" << separator;

	// afiseaza pasii intermediari
	cout << recorded_steps;

	float speed;
	int path[count] = {0};	   // solutia
	int path_nodes_count = 0;  // numar de noduri din solutie
	int goal = finish_node;

	// adauga la solutie nodurile-parinte incepand cu ultimul
	while (goal != start_node) {
		float car_density = (float)traffic[goal][parent_nodes[goal]] /
							distances[goal][parent_nodes[goal]];
		speed = get_speed(car_density);
		time += (float)distances[goal][parent_nodes[goal]] / speed;
		path[path_nodes_count] = goal;
		path_nodes_count++;
		goal = parent_nodes[goal];
	}

	// adauga la solutie si primul nod
	path[path_nodes_count] = start_node;
	path_nodes_count++;

	// afiseaza rezultatul cautarii
	print_results(start_node, finish_node, path, path_nodes_count, costs, time);
	cost = costs[finish_node];
}

/**
 @brief Implementare a algoritmului de cautare in adancime (DFS - depth-first
 search)
 @param start_node punct de plecare (index din city_names, definita global)
 @param finish_node punct de sosire (idem)
 @param time
 @param cost
 @param limit numar maxim de noduri pentru explorarea in adancime
*/
bool depth_first_search(int start_node, int finish_node, float& time, int& cost,
						int limit) {
	int frontier[count] = {start_node};	 // noduri de explorat
	int node_count = 1;					 // numar de noduri de explorat
	bool explored[count] = {false};		 // noduri explorate
	explored[start_node] = true;		 // marcheaza start ca explorat
	int parent_nodes[count] = {0};		 // noduri-parinte
	bool found = false;
	int costs[count] = {0};
	int depth[count] = {0};
	int current_node = 0;
	int step = 1;				 // contor pentru afisarea pasilor
	string recorded_steps = "";	 // contine pasii inregistrati

	while (!found && node_count > 0) {
		// primul element din frontiera devine nodul curent
		current_node = frontier[0];
		int current_cost = costs[current_node];

		// inregistreza pasii
		get_steps(recorded_steps, step, frontier, costs, node_count);
		step++;

		// elimina primul element din frontiera (pop)
		// deplaseaza continutul in uz al frontierei cu un element spre stanga
		for (int i = 0; i < node_count - 1; i++) {
			frontier[i] = frontier[i + 1];
		}
		node_count--;  // actualizeaza numarul de noduri de explorat

		// verifica daca nodul curent este tinta
		if (current_node == finish_node) {
			found = true;
		} else {
			// itereaza in linia din matricea de adiacenta,
			// corespunzatoare nodului curent pentru a gasi nodurile succesoare
			for (int i = 0; i < count; i++) {
				if ((distances[current_node][i] != 0) && !explored[i] &&
					(limit == 0 ? true : (depth[current_node] + 1 <= limit))) {
					parent_nodes[i] = current_node;
					depth[i] = depth[current_node] + 1;
					for (int j = node_count - 1; j >= 0; j--) {
						frontier[j + 1] = frontier[j];
					}
					frontier[0] = i;
					node_count++;  // actualizeaza numarul de noduri de explorat
					costs[i] = current_cost + distances[current_node][i];
					explored[i] = true;	 // marcheaza nodul succesor ca explorat
				}
			}
		}
	}

	if (current_node != finish_node) {
		// cout << "\nNu exista solutie cu restrictiile date.\n";
		return false;
	}

	// afiseaza denumirea algoritmului
	if (limit == 0) {
		cout << "\n\nCautare in adancime (Depth-First Search)" << separator;
	} else {
		cout << "\n\nCautare in adancime (Depth-First Search) cu limita "
			 << limit << separator;
	}

	// afiseaza pasii intermediari
	cout << recorded_steps;

	float speed;
	int path[count] = {0};	   // solutia
	int path_nodes_count = 0;  // numar de noduri din solutie
	int goal = finish_node;

	// adauga la solutie nodurile-parinte incepand cu ultimul
	while (goal != start_node) {
		float car_density = (float)traffic[goal][parent_nodes[goal]] /
							distances[goal][parent_nodes[goal]];
		speed = get_speed(car_density);
		time += (float)distances[goal][parent_nodes[goal]] / speed;
		path[path_nodes_count] = goal;
		path_nodes_count++;
		goal = parent_nodes[goal];
	}

	// adauga la solutie si primul nod
	path[path_nodes_count] = start_node;
	path_nodes_count++;

	// afiseaza rezultatul cautarii
	print_results(start_node, finish_node, path, path_nodes_count, costs, time);
	cost = costs[finish_node];

	return true;
}

/**
 @brief Implementare a algoritmului de cautare cu cost uniform (uniform cost
 search)
 @param start_node punct de plecare (index din city_names, definita global)
 @param finish_node punct de sosire (idem)
 @param time
 @param cost
*/
void uniform_cost_search(int start_node, int finish_node, float& time,
						 int& cost) {
	int frontier[count] = {start_node};	 // noduri de explorat
	int node_count = 1;					 // numar de noduri de explorat
	bool explored[count] = {false};		 // noduri explorate
	explored[start_node] = true;		 // marcheaza start ca explorat
	int parent_nodes[count] = {0};		 // noduri-parinte
	bool found = false;
	int costs[count] = {0};
	int step = 1;				 // contor pentru afisarea pasilor
	string recorded_steps = "";	 // contine pasii inregistrati

	while (!found && node_count > 0) {
		// primul element din frontiera devine nodul curent
		int current_node = frontier[0];
		int current_cost = costs[current_node];

		// inregistreza pasii
		if (display_steps) {
			get_steps(recorded_steps, step, frontier, costs, node_count);
		}
		step++;

		// elimina primul element din frontiera (pop)
		// deplaseaza continutul in uz al frontierei cu un element spre stanga
		for (int i = 0; i < node_count - 1; i++) {
			frontier[i] = frontier[i + 1];
		}
		node_count--;  // actualizeaza numarul de noduri de explorat

		// verifica daca nodul curent este tinta
		if (current_node == finish_node) {
			found = 1;
		} else {
			// itereaza in linia din matricea de adiacenta,
			// corespunzatoare nodului curent pentru a gasi nodurile succesoare
			for (int i = 0; i < count; i++) {
				if ((distances[current_node][i] != 0) && !explored[i] ||
					((distances[current_node][i] != 0) && explored[i] &&
					 (distances[current_node][i] > 0) &&
					 (distances[current_node][i] + current_cost < costs[i]))) {
					frontier[node_count] = i;
					costs[i] = current_cost + distances[current_node][i];
					node_count++;  // actualizeaza numarul de noduri de explorat
					explored[i] = true;	 // marcheaza nodul succesor ca explorat
					parent_nodes[i] = current_node;
				}
			}

			for (int i = 0; i < node_count - 1; i++) {
				for (int j = i + 1; j < node_count; j++) {
					if (costs[frontier[i]] > costs[frontier[j]]) {
						int temp = frontier[i];
						frontier[i] = frontier[j];
						frontier[j] = temp;
					}
				}
			}
		}
	}

	// afiseaza denumirea algoritmului
	cout << "\n\nCautare cu cost uniform (Uniform Cost Search)" << separator;

	// afiseaza pasii intermediari
	cout << recorded_steps;

	float speed;
	int path[count] = {0};	   // solutia
	int path_nodes_count = 0;  // numar de noduri din solutie
	int goal = finish_node;

	while (goal != start_node) {
		float car_density = (float)traffic[goal][parent_nodes[goal]] /
							distances[goal][parent_nodes[goal]];
		speed = get_speed(car_density);
		time += (float)distances[goal][parent_nodes[goal]] / speed;
		path[path_nodes_count] = goal;
		path_nodes_count++;
		goal = parent_nodes[goal];
	}

	// adauga la solutie si primul nod
	path[path_nodes_count] = start_node;
	path_nodes_count++;

	// afiseaza rezultatul cautarii
	print_results(start_node, finish_node, path, path_nodes_count, costs, time);
	cost = costs[finish_node];
}
#pragma endregion Algorithms

#pragma region Utils
/**
 @brief Obtine de la utilizator un id valabil si il aloca variabilei
 primite
 @param id pointer la variabila care va folosi valoarea introdusa
*/
void get_city_id(int* id) {
	int temp;

	while (true) {
		// FIXME: input de tip 2asd e validat ca 2
		if ((cin >> temp) && (temp >= 0) && (temp < count)) {
			cin.ignore(INT_MAX, '\n');	// INT_MAX e arbitrar ales
			break;
		}
		cout << "Id-ul trebuie sa fie un intreg intre 0 si " << count - 1
			 << "!\nMai incearca: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	*id = temp;
}

/**
 @brief Calculeaza viteza medie potrivit formulei din cerinta
 @param car_density
*/
float get_speed(float car_density) {
	return (car_density >= 10) ? 1000 / car_density : 100;
}

/**
 @brief Afiseaza lista oraselor pentru ca utilizatorul sa le poata selecta
 dupa id.
 */
void print_problem() {
	cout << "Lista oraselor:\n";
	for (int i = 0; i < count; i++) {
		cout << setw(4) << std::right << i << ". ";
		cout << setw(15) << std::left << city_names[i] << "\t";
		if ((i + 1) % 4 == 0) {
			cout << '\n';
		}
	}
}

/**
 @brief Inregistreaza pasii intermediari in functii, depinde de setarea
 display_steps
 @param recorded_steps string in care se acumuleaza inregistrarile
 @param step numarul pasului din functia apelanta
 @param frontier lista de noduri de explorat
 @param nodes lista in care se itereaza
 @param node_count numarul de elemente afisate din lista
*/
string get_steps(string& recorded_steps, int step, int frontier[count],
				 int nodes[count], int node_count) {
	if (display_steps) {
		char node[10];
		sprintf(node, "%3d: ", step);
		recorded_steps.append(node);

		for (int i = 0; i < node_count; i++) {
			char distance[10];
			sprintf(distance, "%d", nodes[frontier[i]]);
			string city = city_names[frontier[i]] + " [" + distance + "] ";
			recorded_steps.append(city);
		}
		recorded_steps.append("\n");
	}

	return recorded_steps;
}

/**
 @brief Returneaza un string, in format de ore, minute, (secunde),
 pornind de la timpul primit ca float
 @param time ore, ca numar real
*/
string get_formatted_time(float time) {
	// conversii implicite pentru a pastra partea intreaga
	int hours = time;
	float _minutes = (time - hours) * 60;
	int minutes = _minutes;
	// float _seconds = (_minutes - minutes) * 60;
	// int seconds = _seconds;

	char time_string[10];
	// int count = sprintf(time_string, "%d:%02d:%02d", hours, minutes,
	// seconds);
	sprintf(time_string, "%d:%02d", hours, minutes);

	return time_string;
}

/**
 @brief Afiseaza rezultatul cautarii
 @param start_node
 @param finish_node
 @param path lista de rezultate
 @param path_nodes_count numarul de elemente din lista
 @param cost lista de costuri
 @param time durata
*/
void print_results(int start_node, int finish_node, int path[count],
				   int path_nodes_count, int cost[count], float time) {
	cout << "\nRezultat:\n"
		 << city_names[start_node] << " -> " << city_names[finish_node] << '\n';
	// deruleaza invers path[] pentru a afisa fiecare nod din solutie
	for (int i = path_nodes_count - 1; i >= 0; i--) {
		cout << setw(4) << std::right << path[i] << ". ";
		cout << setw(15) << std::left << city_names[path[i]];
		cout << std::right << setw(9) << cost[path[i]] << " km";
		cout << '\n';
	}
	cout << setw(10) << std::left << "Distanta: " << cost[path[0]] << " km\n";
	cout << setw(10) << std::left << "Durata: " << get_formatted_time(time);
}
#pragma endregion Utils