# 📚 Study Management System

A console-based C++ application designed to help university students organize their academic life — from tracking study sessions to managing tasks and monitoring progress.

---

## 👩‍💻 Team Members

| Name | Module |
|------|--------|
| Malak Medhat | Task Management |
| Habiba Ahmed | Study Session Timer |
| Rana Mohamed | User Management |
| Basmala Adel | Authentication & Login |

---

## 🗂️ Features

### 🔐 Authentication (Basmala Adel)
- User registration and login with username/password
- Change password functionality
- Forgot password recovery
- Account deletion

### 👤 User Management (Rana Mohamed)
- Add, view, update, and delete user profiles
- Search users by ID or name
- Tracks total accumulated study time per user

### ✅ Task Management (Malak Medhat)
- Add tasks with name, notes, and priority (Low / Medium / High)
- View all tasks split into pending and completed
- Edit task details (name, note, priority)
- Delete tasks
- Mark tasks as completed with an automatic completion date stamp

### ⏱️ Study Session Timer (Habiba Ahmed)
- Start a custom-duration study session
- Built-in Pomodoro mode (4 × 25 min focus + breaks)
- View past sessions and today's sessions
- Real-time countdown timer in the terminal
- Sessions are saved and linked to user profiles

### 📊 Statistics & Reports
- Task completion rate with a progress bar
- Subject-wise task analysis
- Study time report broken down by subject
- Weekly summary with motivational feedback

---

## 🛠️ Tech Stack

- **Language:** C++
- **Standard:** C++11 or later
- **Storage:** Plain text files (`users.txt`, `Tasks.txt`, `session_data.txt`, `data.txt`)
- **Libraries:** Standard Library only (`<iostream>`, `<fstream>`, `<vector>`, `<map>`, `<ctime>`, `<thread>`)

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler (g++ recommended)

### Compile
```bash
g++ -std=c++11 passwordmanager.cpp -o StudyManagement
```

### Run
```bash
./StudyManagement
```

> On first launch, register an account from the login screen.

---

## 📁 File Structure

```
StudyManagement/
├── passwordmanager.cpp      # Entry point, login/register logic
├── userManagement.cpp       # User profile management
├── TaskManagement.cpp       # To-do list system
├── Timer.cpp                # Study session timer & Pomodoro
├── Statistics.cpp           # Reports and analytics
├── data.txt                 # Login credentials
├── users.txt                # User profiles
├── Tasks.txt                # Task records
└── session_data.txt         # Study session history
```

---

## 📝 Data Format

**users.txt:** `userID|name|email|registrationDate|studyMinutes`

**Tasks.txt:** `taskNo|userID|taskName|note|priority|isCompleted|completionDate`

**session_data.txt:** `sessionID|userID|subject|sessionType|startTime|endTime|duration`

---

## ⚠️ Notes

- Passwords are stored in plain text — this project is intended for educational purposes only.
- All data persists between runs via local `.txt` files.
- The timer uses real-time `sleep` calls, so the terminal must remain open during a session.

---

## 🎓 About

This is a first-year university group project built to practice object-oriented programming, file I/O, and modular C++ design.
