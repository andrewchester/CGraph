#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "string.h"
 
//All functions assume static length of 20 for all arrays

//Returns index of a label
int get_index (char label, char* label_array) {
	for  (int i = 0; i < 20; i++)
		if (label == label_array[i])
			return i;
	return 0;
}
//Retuns a boolean value, true if the label exists in the array, and false if it doesn't
bool has (char label, char* label_array) {
	for (int i = 0; i < 20; i++) {
		if (label == label_array[i])
			return true;
	}
	return false;
}
//Prints out the matrix
void print_matrix (int matrix[20][20], char* label_array) {
	int vertices = 20; //Initialize the number of vertices as 20
	std::cout << "  ";
	for  (int i = 0; i < 20; i++) {
		if (label_array[i] == 0) {
			vertices = i; //Sets the number of vertices when the end of the label_array is reached
			break;
		}
		std::cout << " " << label_array[i];
	}
	std::cout << std::endl;
	//Loop over the number of vertices and print out the label and row
	for  (int x = 0; x < vertices; x++) {
		std::cout << " " << label_array[x];
		for  (int y = 0; y < vertices; y++) {
			std::cout << " " << matrix[y][x];
		}
		std::cout << std::endl;
	}
	//Print out a ------ below the matrix
	std::cout << "------";
	for (int i = 0; i <= vertices; i++)
		std::cout << "--";
	std::cout << std::endl;
}
//Initialize all values for 2 arrays, fills with 0's
void ini_values (int matrix[20][20], char* label_array) {
	for (int x = 0; x < 20; x++) {
		label_array[x] = 0;
		for (int y = 0; y < 20; y++) {
			matrix[x][y] = 0;
		}
	}
}
//Removes a vertex from the matrix
void remove_vertex (char label, char* label_array, int matrix[20][20]) {
	int li = get_index (label, label_array); //Index of label

	//fills the row and column of a vertex with 0's
	label_array[li] = 0;
	for  (int i = 0; i < 20; i++) {
		matrix[i][li] = 0;
		matrix[li][i] = 0;
	}
	//Shifts the empty 0 row and column to the edge
	for  (int i = li; i < 20; i++) {
		if (i != 19) {
			//Swap i and i + 1 values in label_array
			label_array[i] = label_array[i + 1];
			label_array[i + 1] = 0;
			
			//Swap all values in i and i + 1 row and column
			for (int x = 0; x < 20; x++) {
				matrix[i][x] = matrix[i + 1][x];
				matrix[i + 1][x] = 0;

				matrix[x][i] = matrix[x][i + 1];
				matrix[x][i + 1] = 0;
			}
		}
	}
}
//Removes an edge, just makes it 0
void remove_edge (char f, char s, char* label_array, int matrix[20][20]) {
	int fi = get_index (f, label_array);
	int si = get_index (s, label_array);
	matrix[fi][si] = 0;
}
//Adds a vertex, returns a true/false value if it succeeded or not, will fail if max vertices reached
bool add_vertex (char label, char* label_array) {
	for (int i = 0; i < 20; i++)
		if  (label_array[i] == 0) {
			label_array[i] = label;
			return true;
		}
	return false;
}
//Adds an edge based on a passed in weight
void add_edge (char f, char s, int weight, char* label_array, int matrix[20][20]) {
	int fi = get_index (f, label_array);
	int si = get_index (s, label_array);

	matrix[fi][si] = weight;
}

char* get_adjacent (char label, int matrix[20][20], char* label_array, char* exclude) {
	std::vector<char> adjacent;
	int li = get_index (label, label_array);

	for  (int y = 0; y < 20; y++)
		if (matrix[li][y] != 0 && !has (label_array[y], exclude))
			adjacent.push_back (label_array[y]);

	if(adjacent.size() == 0)
		return 0;

	char* adjacency_list = new char[adjacent.size ()];
	for (unsigned int i = 0; i < adjacent.size (); i++)
		adjacency_list[i] = adjacent.at (i);
	return adjacency_list;
}
int getcost (char f, char s, int matrix[20][20], char* label_array) {
	return matrix[get_index (f, label_array)][get_index (s, label_array)];
}

std::vector<std::pair<char*, int> >* find (char f, char s, int matrix[20][20], char* label_array) {
	std::vector<char> unvisited = std::vector<char>();
	std::vector<std::pair<char*, int> > pairs = std::vector<std::pair<char*, int> >();
	for  (int i = 0; i < strlen (label_array); i++)
		if (label_array[i] != f)
			unvisited.push_back (label_array[i]);
	char* pch = new char[2];
	pch[0] = toupper(f); pch[1] = 0;
	pairs.push_back (std::make_pair (pch, 0));
	std::cout << pairs[0].first << std::endl;
	char* neighbors;
	int temp;
	bool found = false;
	while (unvisited.size () != 0) {
		std::vector<std::pair<char*, int> >::iterator it;
		for (it = pairs.begin(); it != pairs.end(); ++it) {
			char* c = (*it).first;
			neighbors = get_adjacent (c[strlen(c) - 1], matrix, label_array, c);
			std::cout << "neighbors for " << c << ": " << neighbors << std::endl;
			temp = (*it).second;
			if (neighbors == 0 && c[strlen (c) - 1] != s) {
				//pairs.erase(it);
				continue;
			}
			for (int x = 0; x < strlen (neighbors); x++) {
				std::vector<std::pair<char*, int> >::iterator j;
				for (j = pairs.begin(); j != pairs.end(); ++j) {
					if (strcmp(c, (*j).first) == 0) {
						found = true;
						strcat((*j).first, &neighbors[x]);
						(*j).second += getcost (c[strlen (c) - 1], neighbors[x], matrix, label_array);
					}
				}
				if (!found) {
					strcat(c, (char*)neighbors[x]);
					pairs.push_back (std::make_pair (c, temp + getcost (c[strlen (c) - 1], neighbors[x], matrix, label_array)));	
				}	
				unvisited.erase (std::find (unvisited.begin (), unvisited.end (), neighbors[x]));
			}
		}
	}
	std::vector<std::pair<char*, int> >* paths = new std::vector<std::pair<char*, int> > ();
	for (std::vector<std::pair<char*, int> >::iterator p; p != pairs.end (); ++p) {
		if (p->first[strlen (p->first) - 1] == s) {
			paths->push_back (*p);
		}
	}
	return paths;
}

int main () {
	system ("clear");
	//Both arrays static at 20
	int matrix[20][20];
	char label_array[20];
	ini_values (matrix, label_array); //Fills both with 0's

	char* input = new char[20];
	while (true) {
		std::cout << "Enter Command (print, add vertex, add edge, remove vertex, remove edge, find, quit):" << std::endl;
		std::cin.get (input, 20);
		std::cin.clear ();
		std::cin.ignore (100, '\n');

		for (int i = 0; i < strlen (input); i++)
			input[i] = tolower (input[i]);

		if (strcmp (input, "print") == 0) {
			system ("clear");
			print_matrix (matrix, label_array);
		} else if (strcmp (input, "add vertex") == 0) {
			char label;
			std::cout << "Label: ";
			std::cin >> label;
			std::cin.clear ();
			std::cin.ignore (100, '\n');

			if (has (toupper (label), label_array)) //Make sure there aren't duplicates
				std::cout << "Duplicate Vertex" << std::endl;
			else if (!add_vertex (toupper (label), label_array)) //Try to add, if it fails, then it's full
				std::cout << "Max Vertices" << std::endl;
			else{ //Default case
				system ("clear");
				print_matrix (matrix, label_array);
			}
		} else if (strcmp (input, "add edge") == 0) {
			system ("clear");
			print_matrix (matrix, label_array);
			char f;
			char s;
			int weight;

			std::cout << "First Vertex: ";
			std::cin >> f;
			std::cin.clear ();
			std::cin.ignore (100, '\n');
			
			std::cout << "Second Vertex: ";
			std::cin >> s;
			std::cin.clear ();
			std::cin.ignore (100, '\n');

			std::cout << "Weight: ";
			std::cin >> weight;
			std::cin.clear ();
			std::cin.ignore (100, '\n');

			add_edge (toupper (f), toupper (s), weight, label_array, matrix); 
			system ("clear");
			print_matrix (matrix, label_array);
		} else if (strcmp (input, "remove vertex") == 0) {
			system ("clear");
			print_matrix (matrix, label_array);
			char label;
			std::cout << "Label: ";
			std::cin >> label;
			std::cin.clear ();
			std::cin.ignore (100, '\n');

			remove_vertex (toupper (label), label_array, matrix);
			system ("clear");
			print_matrix (matrix, label_array);
		} else if (strcmp (input, "remove edge") == 0) {
			system ("clear");
			print_matrix (matrix, label_array);
			char f;
			char s;

			std::cout << "First Vertex: ";
			std::cin >> f;
			std::cin.clear ();
			std::cin.ignore (100, '\n');
			
			std::cout << "Second Vertex: ";
			std::cin >> s;
			std::cin.clear ();
			std::cin.ignore (100, '\n');

			remove_edge (toupper (f), toupper (s), label_array, matrix);
			system ("clear");
			print_matrix (matrix, label_array);
		} else if (strcmp (input, "find") == 0) {
			system ("clear");
			print_matrix (matrix, label_array);
			char f;
			char s;

			std::cout << "First Vertex: ";
			std::cin >> f;
			std::cin.clear ();
			std::cin.ignore (100, '\n');
			
			std::cout << "Second Vertex: ";
			std::cin >> s;
			std::cin.clear ();
			std::cin.ignore (100, '\n');

			system ("clear");
			print_matrix (matrix, label_array);
			std::vector<std::pair<char*, int> >* paths = find (f, s, matrix, label_array);
			std::cout << "Possible paths: " << std::endl;
			for (std::vector<std::pair<char*, int> >::iterator p; p != paths->end (); ++p)
				std::cout << p->first << ", " << p->second << std::endl;
		} else if (strcmp (input, "exit") == 0 || strcmp (input, "quit") == 0) {
			return 0;
		} else {
			std::cout << "Unrecognized Command" << std::endl;
		}
	}

	return 0;
}