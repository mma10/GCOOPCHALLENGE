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
            public:                              
                int position;
                string designation;                              
        };    

        // Initialize societyMembers class
        class SocietyMember: public responsibility{
            private:
                student member;
        };

        // Initialize society class
        class Society: public responsibility{
            private:
                student secretary;                
                vector<SocietyMember>  members;
                int budget;    
            public:
                Society(){

                }     

                int getBudget(){
                    return budget;
                }
                void amendBudget(int newBudget){
                    budget = newBudget;
                }      
        };

        // Inititalize Council class
        class Council: public responsibility{
            private:
                student secretary;
                vector<Society> societies;
        };

        // Initialize VicePresident class
        class VicePresident: public responsibility{
            private:
                student vicePresident;
                vector<Council> councils;
                // + extra roles
        };    
        
        // Initialize President class
        class President: public responsibility{
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
        bool allocateBudget(vector<pair<string,int>> limit,vector<pair<string,int>> alloted){           
            if(limit.size() != alloted.size() || alloted.size() != societies.size())
                return false;
            int totalAlloted = 0;
            for(int i = 0; i < alloted.size(); i++){
                if(alloted[i].second > limit[i].second * budget / 100)
                    return false;
                totalAlloted += alloted[i].second;
            }
            if(totalAlloted > budget)
                return false;

            for(int i = 0; i < societies.size(); i++)
                for(int j = 0; j < alloted.size(); j++)
                    if(societies[i].designation == alloted[i].first)
                        societies[i].amendBudget(alloted[i].second);
            return true;
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
