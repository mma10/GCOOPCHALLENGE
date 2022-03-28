#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class student{
    
};

class gymkhana{
    private:
        // Initial budget given by the government
        int budget;

        // responsibility class
        class responsibility{
            protected:                              
                int position;
                string designation;                              
        };    

        // Initialize societyMembers class
        class SocietyMember: private responsibility{
            private:
                student member;
        };

        // Initialize society class
        class Society: private responsibility{
            private:
                student secretary;                
                vector<SocietyMember>  members;
                int budget;                                
        };

        // Inititalize Council class
        class Council: private responsibility{
            private:
                student secretary;
                vector<Society> societies;
        };

        // Initialize VicePresident class
        class VicePresident: private responsibility{
            private:
                student vicePresident;
                vector<Council> councils;
                // + extra roles
        };    
        
        // Initialize President class
        class President: private responsibility{
            // president + gymkhana
            private:
                student president;
                VicePresident* vicePresident;
                // + extra roles
        };

        President president;
        VicePresident vicePresident;
        vector<Council> councils;
        vector<Society> societies;
        vector<SocietyMember> societyMembers;
    
        
    public:
        vector<string> positions;
        void addResposibility(){
            
        } 
        
        // gymkhana constructor
        gymkhana(){
            positions = {"President", "VicePresident", "GSecCouncil", "SecSociety", "MemSociety", "RemStudent"};
                                                         
        }

        // limit is the max % of budget alloted to each society
        // alloted is the % of budget requested by each society
        bool allocateBudget(vector<int> limit,vector<int> alloted){
            
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
