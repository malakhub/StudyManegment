#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include<sstream>
using namespace std;

// Input validation helper functions (defined before includes so they're available to included files)
int getValidatedInt(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input! Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

int getValidatedPositiveInt(const string& prompt) {
    int value;
    while (true) {
        value = getValidatedInt(prompt);
        if (value > 0) {
            return value;
        }
        cout << "Please enter a positive number (greater than 0): ";
    }
}

int getValidatedMenuChoice(const string& prompt, int minChoice, int maxChoice) {
    int choice;
    while (true) {
        choice = getValidatedInt(prompt);
        if (choice >= minChoice && choice <= maxChoice) {
            return choice;
        }
        cout << "Invalid choice! Please enter a number between " << minChoice << " and " << maxChoice << ": ";
    }
}

string getValidatedPriority() {
    string priority;
    while (true) {
        cout << "Enter Priority (Low/Medium/High): ";
        cin >> priority;
        if (priority == "Low" || priority == "Medium" || priority == "High" || 
            priority == "low" || priority == "medium" || priority == "high") {
            // Capitalize first letter
            if (priority[0] >= 'a' && priority[0] <= 'z') {
                priority[0] = priority[0] - 'a' + 'A';
            }
            return priority;
        }
        cout << "Invalid priority! Please enter Low, Medium, or High: ";
    }
}

bool isValidDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[2] != '/' || date[5] != '/') return false;
    
    try {
        int day = stoi(date.substr(0, 2));
        int month = stoi(date.substr(3, 2));
        int year = stoi(date.substr(6, 4));
        
        if (day < 1 || day > 31) return false;
        if (month < 1 || month > 12) return false;
        if (year < 1900 || year > 2100) return false;
        
        return true;
    } catch (...) {
        return false;
    }
}

string getValidatedDate(const string& prompt) {
    string date;
    while (true) {
        cout << prompt;
        getline(cin, date);
        if (isValidDate(date)) {
            return date;
        }
        cout << "Invalid date format! Please enter date in DD/MM/YYYY format: ";
    }
}

bool isValidEmail(const string& email) {
    if (email.find('@') == string::npos) return false;
    if (email.find('.') == string::npos) return false;
    if (email.length() < 5) return false;
    return true;
}

string getValidatedEmail(const string& prompt) {
    string email;
    while (true) {
        cout << prompt;
        getline(cin, email);
        if (isValidEmail(email)) {
            return email;
        }
        cout << "Invalid email format! Please enter a valid email address: ";
    }
}

// Include other files after validation functions are defined
#include"Statistics.cpp"
#include"TaskManagement.cpp"
#include"UserManagement.cpp"
#include"Timer.cpp"

string name ,password;
void delete_account()
{
    ifstream fin("data.txt");
    string passline;
    getline(fin,passline);
    fin.close();
    passline="";
    ofstream fout("data.txt");
    fout<<passline;
    cout<<"Your Account was deleted successfully."<<endl;
    return ;
}
void change_password()
{
    string searchName;
    cout << "Enter your username: ";
    cin >> searchName;
    cout<<"Enter your old password: ";
    cin>>password;
    cout<<endl;
    ifstream fin("data.txt");
    string line;
    string allData = "";
    bool userFound = false;
    bool passwordChanged = false;
    while(getline(fin, line))
    {
        if(line.find("Name:") != string::npos)
        {
            allData += line + "\n";
            size_t pos = line.find(":");
            string currentUser = line.substr(pos + 1);
            if(currentUser == searchName)
            {
                userFound = true;
            }
            else
            {
                userFound = false;
            }
        }
        else if(line.find("Password:") != string::npos)
        {
            if(userFound && !passwordChanged)
            {
                string newpassword;
                cout << "Enter new password: ";
                cin >> newpassword;
                allData += "Password:" + newpassword + "\n";
                passwordChanged = true;
            }
            else
            {
                allData += line + "\n";
            }
        }
        else
        {
            allData += line + "\n";
        }
    }
    fin.close();
    if(passwordChanged)
    {
        ofstream fout("data.txt");
        fout << allData;
        fout.close();
        cout <<"\t"<<"Password changed successfully!"<<"\t"<< endl;
        cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
    }
    else
    {
        cout << "User not found!" << endl;
    }
    return ;
}
void menu()
{
    int choice;
    cout<<"Welcome To Study Management System"<<"\n"<<"\t"<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<"\t"<<endl;
    cout<<"1-User Management."<<"\n"<<"2-Study Session Management."<<"\n"<<"3-Task Management."<<"\n"<<"4-Statistics & Reports."<<"\n"<<"5-Change Password."<<"\n"<<"6-Exit."<<endl;
    cout<<"\t"<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<"\t"<<endl;

   do{
        choice = getValidatedMenuChoice("Please,enter your choice: ", 1, 6);
        switch(choice)
        {
        case 1:
        cout<<"User Management"<<endl;
        UserManagement();
        break;
        case 2:
        cout<<"Study Session Management"<<endl;
        SessionMenu();
        break;
        case 3:
        ToDoMenu();
        break;
        case 4:
        statisticMenu();
        break;
        case 5:
        change_password();
        break;
        case 6:
        cout<<"Thank you for using Study Management System."<<endl;
        break;
        default:
        cout<<"Invalid choice! Please,try again."<<endl;
       }
    }while(choice>0 && choice<6);
    return ;
}
void forget_password()
{
    string searchName;
    cout << "Enter your username: ";
    cin >> searchName;
    ifstream fin("data.txt");
    string line;
    string allData = "";
    bool userFound = false;
    bool passwordChanged = false;
    while(getline(fin, line))
    {
        if(line.find("Name:") != string::npos)
        {
            allData += line + "\n";
            size_t pos = line.find(":");
            string currentUser = line.substr(pos + 1);
            if(currentUser == searchName)
            {
                userFound = true;
            }
            else
            {
                userFound = false;
            }
        }
        else if(line.find("Password:") != string::npos)
        {
            if(userFound && !passwordChanged)
            {
                string newpassword;
                cout << "Enter new password: ";
                cin >> newpassword;
                allData += "Password:" + newpassword + "\n";
                passwordChanged = true;
            }
            else
            {
                allData += line + "\n";
            }
        }
        else
        {
            allData += line + "\n";
        }
    }
    fin.close();
    if(passwordChanged)
    {
        ofstream fout("data.txt");
        fout << allData;
        fout.close();
        cout<<"\t"<<"Password changed successfully"<<endl;
        cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<"\t"<<endl;
    }
    else
    {
        cout << "User not found!" << endl;
    }
}
void login()
{
    cout<<"Enter username:"<<endl;
    cin>>name;
    cout<<"Enter password:"<<endl;
    cin>>password;
    ifstream file("data.txt");
    if(file.is_open())
        {
            string line;
            string name1="";
            string password1="";
            bool found =false;
            while(getline(file,line))
                {
                    if(line.find("Name:") !=string::npos)
                        {
                            size_t position1=line.find(":");
                            name1=line.substr(position1+1);
                        }
                    if(line.find("Password:")!=string::npos)
                        {
                            size_t position2=line.find(":");
                            password1=line.substr(position2+1);
                            if(name1==name && password1==password)
                                {
                                    found =true;
                                    break;
                                }
                        }

                }
            file.close();
            if(found)
                {
                    cout<<"\t"<<"Login sucessful!"<<endl;
                    cout<<"─── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ───"<<endl;
                    menu();
                }
            else 
                {
                    cout<<"Invalid username or password"<<endl;
                    cout<<"─── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ──"<<endl;
                    cout<<"1-Forget password"<<endl;
                    cout<<"2-Exit"<<endl;
                    int choice2 = getValidatedMenuChoice("Enter your choice: ", 1, 2);
                    switch(choice2)
                        {
                            case 1:
                                {
                                    forget_password();
                                    break;
                                }
                            case 2:
                                    {
                                        cout<<"Thank you for using study management system"<<endl;
                                        return ;
                                    }
                            default: cout<<"Invalid choice"<<endl;
                        }
                }
        }
    else cout<<"file is not found"<<endl;
    return ;
}
void registeration()
{
    cout<<"Enter username:"<<endl;
    cin>>name;
    cout<<"Enter password:"<<endl;
    cin>>password;
    ofstream file("data.txt",ios::app);
    file <<"Name"<<":"<<name<<endl;
    file <<"Password"<<":"<<password<<endl;
    file.close();
    cout<<"\t"<<"Registration successful"<<endl;
    cout<<"─── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ──"<<endl;
    return ;
}
void loginpage()
{
    int choice1;
    do{
        cout<<"\t"<<"Study management system - Login"<<"\t"<<endl;
        cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
        cout<<"1- login."<<endl;
        cout<<"2- Register."<<endl;
        cout<<"3- Delete Account."<<endl;;
        cout<<"4- Exit."<<endl;
        cout<<"°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･"<<endl;
        choice1 = getValidatedMenuChoice("Please,enter your choice: ", 1, 4);
        switch(choice1)
        {
            case 1:
                    {
                        login();
                        break;
                    }
            case 2:
                    {
                        registeration();
                        break;
                    }
            case 3:
                    {
                        delete_account();
                        break;
                    }
            case 4:
                    {
                        cout<<"<<Thank you for using study management system>>"<<endl;
                        return ;
                    } 
            default: cout<<"Invalid choice please try again!"<<endl;
        }
    }while(choice1!=4);
}
int main()
{
    loginpage();
    return 0;
}


