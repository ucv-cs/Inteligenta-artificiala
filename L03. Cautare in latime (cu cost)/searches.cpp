/**
 * L03. Cautare in latime (cost adaugat)
 * Folosind modelul de calcul al costului de la radacina la nodul curent din
 * exemplul cautarii cu cost uniform, adaugati costul la cautarea in latime.
 * Faceti acest lucru pentru harta obisnuita de la curs (am atasat si aici
 * fisierul cu harta). Va rog asadar sa afisati la ruta gasita de la cautarea in
 * latime si costul drumului gasit. Ne va ajuta sa putem compara eficienta
 * algoritmilor.
 *
 * De altfel, va trebui sa adaugam costurile pentru toti algoritmii de cautare
 * in vederea afisarii numarului de km pentru ruta finala.
 */
#include <iomanip>
#include <iostream>
using namespace std;

string city_names[] = {"Arad",			 "Zerind",	"Oradea",	"Timisoara",
					   "Lugoj",			 "Mehadia", "Drobeta",	"Craiova",
					   "Ramnicu Valcea", "Sibiu",	"Fagaras",	"Pitesti",
					   "Bucuresti",		 "Giurgiu", "Urziceni", "Harsova",
					   "Eforie",		 "Vaslui",	"Iasi",		"Neamt"};
const int count = sizeof(city_names) / sizeof(city_names[0]);
// matricea de adiacenta
int matrix[][count] = {
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
string separator = "\n********************************\n";

/**
 @brief Implementare a algoritmului de cautare in latime (BFS - breadth-first
 search); matrix este matricea de adiacenta folosita (definita global,
 pentru simplitate)
 @param start punct de plecare (index din city_names, definita global)
 @param finish punct de sosire (index din city_names, definita global)
*/
void breadth_first_search(int start_node, int finish_node) {
	int frontier[count] = {start_node};	 // noduri de explorat
	int node_count = 1;					 // numar de noduri de explorat
	bool explored[count] = {false};		 // noduri explorate
	explored[start_node] = true;		 // marcheaza start ca explorat
	int parent_nodes[count] = {0};		 // noduri-parinte
	bool found = false;
	int cost[count] = {0};

	while (!found && node_count > 0) {
		// primul element din frontiera devine nodul curent
		int current_node = frontier[0];
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
				// nodurile succesoare neexplorate sunt adaugate la frontiera
				if (matrix[current_node][i] != 0 && !explored[i]) {
					frontier[node_count] = i;  // evitam frontier[node_count++]
					// (si alte expresii similare) pentru ca poate duce la erori
					// de intelegere a codului
					node_count++;  // actualizeaza numarul de noduri de explorat
					explored[i] = true;	 // marcheaza nodul succesor ca explorat
					parent_nodes[i] = current_node;
					cost[i] = cost[current_node] + matrix[current_node][i];
				}
			}
		}
	}

	int path[count] = {0};	   // solutia
	int path_nodes_count = 0;  // numar de noduri din solutie
	int temp = finish_node;

	// adauga la solutie nodurile-parinte incepand cu ultimul
	while (temp != start_node) {
		path[path_nodes_count] = temp;
		path_nodes_count++;
		temp = parent_nodes[temp];
	}

	// adauga la solutie si primul nod
	path[path_nodes_count] = start_node;
	path_nodes_count++;

	// afiseaza rezultatul cautarii
	cout << "\n\nRezultatul cautarii in latime (Breadth-First Search): "
		 << city_names[start_node] << " -> " << city_names[finish_node] << endl;
	// deruleaza invers path[] pentru a afisa fiecare nod din solutie
	for (int i = path_nodes_count - 1; i >= 0; i--) {
		cout << setw(4) << std::right << path[i] << ". ";
		cout << setw(15) << std::left << city_names[path[i]];
		cout << setw(9) << std::right << "(" << cost[path[i]] << " km)";
		cout << endl;
	}
}

/**
 @brief Implementare a algoritmului de cautare in adancime (DFS - depth-first
 search); matrix este matricea de adiacenta folosita (definita global,
 pentru simplitate)
 @param start punct de plecare (index din city_names, definita global)
 @param finish punct de sosire (index din city_names, definita global)
*/
void depth_first_search(int start_node, int finish_node) {
	int frontier[count] = {start_node};	 // noduri de explorat
	int node_count = 1;					 // numar de noduri de explorat
	bool explored[count] = {false};		 // noduri explorate
	explored[start_node] = true;		 // marcheaza start ca explorat
	int parent_nodes[count] = {0};		 // noduri-parinte
	bool found = false;
	int cost[count] = {0};

	while (!found && node_count > 0) {
		// primul element din frontiera devine nodul curent
		int current_node = frontier[0];
		// elimina primul element din frontiera (pop)
		// deplaseaza continutul in uz al frontierei cu un element spre stanga
		for (int i = 0; i < count; i++) {
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
				// nodurile succesoare neexplorate sunt adaugate la frontiera
				if (matrix[current_node][i] != 0 && !explored[i]) {
					for (int j = node_count; j > 0; j--) {
						frontier[j] = frontier[j - 1];
					}
					frontier[0] = i;
					node_count++;  // actualizeaza numarul de noduri de explorat
					explored[i] = true;	 // marcheaza nodul succesor ca explorat
					parent_nodes[i] = current_node;
					cost[i] = cost[parent_nodes[i]] + matrix[current_node][i];
				}
			}
		}
	}

	int path[count] = {0};	   // solutia
	int path_nodes_count = 0;  // numar de noduri din solutie
	int temp = finish_node;

	// adauga la solutie nodurile-parinte incepand cu ultimul
	while (temp != start_node) {
		path[path_nodes_count] = temp;
		path_nodes_count++;
		temp = parent_nodes[temp];
	}

	// adauga la solutie si primul nod
	path[path_nodes_count] = start_node;
	path_nodes_count++;

	// afiseaza rezultatul cautarii
	cout << "\n\nRezultatul cautarii in adancime (Depth-First Search): "
		 << city_names[start_node] << " -> " << city_names[finish_node] << endl;
	// deruleaza invers path[] pentru a afisa fiecare nod din solutie
	for (int i = path_nodes_count - 1; i >= 0; i--) {
		cout << setw(4) << std::right << path[i] << ". ";
		cout << setw(15) << std::left << city_names[path[i]];
		cout << setw(9) << std::right << "(" << cost[path[i]] << " km)";
		cout << endl;
	}
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
			cout << endl;
		}
	}
}

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

int main() {
	int start;
	int finish;

	print_problem();

	// input loop pentru a putea incerca diferite combinatii de orase
	while (true) {
		cout << "\n\nScrie id-ul orasului de plecare: ";
		get_city_id(&start);
		cout << "Plecare: " << city_names[start];

		cout << "\n\nScrie id-ul orasului de sosire: ";
		get_city_id(&finish);
		cout << "Sosire: " << city_names[finish];

		breadth_first_search(start, finish);
		depth_first_search(start, finish);

		cout << separator;
	}

	return 0;
}