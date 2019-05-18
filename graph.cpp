#include <iostream>
#include <vector>
#include "string.h"

int get_index(char label, char* label_array){
	for (int i = 0; i < 20; i++)
		if(label == label_array[i])
			return i;
	return 0;
}
bool has(char label, char* label_array){
	for(int i = 0; i < 20; i++)
		if(label == label_array[i])
			return true;
	return false;
}

void print_matrix(int length_matrix[20][20], char* label_array){
	int vertices = 20;
	std::cout << "  ";
	for (int i = 0; i < 20; i++){
		if(label_array[i] == 0){
			vertices = i;
			break;
		}
		std::cout << " " << label_array[i];
	}
	std::cout << std::endl;
	for (int x = 0; x < vertices; x++){
		std::cout << " " << label_array[x];
		for (int y = 0; y < vertices; y++){
			std::cout << " " << length_matrix[x][y];
		}
		std::cout << std::endl;
	}
	std::cout << "------";
	for(int i = 0; i <= vertices; i++)
		std::cout << "--";
	std::cout << std::endl;
}
void ini_values(int length_matrix[20][20], char* label_array){
	for(int x = 0; x < 20; x++){
		label_array[x] = 0;
		for(int y = 0; y < 20; y++){
			length_matrix[x][y] = 0;
		}
	}
}
void remove_vertex(char label, char* label_array, int length_matrix[20][20]){
	int li = get_index(label, label_array);

	label_array[li] = 0;
	for (int i = 0; i < 20; i++){
		length_matrix[i][li] = 0;
		length_matrix[li][i] = 0;
	}

	for (int i = li; i < 20; i++){
		if(i != 19){
			label_array[i] = label_array[i + 1];
			label_array[i + 1] = 0;

			for(int x = 0; x < 20; x++){
				length_matrix[i][x] = length_matrix[i + 1][x];
				length_matrix[i + 1][x] = 0;

				length_matrix[x][i] = length_matrix[x][i + 1];
				length_matrix[x][i + 1] = 0;
			}
		}
	}
}
void remove_edge(char f, char s, char* label_array, int length_matrix[20][20]){
	int fi = get_index(f, label_array);
	int si = get_index(s, label_array);
	length_matrix[fi][si] = 0;
	length_matrix[si][fi] = 0;
}
bool add_vertex(char label, char* label_array){
	for(int i = 0; i < 20; i++)
		if (label_array[i] == 0){
			label_array[i] = label;
			return true;
		}
	return false;
}
void add_edge(char f, char s, int weight, char* label_array, int length_matrix[20][20]){
	int fi = get_index(f, label_array);
	int si = get_index(s, label_array);

	length_matrix[fi][si] = weight;
	length_matrix[si][fi] = weight;
}

int main(){
	system("clear");
	int length_matrix[20][20];
	char label_array[20];
	ini_values(length_matrix, label_array);

	char* input = new char[20];
	while(true){
		std::cout << "Enter Command(print, add vertex, add edge, remove vertex, remove edge, quit):" << std::endl;
		std::cin.get(input, 20);
		std::cin.clear();
		std::cin.ignore(100, '\n');

		for(int i = 0; i < strlen(input); i++)
			input[i] = tolower(input[i]);

		if(strcmp(input, "print") == 0){
			system("clear");
			print_matrix(length_matrix, label_array);
		}else if(strcmp(input, "add vertex") == 0){
			char label;
			std::cout << "Label: ";
			std::cin >> label;
			std::cin.clear();
			std::cin.ignore(100, '\n');

			if(!has(toupper(label), label_array))
				std::cout << "Duplicate Vertex" << std::endl;
			else if(!add_vertex(toupper(label), label_array))
				std::cout << "Max Vertices" << std::endl;
			else{
				system("clear");
				print_matrix(length_matrix, label_array);
			}
		}else if(strcmp(input, "add edge") == 0){
			system("clear");
			print_matrix(length_matrix, label_array);
			char f;
			char s;
			int weight;

			std::cout << "First Vertex: ";
			std::cin >> f;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			
			std::cout << "Second Vertex: ";
			std::cin >> s;
			std::cin.clear();
			std::cin.ignore(100, '\n');

			std::cout << "Weight: ";
			std::cin >> weight;
			std::cin.clear();
			std::cin.ignore(100, '\n');

			add_edge(toupper(f), toupper(s), weight, label_array, length_matrix);
			system("clear");
			print_matrix(length_matrix, label_array);
		}else if(strcmp(input, "remove vertex") == 0){
			system("clear");
			print_matrix(length_matrix, label_array);
			char label;
			std::cout << "Label: ";
			std::cin >> label;
			std::cin.clear();
			std::cin.ignore(100, '\n');

			remove_vertex(toupper(label), label_array, length_matrix);
			system("clear");
			print_matrix(length_matrix, label_array);
		}else if(strcmp(input, "remove edge") == 0){
			system("clear");
			print_matrix(length_matrix, label_array);
			char f;
			char s;

			std::cout << "First Vertex: ";
			std::cin >> f;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			
			std::cout << "Second Vertex: ";
			std::cin >> s;
			std::cin.clear();
			std::cin.ignore(100, '\n');

			remove_edge(toupper(f), toupper(s), label_array, length_matrix);
			system("clear");
			print_matrix(length_matrix, label_array);
		}else if(strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0){
			return 0;
		}else{
			std::cout << "Unrecognized Command" << std::endl;
		}
	}

	return 0;
}