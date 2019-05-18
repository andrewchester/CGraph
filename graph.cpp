#include <iostream>
#include <vector>
#include "string.h"

int get_index(char* label, char** label_array){
	for (int i = 0; i < sizeof(label_array); i++)
		if(strcmp(label, label_array[i]) == 0)
			return i;
	return 0;
}
void print_matrix(int length_matrix[20][20], char* label_array[20]){
	int vertices;
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
}

int main(){
	int length_matrix[20][20];
	char* labels[20];
	for (int i = 0; i < 20; i++) labels[i] = 0;

	labels[0] = (char*)("A");
	labels[1] = (char*)("B");
	labels[2] = (char*)("C");

	print_matrix(length_matrix, labels);

	return 0;
}