#include<list>
#include<iostream>
template<std::size_t NP>
void GS_Algorithm(int (&ManPref)[NP][NP], int (&WomenPref)[NP][NP], int np/*number of people*/,int* perfect_matching_table){
//we ignore the maintainness of perfect matching list
//assum ManPref and WomenPref as 2-dimensional array with np*np elements
std::list<int> free_men;
//dynamic allocation of Next Array, Next[i] represents the next pursued woman of the i-th man
int* Next=new int[np];
//dynamic allocation of Current Array, Current[i] represents the current partner of the i-th woman
int* Current=new int[np];
//dynamic allocation of 2D Array Ranking
int** Ranking=new int*[np];


//Initialization
for(int i=0;i<np;i++){
	Next[i]=ManPref[i][0];//the i-th man pursues his most favarite woman
	Current[i]=-1;//the i-th woman has no partner at the beginning
	Ranking[i]=new int[np];
	//Add the i-th man to the free-man list
	free_men.push_back(i);
	for(int j=0;j<np;j++)
		Ranking[i][WomenPref[i][j]]=j; //the i-th woman ranks the WomenPref[i][j]-th man with position j
}

while(free_men.size()>0){
	int one_free_man=free_men.back();	
	int proposed_woman=Next[one_free_man];
	Next[one_free_man]++;
	if(Current[proposed_woman]==-1){
		Current[proposed_woman]=one_free_man;
		free_men.pop_back();
		// add pair free_men-proposed_woman to the perfect matching list
		perfect_matching_table[one_free_man] = proposed_woman;
	}
	else if(Ranking[proposed_woman][Current[proposed_woman]]>Ranking[proposed_woman][one_free_man]){
		//Add Current[proposed_woman] to the free_man list
		//Remove pair Current[proposed_woman]-proposed_woman from perfect matching list 
		//by the property of gs-algorithm, there is actually no need to do this step
		perfect_matching_table[Current[proposed_woman]] = -1;
		//Add pair one_free_man-proposed_woman to the perfect matching list 
		perfect_matching_table[one_free_man] = proposed_woman;
		free_men.pop_back();
		free_men.push_back(Current[proposed_woman]);
		Current[proposed_woman]=one_free_man;		
	}
	else{
		//rejected
	}
}

//Deallocation of Next Array and Current Array
delete [] Next;
delete [] Current;
for(int i=0;i<np;i++)
	delete [] Ranking[i];
delete [] Ranking;
}

int main(){
	enum Man{Xavier,Yancey,Zeus};
	enum Woman{Amy,Bertha,Clare};
	int ManPref[3][3]={
		{Woman::Amy,Woman::Bertha,Woman::Clare},
		{Woman::Bertha,Woman::Amy,Woman::Clare},
		{Woman::Amy,Woman::Bertha,Woman::Clare},
	};
	int WomenPref[3][3]={
		{Man::Yancey,Man::Xavier,Man::Zeus},
		{Man::Xavier,Man::Yancey,Man::Zeus},
		{Man::Xavier,Man::Yancey,Man::Zeus}
	};
	int perfect_matching_table[3];
	GS_Algorithm(ManPref, WomenPref, 3/*number of people*/, perfect_matching_table);
	//cout the perfect matching
	for (int i = 0; i < 3; i++) {
		std::cout << "Man: " << i << "<->Woman: " << perfect_matching_table[i] << std::endl;
	}
	return 0;
}