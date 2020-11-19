/**
 * L13. Scrieti un program care sa aplice algoritmul Hill Climbing pentru
 * problema comis-voiajorului enuntata in cursul Caracteristici si Constrangeri
 * (http://inf.ucv.ro/documents/cstoean/c5IA.pdf), la slide-urile 57-61.
 *
 * Se utilizeaza aceeasi metoda de initializare si de perturbare ca la problema
 * aranjarii damelor.
 *
 * Ce se modifica fata de implementarea pentru problema aranjarii damelor:
 * 1. Trebuie citite/introduse numele oraselor.
 * 2. Trebuie citita/introdusa matricea de distante dintre orase. Din aceasta
 * trebuie sa poata gasi distantele intre oricare doua orase.
 * 3. Trebuie modificata functia de evaluare.
 * 4. Evaluarea celei mai bune solutii nu va mai fi zero - cea mai buna solutie
 * trebuie sa intoarca un tur care sa viziteze toate orasele, deci suma
 * kilometrilor nu poate fi nula.
 */
#include <cstdlib>	 //! srand(), rand()
#include <ctime>	 //! time()
#include <iomanip>	 // setw()
#include <iostream>	 // cout, cin

using namespace std;

#pragma region Setup
void print_result(int*, int);
void copy_list(int*, int*, int);
void generate(int*, int);
int evaluate(int*, int);
void perturb(int*, int);

const int iteration_count = 100;
static int evaluate_call_count = 0;

string city_names[] = {"Bucuresti", "Satu Mare",   "Baia Mare",	 "Oradea",
					   "Arad",		"Timisoara",   "Alba Iulia", "Cluj Napoca",
					   "Bistrita",	"Targu Mures", "Sibiu",		 "Brasov",
					   "Pitesti",	"Craiova",	   "Suceava",	 "Piatra Neamt",
					   "Iasi",		"Braila",	   "Tulcea",	 "Constanta"};

const int city_count = sizeof(city_names) / sizeof(city_names[0]);

// matricea distantelor; reformatata automat de editor...
int distances[][city_count] = {
	{0,	  596, 550, 574, 555, 538, 394, 426, 419, 330,
	 282, 161, 126, 248, 436, 349, 406, 213, 278, 225},
	{596, 0,   67,	135, 250, 304, 331, 170, 216, 271,
	 333, 434, 485, 544, 369, 429, 463, 660, 752, 815},
	{550, 67,  0,	183, 298, 352, 303, 146, 148, 219,
	 305, 388, 457, 516, 326, 387, 420, 618, 710, 768},
	{574, 135, 183, 0,	 115, 169, 278, 147, 263, 249,
	 311, 412, 463, 463, 478, 444, 538, 671, 763, 792},
	{555, 250, 298, 115, 0,	  52,  239, 263, 378, 350,
	 273, 415, 429, 394, 593, 531, 646, 674, 766, 780},
	{538, 304, 352, 169, 52,  0,   217, 316, 417, 327,
	 256, 399, 406, 353, 575, 509, 691, 651, 743, 758},
	{394, 331, 303, 278, 239, 217, 0,	160, 200, 116,
	 113, 232, 268, 293, 358, 292, 407, 490, 583, 612},
	{426, 170, 146, 147, 263, 316, 160, 0,	 119, 101,
	 163, 264, 315, 374, 334, 297, 390, 523, 615, 644},
	{419, 216, 148, 263, 378, 417, 200, 119, 0,	  89,
	 200, 257, 352, 411, 214, 247, 308, 486, 578, 638},
	{330, 271, 219, 249, 350, 327, 116, 101, 89,  0,
	 112, 168, 262, 321, 261, 195, 310, 426, 519, 548},
	{282, 333, 305, 311, 273, 256, 113, 163, 200, 112,
	 0,	  142, 155, 236, 358, 289, 441, 401, 493, 507},
	{161, 434, 388, 412, 415, 399, 232, 264, 257, 168,
	 142, 0,   149, 205, 319, 228, 299, 258, 350, 380},
	{126, 485, 457, 463, 429, 406, 268, 315, 352, 262,
	 155, 149, 0,	123, 468, 378, 448, 318, 404, 351},
	{248, 544, 516, 463, 394, 353, 293, 374, 411, 321,
	 236, 205, 123, 0,	 524, 434, 504, 434, 504, 451},
	{436, 369, 326, 478, 593, 575, 358, 334, 214, 261,
	 358, 319, 468, 524, 0,	  122, 144, 341, 433, 520},
	{349, 429, 387, 444, 531, 509, 292, 297, 247, 195,
	 289, 228, 378, 434, 122, 0,   131, 254, 346, 432},
	{406, 463, 420, 538, 646, 691, 407, 390, 308, 310,
	 441, 299, 448, 504, 144, 131, 0,	271, 364, 434},
	{213, 660, 618, 671, 674, 651, 490, 523, 486, 426,
	 401, 258, 318, 434, 341, 254, 271, 0,	 92,  178},
	{278, 752, 710, 763, 766, 743, 583, 615, 578, 519,
	 493, 350, 404, 504, 433, 346, 364, 92,	 0,	  124},
	{225, 815, 768, 792, 780, 758, 612, 644, 638, 548,
	 507, 380, 351, 451, 520, 432, 434, 178, 124, 0}};
string separator = "\n*****************************************\n";
#pragma endregion Setup

/**
 * @brief Inceputul executiei
 */
int main() {
	srand(time(0));

	// valoare-prag initiala
	int benchmark = 3800;

	int eval_best;

	while (true) {
		int* circuit = new int[city_count];
		int* new_circuit = new int[city_count];

		long start = time(0);
		int time_elapsed = 0;

		int eval_initial = 0;
		int eval_new = 0;
		do {
			generate(circuit, city_count);
			eval_initial = evaluate(circuit, city_count);
			copy_list(circuit, new_circuit, city_count);

			for (int i = 0; i < iteration_count; i++) {
				perturb(new_circuit, city_count);
				eval_new = evaluate(new_circuit, city_count);
				if (eval_initial < eval_new) {
					copy_list(circuit, new_circuit, city_count);
					eval_new = eval_initial;
					eval_best = eval_new;
				}

				// if (eval_new < eval_best) {
				// 	eval_best = eval_new;
				// }
			}
		} while (eval_new > benchmark && /* evaluate_call_count <= 3e6 && */
				 (time_elapsed = difftime(time(0), start)) <= 9);

		// ultima evaluare devine noua valoare-prag
		benchmark = eval_best;

		cout << "\n\nCircuitul initial:\n";
		print_result(circuit, city_count);
		cout << "\nDistanta: " << eval_initial << " km";

		cout << "\n\nCircuitul nou:\n";
		print_result(new_circuit, city_count);
		cout << "\nDistanta: " << eval_new << " km";
		cout << "\nTimp de executie: " << time_elapsed << " s";
		cout << "\nApelari ale functiei de evaluare: " << evaluate_call_count;

		cout << separator;

		delete[] circuit;
		delete[] new_circuit;

		evaluate_call_count = 0;

		char answer;
		cout << "Continuam? (y/n) ";
		cin >> answer;
		if (answer != 'y') {
			break;
		}
	}

	return 0;
}

#pragma region Algorithms
/**
 * @brief Calculeaza distanta intr-un circuit dat si o returneaza, folosind
 * algoritmul din curs (C5IA, p. 61)
 * @param circuit
 * @param count
 * @return distanta totala in circuit
 */
int evaluate(int* circuit, int count) {
	// utilizat la afisare
	evaluate_call_count++;

	int distance = 0;
	// insumeaza distantele dintre orasele listei
	for (int i = 1; i < count - 1; i++) {
		// cumuleaza distantele dintre fiecare doua orase vecine din
		// circuit: [0][1], [1][2], ..., [n-2][n-1]
		distance += distances[circuit[i - 1]][circuit[i]];
	}
	// inchide circuitul cu distanta dintre ultimul oras si primul din
	// configuratie: [n-1][0]
	distance += distances[circuit[count - 1]][circuit[0]];
	return distance;
}

/**
 * @brief Schimba intre ele doua dintre elementele unei liste, alese aleatoriu
 * @param circuit
 * @param count
 */
void perturb(int* circuit, int count) {
	// genereaza doi indecsi aleatorii si distincti ai listei
	int i = rand() % count;
	int j = rand() % count;
	while (i == j) {
		j = rand() % count;
	}

	// schimba intre ele elementele ce corespund indecsilor
	int temp = circuit[i];
	circuit[i] = circuit[j];
	circuit[j] = temp;
}

/**
 * @brief Genereaza o lista cu primele numere naturale nenule, pana la un numar
 * dat (inclusiv), distincte intre ele si permutate aleatoriu
 * @param circuit pointer la lista creata in avans
 * @param count numarul pana la care se genereaza elementele listei
 */
void generate(int* circuit, int count) {
	// genereaza o lista cu numere consecutive
	int i;
	for (i = 0; i < count; i++) {
		circuit[i] = i;
	}

	// amesteca numerele din lista
	i = count - 1;
	while (i > 0) {
		int j = rand() % (i + 1);
		int temp = circuit[i];
		circuit[i] = circuit[j];
		circuit[j] = temp;
		i--;
	}
}
#pragma endregion Algorithms

#pragma region Utils
/**
 * @brief Afiseaza orasele in linii de cel mult 5 elemente
 * @param list
 * @param list_size
 */
void print_result(int* list, int list_size) {
	for (int i = 0; i < list_size; i++) {
		cout << setw(4) << std::right << list[i] << ". ";
		cout << setw(15) << std::left << city_names[list[i]];
		if (((i + 1) % 5 == 0) && (i != list_size - 1)) {
			cout << '\n';
		}
	}
}

/**
 * @brief Copiaza o lista peste o alta lista cu aceeasi dimensiune (nu
 * testeaza!)
 * @param source_list pointer la lista care se copiaza
 * @param destination_list pointer la lista in care se copiaza
 * @param list_size dimensiunea listelor
 */
void copy_list(int* source_list, int* destination_list, int list_size) {
	for (int i = 0; i < list_size; i++) {
		destination_list[i] = source_list[i];
	}
}
#pragma endregion Utils