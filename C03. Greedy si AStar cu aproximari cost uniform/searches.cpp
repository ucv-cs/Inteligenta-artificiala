/**
 * C03. Urmatorul proiect de la curs se refera la implementarea unui program
 * care sa ne permita sa aplicam algoritmii Greedy si A* pentru gasirea rutei de
 * la un oras catre oricare alt oras, nu doar catre Bucuresti, cum am facut pana
 * acum.
 *
 * Pentru a putea face acest lucru, avem nevoie de aproximari din orice oras
 * catre oricare alt oras. Pentru a obtine astfel de valori h, se va folosi
 * cautarea cu cost uniform pentru a se gasi cel mai scurt drum de la orice oras
 * catre orice alt oras. Numarul de km dat de rutele de la cost uniform va
 * reprezenta chiar valoarea h.
 *
 * In acest sens, aveti de ales:
 * 1. Puteti calcula la inceput, inainte de a intra in metoda A*, o matrice h
 * intre oricare doua orase si pe aceasta o utilizati apoi in cadrul
 * algoritmilor Greedy si A*.
 * 2. Puteti modifica metoda de cost uniform astfel incat sa va intoarca costul
 * drumului intre doua orase (in loc de void, cum e acum) si, de cate ori aveti
 * nevoie de o aproximare intre doua noduri n1 si n2, apelati metoda de cost
 * uniform cu argumentele care va trebuie.
 * 3. Varianta cea mai putin eleganta - puteti face doua programe:
 * 3.1 Unul care sa calculeze distantele cu cost uniform intre oricare doua
 * orase si sa le salveze intr-un fisier.
 * 3.2 Al doilea pentru Greedy si A* care sa incarce distantele din fisierul
 * salvat de programul de la 3.1 intr-o matrice h si sa le foloseasca apoi unde
 * are nevoie de aproximarile h.
 */
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

#pragma region Setup
// prototipuri de functii
void uniform_cost_search(int, int, int&, bool = false);
void greedy_search(int, int, int&);
void astar_search(int, int, int&);
void get_city_id(int*);
void print_problem();
string get_steps(string&, int, int[], int[], int);
void print_result(int, int, int[], int, int[]);

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
// matrice de adiacenta cu costurile estimate (h), initializata cu 0
int estimates[count][count] = {{0}};
bool display_steps = false;	 // setare: afiseaza pasii intermediari
string separator =
	"\n************************************************************\n";
#pragma endregion Setup

/**
 * @brief Inceputul executiei
 * @param argc numar de argumente introduse
 * @param *argv[] pointer la un array de caractere, fiecare element este un
 * argument introdus
 * @arg -d seteaza display_steps ca true
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
	int cost_ucs;
	int cost_greedy;
	int cost_astar;

	// completeaza matricea de adiacenta a estimarilor
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			if (i != j) {
				uniform_cost_search(i, j, cost_ucs);
				estimates[i][j] = cost_ucs;
			}
		}
	}

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

		uniform_cost_search(start, finish, cost_ucs, true);
		greedy_search(start, finish, cost_greedy);
		astar_search(start, finish, cost_astar);

		cout << "\n\nSumar:" << separator;
		cout << "UCS    : " << setw(4) << std::right << cost_ucs << " km\n";
		cout << "Greedy : " << setw(4) << std::right << cost_greedy << " km\n";
		cout << "A*     : " << setw(4) << std::right << cost_astar << " km\n";

		cout << separator;

		// reseteaza variabilele pentru urmatorul input
		cost_ucs = 0;
		cost_greedy = 0;
		cost_astar = 0;
	}

	return 0;
}

#pragma region Algorithms
/**
 * @brief Implementare a algoritmului de cautare cu cost uniform (uniform cost
 * search)
 * @param start_node punct de plecare (index din city_names, definita global)
 * @param finish_node punct de sosire (idem)
 * @param cost valoarea returnata
 * @param display optiune de afisare a rezultatelor; implicit: false
 */
void uniform_cost_search(int start_node, int finish_node, int& cost,
						 bool display) {
	int frontier[count] = {start_node};
	int frontier_count = 1;
	bool explored[count] = {false};
	explored[start_node] = true;
	int ascendants[count] = {0};
	bool found = false;
	int costs[count] = {0};
	int step = 1;
	string recorded_steps;

	while (!found && frontier_count > 0) {
		// primul element din frontiera devine nodul curent
		int current_node = frontier[0];
		int current_cost = costs[current_node];

		// inregistreza pasii
		if (display_steps) {
			get_steps(recorded_steps, step, frontier, costs, frontier_count);
		}
		step++;

		// elimina primul element din frontiera (pop)
		// deplaseaza continutul in uz al frontierei cu un element spre stanga
		for (int i = 0; i < frontier_count - 1; i++) {
			frontier[i] = frontier[i + 1];
		}
		frontier_count--;

		// verifica daca nodul curent este tinta
		if (current_node == finish_node) {
			found = true;
		} else {
			// itereaza in linia din matricea de adiacenta,
			// corespunzatoare nodului curent pentru a gasi nodurile succesoare
			for (int i = 0; i < count; i++) {
				if ((distances[current_node][i] != 0) && !explored[i] ||
					((distances[current_node][i] != 0) && explored[i] &&
					 (distances[current_node][i] > 0) &&
					 (distances[current_node][i] + current_cost < costs[i]))) {
					frontier[frontier_count] = i;
					costs[i] = current_cost + distances[current_node][i];
					frontier_count++;
					explored[i] = true;
					ascendants[i] = current_node;
				}
			}

			for (int i = 0; i < frontier_count - 1; i++) {
				for (int j = i + 1; j < frontier_count; j++) {
					if (costs[frontier[i]] > costs[frontier[j]]) {
						int temp = frontier[i];
						frontier[i] = frontier[j];
						frontier[j] = temp;
					}
				}
			}
		}
	}

	int solution[count] = {0};	// solutia
	int solution_count = 0;		// numar de noduri din solutie
	int current_node = finish_node;

	while (current_node != start_node) {
		solution[solution_count] = current_node;
		solution_count++;
		current_node = ascendants[current_node];
	}
	solution[solution_count] = start_node;
	solution_count++;

	cost = costs[finish_node];

	if (display) {
		// sectiunea de afisare
		cout << "\n\nCautare cu cost uniform" << separator;
		// pasii intermediari
		cout << recorded_steps;
		// rezultatul
		print_result(start_node, finish_node, solution, solution_count, costs);
	}
}

/**
 * @brief Implementare a algoritmului de cautare greedy
 * @param start_node punct de plecare (index din city_names, definita global)
 * @param finish_node punct de sosire (idem)
 * @param cost valoarea returnata
 */
void greedy_search(int start_node, int finish_node, int& cost) {
	int frontier[count] = {start_node};
	int frontier_count = 1;
	bool explored[count] = {false};
	explored[start_node] = true;
	int ascendants[count] = {0};
	bool found = false;
	int costs[count] = {0};
	int step = 1;
	string recorded_steps;

	while (!found && frontier_count > 0) {
		// primul element din frontiera devine nodul curent
		int current_node = frontier[0];
		int current_cost = costs[current_node];

		// inregistreza pasii
		if (display_steps) {
			get_steps(recorded_steps, step, frontier, costs, frontier_count);
		}
		step++;

		// elimina primul element din frontiera (pop)
		// deplaseaza continutul in uz al frontierei cu un element spre stanga
		for (int i = 0; i < frontier_count - 1; i++) {
			frontier[i] = frontier[i + 1];
		}
		frontier_count--;  // actualizeaza numarul de noduri de explorat

		// verifica daca nodul curent este tinta
		if (current_node == finish_node) {
			found = true;
		} else {
			// itereaza in linia din matricea de adiacenta,
			// corespunzatoare nodului curent pentru a gasi nodurile succesoare
			for (int i = 0; i < count; i++) {
				if ((distances[current_node][i] != 0) && !explored[i]) {
					frontier[frontier_count] = i;
					costs[i] = current_cost + distances[current_node][i];
					frontier_count++;
					explored[i] = true;
					ascendants[i] = current_node;
				}
			}

			for (int i = 0; i < frontier_count - 1; i++) {
				for (int j = i + 1; j < frontier_count; j++) {
					if (estimates[frontier[i]] > estimates[frontier[j]]) {
						int temp = frontier[i];
						frontier[i] = frontier[j];
						frontier[j] = temp;
					}
				}
			}
		}
	}

	int solution[count] = {0};
	int solution_count = 0;
	int current_node = finish_node;

	while (current_node != start_node) {
		solution[solution_count] = current_node;
		solution_count++;
		current_node = ascendants[current_node];
	}
	solution[solution_count] = start_node;
	solution_count++;

	cost = costs[finish_node];

	// sectiunea de afisare
	cout << "\n\nCautare greedy" << separator;
	// pasii intermediari
	cout << recorded_steps;
	// rezultatul
	print_result(start_node, finish_node, solution, solution_count, costs);
}

/**
 * @brief Implementare a algoritmului de cautare A*
 * @param start_node punct de plecare (index din city_names, definita global)
 * @param finish_node punct de sosire (idem)
 * @param cost valoarea returnata
 */
void astar_search(int start_node, int finish_node, int& cost) {
	int frontier[count] = {start_node};
	int frontier_count = 1;
	bool explored[count] = {false};
	explored[start_node] = true;
	int ascendants[count] = {0};
	bool found = false;
	int costs[count] = {0};
	int step = 1;
	string recorded_steps;

	while (!found && frontier_count > 0) {
		// primul element din frontiera devine nodul curent
		int current_node = frontier[0];
		int current_cost = costs[current_node];

		// inregistreza pasii
		if (display_steps) {
			get_steps(recorded_steps, step, frontier, costs, frontier_count);
		}
		step++;

		// elimina primul element din frontiera (pop)
		// deplaseaza continutul in uz al frontierei cu un element spre stanga
		for (int i = 0; i < frontier_count - 1; i++) {
			frontier[i] = frontier[i + 1];
		}
		frontier_count--;  // actualizeaza numarul de noduri de explorat

		// verifica daca nodul curent este tinta
		if (current_node == finish_node) {
			found = true;
		} else {
			// itereaza in linia din matricea de adiacenta,
			// corespunzatoare nodului curent pentru a gasi nodurile succesoare
			for (int i = 0; i < count; i++) {
				if ((distances[current_node][i] != 0) && !explored[i]) {
					frontier[frontier_count] = i;
					costs[i] = current_cost + distances[current_node][i];
					frontier_count++;
					explored[i] = true;
					ascendants[i] = current_node;
				}
			}

			for (int i = 0; i < frontier_count - 1; i++) {
				for (int j = i + 1; j < frontier_count; j++) {
					if ((costs[frontier[i]] + estimates[frontier[i]]) >
						(costs[frontier[j]] + estimates[frontier[j]])) {
						int temp = frontier[i];
						frontier[i] = frontier[j];
						frontier[j] = temp;
					}
				}
			}
		}
	}

	int solution[count] = {0};
	int solution_count = 0;
	int current_node = finish_node;

	while (current_node != start_node) {
		solution[solution_count] = current_node;
		solution_count++;
		current_node = ascendants[current_node];
	}
	solution[solution_count] = start_node;
	solution_count++;

	cost = costs[finish_node];

	// sectiunea de afisare
	cout << "\n\nCautare A*" << separator;
	// pasii intermediari
	cout << recorded_steps;
	// rezultatul
	print_result(start_node, finish_node, solution, solution_count, costs);
}
#pragma endregion Algorithms

#pragma region Utils
/**
 * @brief Obtine de la utilizator un index valabil si il aloca variabilei
 * primite
 * @param id pointer la variabila care va folosi valoarea introdusa
 */
void get_city_id(int* id) {
	int temp;

	while (true) {
		// FIXME: input de tip 2asd e validat ca 2
		if ((cin >> temp) && (temp >= 0) && (temp < count)) {
			cin.ignore(1000, '\n');	 // 1000 e arbitrar ales
			break;
		}
		cout << "Indexul trebuie sa fie un intreg intre 0 si " << count - 1
			 << "!\nMai incearca: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	*id = temp;
}

/**
 * @brief Afiseaza lista oraselor pentru ca utilizatorul sa le poata selecta
 * dupa id.
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
 * @brief Inregistreaza pasii intermediari in functii, depinde de setarea
 * display_steps
 * @param recorded_steps string in care se acumuleaza inregistrarile
 * @param step numarul pasului din functia apelanta
 * @param frontier lista de noduri de explorat
 * @param nodes lista in care se itereaza
 * @param node_count numarul de elemente afisate din lista
 */
string get_steps(string& recorded_steps, int step, int frontier[], int nodes[],
				 int node_count) {
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
 * @brief Afiseaza rezultatul cautarii
 * @param start_node
 * @param finish_node
 * @param solution lista de rezultate
 * @param solution_count numarul de elemente din lista
 * @param costs lista de costuri
 */
void print_result(int start_node, int finish_node, int solution[],
				  int solution_count, int costs[]) {
	cout << "\nRezultat:\n"
		 << city_names[start_node] << " -> " << city_names[finish_node] << '\n';
	// deruleaza invers path[] pentru a afisa fiecare nod din solutie
	for (int i = solution_count - 1; i >= 0; i--) {
		cout << setw(4) << std::right << solution[i] << ". ";
		cout << setw(15) << std::left << city_names[solution[i]];
		cout << std::right << setw(9) << costs[solution[i]] << " km";
		cout << '\n';
	}
	cout << setw(10) << std::left << "Distanta: " << costs[solution[0]]
		 << " km\n";
}
#pragma endregion Utils