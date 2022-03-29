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
                    return true;
                }

                void printPoll(){
                    cout << statement << endl;
                    int resSum = 0;
                    for(int res: responses)
                        resSum += res;
                    for(int i = 1; i <= choices.size(); i++)
                        cout << responses[i-1] * 100 / resSum << "% : " <<  i << ". " << choices[i-1] << endl;
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
                int id;
                string name; 
                bool success;
                vector<pair<string,int>> societies;    
                Discussion disc;                  

                // API to create a discussion for an event
                // Discussion newDiscussion(){
                //     return Discussion();
                // };
                Event(int ID,string eventName){
                    id = ID, name = eventName;
                }
        };

        // Student class
        class student{               
            public:  
                int id;      
                string name; 

                // Write a new message to the discussion
                bool writeMessage(Discussion &disc,string msge){                    
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
        vector<Event> events; 
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
        // type = 3 -> Poll for all students
        bool executePoll(Poll &poll){            
            int size = 0;
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
                // Poll for all students
                case 3:
                    size = allStudents.size();
                    break;
                default:
                    return false;
            }

            int options = poll.choices.size(); 
            vector<int> responses(options);
            for(int i = 0; i < size; i++){                       
                int response = rand() % options;                                
                responses[response]++;                        
            }
            return poll.setResponses(responses);            
        }          
        
        // gymkhana constructor
        Gymkhana(){
            positions = {"President", "VicePresident", "GSecCouncil", "SecSociety", "MemSociety", "RemStudent"};     
            budget = 80000;                                                    
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
            return event.success = true;            
        }


        /* Custom Function to create and engage instances(objects) with the system */

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
            societies.push_back(Society(3,"DanceMusic",allStudents[6]));
            societyMembers.push_back(SocietyMember(4,"Neuromancers",allStudents[5]));
            societyMembers.push_back(SocietyMember(4,"Robotics",allStudents[7]));
            societyMembers.push_back(SocietyMember(4,"Robotics",allStudents[3]));
            societyMembers.push_back(SocietyMember(4,"DanceMusic",allStudents[8]));
            societyMembers.push_back(SocietyMember(4,"DanceMusic",allStudents[1]));
            restStudents.push_back(allStudents[9]);  

            // Add their relation, if required          
        }

        // Print budget of each society
        void printBudget(){
            for(Society &soc: societies)
                cout << soc.designation << " " << soc.getBudget() << endl;
        }

        // Create and sanction funds for the event
        bool createAndSanctionEvent(){
            Event newEvent(1,"General Championship");
            vector<pair<string,int>> funds = {{"Neuromancers",10000},{"DanceMusic",12000}};
            newEvent.societies = funds;
            events.push_back(newEvent);   
            sanctionEvent(events[0]);         
            return events[0].success;
        }

        // Create a poll with a gymkhana entity, and execute it based on its type
        void createAndExecPoll(){
            // Lets create a poll via Neuromancer's secretary: societies[0]            
            string stmt = "How many tech events should be held in General Championship";
            vector<string> choices = {"One", "Two", "Three"};
            Poll newPoll = societies[0].openNewPoll(stmt,choices,3);                        
            if(executePoll(newPoll)){
                cout << "New Poll successfully created" << endl;
                newPoll.printPoll();
            }
            else    
                cout << "Failed to create new poll" << endl;            
        }

        // Extend the discussion of the event, by inserting comments from students
        void extendDiscussion(){
            // Here we extend the discussion of event: General Championship: event[0]
            // Given are the comments from students regards to the event
            vector<pair<string,int>> comments = {{"GC should be held asap!",0}, {"I think we should spend time to analyse budget",3}, {"We could go about another round for fund raising",7}};
            cout << "Discussion on " << events[0].name << " event" << endl;
            for(pair<string,int> &comment: comments){
                int stNum = comment.second;
                string msge = comment.first;
                if(allStudents[stNum].writeMessage(events[0].disc,msge))
                    events[0].disc.printLatestMsge();
                else
                    cout << "Error writing message to the event discussion" << endl;
            }
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
    cout << endl;


    // Add gymkhana entities 
    gymkhana.addEntities();
    cout << "Entities addded" << endl << endl;


    // Execute budget for societies
    vector<pair<string,int>> limit = {{"Neuromancers",40}, {"Robotics",60}, {"DanceMusic",40}};
    vector<pair<string,int>> alloted = {{"Neuromancers",15000}, {"Robotics",20000}, {"DanceMusic",17000}}; 
    if(gymkhana.allocateBudget(limit,alloted)){
        cout << "Budget alloted within societies" << endl;
        gymkhana.printBudget(); 
    }
    else
        cout << "Allocation out of constrains" << endl;    
    cout << endl;   
    

    // Sanction budget for events and create events
    if(gymkhana.createAndSanctionEvent())
        cout << "Funds successfully sanctioned for the event" << endl;
    else
        cout << "Sorry, funds could not be sanctioned for the event due to insufficient budget" << endl;
    cout << "Remaining Budget for all societies" << endl;
    gymkhana.printBudget();   
    cout << endl;


    // Demo polls
    gymkhana.createAndExecPoll();
    cout << endl;


    // Demo discussion
    gymkhana.extendDiscussion();

	return 0;
}
