#include<deque>
#include<list>
#include<stack>
#include<iostream>
void bfs(std::list<int>* adjancency_table,int tl/*table_length*/,int sn/*starting node*/,std::list<int>* bfs_tree){
bool* Discovered=new bool[tl];
std::deque<int> quque;
for(int i=0;i<tl;i++)
    Discovered[i]=false;
quque.push_back(sn);
Discovered[sn] = true;
while(!quque.empty()){
    int fe/*front element*/=quque.front();
    quque.pop_front();    
    for(auto i=adjancency_table[fe].begin();i!=adjancency_table[fe].end();i++){
        if(!Discovered[*i]){
            Discovered[*i]=true;
			//add (fe,*i) to the BFS Tree
			bfs_tree[fe].push_back(*i);
            quque.push_back(*i);
        }
    }
}
delete [] Discovered;
}
void dfs(std::list<int>* adjancency_table, int tl/*table_length*/, int sn/*starting node*/, std::list<int>* dfs_tree) {
	bool* Explored = new bool[tl];
	int* parent = new int[tl];
	std::stack<int> dfs_stack;
	for (int i = 0; i<tl; i++)
		Explored[i] = false;
	dfs_stack.push(sn);
	parent[sn] = -1;/*root element has no parent*/
	while (!dfs_stack.empty()) {
		int fe/*front element*/ = dfs_stack.top();
		dfs_stack.pop();
		if (!Explored[fe]) {
			Explored[fe] = true;
			if(fe!=sn)
				dfs_tree[parent[fe]].push_back(fe);
			for (auto i = adjancency_table[fe].begin(); i != adjancency_table[fe].end(); i++) {			
				parent[*i] = fe;
				dfs_stack.push(*i);
			}
		}
	}
	delete[] Explored;
	delete[] parent;
}

int main(){
    //construct the adjancency_table;
    std::list<int> at[8];
	std::list<int> bfs_tree[8];
	std::list<int> dfs_tree[8];
    //node 0 has 2 neighbors
    at[0].push_back(1);
    at[0].push_back(2);

    //node 1
    at[1].push_back(0);
    at[1].push_back(2);
    at[1].push_back(3);
    at[1].push_back(4);

    //node 2
    at[2].push_back(0);
    at[2].push_back(1);
    at[2].push_back(4);
    at[2].push_back(6);
    at[2].push_back(7);

    //node 3
    at[3].push_back(1);
    at[3].push_back(4);

    //node 4
    at[4].push_back(1);
    at[4].push_back(2);
    at[4].push_back(5);
    at[4].push_back(3);

    //node 5
    at[5].push_back(4);
    
    //node 6
    at[6].push_back(2);
    at[6].push_back(7);
    
    //node 7
    at[7].push_back(2);
    at[7].push_back(6);

	//0 is the root_element of bfs_tree
    bfs(at,8,0,bfs_tree);
	std::cout << "BFS Tree: ";
	for(int i=0;i<8;i++)
		if(!bfs_tree[i].empty()){
			std::cout << i << ':';
			for (auto j = bfs_tree[i].begin(); j != bfs_tree[i].end(); j++)
				std::cout << *j << ' ';
			std::cout << std::endl;
		}
	std::cout << std::endl;

	dfs(at, 8, 0, dfs_tree);
	std::cout << "DFS Tree: ";
	for (int i = 0; i<8; i++)
		if (!dfs_tree[i].empty()) {
			std::cout << i << ':';
			for (auto j = dfs_tree[i].begin(); j != dfs_tree[i].end(); j++)
				std::cout << *j << ' ';
			std::cout << std::endl;
		}
	std::cout << std::endl;

    return 0;
}
