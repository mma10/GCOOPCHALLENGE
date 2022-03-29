#include <iostream>
#include<bits/stdc++.h>
using namespace std;


class Gymkhana{
    private:
        // Initial budget given by the government
        int budget;

        // Initialize Poll class: Private so that only the roleplayers can create one
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


        // responsibility class
        class responsibility{
            public:                              
                int position;
                string designation; 

                Poll openNewPoll(string stmt,vector<string> choices,int type){
                    return Poll(stmt,choices,type);
                }        
                responsibility(int pos,string des){
                    position = pos, designation = des;
                }                         
        };       
               
        // Message class as discussion subunit
        class Message{
            public:
                string studentName;
                string msge;
                string time;
                Message(string stName,string message,string Time){
                    studentName = stName, msge = message, time = Time;
                }
        };

        // Discussion in an event    
        class Discussion{
            public:
                vector<Message> msges;

                // get Random date string for now
                string getRandTime(){                    
                    return "29/03/2022 " + to_string(rand() % 24) + ":" + to_string(rand() % 60);
                }
                // Add message to the discussion messages                                
                bool addMessage(string msge,string stName){
                    msges.push_back(Message(stName,msge,getRandTime()));
                    return true;
                }

                // Read latest message
                void printLatestMsge(){
                    int size = msges.size();
                    if(size > 0){
                        Message lastMsge = msges[size-1];
                        cout << "On " + lastMsge.time + "," + lastMsge.studentName + " wrote " + lastMsge.msge << endl;
                    }
                }
        };   

        // Inititate event class
        class Event{            
            public: 
                bool success;
                vector<pair<string,int>> societies;                       

                // API to create a discussion for an event
                Discussion newDiscussion(){
                    return Discussion();
                };
        };

        // Student class
        class student{               
            public:  
                int id;      
                string name;                
               
                // Get random message from dataset
                string getNewMessageStr(){                    
                    vector<string> msges = {"Hey, hope everything is fine", "Good to know", "Please post to next day"};
                    return msges[rand() % msges.size()];
                }
                // Write a new message to the discussion
                bool writeMessage(Discussion &disc){
                    string msge = getNewMessageStr();
                    return disc.addMessage(msge,name);                    
                }                
        };              

        

                
        // Initialize societyMembers class
        class SocietyMember: public responsibility{
            private:
                student member;
            public:
                SocietyMember(int position,string designation,student st): responsibility(position,designation){
                    member = st;
                }
        };
        
        // Initialize society class
        class Society: public responsibility{
            private:
                student secretary;                
                vector<SocietyMember>  members;
                int budget;    
            public:
                int getBudget(){
                    return budget;
                }
                void amendBudget(int newBudget){
                    budget = newBudget;
                }          
                Society(int position,string designation,student st): responsibility(position,designation){
                    secretary = st;                    
                    budget = 0;
                }    
        };

        // Inititalize Council class
        class Council: public responsibility{
            private:
                student secretary;
                vector<Society> societies;
            public:
                Council(int position,string designation,student st): responsibility(position,designation){
                    secretary = st;                    
                }
        };

        // Initialize VicePresident class
        class VicePresident: public responsibility{
            private:
                student vicePresident;
                vector<Council> councils;
                // + extra roles       
            public:     
                VicePresident(int position,string designation,student st): responsibility(position,designation){
                    vicePresident = st;
                } 
        };    
        
        // Initialize President class
        class President: public responsibility{
            // president + gymkhana
            private:
                student president;
                vector<VicePresident> vicePresident;
                // + extra roles 
            public:  
                President(int position,string designation,student st): responsibility(position,designation){
                    president = st;
                }             
        };


        // Inititate instances of gymkhana entities
        vector<student> allStudents;    
        vector<President> president;
        vector<VicePresident> vicePresident;    
        vector<Council> councils;
        vector<Society> societies;
        vector<SocietyMember> societyMembers;
        vector<student> restStudents;        
        
    public:      
        vector<string> positions;
        
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
        
        // gymkhana constructor
        Gymkhana(){
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

        void addStudent(int id,string studentName){
            student newStudent;
            newStudent.id = id;
            newStudent.name = studentName;
            allStudents.push_back(newStudent);
            cout << newStudent.name << " added" << endl;
        }

        // Add entities of Gymkhana
        void addEntities(){
            president.push_back(President(0,"Gymkhana",allStudents[0]));  
            vicePresident.push_back(VicePresident(1,"Gymkhana",allStudents[0]));
            councils.push_back(Council(2,"Tech",allStudents[2]));
            councils.push_back(Council(2,"Cultural",allStudents[3]));
            societies.push_back(Society(3,"Neuromancers",allStudents[4]));
            societies.push_back(Society(3,"Robotics",allStudents[5]));
            societies.push_back(Society(3,"Dance and music",allStudents[6]));
            societyMembers.push_back(SocietyMember(4,"Neuromancers",allStudents[5]));
            societyMembers.push_back(SocietyMember(4,"Robotics",allStudents[7]));
            societyMembers.push_back(SocietyMember(4,"Robotics",allStudents[3]));
            societyMembers.push_back(SocietyMember(4,"Dance and Music",allStudents[8]));
            societyMembers.push_back(SocietyMember(4,"Dance and Music",allStudents[1]));
            restStudents.push_back(allStudents[9]);  

            // Add their relation, if required          
        }
};

void greet(){
    cout << "Welcome to Gymkhana Management System" << endl;
    cout << "An instance of gymkhana will be created" << endl;
}

int main()
{
    greet();

    // Crete gymkhana class
    Gymkhana gymkhana;   
     
    // Add students
    gymkhana.addStudent(1,"Ramesh");
    gymkhana.addStudent(2,"Mahesh");
    gymkhana.addStudent(3,"Raja");
    gymkhana.addStudent(4,"Aarti");
    gymkhana.addStudent(5,"Pooja");
    gymkhana.addStudent(6,"Mohan");
    gymkhana.addStudent(7,"Ravi");
    gymkhana.addStudent(8,"Raju");
    gymkhana.addStudent(9,"Lakshman");
    gymkhana.addStudent(10,"Adil");

    // Add gymkhana entities 
    gymkhana.addEntities();

    // Execute budget for societies

    // Sanction budget for societies

    // Demo polls

    // Demo discussion

	return 0;
}
