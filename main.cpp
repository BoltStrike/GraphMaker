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

int main() {
  vector<node*> graph = vector<node*>();
  vector<edge*> edgecont = vector<edge*>();
  bool run = true;
  cout << "Welcome to Graph Creator" << endl;
  while (run == true) {
    char* input = new char [80];
    cout << "What do you wish to do? (addv, removev, adde, removee, print)" << endl;
    cin.getline(input, 80);
    if (strcmp(input, "addv") == 0) {
      addVert(graph);
    }
    else if(strcmp(input, "removev") == 0) {
      delVert(graph, edgecont);
    }
    else if(strcmp(input, "adde") == 0) {
      addEdge(graph, edgecont);
    }
    else if(strcmp(input, "removee") == 0) {
      graph = delEdge(graph, edgecont);
    }
    else if (strcmp(input, "print") == 0) {
      print(graph);
    }
    else if(strcmp(input, "quit") == 0) {
      run = false;
    }
  }
}

void addVert(vector<node*>& graph) {
  cout << "Please input a name for the node" << endl;
  node* newnode = new node();
  char* input = new char[80];
  cin.getline(input, 80);
  newnode -> setName(input);
  graph.push_back(newnode);
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
  if (count > 1) {
    for (i=graph.begin(); i!=graph.end(); ++i){
      vector<node*> connect = (*i) -> getVect();
      for(j = connect.begin(); j!=connect.end(); ++j) {
	if((*j) != NULL && strcmp((*j) -> getName(), input) == 0) {
	  connect.erase(j);
	  break;
	}
      }
    }
    if(edgecont.empty() != true) {
      for(k=edgecont.begin(); k!=edgecont.end(); ++k) {
	if((*k) -> firstp -> getName() != NULL) {
	  if(strcmp((*k) -> firstp -> getName(), input) == 0 || strcmp((*k) -> secondp -> getName(), input) == 0) {
	    edgecont.erase(k);
	    break;
	  }
	}
      }
    }
    
  }
}

void addEdge(vector<node*>& graph, vector<edge*>& edgecont) {
  vector<node*>::const_iterator i;
  vector<node*>::const_iterator j;
  edge* newe = new edge();
  cout << "Please enter the first node" << endl;
  char* firstnode = new char[80];
  cin.getline(firstnode, 80);
  bool flag = false;
  for (i=graph.begin(); i!=graph.end(); ++i){
    if(strcmp((*i) -> getName(), firstnode) == 0) {
      newe -> firstp = (*i);
      flag = true;
      break;
    }
  }
  if (flag == false){
    cout << "The node you entered does not exist" << endl;
    return;
  }

  cout << "Please enter the second node" << endl;
  char* secondnode = new char[80];
  cin.getline(secondnode, 80);
  flag = false;
  for (j=graph.begin(); j!=graph.end(); ++j){
    if(strcmp((*j) -> getName(), secondnode) == 0) {
      newe -> secondp = (*j);
      (*i)-> vectPush(*j);
      flag = true;
    }
  }
  if (flag == false){
    cout << "The node you entered does not exist" << endl;
    return;
  }
  
  cout << "Please enter the weight" << endl;
  char* weightval = new char[80];
  cin.getline(weightval, 80);
  newe -> weight = weightval;
  edgecont.push_back(newe);
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

  for(i=graph.begin(); i!=graph.end(); ++i) {
    if(strcmp((*i) -> getName(), firstnode) == 0) {
      vector<node*> connect = (*i) -> getVect();
	for(j=(*i) -> getVect().begin(); j!=(*i) -> getVect().end(); ++j) {
	  cout << (*j) -> getName();
	  if((*j) != NULL && strcmp((*j) -> getName(), secondnode) == 0) {
	    (*i) -> vectErase(j);
	    break;
	  }
	}
    }
  }
  return graph;

}

void print(vector<node*> graph) {
  vector<node*>::const_iterator i;
  vector<node*>::const_iterator j;
  vector<node*>::const_iterator k;
  vector<node*>::const_iterator l;
  cout << "  ";
  for(i=graph.begin(); i!=graph.end(); ++i){
    cout << (*i)->getName() << " ";
  }
  cout << endl;
  for(i=graph.begin(); i!=graph.end(); ++i){
    cout << (*i)->getName() << " ";
    //vector<node*> connect = (*i) -> getVect();
    for(j=graph.begin(); j!=graph.end(); ++j){//goes for length of graph
      vector<node*> connect = (*j) -> getVect();
      bool flag = false;
      for(k=connect.begin(); k!=connect.end(); ++k){
	for(l=graph.begin(); l!= graph.end(); ++l) {//needed to have top as start node
	  if((*l) == (*k) && (*i) == (*l)) {
	    cout << "T";
	    flag = true;
	  }
	}
      }
      if(flag == false) {
	cout << "F";
      }
      cout << " ";
    }
    cout << endl;
  }
  
}
