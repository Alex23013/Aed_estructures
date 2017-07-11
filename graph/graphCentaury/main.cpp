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

template <class n, class e>
class c_graph{
public:
    typedef c_graph<n,e> self;
    typedef c_Node<self> Node;
    typedef c_Edge<self> Edge;
    typedef n N;
    typedef e E;

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

int main()
{
    c_graph<int,string> Centaury;

    Centaury.insert_node(1);
Centaury.recorrer_grafo();
    Centaury.insert_node(2);
    Centaury.insert_edge("a",1,2,0);
	Centaury.insert_edge("b",1,2,1);
Centaury.recorrer_grafo();
    Centaury.remove_edge("a",1,2);
Centaury.recorrer_grafo();
    Centaury.remove_node(1);
	
	Centaury.recorrer_grafo();
    return 0;
}

