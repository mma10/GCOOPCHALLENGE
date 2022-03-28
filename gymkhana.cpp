#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class student{
    
};

class gymkhana{
    private:
        // Initial budget given by the government
        int budget;
        
        // Numerics of the gymkhana
        vector<int> limitPosition = {1, 1, INT_MAX,INT_MAX,INT_MAX,INT_MAX};
        vector<int> countPosition = {0, 0, 0, 0, 0, 0};
        
        // Hierarchy tree
        class responsibility{
            public:
                // Value of the node
                string position;
                string designation;
                student inchargeStudent;
                
                // Connections of the node
                responsibility* parent;
                vector<responsibility*> children;
        };
        responsibility* root;
        
        
    public:
        vector<string> position;
        void addResposibility(){
            
        } 
        
        gymkhana(){
            position = {"President", "VicePresident", "GSecCouncil", "SecSociety", "MemSociety", "RemStudent"};
            root = NULL;
        }
        
};

void greet(){
    cout << "Welcome to Gymkhana Management System" << endl;
}

int main()
{
    greet();
    
	return 0;
}
