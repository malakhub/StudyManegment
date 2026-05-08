#ifndef TASKMANAGEMENT_CPP
#define TASKMANAGEMENT_CPP
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;
void menu();
void showAllTasks(int);
void addTask();
void editTask();
string CurrentDate();
void deleteTask();
void ToDOMenu();
void markTask();
class ToDoList
{
private:
    int UserID = 0;
    int TaskNo = 0;
    string TaskName, Note, Priority, CompletionDate = "PENDING";
    bool isCompleted = false;

public:
    void setUserID(int id) { UserID = id; }
    void setTaskNo(int no) { TaskNo = no; }
    void setTaskName(string name) { TaskName = name; }
    void setTaskNote(string note) { Note = note; }
    void setTaskPriority(string Priority) { this->Priority = Priority; }
    void setCompleted(bool status) { isCompleted = status; }
    void setCompletionDate(string date) { CompletionDate = date; }

    int getUserID() { return UserID; }
    int getTaskNo() { return TaskNo; }
    string getTaskName() { return TaskName; }
    string getTaskNote() { return Note; }
    string getTaskPriority() { return Priority; }
    bool getCompleted() { return isCompleted; }
    string getCompletionDate() { return CompletionDate; }

    void display()
    {
        cout << "\n --- Task Details >⩊< --- \n";
        cout << "User ID: " << getUserID() << "\n";
        cout << "Task No.: " << getTaskNo() << "\n";
        cout << "Task Name: " << getTaskName() << "\n";
        cout << "Note: " << getTaskNote() << "\n";
        cout << "Priority: " << getTaskPriority() << "\n";
        if (isCompleted)
            cout << "Status: Completed On " << getCompletionDate() << "\n";
        else
            cout << "Status: Pending\n";
        cout << "─── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ───── ⋆⋅☆⋅⋆ ────\n";
    }
};
ToDoList Organizer(string Line)
{
    ToDoList tasks;
    string str;
    vector<string> elements;
    size_t pos = 0;
    while ((pos = Line.find('|')) != string::npos)
    {
        str = Line.substr(0, pos);
        elements.push_back(str);
        Line.erase(0, pos + 1);
    }
    elements.push_back(Line);
    if (elements.size() == 7)
    {
        tasks.setTaskNo(stoi(elements[0]));
        tasks.setUserID(stoi(elements[1]));
        tasks.setTaskName(elements[2]);
        tasks.setTaskNote(elements[3]);
        tasks.setTaskPriority(elements[4]);
        tasks.setCompleted(elements[5] == "1");
        tasks.setCompletionDate(elements[6]);
    }
    return tasks;
}
void showAllTasks(int userId = -1)
{
    int id, cCount = 0, pCount = 0;
    string line;
    if (userId == -1)
    {
        id = getValidatedPositiveInt("Enter Your ID: ");
    }
    else
    {
        id = userId;
    }

    ifstream file("Tasks.txt");
    cout << "°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･\n   --- ★ Your Tasks ★ ---\n°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･\n";
    cout << "\tPENDING TASKS\n";
    while (getline(file, line))
    {
        ToDoList M = Organizer(line);
        if (M.getCompleted() == false && M.getUserID() == id)
        {
            pCount++;
            cout << pCount << ". " << M.getTaskName() << "  —  (ID: " << M.getTaskNo() << ", Priority: " << M.getTaskPriority() << ")\n";
        }
    }
    file.clear();  // EOF handling
    file.seekg(0); // read form the begin of file
    cout << "\tCOMPLETED TASKS\n";
    while (getline(file, line))
    {
        ToDoList M = Organizer(line);
        if (M.getCompleted() == true && M.getUserID() == id)
        {
            cCount++;
            cout << cCount << ". " << M.getTaskName() << "  —  (ID: " << M.getTaskNo() << ", Priority: " << M.getTaskPriority() << ")\n";
        }
    }
    file.close();

    cout << "\n°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･";
    cout << "\nPending: " << pCount;
    cout << "\nCompleted: " << cCount;
    cout << "\nTotal: " << (pCount + cCount);
    cout << "\n°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･\n";
}
void SaveToFile(ToDoList task)
{
    ofstream file("Tasks.txt", ios::app);
    if (file.is_open())
    {
        file << task.getTaskNo() << "|" << task.getUserID() << "|"
             << task.getTaskName() << "|" << task.getTaskNote() << "|"
             << task.getTaskPriority() << "|";
        if (task.getCompleted())
            file << "1|";
        else
            file << "0|";
        file << task.getCompletionDate() << "\n";
    }
}
void addTask()
{
    ToDoList task;
    int id, no;
    string name, note, priority, line;
    id = getValidatedPositiveInt("Enter Your ID: ");
    task.setUserID(id);
    /*Task No*/ int max = 0;
    int a;
    ifstream file("Tasks.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            a = stoi(line.substr(0, line.find('|')));
            if (a > max)
                max = a;
        }
        file.close();
    }
    no = max + 1;
    task.setTaskNo(no);
    cin.ignore();
    cout << "Enter Task Name: ";
    getline(cin, name);
    task.setTaskName(name);
    cout << "Enter Your Note: ";
    getline(cin, note);
    task.setTaskNote(note);
    priority = getValidatedPriority();
    task.setTaskPriority(priority);
    task.setCompleted(false);
    task.display();
    do
    {
        int saveChoice = getValidatedMenuChoice("Click 1 to Save Task or 0 to Cancel: ", 0, 1);
        if (saveChoice == 1)
        {
            SaveToFile(task);
            cout << "Task Saved Successfully!!\n";
            break;
        }
        else if (saveChoice == 0)
        {
            cout << "Task Not Saved.\n";
            break;
        }
    } while (true);
}
void editTask()
{
    int id, tn, a, i = -1, j = 0;
    string line;
    cout << "Enter Your ID: ";
    cin >> id;

    cout << "\tYOUR TASKS:\n";
    ifstream filee("Tasks.txt");
    while (getline(filee, line))
    {
        ToDoList M = Organizer(line);
        if (M.getUserID() == id)
        {
            j++;
            cout << j << ". " << M.getTaskName() << "  —  (ID: " << M.getTaskNo() << ", Priority: " << M.getTaskPriority() << ")\n";
        }
    }
    filee.close();

    tn = getValidatedPositiveInt("Enter The ID Of The Task You Want To Edit: ");
    vector<ToDoList> lines;
    ifstream file("Tasks.txt");
    while (getline(file, line))
    {
        ToDoList b = Organizer(line);
        lines.push_back(b);
        if (b.getUserID() == id && b.getTaskNo() == tn)
            i = lines.size() - 1;
    }
    file.close();
    if (i == -1)
    {
        cout << "Task not found!\n";
        return;
    }
    do
    {
        cout << "\n --- Choose What You Want To Edit <3 --- \n";
        cout << "1. Task Name: " << lines[i].getTaskName() << "\n";
        cout << "2. Note: " << lines[i].getTaskNote() << "\n";
        cout << "3. Priority: " << lines[i].getTaskPriority() << "\n";
        cout << "4. Exit" << endl;
        cout << "°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･\n";
        a = getValidatedMenuChoice("Enter your choice: ", 1, 4);
        switch (a)
        {
        case 1:
        {
            string tm;
            cout << "Enter The New Task Name: ";
            cin.ignore();
            getline(cin, tm);
            lines[i].setTaskName(tm);
            lines[i].display();
            break;
        }
        case 2:
        {
            string tm;
            cout << "Enter The New Note: ";
            cin.ignore();
            getline(cin, tm);
            lines[i].setTaskNote(tm);
            lines[i].display();
            break;
        }
        case 3:
        {
            string tm;
            cout << "Enter The New Priority: ";
            cin.ignore();
            getline(cin, tm);
            lines[i].setTaskPriority(tm);
            lines[i].display();
            break;
        }
        case 4:
        {
            cout << "Saving changes...\n";
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n";
        }
        }
    } while (a != 4);
    // delete
    ofstream outfile("Tasks.txt"); // Defult= Erase mode.
    for (int i = 0; i < lines.size(); i++)
    {
        outfile << lines[i].getTaskNo() << "|" << lines[i].getUserID() << "|"
                << lines[i].getTaskName() << "|" << lines[i].getTaskNote() << "|"
                << lines[i].getTaskPriority() << "|";
        if (lines[i].getCompleted())
            outfile << "1|";
        else
            outfile << "0|";
        outfile << lines[i].getCompletionDate() << "\n";
    }
}
string CurrentDate()
{
    time_t now = time(0);
    tm *t = localtime(&now);
    return (to_string(t->tm_mday) + "/" + to_string(1 + t->tm_mon) + "/" + to_string(1900 + t->tm_year));
}
void ToDoMenu()
{
    int choice;
    do
    {
        cout << "°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･" << endl;
        cout << "--- To-Do List Menu >⩊< --- \n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Edit Task\n";
        cout << "4. Delete Task\n";
        cout << "5. Mark Task as Completed\n";
        cout << "6. Exit\n";
        cout << "°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･°❀⋆.ೃ࿔*:･ \n";
        choice = getValidatedMenuChoice("Enter your choice: ", 1, 6);
        switch (choice)
        {
        case 1:
        {
            addTask();
            break;
        }
        case 2:
        {
            showAllTasks();
            break;
        }
        case 3: // Edit Task
        {
            editTask();
            break;
        }
        case 4: // Delete Task
        {
            deleteTask();
            break;
        }
        case 5: // Mark Task as Completed
        {
            markTask();
            break;
        }
        case 6: // Exit
        {
            cout << "Returning to main menu...\n";
            menu();
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n";
        }
        }
    } while (choice != 6);
}
void deleteTask()
{
    int id, tn;
    id = getValidatedPositiveInt("Enter Your ID: ");
    ifstream file("Tasks.txt");
    string line;
    vector<string> lines;
    int j = 0;
    cout << "\tYOUR TASKS:\n";
    ifstream filee("Tasks.txt");
    while (getline(filee, line))
    {
        ToDoList M = Organizer(line);
        if (M.getUserID() == id)
        {
            j++;
            cout << j << ". " << M.getTaskName() << "  —  (ID: " << M.getTaskNo() << ", Priority: " << M.getTaskPriority() << ")\n";
        }
    }
    filee.close();
    tn = getValidatedPositiveInt("Select The ID Of TASK You Want To Delete\n");
    while (getline(file, line))
    {
        ToDoList b = Organizer(line);
        if (!(b.getUserID() == id && b.getTaskNo() == tn))
        {
            lines.push_back(line);
        }
    }
    file.close();
    ofstream outfile("Tasks.txt");
    for (int i = 0; i < lines.size(); i++)
    {
        outfile << lines[i] << "\n";
    }
    cout << "Task Deleted Successfully </3 !!\n";
}
void markTask()
{
    int id;
    int j = 0;
    id = getValidatedPositiveInt("Enter Your ID: ");
    cout << "\tYOUR TASKS:\n";
    ifstream filee("Tasks.txt");
    string line;
    while (getline(filee, line))
    {
        ToDoList M = Organizer(line);
        if (M.getUserID() == id)
        {
            j++;
            cout << j << ". " << M.getTaskName() << "  —  (ID: " << M.getTaskNo() << ", Priority: " << M.getTaskPriority() << ")\n";
        }
    }
    filee.close();
    int taskId = getValidatedPositiveInt("Enter Task ID To Mark Completed\n");
    vector<ToDoList> tasks;
    ifstream file("Tasks.txt");
    bool found = false;
    int i = 0;

    while (getline(file, line))
    {
        ToDoList r = Organizer(line);
        tasks.push_back(r);
        if (r.getTaskNo() == taskId && r.getUserID() == id)
        {
            found = true;
            i = tasks.size() - 1;
        }
    }
    file.close();
    if (tasks[i].getCompleted())
    {
        cout << "\nTask is already completed <3 !!\n";
        return;
    }
    tasks[i].setCompleted(true);
    tasks[i].setCompletionDate(CurrentDate());
    ofstream outFile("Tasks.txt");
    for (int i = 0; i < tasks.size(); i++)
    {
        outFile << tasks[i].getTaskNo() << "|"
                << tasks[i].getUserID() << "|"
                << tasks[i].getTaskName() << "|"
                << tasks[i].getTaskNote() << "|"
                << tasks[i].getTaskPriority() << "|"
                << (tasks[i].getCompleted() ? "1" : "0") << "|"
                << tasks[i].getCompletionDate() << endl;
    }
    outFile.close();

    cout << "\n✓ Task marked as complete!\n";
    cout << "Great job finishing: " << tasks[i].getTaskName() << endl;
}
#endif