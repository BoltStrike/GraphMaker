#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class node {
  char* name;
  vector<node*> connect;
public:
  char* getName();
  void setName(char*);
  vector<node*> getVect();
  void vectPush(node* toPush) {//function is in class as otherwise doesnt recognize connect
    connect.push_back(toPush);
  }
  void vectErase(vector<node*>::const_iterator it) {
    connect.erase(it);
  }
};

char* node::getName() {
  return name;
}

void node::setName(char* newname) {
  name = newname;
}

vector<node*> node::getVect() {
  return connect;
}


struct edge {
  node* firstp = NULL;
  node* secondp = NULL;
  char* weight;
};


void addVert(vector<node*>&);
void delVert(vector<node*>&, vector<edge*>&);
void addEdge(vector<node*>&, vector<edge*>&);
vector<node*> delEdge(vector<node*>&, vector<edge*>&);
void print(vector<node*>);
void printAllConn(vector<node*>);
void printSingleConn(vector<node*>, vector<node*>::const_iterator);
void printEdgeCont(vector<edge*>);


int main() {
  vector<node*> graph = vector<node*>(); //vector which holds all nodes
  vector<edge*> edgecont = vector<edge*>(); //vector that holds all edges
  bool run = true;
  cout << "Welcome to Graph Creator" << endl;
  while (run == true) { //will continue running till quit
    char* input = new char [80]; //takes in input
    cout << "What do you wish to do? (addv, removev, adde, removee, print, quit)" << endl;
    cin.getline(input, 80);
    if (strcmp(input, "addv") == 0) {
      addVert(graph); //runs add vertice
    }
    else if(strcmp(input, "removev") == 0) {
      delVert(graph, edgecont); //runs delete vert
    }
    else if(strcmp(input, "adde") == 0) {
      addEdge(graph, edgecont); //runs add edge
    }
    else if(strcmp(input, "removee") == 0) {
      graph = delEdge(graph, edgecont); //runs delete add 
    }
    else if (strcmp(input, "print") == 0) {
      print(graph); //prints adjacency
      printAllConn(graph); // prints out each node connection
      printEdgeCont(edgecont);//prints all edges
    }
    else if(strcmp(input, "quit") == 0) {
      run = false;
    }
  }
}

void addVert(vector<node*>& graph) {
  cout << "Please input a name for the node" << endl;
  node* newnode = new node(); //new node
  char* input = new char[80];
  cin.getline(input, 80); //takes from cin name for node
  newnode -> setName(input); //setname of node
  graph.push_back(newnode); //add to vector
}

void delVert(vector<node*>& graph, vector<edge*>& edgecont) {
  vector<node*>::iterator i;
  vector<node*>::iterator j;
  vector<edge*>::iterator k;
  if(edgecont.empty() == true) {
    cout << "aaassa";
  }
  cout << "Please input the name of the node to delete" << endl;
  node* newnode = new node();
  char* input = new char[80];
  cin.getline(input, 80);
  int count = 0;
  for (i=graph.begin(); i!=graph.end(); ++i){
    if((*i) != NULL && strcmp((*i) -> getName(), input) == 0) {
      graph.erase(i);
      break;
    }
    count ++;
  }
  cout << count;
  //if (count > 1) {
    for (i=graph.begin(); i!=graph.end(); ++i){
      vector<node*> connect = (*i) -> getVect();
      for(j = connect.begin(); j!=connect.end(); ++j) {
	if((*j) != NULL && strcmp((*j) -> getName(), input) == 0) {
	  connect.erase(j);
	  //break;
	}
      }
    }
    if(edgecont.empty() != true) {
      for(k=edgecont.begin(); k!=edgecont.end(); ++k) {
	if((*k) -> firstp -> getName() != NULL) {
	  if(strcmp((*k) -> firstp -> getName(), input) == 0 || strcmp((*k) -> secondp -> getName(), input) == 0) {
	    edgecont.erase(k);
	    //break;
	  }
	}
      }
    }
    
    //}
}

void addEdge(vector<node*>& graph, vector<edge*>& edgecont) {
  vector<node*>::const_iterator i; //iterators for the node vector
  vector<node*>::const_iterator j;
  edge* newe = new edge(); //makes new edge
  cout << "Please enter the first node" << endl;
  char* firstnode = new char[80]; 
  cin.getline(firstnode, 80); //gets first node for edge
  bool flag = false;
  for (i=graph.begin(); i!=graph.end(); ++i){ //runs thru node vector
    if(strcmp((*i) -> getName(), firstnode) == 0) { // if matches
      newe -> firstp = (*i); //records node which match input
      flag = true;
      break;
    }
  }
  if (flag == false){ //if the node wasnt found
    cout << "The node you entered does not exist" << endl;
    return;
  }

  cout << "Please enter the second node" << endl;
  char* secondnode = new char[80]; 
  cin.getline(secondnode, 80);//gets the second node name
  flag = false;
  for (j=graph.begin(); j!=graph.end(); ++j){//searches thru for second node
    if(strcmp((*j) -> getName(), secondnode) == 0) {
      newe -> secondp = (*j);//records second node
      (*i)-> vectPush(*j); //Add as a connection
      flag = true;
    }
  }
  if (flag == false){ //if node was not found
    cout << "The node you entered does not exist" << endl;
    return;
  }
  
  cout << "Please enter the weight" << endl; //takes edge weight
  char* weightval = new char[80];
  cin.getline(weightval, 80);
  newe -> weight = weightval; //puts into the edge
  edgecont.push_back(newe); //puts edge into vector
}

vector<node*> delEdge(vector<node*>& graph, vector<edge*>& edgecont) {
  vector<edge*>::const_iterator k;
  vector<node*>::const_iterator i;
  vector<node*>::const_iterator j;
  cout << "Please enter the first node" << endl;
  char* firstnode = new char[80];
  cin.getline(firstnode, 80);
   cout << "Please enter the second node" << endl;
  char* secondnode = new char[80];
  cin.getline(secondnode, 80);
  for(k=edgecont.begin(); k!=edgecont.end(); ++k) {
    if((*k) -> firstp -> getName() != NULL) {
      if(strcmp((*k) -> firstp -> getName(), firstnode) == 0 || strcmp((*k) -> secondp -> getName(), secondnode) == 0) {
	edgecont.erase(k);
	break;
      }
    }
  }
  cout<< "I" << endl;
  for(i=graph.begin(); i!=graph.end(); ++i) {
    if(strcmp((*i) -> getName(), firstnode) == 0) {
      vector<node*> connect = (*i) -> getVect();
      cout << "a" << endl;
	for(j=connect.begin(); j!=connect.end(); ++j) {
	  cout << (*j) -> getName();
	  if((*j) != NULL && strcmp((*j) -> getName(), secondnode) == 0) {
	    connect.erase(j);
	    break;
	  }
	}
    }
  }
  return graph;

}

void print(vector<node*> graph) {
  vector<node*>::const_iterator i;//all iterators needed for adjacency table
  vector<node*>::const_iterator j;
  vector<node*>::const_iterator k;
  vector<node*>::const_iterator l;
  cout << "  ";
  for(i=graph.begin(); i!=graph.end(); ++i){
    cout << (*i)->getName() << " "; //prints all node names at top
  }
  cout << endl;
  for(i=graph.begin(); i!=graph.end(); ++i){ //for vert node name
    cout << (*i)->getName() << " ";
    for(j=graph.begin(); j!=graph.end(); ++j){//goes for length of graph, gets each connect
      vector<node*> connect = (*j) -> getVect(); //gets the connect vector
      bool flag = false;
      for(k=connect.begin(); k!=connect.end(); ++k){//for connected vector
	for(l=graph.begin(); l!= graph.end(); ++l) {//needed to have top as start node
	  if((*l) == (*k) && (*i) == (*l)) {//if the connected vector has the graph node and the graph nodes match
	    cout << "T"; //indicates there is connection
	    flag = true;
	  }
	}
      }
      if(flag == false) {
	cout << "F"; //indicates no connection
      }
      cout << " ";
    }
    cout << endl;
  }
  
}

void printAllConn(vector<node*> graph) {
  vector<node*>::const_iterator i;
  vector<node*>::const_iterator k;

  for(i=graph.begin(); i!=graph.end(); ++i){
    // go through the graph vector for each node
    // look at connect and if it has nodes, print the nodes names
      vector<node*> connect = (*i) -> getVect();
      printSingleConn(graph, i);
  }
}


void printSingleConn(vector<node*> graph, vector<node*>::const_iterator it)
{
  vector<node*>::const_iterator j; //iterator for node vector
  int connctr =0;

  if ((*it) == NULL) //if passed in iterator null
  {
    cout << "Error - invalid iterator passed to printSingleConn" << endl;
    exit (-1);
  }
  //prints out node being checked
  cout << "connections for node =  "; 
  cout << (*it)->getName() << " ";
  cout << endl;

  vector<node*> connect = (*it) -> getVect(); //takes connections of checked node
  
  for(j=connect.begin(); j!=connect.end(); ++j) //for entirety of connection list
    { //printout connections or lack there of
    connctr++;
    cout << "  connects with " << (*j)->getName() << " " << endl;
  }	  
  if (connctr == 0)
    cout << "  no connection entries for this node" << endl;
}

void printEdgeCont(vector<edge*> edgecont)
{
  vector<edge*>::iterator k; //iterator for edge vector

  for(k=edgecont.begin(); k!=edgecont.end(); ++k) { //runs thru edge vector
    if ((*k) == NULL) //if iterator is null
      { //no edges yet
      cout << "No Edge entries" << endl;
      break;
    }
    //print all data on edge
    cout << "Edge entry: " << endl;
    cout << "  firstnode = " << (*k) -> firstp -> getName() << endl;
    cout << "  secondnode = " << (*k) -> secondp -> getName() << endl;
    cout << "  weight = " << (*k) -> weight << endl;
  }
}
