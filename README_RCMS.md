# 🍽️ Restaurant Chain Management System (RCMS)

A C++ data structures project built for **"Koul Hani"** — a food service retail chain — to efficiently manage, analyze, and optimize restaurant data across Algeria.

> 📚 Course: Data Structures and Algorithms 2 — ENSIA (Dec 2023)  
> 👩‍💻 Team: Bouzira Maroua · Boubenider Hanane · Latreche Dhikra Maram · Ben Chabane Rafida Djomana  
> 🏫 Supervisor: Prof. Ahmed Guessoum

---

## 📌 Problem Statement

The company needs a system to:
- Manage data for owned and franchised restaurants (name, ID, employees, sales, costs...)
- Track performance metrics: ROI on publicity, cuisine ratings, monthly sales
- Determine monthly national prize winners per cuisine
- Search restaurants by wilaya, city, district, or time period

---

## 🏗️ System Architecture

### Data Structures Used

| Structure | Purpose |
|---|---|
| **Binary Search Tree (BST)** | Core restaurant storage, ordered by ID |
| **AVL Tree** | Self-balancing extension for large datasets |
| **Stack** | Determining monthly prize winners per cuisine |
| **Vectors** | Hierarchical storage of daily/monthly/yearly data |

### Key Classes & Structs

```
RestaurantChainManagementSystem
│
├── Restaurant (struct)
│   ├── SalesHash          → daily / monthly / yearly sales per cuisine
│   └── CostHash           → daily / monthly / yearly costs
│
├── Cuisine[5]             → Algerian, Syrian, Chinese, Indian, European
└── LinkFile               → Unique ID generation per restaurant
```

---

## ⚙️ Features

### 🔍 Restaurant Search
- Search by **wilaya**, **city**, **district**
- Filter by **year**, **month**, or **date range**

### 📊 Sales & Costs Tracking
- Record and retrieve **daily / monthly / yearly** sales & costs
- Per-cuisine breakdown across 5 cuisine types
- Total sales between any two dates

### 🏆 Winner Determination
- Monthly national prize per cuisine based on **adjusted sales + ratings**
- Stack-based traversal runs in **O(n)** — efficient for large datasets

### 📈 Ratio Analysis
- ROI on publicity = monthly sales / publicity spend
- List ratios by wilaya, city, or specific restaurant ID

### 🆔 Unique ID Generation
- IDs encode wilaya + city + district + auto-increment
- ASCII-based hashing ensures uniqueness across the system

---

## 🌳 BST vs AVL Performance

For this project's dataset size, BST was faster due to lower overhead. AVL shines on larger, more dynamic datasets.

```
Running Time (ms)
│
6000 │                                        ● AVL
     │                               ●
4000 │                      ●
     │             ●
2000 │    ●  ● BST                            ● BST
     │
     └────────────────────────────────────────
       50   115   179   243   279   351   (restaurants)
```

---

## 📂 Data Files

| File | Content |
|---|---|
| `dba.csv` | Restaurant info: name, ownership, employees, wilaya, city, district, date, ID |
| `dbaForSalesCosts.csv` | Daily sales & costs per cuisine per restaurant |
| `Rating.csv` | Monthly cuisine ratings per restaurant |

> ⚠️ **Before running:** update file paths in `main()` and in `calculateAmount()` to match your local setup.

---

## 🧩 Work Division

| Member | Contributions |
|---|---|
| **Bouzira Maroua** | BST insert/remove, file reading, Sales & Cost structs & classes, ratio functions, website UI |
| **Latreche Dhikra Maram** | ID generation system (`LinkFile`), full database generation (3 CSV files), `GetRateOfACuisine` |
| **Boubenider Hanane** | `RestaurantChainManagementSystem` class, AVL Tree implementation, winner determination |
| **Ben Chabane Rafida** | System abstract structure, search functions, graphical representations, report writing |

---

## 🛠️ Tech Stack

![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=cplusplus&logoColor=white)
![HTML](https://img.shields.io/badge/HTML5-E34F26?style=flat&logo=html5&logoColor=white)
![CSS](https://img.shields.io/badge/CSS3-1572B6?style=flat&logo=css3&logoColor=white)
![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=flat&logo=javascript&logoColor=black)
![PHP](https://img.shields.io/badge/PHP-777BB4?style=flat&logo=php&logoColor=white)

---

## 📚 References

- Mark Allen Weiss — *Data Structures and Algorithm Analysis in C++*, 4th ed., Pearson (2014)
- Course materials by Prof. Ahmed Guessoum (ENSIA)
- LucidCharts for diagram design
