#ifndef TIMER_CPP
#define TIMER_CPP
#include<bits/stdc++.h>
using namespace std;
void menu();
class Timer 
{
    private:
        int duration; 
        int sessionID;
        int userID;
        string subject;
        string startTime;
        string endTime;
        string sessionType;
    public:
        Timer()
        {
            sessionID=0;
            userID=0;
            duration=0;
        }
        void setDuration (int m) {duration = m;}
        void setSessionID (int id) {sessionID = id;}
        void setUserID (int id) {userID = id;}
        void setSubject (string sub) {subject = sub;}
        void setStartTime (string start) {startTime = start;}
        void setEndTime (string end) {endTime = end;}
        void setSessionType (string type) {sessionType = type;}

        int getDuration () {return duration;}
        int getSessionID () {return sessionID;}
        int getUserID () {return userID;}
        string getSubject () {return subject;}
        string getStartTime () {return startTime;}
        string getEndTime () {return endTime;}
        string getSessionType () {return sessionType;}

        void display() 
        {
            cout<<endl<<"⋆˚✿˖°Session Details⋆˚✿˖°"<<endl;
            cout << "Session ID: " << sessionID << endl;
            cout << "User ID: " << userID << endl;
            cout << "Subject: " << subject << endl;
            cout << "Session Type: " << sessionType << endl;
            cout << "Start Time: " << startTime << endl;
            cout << "End Time: " << endTime << endl;
            cout << "Duration: " << duration << " minutes" << endl;
            cout<<"⋆˚✿˖°⋆˚✿˖°⋆˚✿˖°⋆˚✿˖°⋆˚✿˖°⋆˚✿˖°⋆˚✿"<<endl;
        }
};
void SessionMenu();
void startNewSession();
void viewPastSessions();
void viewTodaysSessions();
void pomodoroSession();
string getTimeNow();
string getDateNow();
int generateSessionID();
void countdown(int minutes);
void saveSession(Timer session);
Timer readSession(string line);
bool userExists(int id);
void updateUserStudyTime(int userID, int minutesToAdd); 
void SessionMenu()
{
    int choice;
    do
    {
        cout<<endl<<"︵‿₊୨ᰔ୧₊‿︵‧˚₊⊹︵‿₊୨ᰔ୧₊‿︵‧˚₊⊹"<<endl;
        cout<<"     STUDY SESSION MENU "<<endl;
        cout<<"︵‿₊୨ᰔ୧₊‿︵‧˚₊⊹︵‿₊୨ᰔ୧₊‿︵‧˚₊⊹"<<endl;
        cout<<"1. Start New Session"<<endl;
        cout<<"2. View Past Sessions"<<endl;
        cout<<"3. View Today's Sessions"<<endl;
        cout<<"4. Pomodoro Session"<<endl;
        cout<<"5. Back to Main Menu"<<endl;
        cout<<"︵‿₊୨ᰔ୧₊‿︵‧˚₊⊹︵‿₊୨ᰔ୧₊‿︵‧˚₊⊹"<<endl;
        choice = getValidatedMenuChoice("Enter your choice: ", 1, 5);
        switch(choice) 
        {
            case 1: startNewSession(); break;
            case 2: viewPastSessions(); break;
            case 3: viewTodaysSessions(); break;
            case 4: pomodoroSession(); break;
            case 5: {
                        cout<<"Returning to main menu..."<<endl;
                        menu();
                        break;
                    }
            default: cout<<"Invalid choice. Please try again."<<endl;
        }
    } while (choice !=5);
    }

string getTimeNow()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string datetime = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year) + " " +
                        to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min);
    return datetime;
}

string getDateNow()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string date = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    return date;
}

int generateSessionID()
{
int maxID =0;
int id;
string line;
ifstream file("session_data.txt");
if (file.is_open())
{
    while (getline(file, line))
    {
        if(line.empty()) continue;
        size_t pos = line.find('|');
        if (pos != string::npos)
        {
            id = stoi(line.substr(0, pos));
            if (id > maxID) maxID = id;
        }
    }
    file.close();
}
maxID++;
return maxID;
}

void countdown(int minutes)
{
    cout <<endl<<"Timer started for " << minutes << " minutes." << endl;
    for (int m=(minutes-1); m>=0; m--)
    {
        for (int s=59; s>=0; s--)
        {
            cout << "\rTime Remaining: " << (m < 10 ? "0" : "") << m << ":" << (s < 10 ? "0" : "") << s<<" "<< flush;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    cout<<"\a";
    cout <<endl<<"Time's up! Great job!"<<endl;
}

void startNewSession()
{
    Timer session;
    int userID, choice, duration;
    string subject;

    userID = getValidatedPositiveInt("Enter your User ID: ");
    if(!userExists(userID))
    {
        cout << "User ID not found. Please register first." << endl;
        return;
    }
    session.setUserID(userID);
    session.setSessionID(generateSessionID());
    cin.ignore();
    cout << "Enter Subject/Topic for this session: ";
    getline(cin, subject);
    session.setSubject(subject);

    cout <<endl<<"Select Session Type: "<<endl;
    cout << "1- Pomodoro (25 min)"<<endl;
    cout << "2- Custom duration"<<endl;
    choice = getValidatedMenuChoice("Enter your choice: ", 1, 2);

    switch (choice)
    {
        case 1:
            session.setSessionType("Pomodoro");
            duration = 25;
            break;
        case 2:
            session.setSessionType("Custom");
            duration = getValidatedPositiveInt("Enter duration in minutes: ");
            break;
        default:
            cout << "Invalid choice! Defaulting to to 25 minutes."<<endl;
            session.setSessionType("Pomodoro");
            duration = 25;
    }
    session.setDuration(duration);
    session.setStartTime(getTimeNow());
    cout<<endl<<"Starting your study session for"<<subject<<" ... "<<endl;
    countdown(duration);
    session.setEndTime(getTimeNow());
    saveSession(session);
    updateUserStudyTime(userID, duration);
    cout<<endl<<"Session completed and saved!"<<endl;
}
void saveSession(Timer session)
{
    ofstream file("session_data.txt", ios::app);
    if (file.is_open())
    {
        file << session.getSessionID() << "|"
             << session.getUserID() << "|"
             << session.getSubject() << "|"
             << session.getSessionType() << "|"
             << session.getStartTime() << "|"
             << session.getEndTime() << "|"
             << session.getDuration() << endl;
        file.close();
    }
    else
        cout << "Unable to open file to save session data." << endl;
}
void viewPastSessions()
{
    int userID = getValidatedPositiveInt("Enter your User ID to view past sessions: ");
    if(!userExists(userID))
    {
        cout << "User ID not found. Please register first." << endl;
        return;
    }
    ifstream file("session_data.txt");
    string line;
    int count =0;
    int totalMinutes =0;
    if (!file.is_open())
    {
        cout<<"Error : could not open file :("<<endl;
        return;
    }
    cout<<endl<<"°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚"<<endl;
    cout<<"          YOUR PAST SESSIONS :"<<endl;
    cout<<"°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚"<<endl;
    while (getline(file, line))
    {
        if(line.empty()) continue;
        Timer session = readSession(line);
        if (session.getUserID()==userID)
        {
            session.display();
            totalMinutes += session.getDuration();
            count++;
        }
    }
    file.close();
    if (count==0) cout<<endl<<"No sessions found for User ID: "<<userID<<endl;
    else 
    {
        cout<<endl<<"°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚"<<endl;
        cout<<"Total Sessions: "<<count<<endl;
        cout<<"Total Time Studied: "<<totalMinutes<<" minutes"<<endl;
        cout<<" ("<<totalMinutes/60<<" hours and "<<totalMinutes%60<<" minutes)"<<endl;
        cout<<"°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚"<<endl;
    }
}
Timer readSession(string line)
{
    Timer session;
    if(line.empty()) return session;
    size_t pos = 0;
    string token;
    vector<string> tokens;
    while ((pos = line.find('|')) != string::npos) 
    {
        token = line.substr(0, pos);
        tokens.push_back(token);
        line.erase(0, pos + 1);
    }
    tokens.push_back(line);

    session.setSessionID(stoi(tokens[0]));
    session.setUserID(stoi(tokens[1]));
    session.setSubject(tokens[2]);
    session.setSessionType(tokens[3]);
    session.setStartTime(tokens[4]);
    session.setEndTime(tokens[5]);
    session.setDuration(stoi(tokens[6]));

    return session;
}
void viewTodaysSessions()
{
    int userID = getValidatedPositiveInt("Enter your User ID to view today's sessions: ");
    if(!userExists(userID))
    {
        cout << "User ID not found. Please register first." << endl;
        return;
    }
    string todayDate = getDateNow();
    ifstream file("session_data.txt");
    string line;
    int count =0;
    int totalMinutes =0;
    if (!file.is_open())
    {
        cout<<"Error : could not open file :("<<endl;
        return;
    }
    cout<<endl<<"°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚"<<endl;
    cout<<"       YOUR SESSIONS FOR TODAY :"<<endl;
    cout<<"°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚"<<endl;
    while (getline(file, line))
    {
        Timer session = readSession(line);
        if (session.getUserID()==userID)
        {
            string sessionDate = session.getStartTime().substr(0, session.getStartTime().find(' '));
            if (sessionDate == todayDate)
            {
                session.display();
                totalMinutes += session.getDuration();
                count++;
            }
        }
    }
    file.close();
    if (count==0) cout<<endl<<"No sessions found for today. Start studying!"<<endl;
    else 
    {
        cout<<endl<<"°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚"<<endl;
        cout<<"Total Sessions Today: "<<count<<endl;
        cout<<"Total Time Studied Today: "<<totalMinutes<<" minutes"<<endl;
        cout<<" ("<<totalMinutes/60<<" hours and "<<totalMinutes%60<<" minutes)"<<endl;
        cout<<"°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚"<<endl;
    }
}

void pomodoroSession() {
    int userID;
    string subject;
    
    cout <<endl<< " POMODORO SESSION"<<endl;
    cout << "Pattern: 25 min work → 5 min break → Repeat 4 times → 15min long break"<<endl<<endl;
    
    userID = getValidatedPositiveInt("Enter User ID: ");
    cin.ignore();
    cout << "Enter subject: ";
    getline(cin, subject);
    
    int totalStudyTime = 0;
    
    for(int cycle = 1; cycle <= 4; cycle++) {
        cout <<endl<< "Cycle " << cycle << " of 4: Focus Time!"<<endl;
        countdown(25);
        totalStudyTime += 25;
        
        Timer session;
        session.setSessionID(generateSessionID());
        session.setUserID(userID);
        session.setSubject(subject);
        session.setSessionType("Pomodoro");
        session.setStartTime(getTimeNow());
        session.setDuration(25);
        session.setEndTime(getTimeNow());
        saveSession(session);
        
        if(cycle < 4) {
            cout <<endl<< "Short break time! (5 minutes)"<<endl;
            countdown(5);
        } else {
            cout <<endl<< " All cycles complete! Long break time! (15 minutes)"<<endl;
            countdown(15);
        }
    }
    updateUserStudyTime(userID, totalStudyTime);
    
    cout <<endl<< "°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚"<<endl;
    cout << "Pomodoro session complete!"<<endl;
    cout << "Total study time: " << totalStudyTime << " minutes"<<endl;
    cout << "°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚°❀⋆.ೃ࿔:･°❀⋆.ೃ࿔:･⊹₊˚"<<endl;
}
#endif