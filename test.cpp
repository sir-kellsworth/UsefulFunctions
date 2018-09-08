/**********************************************************************
 *
 * Filename:    test.cpp
 * 
 * Description: Examples of using the useful functions. Particuarly the
 * 			sorting and searching methods
 *
 * Notes:
 *
 * 
 * Copyright (c) 2018 by Kelly Klein.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#include <useful.h>
#include <vector>
#include <memory>
#include <iostream>
#include <chrono>

void splitTest(){
	std::string test = "hello world how do you do";
	std::vector<std::string> out = useful::split(test,' ');
	for(int i = 0; i < out.size(); i++){
		std::cout << out[i] << std::endl;
	}
}

void combinationsTest(){
	std::vector<double> test({1,4,5,7,3,9,2});
	std::cout << "before" << std::endl;
	for(int i = 0; i < test.size(); i++){
		std::cout << test[i] << " ";
	}
	std::cout << std::endl;

	useful::mergeSort(test);
	useful::reverse(test);

	std::cout << "after" << std::endl;
	for(int i = 0; i < test.size(); i++){
		std::cout << test[i] << " ";
	}
	std::cout << std::endl;

	std::cout << useful::combination(10,4) << std::endl;
}

/*void logTest(){
	logger::LOG_I("TEST","logged that brah");
	logger::LOG_E("ERROR TEST","some shit brah");
}*/

void printArray(std::vector<int> array){
	for(int i = 0; i < array.size(); i++){
		std::cout << array[i] << std::endl;
	}
}

void sortTest(){
	srand(time(NULL));
	std::vector<double> array;
	int size = 5000000;
	double MAX = 5000000;
	double MIN = 0;
	array.resize(size);
	for(int sort = 0; sort < 4; sort++){
		switch(sort){
		case 0:
			std::cout << "starting quick sort" << std::endl;
		break;
		case 1:
			std::cout << "starting heap sort" << std::endl;
		break;
		case 2:
			std::cout << "starting merge sort" << std::endl;
		break;
		case 3:
			std::cout << "starting shell sort" << std::endl;
		break;
		};
		double average = 0;
		for(int epoch = 0; epoch < 10; epoch++){
			for(int i = 0; i < size; i++){
				array[i] = (MAX - MIN) * ((double)rand() / RAND_MAX) - ((MAX-MIN)/2);
			}

			std::chrono::high_resolution_clock::time_point start;
			std::chrono::high_resolution_clock::time_point end;
			switch(sort){
			case 0:
				//quick sort
				start = std::chrono::high_resolution_clock::now();
				useful::quickSort(array);
				end = std::chrono::high_resolution_clock::now();
			break;
			case 1:
				//heap sort
				start = std::chrono::high_resolution_clock::now();
				useful::heapSort(array);
				end = std::chrono::high_resolution_clock::now();
			break;
			case 2:
				//merge sort
				start = std::chrono::high_resolution_clock::now();
				useful::mergeSort(array);
				end = std::chrono::high_resolution_clock::now();
			break;
			case 3:
				//shell sort
				start = std::chrono::high_resolution_clock::now();
				useful::shellSort(array);
				end = std::chrono::high_resolution_clock::now();
			break;
			};
			std::chrono::duration<double, std::milli> time_span = end - start;
			average += time_span.count();
		}

		average /= 10;
		std::cout << "average sort time: " << average << " milliseconds" << std::endl;

	}
}

void searchTest(){
	srand(time(NULL));
	std::vector<double> array;
	int size = 5000000;
	double MAX = 5000000;
	double MIN = 0;
	array.resize(size);
	for(int search = 0; search < 3; search++){
		switch(search){
		case 0:
			std::cout << "starting linear search" << std::endl;
		break;
		case 1:
			std::cout << "starting binary search" << std::endl;
		break;
		case 2:
			std::cout << "starting jump search" << std::endl;
		break;
		};
		double average = 0;
		for(int epoch = 0; epoch < 10; epoch++){
			for(int i = 0; i < size; i++){
				array[i] = (MAX - MIN) * ((double)rand() / RAND_MAX) - ((MAX-MIN)/2);
			}
			double wanted = array[(MAX - MIN) * ((double)rand() / RAND_MAX)];
			useful::quickSort(array);

			std::chrono::high_resolution_clock::time_point start;
			std::chrono::high_resolution_clock::time_point end;
			switch(search){
			case 0:
				start = std::chrono::high_resolution_clock::now();
				useful::linearSearch(array,wanted);
				end = std::chrono::high_resolution_clock::now();
			break;
			case 1:
				start = std::chrono::high_resolution_clock::now();
				useful::binarySearch(array,wanted);
				end = std::chrono::high_resolution_clock::now();
			break;
			case 2:
				start = std::chrono::high_resolution_clock::now();
				useful::jumpSearch(array,wanted);
				end = std::chrono::high_resolution_clock::now();
			break;
			};
			std::chrono::duration<double, std::milli> time_span = end - start;
			average += time_span.count();
		}
		average /= 10;
		std::cout << "average sort time: " << average << " milliseconds" << std::endl;
	}
}

void testIndividual(){
	std::vector<int> array;
	int MAX = 50;
	int MIN = 0;
	array.resize(50);
	for(int i = 0; i < 50; i++){
		//array[i] = (MAX - MIN) * (rand() / RAND_MAX);// - ((MAX-MIN)/2);
		array[i] = rand() % (MAX - MIN);
	}
	logger::LOG_I("Array Error:","unsorted array:",true);
	printArray(array);
	useful::mergeSort(array);
	logger::LOG_I("Array Error:","sorted array:",true);
	printArray(array);
}

int main(int argc,char *argv[]){
	testIndividual();

	return 0;
}
