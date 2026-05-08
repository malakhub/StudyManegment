#ifndef STATISTICS_CPP
#define STATISTICS_CPP
#include<iostream>
#include<iomanip>
#include<map>
#include<fstream>
#include<vector>
#include<string>
#include"TaskManagement.cpp"
using namespace std;
void menu();
void taskComletionRate()
{
    int userID = getValidatedPositiveInt("Please,enter user ID: ");
    int totalTasks=0,completedTasks=0;
    ifstream fin("Tasks.txt");
    string line;
    while(getline(fin,line))
        {
            ToDoList task=Organizer(line);
            if(task.getUserID()==userID)
            {
                totalTasks++;
                if(task.getCompleted())
                {
                    completedTasks++;
                }
            }
        }
    fin.close();
    cout<<"⊹₊˚‧︵‿₊୨ᰔ୧₊‿︵‧˚₊⊹⊹₊˚‧︵‿₊୨ᰔ୧₊‿︵‧˚₊⊹"<<endl;
    cout<<"\t"<<"TASK COMPLETION REPORT"<<"\t"<<endl;
    cout<<"⊹₊˚‧︵‿₊୨ᰔ୧₊‿︵‧˚₊⊹⊹₊˚‧︵‿₊୨ᰔ୧₊‿︵‧˚₊⊹"<<endl;
    cout<<"The number of Total Tasks: "<<totalTasks<<endl;
    cout<<"The number of Completed Tasks: "<<completedTasks<<endl;
    cout<<"The number of Remaining Tasks: "<<(totalTasks-completedTasks)<<endl;
    if(totalTasks>0)
    {
        float ratio=(completedTasks*100.0)/totalTasks;
        cout<<"Task Completion Rate: "<<fixed<<setprecision(1)<<ratio<<"%"<<endl;
        cout<<"Progress: [";
        int bars=(int)(ratio/10);
        for(int i=0;i<10;i++)
            {
                if(i<bars)
                {
                    cout << "█";
                }
                else cout << "░";
            }
        cout<<"]"<<endl;
    }
}
void subjectWiseAnalysis()
{
    int userID = getValidatedPositiveInt("Please,enter userID: ");
    map<string, int>totalSubject;
    map<string, int>completedSubject;
    ifstream fin("Tasks.txt");
    string line;
    while(getline(fin,line))
    {
        ToDoList task=Organizer(line);
        if(task.getUserID()==userID)
        {
            string subject=task.getTaskName();
            totalSubject[subject]++;
            if(task.getCompleted())
            {
                completedSubject[subject]++;
            }
        }
    }
    fin.close();
    cout<<"⊹₊˚‧︵‿₊୨ᰔ୧₊‿︵‧˚₊⊹⊹₊˚‧︵‿₊୨ᰔ୧₊‿︵‧˚₊⊹"<<endl;
    cout<<"\t"<<"SUBJECT-WISE ANALYSIS"<<"\t"<<endl;
    cout<<"─── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ── "<<endl;
    for(auto& pair : totalSubject)
    {
        string subject = pair.first;
        int total = pair.second;
        int completed = completedSubject[subject];
        double percentage = (completed * 100.0) / total;
        cout << "˚˖𓍢ִ໋❀" << subject<<endl;
        cout<<"The number of Total Tasks: "<<total<<endl;
        cout<<"The number of Completed Tasks: "<<completed<<endl;
        cout<<"Task Completion Rate: "<<percentage<<fixed<<setprecision(1)<<"%"<<endl;
    }
    cout<<"─── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ──"<<endl;
}
void studyTimeReport()
{
    int userID = getValidatedPositiveInt("Please,enter userID: ");
    int totalMinutes=0,sessionCount=0;
    map<string,int>subjectTime;
    ifstream file("session_data.txt");
    string line;
    while(getline(file,line))
    {
        vector<string>fileline;
        string subline;
        size_t position=0;
        while(position==line.find('|') !=string::npos)
        {
            subline=line.substr(0,position);
            fileline.push_back(subline);
            line.erase(0,position+1);
        }
        fileline.push_back(line);
        if(fileline.size()>=7 && stoi(fileline[1])==userID)
        {
            string subject = fileline[2];
            int duration = stoi(fileline[6]);

            totalMinutes += duration;
            sessionCount++;
            subjectTime[subject]+=duration;
        }
    }
    file.close();
    cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
    cout<<"\t"<<"STUDY TIME REPORT"<<"\t"<<endl;
    cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
    cout<<"˚˖𓍢ִ໋❀Total sessions: "<<sessionCount<<endl;
    cout<<"˚˖𓍢ִ໋❀Total time: "<<totalMinutes<<"min"<<endl;
    float average=totalMinutes*1.0/sessionCount;
    cout<<"˚˖𓍢ִ໋❀Average time per session: "<<average<<"min"<<endl;
    cout << "\n\nTime by Subject:\n";
    for(auto& pair : subjectTime) 
    {
        cout << "˚˖𓍢ִ໋❀" << pair.first << ": " << pair.second<< " min "<<endl;
    }
    cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
}
void weeklySummary() 
{
    int userID = getValidatedPositiveInt("Enter User ID: ");
    int tasksCompleted = 0;
    int studyMinutes = 0;
    int sessions = 0;
    ifstream taskFile("Tasks.txt");
    string line;
    while(getline(taskFile, line)) {
        ToDoList task = Organizer(line);
        if(task.getUserID() == userID && task.getCompleted())
        {
            if(task.getCompletionDate() != "N/A") {
                tasksCompleted++;
            }
        }
    }
    taskFile.close();
    ifstream sessionFile("session_data.txt");
    while(getline(sessionFile, line)) {
        vector<string> fileline;
        string subline;
        size_t position = 0;
        
        while((position = line.find('|')) != string::npos) {
            subline = line.substr(0, position);
            fileline.push_back(subline);
            line.erase(0, position + 1);
        }
        fileline.push_back(line);
        if(fileline.size() >= 7 && stoi(fileline[1]) == userID) {
            studyMinutes += stoi(fileline[6]);
            sessions++;
        }
    }
    sessionFile.close();
    cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
    cout <<"\t"<<" WEEKLY SUMMARY"<<"\t"<<endl;
    cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
    cout << "📅 This Week's Progress:"<<endl;
    cout << "✓ Tasks Completed: " << tasksCompleted<<endl;
    cout << "⏰ Study Sessions: " << sessions<<endl;
    cout << "📚 Total Study Time: " << studyMinutes << " minu"<<endl;
    if(sessions > 0) 
    {
        cout << "\n📊 Average per session: " << (studyMinutes/sessions)<< " min"<<endl;
    }
    if(studyMinutes >= 300) { // 5 hours
        cout << "🎉 Excellent work this week!"<<endl;} 
        else if(studyMinutes >= 120) {
        cout << "👍 Good progress! Keep it up!"<<endl;} 
        else {
        cout << "💪 Let's aim for more study time next week!"<<endl;}
    cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl; 
}
void statisticMenu()
{
    int choice;
    do
        {
            cout<<"\t"<<"Statistice and Reports"<<"\t"<<endl;
            cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
            cout<<"1- Task Completion Rate."<<endl;
            cout<<"2- Subject-Wise Analysis."<<endl;
            cout<<"3- Study Time Report."<<endl;
            cout<<"4- Weekly Summary."<<endl;
            cout<<"5- Back to main Menu."<<endl;
            cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
            choice = getValidatedMenuChoice("please,enter your choice: ", 1, 5);
            switch(choice)
            {
                case 1:
                    {
                        taskComletionRate();
                        break;
                    }
                case 2:
                    {
                        subjectWiseAnalysis();
                        break;
                    }
                case 3:
                    {
                        studyTimeReport();
                        break;
                    }
                case 4:
                    {
                        weeklySummary();
                        break;
                    }
                case 5:
                    {
                        cout<<"Returning to main menu..."<<endl;
                        menu();
                        break;
                    }
                default : cout<<"Invalid choice! please,try again."<<endl;
            }
        }while(choice!=5);
}
#endif