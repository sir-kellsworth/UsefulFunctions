/**********************************************************************
 *
 * Filename:    useful.cpp
 * 
 * Description: Description of useful functions
 *
 * Notes: Quite a few of the functions are template functions and are defined here
 *
 * 
 * Copyright (c) 2018 by Kelly Klein.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#ifndef USEFUL_H
#define USEFUL_H

#include <vector>
#include <iostream>
#include <string>

namespace useful{

//sort algorithms
template <class T>
void merge(std::vector<T>& array, std::vector<T>& array1, std::vector<T>& array2);
template <class T>
void mergeSort(std::vector<T>& array);

template <class T>
void quickSort(std::vector<T> &data);
template <class T>
void quickSort_partial(std::vector<T> &data,int l,int r);

template <class T>
void heapSort(std::vector<T> &data);
template <class T>
void heapify(std::vector<T> &data,int n,int i);

template <class T>
void shellSort(std::vector<T> &data);

template <class T>
void swap(T *a,T *b);
template <class T>
void reverse(std::vector<T>& array);

//search algorithms
template <class T>
int linearSearch(std::vector<T> &array, T &wanted);
template <class T>
int binarySearch(std::vector<T> &array, T &wanted);
template <class T>
int jumpSearch(std::vector<T> &array, T &wanted);

unsigned long long factorial(int n);
unsigned long combination(int n,int k);
std::vector<std::string> split(std::string &str,char dil);

}

//template definitions

//recursive merge function
template <typename T>
void useful::merge(std::vector<T>& array, std::vector<T>& array1, std::vector<T>& array2) {
	array.clear();

	int i = 0;
	int j = 0;
	int k = 0;
	for( i = 0, j = 0, k = 0; i < array1.size() && j < array2.size(); k++){
		if(array1.at(i) <= array2.at(j)){
			array.push_back(array1[i]);
			i++;
		}else if(array1.at(i) > array2[j]){
			array.push_back(array2[j]);
			j++;
		}
		k++;
	}

	while(i < array1.size()){
		array.push_back(array1[i]);
		i++;
	}

	while(j < array2.size()){
		array.push_back(array2[j]);
		j++;
	}
}

//actual function to call
template <class T>
void useful::mergeSort(std::vector<T>& array) {
    if (array.size() > 1){
        std::vector<T> array1(array.begin(), array.begin() + array.size() / 2);
        mergeSort(array1);
        std::vector<T> array2(array.begin() + array.size() / 2, array.end());
        mergeSort(array2);
        merge(array, array1, array2);
    }
}

template <class T>
void useful::reverse(std::vector<T> &array){
	std::vector<T> ret;
	for(int i = array.size()-1; i >= 0; i--){
		ret.push_back(array[i]);
	}
	array = ret;
}

//fucntion to call
template <class T>
void useful::quickSort(std::vector<T> &data){
	quickSort_partial(data,0,data.size()-1);
}

//recursive function
template <class T>
void useful::quickSort_partial(std::vector<T> &data,int l,int r){
	if (l >= r){
		return;
	}

	T pivot = data[r];//data[(r-l)/2];
	int cnt = l;

	for(int i = l; i <= r; i++){
		if(data[i] <= pivot){
			swap(&data[cnt],&data[i]);
			cnt++;
		}
	}

	quickSort_partial(data,l,cnt-2);
	quickSort_partial(data,cnt,r);	
}

//function to call
template <class T>
void useful::heapSort(std::vector<T> &data){
	for(int i = data.size() / 2 - 1; i >= 0; i--){
		heapify(data,data.size(),i);
	}

	for(int i = data.size()-1; i >= 0; i--){
		swap(&data[0],&data[i]);

		heapify(data,i,0);
	}
}

//recursive function
template <class T>
void useful::heapify(std::vector<T> &data,int n,int i){
	int largest = i;
	int l = 2*i + 1;
	int r = 2*i + 2;

	if(l < n && data[l] > data[largest]){
		largest = l;
	}

	if(r < n && data[r] > data[largest]){
		largest = r;
	}

	if(largest != i){
		swap(&data[i],&data[largest]);
		heapify(data,n,largest);
	}
}

/*
	sorts by starting at a large interval like the first, middle and last elements
	and sorts them. Then it decreases the interval by one and sorts the elements.
	Continues until entire array is sorted
*/
template <class T>
void useful::shellSort(std::vector<T> &data){
	for(int interval = data.size()/2; interval > 0; interval/=2){
		for(int i = interval; i < data.size(); i++){
			for(int j = i-interval; j >= 0 && data[j] > data[j+interval]; j-=interval){
				swap(&data[j],&data[j+interval]);
			}
		}
	}
}

//search algorithms
template <class T>
int useful::linearSearch(std::vector<T> &array, T &wanted){
	for(int i = 0; i < array.size(); i++){
		if(array[i] == wanted){
			return i;
		}
	}

	return -1;
}

/*
	searches the array by starts at the middle then adjusts either the left side
	or the right side depending on if it the wanted element is above or below the
	middle element.
*/
template <class T>
int useful::binarySearch(std::vector<T> &array, T &wanted){
	int r = array.size()-1;
	int l = 0;

	while(r >= l){
		int mid = l + (r - l)/2;

		if(array[mid] == wanted){
			return mid;
		}

		if(array[mid] > wanted){
			r = mid-1;
		}

		if(array[mid] < wanted){
			l = mid+1;
		}
	}

	return -1;
}

/*
	best case is, the wanted element is the first element. If not, then it checks
	each element by 'jumping' or skipping by 4 elements, then 3 elements and so on until it finds it
*/
template <class T>
int useful::jumpSearch(std::vector<T> &array, T &wanted){
	if(wanted == array[0]){
		return 0;
	}

	for(int i = 4; i < array.size(); i+=4){
		if(wanted == array[i]){
			return i;
		}

		if(wanted < array[i]){
			for(int j = i-3; j < i; j++){
				if(array[j] == wanted){
					return j;
				}
			}
		}
	}
}

/*
	super awesome and totally origional swap function used by a lot other functions
*/
template <class T>
void useful::swap(T *a,T *b){
	T tmp = *b;
	*b = *a;
	*a = tmp;
}

namespace logger{

void LOG_I(std::string tag,std::string message,bool log = false);
void LOG_W(std::string tag,std::string message,bool log = false);
void LOG_E(std::string tag,std::string message,bool log = false);
}


#endif
