//
//  main.cpp
//  DataStructures 2 Ex 4
//
//  Created by Jacques Benzakein on 1/10/19.
//  Copyright © 2019 Q Technologies. All rights reserved.
//

#include <iostream>
#include <map>
//#include "graphs.h"

using namespace std;

class Edge;

class Vertex{
public:
    //Name of this particular task
    string task;
    //Pointer to the start of a linked list of edges to other tasks that need to come after this one
    Edge* edgelist;
    
    Vertex(){}
    
    Vertex(string taskName){
        task = taskName;
    }
    
};

class Edge{
    Vertex from;
    Vertex to;
    
    int distance;
    
    Edge(){
        
    }
    
};

class Graph{
public:
    
    map<string, Vertex> tasklist;
    
    Graph(){
        
    }
    
    bool addv(string taskName){
        Vertex vertexToAdd = Vertex(taskName);
        return true;
    }
    
    bool adde(string from, string to){
        return true;
    }
    
    void printAll(){
        //For every node, print all its edges
    }
    
    void topologicalSort(){
        
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
                    cout << "byebye";  break;
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
