#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class student{
    
};

class Event{
    public: 
        bool success;
        vector<pair<string,int>> societies;        
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

        // Objects of gymkhana entities
        President president;
        VicePresident vicePresident;
        vector<Council> councils;
        vector<Society> societies;
        vector<SocietyMember> societyMembers;
        vector<student> restStudents;
        
    public:
        // Initialize Poll class
        class Poll{
            private:
                vector<int> responses;
            public:                
                string statement;
                vector<string> choices;
                int type;

                bool setResponses(vector<int> res){
                    responses = res;
                }

                void printPoll(){
                    cout << statement << endl;
                    int resSum = 0;
                    for(int res: responses)
                        resSum += res;
                    for(int i = 1; i <= choices.size(); i++)
                        cout << responses[i] * 100 / resSum << "% : " <<  i << ". " << choices[i] << endl;
                }
                
                Poll(string stmt,vector<string> chs,int typ){
                    statement = stmt, choices = chs, type = typ;
                    responses = vector<int> (choices.size(),0);
                }

        };

        // Function to execute the poll
        // type = 0 -> Poll only for heads
        // type = 1 -> Poll only for all society members
        // type = 2 -> Poll only for rest of students
        bool executePoll(Poll &poll){            
            int size;
            // Assign random value from each candidate
            switch(poll.type){
                // Poll only for heads: President + V.President + All council heads + All society heads
                case 0:
                    size = 2 + councils.size() + societies.size();                     
                    break;
                // Poll only for society members
                case 1:
                    size = societyMembers.size();
                    break;
                // Poll only for rest of students
                case 2:
                    size = restStudents.size();
                    break;
                default:
                    return false;
            }

            int options = poll.choices.size(); 
            vector<int> responses;
            for(int i = 0; i < size; i++){
                int response = rand() % options;
                responses[response]++;                        
            }
            return poll.setResponses(responses);            
        }      

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
            // Return false for obvious cases       
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

            // Assign each society with their respective budget
            for(int i = 0; i < societies.size(); i++)
                for(int j = 0; j < alloted.size(); j++)
                    if(societies[i].designation == alloted[i].first)
                        societies[i].amendBudget(alloted[i].second);
            return true;
        }        

        // Sanctions funds for the event if available for each society
        bool sanctionEvent(Event &event){
            // Check if all societies can be sanctioned successfully
            for(pair<string,int> soc: event.societies)
                for(Society &society: societies)
                    if(society.designation == soc.first)
                        if(soc.second > society.getBudget()){
                            event.success = false;
                            return false;                
                        }
            // If yes, then sanction them funds and deduct from their budget      
            for(pair<string,int> soc: event.societies)
                for(Society &society: societies)
                    if(society.designation == soc.first)
                        if(soc.second <= society.getBudget())
                            society.amendBudget(society.getBudget() - soc.second); 
            // Mark the event as successful
            event.success = true;
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
