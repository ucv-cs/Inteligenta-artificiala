/**
 C02. Implementați algoritm de căutare bidirecțională astfel încât să avem
combinații din următoarele căutări: Lățime, Adâncime.
Instrucțiuni legate de căutarea bidirecțională:
1. Programul va porni concomitent de la nodul de start cu căutare în lățime și
de la cel de stop cu căutare în adâncime.
2. Va trebui să rețineți câte două tablouri distincte de noduri, vizitate,
parinte, o serie pentru căutarea de la start și una pentru cea de la stop.
3. Vă opriți când un nod din lista de vizitate1 se găsește și în lista de
vizitate2. Atunci se poate construi soluția finală concatenând lista de la start
la nodul comun (dintre vizitate1 și vizitate2) cu cea de la nodul comun la stop.
*/
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

#pragma region Setup
// prototipuri de functii
void bidirectional_search(int, int, int&);
void get_city_id(int*);
void print_problem();
string record_steps(string&, int, int[], int[], int);
void print_results(int, int, int[], int, int[]);
bool intersect_arrays(bool[], bool[], int&);
void reverse_array(int[], int);

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
	int cost;

	// input loop pentru a putea incerca diferite combinatii de orase,
	// fara a restarta aplicatia si fara a le hardcoda
	while (true) {
		print_problem();

		cout << "\n\nScrie indexul orasului de plecare: ";
		get_city_id(&start);
		cout << "Plecare: " << city_names[start];

		cout << "\n\nScrie indexul orasului de sosire: ";
		get_city_id(&finish);
		cout << "Sosire: " << city_names[finish];

		bidirectional_search(start, finish, cost);
	}

	return 0;
}

#pragma region Algorithms
/**
 @brief Implementare a algoritmului de cautare bidirectionala (BFS+DFS)
 @param start_node punct de plecare (index din city_names, definita global)
 @param finish_node punct de sosire (idem)
 @param cost
*/
void bidirectional_search(int start_node, int finish_node, int& cost) {
	// BFS
	int start_current_node = start_node;
	int start_frontier[count] = {start_current_node};
	int start_frontier_count = 1;
	bool start_explored[count] = {false};
	start_explored[start_current_node] = true;
	int start_ascendants[count] = {0};
	int start_costs[count] = {0};

	// DFS
	int finish_current_node = finish_node;
	int finish_frontier[count] = {finish_current_node};
	int finish_frontier_count = 1;
	bool finish_explored[count] = {false};
	finish_explored[finish_current_node] = true;
	int finish_ascendants[count] = {0};
	int finish_costs[count] = {0};

	bool found = false;
	int join_node = 0;

	int start_step = 1;
	string start_recorded_steps;
	int finish_step = 1;
	string finish_recorded_steps;

	while (!found && start_frontier_count > 0 && finish_frontier_count > 0) {
		start_current_node = start_frontier[0];
		int start_current_cost = start_costs[start_current_node];
		finish_current_node = finish_frontier[0];
		int finish_current_cost = finish_costs[finish_current_node];

		// inregistreaza pasii pentru afisare ulterioara
		record_steps(start_recorded_steps, start_step, start_frontier,
					 start_costs, start_frontier_count);
		start_step++;
		record_steps(finish_recorded_steps, finish_step, finish_frontier,
					 finish_costs, finish_frontier_count);
		finish_step++;

		for (int i = 0; i < start_frontier_count - 1; i++) {
			start_frontier[i] = start_frontier[i + 1];
		}
		start_frontier_count--;

		int current_node = 0;
		// verifica daca nodul curent este unul explorat de ambele parcurgeri
		if (intersect_arrays(start_explored, finish_explored, current_node)) {
			join_node = current_node;
			found = true;
		} else {
			// BFS de la start_node
			for (int i = 0; i < count; i++) {
				if (distances[start_current_node][i] != 0 &&
					!start_explored[i]) {
					start_frontier[start_frontier_count] = i;
					start_frontier_count++;
					start_explored[i] = true;
					start_ascendants[i] = start_current_node;
					start_costs[i] =
						start_current_cost + distances[start_current_node][i];
				}
			}

			// DFS de la finish_node
			for (int i = 0; i < count; i++) {
				if (distances[finish_current_node][i] != 0 &&
					!finish_explored[i]) {
					for (int j = finish_frontier_count - 1; j >= 0; j--) {
						finish_frontier[j + 1] = finish_frontier[j];
					}
					finish_frontier[0] = i;
					finish_frontier_count++;
					finish_explored[i] = true;
					finish_ascendants[i] = finish_current_node;
					finish_costs[i] =
						finish_current_cost + distances[finish_current_node][i];
				}
			}
		}
	}

	// afiseaza denumirea algoritmului
	cout << "\n\nCautare bidirectionala" << separator;

	// afiseaza pasii intermediari
	cout << start_recorded_steps;
	cout << finish_recorded_steps;

	int solution[count] = {0};
	int solution_count = 0;
	int current_node = join_node;

	// pregateste solutia incepand cu finalul
	while (current_node != finish_node) {
		solution[solution_count] = current_node;
		solution_count++;
		current_node = finish_ascendants[current_node];
	}
	solution[solution_count] = finish_node;
	solution_count++;
	reverse_array(solution, solution_count);

	solution_count--;  // scade indexul pentru a se suprapune
					   // join_node din cele doua liste
	current_node = join_node;
	while (current_node != start_node) {
		solution[solution_count] = current_node;
		solution_count++;
		current_node = start_ascendants[current_node];
	}
	solution[solution_count] = start_node;
	solution_count++;

	// calculul costurilor asociate nodurilor din solutie
	int costs[count] = {0};
	for (int i = solution_count - 2; i >= 0; i--) {
		costs[i] += costs[i + 1] + distances[solution[i]][solution[i + 1]];
	}
	cost = costs[0];

	// afisare
	print_results(start_node, finish_node, solution, solution_count, costs);
}
#pragma endregion Algorithms

#pragma region Utils
/**
 @brief Obtine de la utilizator un index valabil si il aloca variabilei
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
		cout << "Indexul trebuie sa fie un intreg intre 0 si " << count - 1
			 << "!\nMai incearca: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	*id = temp;
}

/**
 @brief Afiseaza lista oraselor pentru ca utilizatorul sa le poata selecta
 dupa index.
 */
void print_problem() {
	cout << "\nLista oraselor:\n";
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
 @return recorded_steps pasii inregistrati
*/
string record_steps(string& recorded_steps, int step, int frontier[],
					int nodes[], int node_count) {
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
 @brief Afiseaza rezultatul cautarii
 @param start_node
 @param finish_node
 @param path lista de rezultate
 @param path_nodes_count numarul de elemente din lista
 @param cost lista de costuri
 @param time durata
*/
void print_results(int start_node, int finish_node, int path[], int path_count,
				   int costs[]) {
	cout << "\nRezultat:\n"
		 << city_names[start_node] << " -> " << city_names[finish_node] << '\n';
	// deruleaza invers path[] pentru a afisa fiecare nod din solutie
	for (int i = path_count - 1; i >= 0; i--) {
		cout << setw(4) << std::right << path[i] << ". ";
		cout << setw(15) << std::left << city_names[path[i]];
		cout << std::right << setw(9) << costs[i] << " km";
		cout << '\n';
	}
	cout << setw(10) << std::left << "Distanta: " << costs[0] << " km\n";
}

/**
 @brief Verifica daca doua liste se intersecteaza
 @param first[]
 @param second[]
 @param index
 */
bool intersect_arrays(bool first[], bool second[], int& index) {
	for (int i = 0; i < count; i++) {
		if (first[i] && second[i]) {
			index = i;
			return true;
		}
	}
	return false;
}

/**
 @brief Inverseaza elementele dintr-un array
 @param array[]
 @param count
 */
void reverse_array(int array[], int count) {
	int temp;
	int i = 0;
	int j = count - 1;
	while (i < j) {
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
		i++;
		j--;
	}
}
#pragma endregion Utils