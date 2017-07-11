#ifndef CGRAPH_H
#define CGRAPH_H

#include <iostream>
#include <vector>

using namespace std;

template <class G>
class c_Node{
public:
    typedef typename G::N N;
    typedef typename G::Edge Edge;
    c_Node(N x){
        m_data=x;
        //DIJKSTRA
        d_dist = -1; // iniciando a infinito
        d_visitado = false; // no visitado
        nodo_ant = nullptr;
        //--------------------------

    }

    N m_data;
    vector<Edge*> m_nedges;

    //--DIJKSTRA
        typedef typename G::E E;
        E d_dist; //distancia a nodo inicial
        bool d_visitado; // fue visitado
        c_Node<G>* nodo_ant; //puntero a nodo anterior
        //-----------------------------


    void print_aristas(){
        if(m_nedges.size()>0){
            for(int i=0;i<m_nedges.size();i++){

                if(m_nedges[i]->m_dir == 0){//bidireccion
                    cout<<m_nedges[i]->m_data<<"(";
                    if(m_nedges[i]->m_node[0]->m_data==m_data){
                        cout<< m_nedges[i]->m_node[1]->m_data<<")-";
                    }else{
                        cout<< m_nedges[i]->m_node[0]->m_data<<")-";
                    }

                }else{//de 0 a 1
                    if(m_nedges[i]->m_node[0]->m_data==m_data){
                        cout<<m_nedges[i]->m_data<<"(";
                        cout<< m_nedges[i]->m_node[1]->m_data<<")-";
                    }

                }
            }
            cout<<"\n";
        }else{
            cout<<"--\n";}
    }
    ~c_Node(){
            while(!m_nedges.empty()){
                delete m_nedges.front();
            }
        }

};

template <class G>
class c_Edge{
public:
    typedef typename G::Node Node;
    typedef typename G::E E;

    c_Edge(E x,Node *a, Node *b, bool dir){
        m_node[0]=a;
        m_node[1]=b;
        m_data=x;
        m_dir=dir;
        utilizado = false;
    }

    bool m_dir;//0 BIDIRECCIONAL---1 UNIDIRECCIONAL de m_node[0] a m_node[1]
    E m_data;
    Node* m_node[2];

    //DIJKSTRA
        bool utilizado;
        //-----


    ~c_Edge(){

            typename vector<c_Edge<G>*>::iterator it = m_node[0]->m_nedges.begin();
            while (*it != this){
                it++;
            }
            m_node[0]->m_nedges.erase(it);
            it = m_node[1]->m_nedges.begin();
            while (*it != this){
                it++;
            }
            m_node[1]->m_nedges.erase(it);

        }
};

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
    //vector<Edge*> m_edges;

    bool insert_node(N);
    bool insert_edge(E,N,N,bool);
    bool remEdge(Node *ini, Node *fin, e data, bool dir);
    bool remEdge(Edge* ez);
    bool remove_node(n);
    bool remo_node(vecIt it);
    bool findNode(n x, vecIt &it);

    void recorrer_grafo(){
        cout<<"\nMis nodos: \n";
        for(int i=0;i<m_nodes.size();i++){
            cout<<m_nodes[i]->m_data<<" : ";
            m_nodes[i]->print_aristas();
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
    //m_edges.push_back(new_edge);
    return 1;
}

template <typename n, typename e>
bool c_graph<n,e>::remEdge(Node *ini, Node *fin, e dato, bool dir){
    return false;
}

template <typename n, typename e>
bool c_graph<n,e>::remEdge(Edge* ez){
    delete ez;
    return 1;
}


template <class n, class e>
bool c_graph<n,e>::findNode(n x, vecIt &it) {
    it = m_nodes.begin();
    while (it != m_nodes.end() ){
        if ( (*it)->m_data == x )
            return true;
        it++;
    }
    return false;
}

template <class n, class e>
bool c_graph<n,e>::remove_node(n x){
    vecIt it;
    if(!findNode(x,it)) return false;
    delete (*it);
    m_nodes.erase(it);
    return true;
}

template <class n, class e>
bool c_graph<n,e>::remo_node(vecIt it){
    delete (*it);
    m_nodes.erase(it);
    return true;}




#endif // CGRAPH_H
