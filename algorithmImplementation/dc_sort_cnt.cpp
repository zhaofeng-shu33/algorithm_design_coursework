/*** 
 created on 24/10/2017 
 author: zhaofeng-shu33
 license: Apache Version 2.0
***/
#include<string>
#include<iostream>
#include<cassert>

template <class T>
void _dc_sort(T* array_to_sort, T* additional_array_needed,int start_ptr,int end_ptr) {
	//class T should overload '<' operator
	if (end_ptr == start_ptr + 1)
		return;
	assert(end_ptr != start_ptr);
	int middle_ptr = (start_ptr + end_ptr) / 2;
	_dc_sort(array_to_sort, additional_array_needed, start_ptr, middle_ptr);
	_dc_sort(array_to_sort, additional_array_needed, middle_ptr, end_ptr);
	int front_array_index = start_ptr,back_array_index= middle_ptr,output_array_index= start_ptr;
	while (output_array_index < end_ptr) {
		if (back_array_index==end_ptr || (front_array_index<middle_ptr && array_to_sort[front_array_index] < array_to_sort[back_array_index]) ) {
			additional_array_needed[output_array_index] = array_to_sort[front_array_index];
			front_array_index++;
		}
		else {
			additional_array_needed[output_array_index] = array_to_sort[back_array_index];
			back_array_index++;
		}
		output_array_index++;
	}
	//copy additional_array_needed to array_to_sort
	while (start_ptr < end_ptr){
		array_to_sort[start_ptr] = additional_array_needed[start_ptr];
		start_ptr++;
	}
}

template <class T>
void dc_sort(T* array_to_sort, int array_len) {
	T* additional_array_needed = new T[array_len];
	_dc_sort(array_to_sort, additional_array_needed, 0, array_len);
	delete[] additional_array_needed;
}


template <class T>
int _inversion_count(T* array_to_count, T* additional_array_needed, int start_ptr, int end_ptr) {
	//class T should overload '<' operator
	if (end_ptr == start_ptr + 1)
		return 0;
	assert(end_ptr != start_ptr);
	int middle_ptr = (start_ptr + end_ptr) / 2;
	int inversion_front_count, inversion_back_count;
	inversion_front_count=_inversion_count(array_to_count, additional_array_needed, start_ptr, middle_ptr);
	inversion_back_count=_inversion_count(array_to_count, additional_array_needed, middle_ptr, end_ptr);
	int front_array_index = start_ptr, back_array_index = middle_ptr, output_array_index = start_ptr;
	int inversion_front_and_back_count=0;
	while (output_array_index < end_ptr) {
		if (back_array_index == end_ptr || (front_array_index<middle_ptr && array_to_count[front_array_index] < array_to_count[back_array_index])) {
			additional_array_needed[output_array_index] = array_to_count[front_array_index];
			front_array_index++;
		}
		else {
			inversion_front_and_back_count += (middle_ptr- front_array_index);
			additional_array_needed[output_array_index] = array_to_count[back_array_index];
			back_array_index++;
		}
		output_array_index++;
	}
	//copy additional_array_needed to array_to_count
	while (start_ptr < end_ptr) {
		array_to_count[start_ptr] = additional_array_needed[start_ptr];
		start_ptr++;
	}
	return (inversion_front_count + inversion_back_count + inversion_front_and_back_count);
}

template <class T>
int inversion_count(T* array_to_count, int array_len) {
	T* additional_array_needed = new T[array_len];
	int total_inversion_count;
	total_inversion_count=_inversion_count(array_to_count, additional_array_needed, 0, array_len);
	delete[] additional_array_needed;
	return total_inversion_count;
}




int main() {
	char a[]="ALGORITHMS";
	dc_sort(a, strlen(a));
	std::cout << a;
	int b[] = {1,5,4,8,10,2,6,9,12,11,3,7};
	std::cout<<std::endl<<inversion_count(b, sizeof(b)/sizeof(int));
	return 0;
}
