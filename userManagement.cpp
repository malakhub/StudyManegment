#ifndef USERMANAGEMENT_CPP
#define USERMANAGEMENT_CPP
#include<bits/stdc++.h>
using namespace std;
void menu();
using ll = long long;
class User 
{
    private:
        int userID;
        string name;
        string email;
        string registrationDate;
        int studyMinutes;
    public:
        User()
        {
            userID=0;
            studyMinutes=0;
        } 
        void setUserID(int id) {userID = id;}
        void setName(string n) {name = n;}
        void setEmail(string e) {email = e;}
        void setRegistrationDate(string date) {registrationDate = date;}
        void setStudyMinutes(int hours) {studyMinutes = hours;}
        int getUserID() {return userID;}
        string getName() {return name;}
        string getEmail() {return email;}
        string getRegistrationDate() {return registrationDate;}
        int getStudyMinutes() {return studyMinutes;}

        void displayInfo() 
        {
        cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
        cout<<"---User Details---"<<endl;
        cout << "User ID: " << userID << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Registration Date: " << registrationDate << endl;
        cout << "Total Study Time: " << studyMinutes <<" minutes ("<<  studyMinutes/60 << " hours " << studyMinutes%60 << " minutes)"<<endl;
        cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
        }
};
void addUser();
int generateID();
void showUsers();
User readUser(string);
void updateInfo();
void deleteUser();
void searchUser();
void searchByID();
void searchByName();
void UserManagement();
bool userExists(int id);
void updateUserStudyTime(int userID, int minutesToAdd);
void UserManagement()
{
    int choice;
    do 
    {
        cout<<endl<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
        cout<<"\t"<<"USER MANAGEMENT"<<endl;
        cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
        cout << "1. Add New User" << endl;
        cout << "2. View All User Details"<<endl;
        cout << "3. Update User info"<<endl;
        cout << "4. Delete User"<<endl;
        cout << "5. Search User"<<endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "─── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ───"<<endl;
        choice = getValidatedMenuChoice("Enter your choice: ", 1, 6);

        switch (choice)
        {
            case 1: addUser(); break;
            case 2: showUsers(); break;
            case 3: updateInfo(); break;
            case 4: deleteUser(); break;
            case 5: searchUser(); break;
            case 6: {
                        cout<<"Returning to main menu..."<<endl;
                        menu();
                        break;
                    }
            default: cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice !=6);
}
void addUser()
{
    User newUser;
    string name, email, date;
    int newID;
    newID = generateID();
    newUser.setUserID(newID);
    cin.ignore();
    cout <<endl<<"Enter Name: "<<endl;
    getline(cin, name);
    newUser.setName(name);
    email = getValidatedEmail("Enter Email: \n");
    newUser.setEmail(email);
    date = getValidatedDate("Enter Registration Date (DD/MM/YYYY): \n");
    newUser.setRegistrationDate(date);
    newUser.setStudyMinutes(0);
    ofstream file("users.txt", ios::app);
    if (file.is_open())
    {
        file<<endl<<newUser.getUserID()<<"|"
        <<newUser.getName()<<"|"
        <<newUser.getEmail()<<"|"
        <<newUser.getRegistrationDate()<<"|"
        <<newUser.getStudyMinutes()<<endl;
        file.close();
        cout<<endl<<"User added successfully !"<<endl;
        cout<<"Your User ID is: "<<newID<<endl;
    }
    else cout<<"Error : could not open file :("<<endl;
}
int generateID()
{
    int maxID =0;
    int id;
    string line;
    ifstream file("users.txt");
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
User readUser(string line)
{
    User user;
    if(line.empty()) return user;
    vector<string> things;
    string thing;
    size_t pos =0;
    while ((pos = line.find('|'))!= string::npos)
    {
        thing = line.substr(0, pos);
        things.push_back(thing);
        line.erase(0, pos+1);
    }
    things.push_back(line);

    user.setUserID(stoi(things[0]));
    user.setName(things[1]);
    user.setEmail(things[2]);
    user.setRegistrationDate(things[3]);
    user.setStudyMinutes(stoi(things[4]));
    return user;
}

void showUsers()
{
    ifstream file("users.txt");
    string line;
    int count=0;
    if (!file.is_open())
    {
        cout<<"Error : could not open file :("<<endl;
        return;
    }
    cout<<endl<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
    cout<<"\t"<<"ALL REGISTERED USERS :"<<endl;
    cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
    while (getline(file, line))
    {
        if(line.empty()) continue;
        User user = readUser(line);
        user.displayInfo();
        count++;
    }
    file.close();
    if (count==0) cout<<endl<<"No users registered yet."<<endl;
    else cout<<endl<<"Total Users: "<<count<<endl;
}
void updateInfo()
{
    int uID = getValidatedPositiveInt("Enter User ID to update your info: ");
    vector<User> users;
    ifstream file("users.txt");
    string line;
    bool found=false;
    int pos=0;
    while (getline(file, line))
    {
        if(line.empty()) continue;
        User user = readUser(line);
        users.push_back(user);
        if (user.getUserID()==uID)
        {
            found=true;
            pos=users.size()-1;
        }
    }
    file.close();
    if(!found)
    {
        cout<<endl<<"No user found, please ensure you entered the correct ID, or contact the administrator."<<endl;
        return;
    }
    cout<<"----Current Info----"<<endl;
    users[pos].displayInfo();
    int choice = getValidatedMenuChoice("\nWhat would you like to update?\n1. Name\n2. Email\n3. Both\nEnter your choice: ", 1, 3);
    cin.ignore();
    if (choice==1||choice==3)
    {
        string newname;
        cout<<endl<<"Enter new Name: ";
        getline(cin, newname);
        users[pos].setName(newname);
    }
    if (choice==2||choice==3)
    {
        string newemail;
        cout<<endl<<"Enter new Email: ";
        getline(cin, newemail);
        users[pos].setEmail(newemail);
    }
    ofstream outfile("users.txt");
    for (size_t i=0; i<users.size(); i++)
    {
        outfile<<users[i].getUserID()<<"|"
        <<users[i].getName()<<"|"
        <<users[i].getEmail()<<"|"
        <<users[i].getRegistrationDate()<<"|"
        <<users[i].getStudyMinutes()<<endl;
    }
    outfile.close();
    cout<<endl<<"User info updated successfully!"<<endl;
}
void deleteUser()
{
    int dID = getValidatedPositiveInt("Enter the user ID to delete: ");
    vector<User> users;
    ifstream file("users.txt");
    string line;
    bool found=false;
    while (getline(file, line))
    {
        if(line.empty()) continue;
        User user = readUser(line);
        if (user.getUserID()==dID) found=true;
        else users.push_back(user);
    }
    file.close();
    if(!found)
    {
        cout<<endl<<"No user found with the given ID."<<endl;
        return;
    }
    char confirm;
    cout<<endl<<"Are you sure you want to delete this user? (y/n): ";
    cin>>confirm;
    if (confirm=='y'||confirm=='Y')
    {
        ofstream outfile("users.txt");
        for (size_t i=0; i<users.size(); i++)
        {
            outfile<<users[i].getUserID()<<"|"
            <<users[i].getName()<<"|"
            <<users[i].getEmail()<<"|"
            <<users[i].getRegistrationDate()<<"|"
            <<users[i].getStudyMinutes()<<endl;
        }
        outfile.close();
        cout<<endl<<"User deleted successfully!"<<endl;
    }
    else cout<<endl<<"Deletion cancelled."<<endl;
}
void searchUser()
{
    int sChoice = getValidatedMenuChoice("\nSearch User by:\n1. User ID\n2. Name\nEnter your choice: ", 1, 2);
    if (sChoice==1)
        searchByID();
    else if (sChoice==2)
        searchByName();
    else cout<<endl<<"Invalid choice."<<endl;
}
void searchByID()
{
    int sID = getValidatedPositiveInt("Enter User ID to search: ");
    ifstream file("users.txt");
    string line;
    bool found=false;
    while (getline(file, line))
    {
        if(line.empty()) continue;
        User user = readUser(line);
        if (user.getUserID()==sID)
        {
            cout<<endl<<"User found:"<<endl;
            user.displayInfo();
            found=true;
            break;
        }
    }
    file.close();
    if (!found) cout<<endl<<"No user found with the given ID."<<endl;
}
void searchByName()
{
    string sName;
    cout<<"Enter Name to search: ";
    cin.ignore();
    getline(cin, sName);
    ifstream file("users.txt");
    string line;
    bool found=false;
    cout<<endl<<"Search Results:"<<endl;
    while (getline(file, line))
    {
        if(line.empty()) continue;
        User user = readUser(line);
        if (user.getName()==sName)
        {
            user.displayInfo();
            found=true;
        }
    }
    file.close();
    if (!found) cout<<endl<<"No user found with the given Name."<<endl;
}

bool userExists(int id)
{
    ifstream file("users.txt");
    string line;
    while (getline(file, line))
    {
        if(line.empty()) continue;
        User user = readUser(line);
        if (user.getUserID() == id)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
void updateUserStudyTime(int userID, int minutesToAdd)
{
    vector<User> users;
    ifstream file("users.txt");
    string line;
    while (getline(file, line))
    {
        if(line.empty()) continue;
        User user = readUser(line);
        if (user.getUserID() == userID)
        {
            int currentMinutes = user.getStudyMinutes();
            currentMinutes += minutesToAdd;
            user.setStudyMinutes(currentMinutes);
        }
        users.push_back(user);
    }
    file.close();
    ofstream outfile("users.txt");
    for (size_t i = 0; i < users.size(); i++)
    {
        outfile << users[i].getUserID() << "|"
                << users[i].getName() << "|"
                << users[i].getEmail() << "|"
                << users[i].getRegistrationDate() << "|"
                << users[i].getStudyMinutes() << endl;
    }
    outfile.close();
}
#endif