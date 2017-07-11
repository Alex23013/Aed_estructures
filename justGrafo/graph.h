#ifndef GRAPH_H
#define GRAPH_H
#include "edge_node.h"

template <class n, class e>
class c_graph{
public:
    typedef c_graph<n,e> self;
    typedef c_Node<self> Node;
    typedef c_Edge<self> Edge;
    typedef n N;
    typedef e E;
    typedef typename vector<Node*>::iterator vecIt;

    vector<Node*> m_nodes;
    vector<Edge*> m_edges;

    bool insert_node(N);
    bool insert_edge(E,N,N,bool);
    bool remove_edge(E,N,N);
    bool remove_node(N);

    void recorrer_grafo(){
        cout<<"\nMis nodos: \n";
        for(int i=0;i<m_nodes.size();i++){
            cout<<m_nodes[i]->m_data<<" : ";
            m_nodes[i]->print_aristas();
            //cout<<*(((mis_nodos[i])->m_edges).begin());
        }
    }

    int min_array(int* array, int size, bool * vis){
        int min =100;
        int pos =0;
        for(int i =0;i<size;i++){
            if(array[i]<min && array[i]>0 && vis[i]==0 ){
                min =array[i];
                pos =i;
            }
        }
        return pos;
    }
    bool esta(vector<Node*> a, Node* buscado){
        for(int i =0;i< a.size();i++){
            if(a[i]->m_data == buscado->m_data )
            {return true;}
        }
        return false;
    }

    vector<Node*>  mis_vecinos_a(Node* a){
          vector<Node*> vecinos;
         //  cout<<"mis vecinos son: \t";
          for(int i=0;i < a->m_nedges.size();i++){
              if(a->m_nedges[i]->m_node[0]->m_data==a->m_data){
           //       cout<< a->m_nedges[i]->m_node[1]->m_data<<"-";
                  vecinos.push_back(a->m_nedges[i]->m_node[1]);
              }else{
           //       cout<< a->m_nedges[i]->m_node[0]->m_data<<"-";
                  vecinos.push_back(a->m_nedges[i]->m_node[0]);
              }
          }
          return vecinos;
      }

    int distancia_a_b(Node* a,char b){
        cout<<a->m_data<<" y "<<b;
        for(int i=0;i < a->m_nedges.size();i++){
            if(a->m_nedges[i]->m_node[0]->m_data==a->m_data){
                //cout<<"1"<< a->m_nedges[i]->m_node[1]->m_data<<"-";
                if(a->m_nedges[i]->m_node[1]->m_data == b){
                    //cout<<"este es: "<<a->m_nedges[i]->m_data<<"\n";
                    return a->m_nedges[i]->m_data;
                }
            }else{
                cout<<"0" <<a->m_nedges[i]->m_node[0]->m_data<<"-";
            }
         }
        return 0;
    }

    bool vistados(bool * a, int size){
        for(int i =0;i< size;i++){
            if(a[i]== false )
            {return false;}
        }
        return true;
    }

    void dijkstra(int source){
       vector<Node*> Q;
       int distancia[m_nodes.size()];
       char anterior[m_nodes.size()];
       bool visitado[m_nodes.size()];
       for(int i =0 ;i<m_nodes.size();i++){
           distancia[i]=-1;
           anterior[i]=' ';
           Q.push_back(m_nodes[i]);
           visitado[i]=false;
       }
       int pos_min =min_array(distancia,m_nodes.size(),visitado);
       distancia[source]=0;
       for(int i =0 ;i<m_nodes.size();i++){
           cout<<Q[i]->m_data <<" "<<distancia[i];
           cout<<" ("<<anterior[i]<<")\n";
       }
int y=0;
       while(!vistados(visitado,m_nodes.size())){

           pos_min =min_array(distancia,m_nodes.size(),visitado);
           cout<<"visitado: ";
           for(int i =0;i< m_nodes.size();i++){
               cout<<visitado[i]<<"-";
           }
           cout<<"\n";
           Node* u = Q[pos_min];
           cout<<"\nmin:"<<u->m_data<<"\n";
           distancia[pos_min]=100;
           visitado[pos_min]=true;
           y++;
           //vecIt it = Q.begin();

           vector<Node*> ab=mis_vecinos_a(u);
           //Q.erase(it+pos_min);
           /*for(int i =0;i < ab.size();i++){
               if(!esta(Q, ab[i])){
                   ab[i]->m_data=-2;
               }
           }

           for(int i=0;i < ab.size();i++){
               if(ab[i]->m_data != -2){
                   cout<<"#"<<ab[i]->m_data<<"\n";
                  cout<<distancia_a_b(m_nodes[source],ab[i]->m_data);
                   // int alt =distancia[pos_min];
               }
           }*/

       }

    }
};

template <class n, class e>
bool c_graph<n,e>::insert_node(N x){

    Node* new_node=new Node(x);
    m_nodes.push_back(new_node);
    return 1;
}

template <class n, class e>
bool c_graph<n,e>::insert_edge(E x,N a,N b,bool dir){

    Node *Na,*Nb;
    for(int i=0; i<m_nodes.size(); i++){

        if(m_nodes[i]->m_data==a) Na=m_nodes[i];
        if(m_nodes[i]->m_data==b) Nb=m_nodes[i];
    }
    Edge* new_edge=new Edge(x,Na,Nb,dir);
    Na->m_nedges.push_back(new_edge);
    Nb->m_nedges.push_back(new_edge);
    m_edges.push_back(new_edge);
    return 1;
}

template <class n, class e>
bool c_graph<n,e>::remove_edge(E x,N a,N b){

    Node *Na,*Nb;
    for(int i=0; i<m_nodes.size(); i++){

        if(m_nodes[i]->m_data==a) Na=m_nodes[i];
        if(m_nodes[i]->m_data==b) Nb=m_nodes[i];
    }
    Edge* borrar;
    for(int i=0; i<m_nodes.size(); i++){
        for(int j=0; j<m_nodes[i]->m_nedges.size(); j++){

            if((m_nodes[i]->m_nedges[j])->m_data==x && (m_nodes[i]->m_nedges[j])->m_node[0]==Na && (m_nodes[i]->m_nedges[j])->m_node[1]==Nb){

                m_nodes[i]->m_nedges.erase(m_nodes[i]->m_nedges.begin()+j);
            }
        }
    }
    for(int i=0; i<m_edges.size(); i++){

        if((m_edges[i])->m_data==x && (m_edges[i])->m_node[0]==Na && (m_edges[i])->m_node[1]==Nb){
            borrar= m_edges[i];
            m_edges.erase(m_edges.begin()+i);
            delete borrar;
        }
    }
    return 1;
}

template <class n, class e>
bool c_graph<n,e>::remove_node(N x){

    Node* borrar;
    for(int i=0; i<m_nodes.size(); i++){

        if((m_nodes[i])->m_data==x){
            borrar= m_nodes[i];
            for(int j=0; j<(m_nodes[i])->m_nedges.size(); j++){

                remove_edge(((m_nodes[i])->m_nedges[j])->m_data,((m_nodes[i])->m_nedges[j])->m_node[0]->m_data,((m_nodes[i])->m_nedges[j])->m_node[1]->m_data);
            }
            m_nodes.erase(m_nodes.begin()+i);
            delete borrar;
        }
    }
    return 1;
}
#endif // GRAPH_H
