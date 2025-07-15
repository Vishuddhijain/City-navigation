# 🌆 City Navigation Assistant – Shimla 

A **console-based C++ application** designed to help tourists and locals explore **Shimla's scenic and historical landmarks** with ease. The system leverages **graph algorithms, intelligent routing, and user reviews** to deliver a complete travel guidance experience.

---

## 🚀 Project Overview

This project simulates a **smart navigation tool** for Shimla city, offering route planning, multiple path suggestions, travel estimations, and customized tourist recommendations. Built entirely in **C++**, it showcases the practical application of **data structures, algorithms, and file handling**.

---

## 🛠️ Technologies & Concepts

* **Language**: C++
* **Graph Representations**: Adjacency List & Matrix
* **Algorithms Used**:

  * Depth First Search (DFS)
  * Breadth First Search (BFS)
  * Dijkstra’s Algorithm (for shortest paths)
  * Backtracking (for full route discovery)
  * Greedy techniques (for transport mode optimization)
* **File I/O**: To manage user reviews and rating storage
* **Menu-Driven Console UI**: For interactive travel assistance

---

## 🔑 Key Functionalities

### 🔍 1. Complete Route Discovery

* Identifies **all possible paths** between two locations using **BFS, DFS, and recursive backtracking**.
* Allows users to explore scenic or offbeat travel routes.

### 🧽 2. Smart Path & Travel Analysis

* Calculates **shortest travel distance** with **Dijkstra’s algorithm**.
* Provides detailed trip data:

  * Estimated travel time
  * Fare calculation based on transport mode
* Transport Modes Supported:

  * 🏃 Walking
  * 🚗 Driving
  * 🚌 Public Transit
* Dynamically adjusts estimates based on **user choices and traffic scenarios**.

### 🌟 3. Ratings & Reviews

* View **real-time average ratings** for destinations.
* Leave your own **reviews and star ratings**.
* Data is stored using **persistent file handling** techniques.

### 🎯 4. Personalized Tourist Suggestions

* Recommends places based on interest categories:

  * Nature 🌲
  * Adventure 🧷
  * History 🏰
* Custom suggestions based on user preferences and travel goals.

---

## 📂 How to Use

### 📟 Setup Instructions

1. **Download or clone** the repository to your local system.
2. Compile using a C++ compiler (`g++`, `clang++`, etc.):

   ```bash
   g++ -o nav_app city_navigation.cpp
   ./nav_app
   ```
3. Follow the on-screen instructions from the **menu-driven interface**.

---

## 📸 Sample Console Menu

```
======= Shimla Travel Navigator =======
1. View All Routes
2. Find Shortest Route
3. Check Fare & Time
4. Explore Tourist Places
5. Rate a Destination
6. View Destination Reviews
7. Exit
```


