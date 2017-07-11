#ifndef EDGE_NODE_H
#define EDGE_NODE_H

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
    }

    N m_data;
    vector<Edge*> m_nedges;


    void print_aristas(){
        if(m_nedges.size()>0){
            //cout<<"aris:";
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
    }

    bool m_dir;//0 BIDIRECCIONAL---1 UNIDIRECCIONAL
    E m_data;
    Node* m_node[2];
};

#endif // EDGE_NODE_H
