//
//  main.cpp
//  DataStructures 2 Ex 4
//
//  Created by Jacques Benzakein on 1/10/19.
//  Copyright © 2019 Q Technologies. All rights reserved.
//

#include <iostream>
#include <map>
#include <stack>
#include <queue>
//#include "graphs.h"

using namespace std;



class Edge;

class Vertex{
public:
    //Name of this particular task
    string task;
    //Pointer to the start of a linked list of edges to other tasks that need to come after this one
    Edge* edgelist;
    
    int inDegree = 0;
    int outDegree = 0;
    
    int startTime = 0;
    int endTime = 0;
    
    bool visited;
    
    Vertex(){}
    
    Vertex(string taskName){
        task = taskName;
        edgelist = nullptr;
        visited = false;
    }
    
};

stack<Vertex> s;

class Edge{
public:
    Vertex* from;
    Vertex* to;
    
    int distance;
    
    Edge* next;
    
    Edge(){}
    
//    Edge(string f, string t){
//        from = f;
//        to = t;
//    }
    
    Edge(Vertex* f, Vertex* t){
        from = f;
        to = t;
        next = nullptr;
    }
    
};

class Graph{
public:
    
    map<string, Vertex> tasklist;
    
    Graph(){
        
    }
    
    bool addv(string taskName){
        auto yeger = tasklist.find(taskName);
        if(yeger == tasklist.end()){
            Vertex vertexToAdd = Vertex(taskName);
            tasklist.insert({taskName, vertexToAdd});
            cout << "Inserted \"" << taskName << "\"\n";
            return true;
        }else{
            return false;
        }
    }
    
    bool adde(string from, string to){
        auto foundFrom = tasklist.find(from);
        auto foundTo = tasklist.find(to);
        if((foundFrom != tasklist.end()) && (foundTo != tasklist.end())){ //"from" and "to" have actually been entered into our list somewhere
            foundFrom->second.outDegree++;
            foundTo->second.inDegree++;
            Edge* current = foundFrom->second.edgelist;
            if(current == nullptr){
                cout << "list was empty, adding now.\n";
                tasklist.at(from).edgelist = new Edge(&(foundFrom->second), &(foundTo->second));
            }else{
                while (current->next != nullptr){
                    if(((*current).from->task == from) && ((*current).to->task == to)){
                        cout << "Edge already exists.\n";
                        return false;
                    }
                    current = current->next;
                }
                current->next = new Edge(&(foundFrom->second), &(foundTo->second));
                current->next->next = nullptr;
            }
            return true;
        }else{
            cout << "One of those tasks is not yet in the system\n";
            return false;
        }
        return true;
    }
    
    void printAll(){
        //For every node, print all its edges
        for(auto it = tasklist.cbegin(); it != tasklist.cend(); ++it){
            cout << it->second.task << ":\n";
            Edge* current = it->second.edgelist;
            while(current != nullptr){
                cout << "\tEdge from " << current->from->task << " to " << current->to->task << endl;
                current = current->next;
            }
        }
        
        cout << endl;
    }
    
    void topologicalSort(){
        queue<Vertex> inDegreeZero;
        //Find all nodes with indegree 0
        for(auto it = tasklist.begin(); it != tasklist.end(); ++it){
//            it->second.startTime = 0;
//            it->second.endTime = 0;
            it->second.visited = false;
            if(it->second.inDegree == 0){
                inDegreeZero.push(it->second);
            }
        }
        int time = 0;
        while(!inDegreeZero.empty()){
            time = DFS(time, &(inDegreeZero.front()));
            inDegreeZero.pop();
        }
        //TODO- Read off the stack
        if(!s.empty()){
            cout << s.top().task;
            s.pop();
            while(!s.empty()){
                Vertex current = s.top();
                cout << " -> " << current.task;
                s.pop();
            }
        }
    }
    
    int DFS(int time, Vertex* node){
        node->startTime = time++;
//        node->visited = false;
        Edge* current = node->edgelist;
        while(current != nullptr){
            if((*(current->to)).visited == false){
                time = DFS(time, (current->to));
            }
            current = current->next;
        }
        node->endTime = time++;
        node->visited = true;
        s.push(*(node));
        return time;
    }
};

int main(){
    Graph g;
    try{
        string v1, v2, name;
        int choice;
        cout << "Choose one of the following:\n";
        cout << "1-to add a task\n";
        cout << "2 - to add a priority rule\n";
        cout << "3 - to print all the graph\n";
        cout << "4 - print a recommended task order\n";
        cout << "5 - exit\n";
        do{
            cin >> choice;
            switch (choice){
                case 1:
                    cout << "Enter the task you want to add\n";
                    cin >> v1;
                    if (!g.addv(v1)){
                        cout << "ERROR\n";
                    }
                    break;
                case 2:
                    cout << "Enter earlier task and the later task\n";
                    cin >> v1 >> v2;
                    if (!g.adde(v1, v2)){
                        cout << "ERROR\n";
                    }
                    break;
                case 3:
                    cout << "The graph:\n";
                    g.printAll();
                    cout << endl;
                    break;
                case 4:
                    cout << "The recommended order:\n";
                    g.topologicalSort();
                    cout << endl;
                    break;
                case 5:
                    cout << "byebyebye";  break;
                default:
                    cout << "ERROR\n";
            }
        } while (choice != 5);
    }
    
    catch (string s){
        cout << s << endl;
    }
    
    return 0;
}
