#include <iostream>
#include "LinkedList.cpp"
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

//CONSTANTS

int ARR_SIZE = 256;
string SHAKESPEARE_FILE = "shakespeare-cleaned5.txt";


//findNewIndex iteratively searches from the item before "catch item", to the head of the list. 
//it searches lexicographically and by the node "counter" value. 
//it returns "nullptr" if it made it to the head and didn't find a suitable value
//or it returns a pointer to a suitable node
Node<string>* findNewIndex(Node<string>* start_node, Node<string>* node){
  Node<string>* curr = start_node;
	while(curr != nullptr and (curr->counter < node->counter)){
		curr = curr->prev;
	}
  while(curr != nullptr and (curr->counter == node->counter) and (node->data.compare(curr->data) < 0)){  
    curr = curr->prev;
  }
	return curr;
}

//printNode is a debugging function that prints the info of Node to std::cout
void printNode(Node<string>* node){
	cout << "Node: "<< node->data << endl;
	cout << "prev: ";
	if (node->prev != nullptr)
		cout << node->prev->data;
	else
		cout << "Nullpointer";
	cout << " Next: ";
	if (node->next != nullptr)
		cout << node->next->data;
	else
		cout << "Nullpointer";
	cout << endl;
}


int main(int argc, char* argv[]){

    if (argc > 3) //checks amount of args
    {
        throw std::invalid_argument("Usage: ./bard <INPUT FILE> <OUTPUT FILE>"); //throws error
    }

		ifstream shakespeare;
		ifstream input;
		ofstream output;

		//global variables
    int array_pos = 0;
    int list_pos = 0;
    int list_index = 0;
    string foo = "";
    string numbers;

		//open fstreams
		shakespeare.open(SHAKESPEARE_FILE);
		input.open(argv[1]);
		output.open(argv[2]);

		//initialize arr_of_lists and set all it's values to nullptr
		LinkedList<string>* arr_of_lists[ARR_SIZE];
		for (int i = 0; i< ARR_SIZE; i++) {
			arr_of_lists[i] = nullptr;
		}

		

		//take all the words, and assign them to their respective index
		//   within the array of linked lists
		while (getline(shakespeare, foo)){
			//foo is the current word we are looking at
			int i = foo.length(); // i is the length of foo, so it will doubly serve as the index within the array of lists
			if (i < 0){
				continue;
			}

			if (arr_of_lists[i] == nullptr){ // if index is empty
				//add new node
				arr_of_lists[i] = new LinkedList<string>();
				arr_of_lists[i]->insert_front(foo);
	
			}
			else{ //if it is not empty
				Node<string>* catch_item = arr_of_lists[i]->firstRef(foo); //firstRef iterates through the list (starting from the head)
																																	 //and returns a pointer to the first Node with the same data 
																																	 //as that data provided in the argument, or a nullpointer
																																	 
				if (catch_item != nullptr){//if catch_item is not a nullptr, then a node with data "foo" has been found
					catch_item->counter++;   // add to it;

					arr_of_lists[i]->pop_lol(catch_item);//then, pop said Node from list, but keep its old ptrs;

          if (arr_of_lists[i]->front() == nullptr){//if, with catch_item gone, the list is empty, then re-insert  catch_item;
						arr_of_lists[i]->insert_front(catch_item); //we can just make it the head
					}else{//else, find the newest position that it can be in
						Node<string>* new_index = findNewIndex(catch_item->prev, catch_item);
						//save the output of findNewIndex to new_index
						if(new_index == nullptr){ 
						    arr_of_lists[i]->insert_front(catch_item);//if the new_index is a nullptr, that means catch_item > list head. 
																													//so we can re-assign the head of the list to catch_item
						}
						else{//if it finds a node, place catch_item the node.
							arr_of_lists[i]->insertFromNext(new_index, catch_item);
						}
					}
				}
				else{// if no data for "foo" exists, push to the back 
					arr_of_lists[i]->insert_back(foo);
				}
			}
		}

		shakespeare.close();


		//now, get inputs:


    Node<string>* curr = nullptr;
		while (getline(input, numbers)){//for each row in input, we take the values and store them into the "numbers" string
			if(numbers.length() == 0){
        continue;
      }
      //access inputs array_pos, list_pos
      foo = "";
      for (auto x: numbers){
        if (x == ' '){
          array_pos = stoi(foo);
          foo = "";
        }else{
          foo += x;
        }
      }
      list_pos = stoi(foo);

      //now, access position in list:
      if (arr_of_lists[array_pos] != nullptr){
        curr = arr_of_lists[array_pos]->front();
      }
      else{
        curr = nullptr;
      }
      list_index = 0;

			//if a list exists at position array_pos, we search through that list to find
			// the value at position list_pos
      while (curr != nullptr and list_index != list_pos){
        curr = curr->next;
        list_index++;
      }
			//if there is a node at that position, we push the "data" to our output file
      if(curr != nullptr){
        output << curr->data << endl;
      }//otherwise, we push a hyphen, to indicate nothing was found at that position
      else{
        output << '-' << endl;
      }

		}
		

		//we close our fstreams
		input.close();
		output.close();

}

