#ifndef C_RBTREE_H
#define C_RBTREE_H

#include<iostream>
#include<deque>
#include<stack>

using namespace std;

template<class T>

struct c_Node{

    T m_data;
    c_Node<T>* m_child[2];
    int m_altura;
    int m_fbalance;
    string m_color;

    c_Node(T dato){

        m_data=dato;
        m_altura=1;
        m_fbalance=0;
        m_color="red";
        m_child[0]=0;
        m_child[1]=0;
    }
};

template <class T>
class c_RB_Iterator{

public:
    pair<c_Node<T>*,int> m_pair;
    int m_id;

    deque<pair<c_Node<T>*,int> > m_i;

    c_RB_Iterator<T> operator=(c_RB_Iterator<T> x){

        m_i=x.m_i;
        return *this;
    }

    bool operator!=(c_RB_Iterator<T> x){

        return m_i!=x.m_i;
    }

    c_RB_Iterator<T> operator++(int){

        //ORBengo el tope de mi pila y lo pongo en m_pair IMPORTANTE: inorder y postorder neciesitan una pila
        //lena con el hijo mas izquierdo como tope
        m_pair=m_i.front();

        do{
            m_i.pop_front();

            /** *********************************************************************************************
             *                  SECCION QUE VA SIEMPRE A LA IZQUIERDA                                       *
             * **********************************************************************************************/
            ///Solo ingresa si el estado del tope de la pila es igual al ID que manejo
            if(m_pair.second==m_id){

                /// Actualizo el estado del tope de mi pila
                m_i.push_front(make_pair(m_pair.first,(m_id+1)%3));

                /// Empilo el de mi izquierda
                if(m_pair.first->m_child[0]) m_i.push_front(make_pair(m_pair.first->m_child[0],m_id));
            }
            /** *********************************************************************************************/

            /************************************************************************************************
             *                  SECCION QUE VA SIEMPRE A LA DERECHA                                         *
             * **********************************************************************************************/
            /* Solo ingresa si el estado del tope de la pila es igual al ID que manejo +1 (como solo tengo
             * ID:0,1,2 hago %3 para que siempre este en ese rango**/

            else if(m_pair.second==(m_id+1)%3){

                // Actualizo el estado del tope de mi pila
                m_i.push_front(make_pair(m_pair.first,(m_id+2)%3));

                // Empilo el de mi izquierda
                if(m_pair.first->m_child[1]) m_i.push_front(make_pair(m_pair.first->m_child[1],m_id));
            }
            /************************************************************************************************/
           m_pair=m_i.front();

        }
        while(m_pair.second!=1 and !m_i.empty());
        return *this;
    }

    T operator*(){

        m_pair=m_i.front();
        return m_pair.first->m_data;
    }

};
template <class T>
class c_RB_Inorder_Iterator : public c_RB_Iterator<T>{

public:
    c_RB_Inorder_Iterator(){

        this->m_id=0;
    }

};

template <class T>
class c_RB_Preorder_Iterator : public c_RB_Iterator<T>{

public:
    c_RB_Preorder_Iterator(){

        this->m_id=1;
    }

};

template <class T>
class c_RB_Postorder_Iterator : public c_RB_Iterator<T>{

public:
    c_RB_Postorder_Iterator(){

        this->m_id=2;
    }

};

template <class T>
class c_RB_BFS_Iterator : public c_RB_Iterator<T>{

public:

    c_RB_BFS_Iterator(){}


    c_RB_Iterator<T> operator++(int){

        this->m_pair=this->m_i.front();
        this->m_i.pop_front();
        if(this->m_pair.first->m_child[0]) this->m_i.push_back(make_pair(this->m_pair.first->m_child[0],0));
        if(this->m_pair.first->m_child[1]) this->m_i.push_back(make_pair(this->m_pair.first->m_child[1],0));

        return *this;

    }

};


template<class Tr>

class c_RBTRee
{
    public:

        c_RBTRee();
        typedef typename Tr::T T;
        typedef typename Tr::C C;

        typedef c_RB_Inorder_Iterator<T> inorder_iterator;
        typedef c_RB_Postorder_Iterator<T> postorder_iterator;
        typedef c_RB_Preorder_Iterator<T> preorder_iterator;
        typedef c_RB_BFS_Iterator<T> bfs_iterator;

        bool find(T , c_Node<T>**&);
        bool insert(T);
        bool remove(T);
        void inorden(c_Node<T>*);
        void check_balance();
        void uncle_black(c_Node<T>**&,int);
        void uncle_red(c_Node<T>**&);
        void balance(c_Node<T>**&,int);

        inorder_iterator inbegin();
        inorder_iterator inend();
        postorder_iterator postbegin();
        postorder_iterator postend();
        preorder_iterator prebegin();
        preorder_iterator preend();
        bfs_iterator bfsbegin();
        bfs_iterator bfsend();

        C m_cmp;
        c_Node<T>*m_root;
        stack<pair<c_Node<T>**,int> > m_pila;
};

template<class Tr>

c_RBTRee<Tr>::c_RBTRee()
{
    m_root=nullptr;
}

template<class Tr>

void c_RBTRee<Tr>::uncle_black(c_Node<T>**&t,int e)
{
    cout<<"UNCLE BLACK";
    c_Node<T>* p=(*t);
    if(!p->m_child[e]->m_child[e] || p->m_child[e]->m_child[e]->m_color=="black"){
        t=&p->m_child[e];
        //LEFT RIGHT
        if(e==0){

            c_Node<T>*temp=(*t);
            cout<<"entro "<<(*t)->m_data;
            (*t)=(*t)->m_child[1];
            temp->m_child[1]=temp->m_child[1]->m_child[0];
            (*t)->m_child[0]=temp;
            m_pila.push(make_pair(t,0));
            m_pila.push(make_pair(&((*t)->m_child[0]),0));
        }
        else{
            //RIGHT LEFT
            c_Node<T>*temp=(*t);
            cout<<"entro "<<(*t)->m_data;
            (*t)=(*t)->m_child[0];
            temp->m_child[0]=temp->m_child[0]->m_child[1];
            (*t)->m_child[1]=temp;
            m_pila.push(make_pair(t,1));
            m_pila.push(make_pair(&((*t)->m_child[1]),1));
        }
    }
    else{

        if(e==0){

            //LEFT LEFT
            c_Node<T>*temp=(*t)->m_child[0];
            (*t)->m_child[0]=(*t)->m_child[0]->m_child[1];
            temp->m_child[1]=(*t);
            (*t)=temp;
            (*t)->m_color="black";
            (*t)->m_child[1]->m_color="red";
            m_pila.push(make_pair(t,0));
            m_pila.push(make_pair(&((*t)->m_child[1]),1));
        }
        else{

            //RIGHT RIGHT
            c_Node<T>*temp=(*t)->m_child[1];
            (*t)->m_child[1]=(*t)->m_child[1]->m_child[0];
            temp->m_child[0]=(*t);
            (*t)=temp;
            (*t)->m_color="black";
            (*t)->m_child[0]->m_color="red";
            m_pila.push(make_pair(t,1));
            m_pila.push(make_pair(&((*t)->m_child[0]),0));
        }
    }
    //LEFT LEFT
    /*if(e==0 && fbalance<0){

        c_Node<T>*temp=(*t)->m_child[0];
        cout<<"entro "<<(*t)->m_data;
        (*t)->m_altura-=2;
        (*t)->m_child[0]=(*t)->m_child[0]->m_child[1];
        temp->m_child[1]=(*t);
        (*t)=temp;
        m_pila.push(make_pair(t,0));
        m_pila.push(make_pair(&((*t)->m_child[1]),1));
    }
    //RIGHT RIGHT
    if(e==1 && fbalance>0){

        c_Node<T>*temp=(*t)->m_child[1];
        cout<<"entro "<<(*t)->m_data;
        (*t)->m_altura-=2;
        (*t)->m_child[1]=(*t)->m_child[1]->m_child[0];
        temp->m_child[0]=(*t);
        (*t)=temp;
        m_pila.push(make_pair(t,1));
        m_pila.push(make_pair(&((*t)->m_child[0]),0));
    }*/
}

template<class Tr>

void c_RBTRee<Tr>::uncle_red(c_Node<T>**&t)
{
    c_Node<T>*p=(*t);
    cout<<"UNCLE RED";
    p->m_color="red";
    p->m_child[0]->m_color="black";
    p->m_child[1]->m_color="black";
}


template<class Tr>

void c_RBTRee<Tr>::check_balance()
{
    c_Node<T>* p;
    int e, cont_red;
    c_Node<T>** t;
    e=0;
    cont_red=0;
    while(!m_pila.empty()){
        cout<<"llegue"<<endl;
        t=m_pila.top().first;
        p=*t;
        if(p->m_color=="red") ++cont_red;

        else {

            if (cont_red==1)cont_red=0;
            if(cont_red==2){

                if(!p->m_child[!e] || p->m_child[!e]->m_color=="black") uncle_black(t,e);
                else uncle_red(t);
                if((*m_pila.top().first)->m_color=="red")cont_red=1;
                else cont_red=0;
            }
        }
        cout<<"veo "<<p->m_data<<" ";
        e=m_pila.top().second;
        m_root->m_color="black";
        m_pila.pop();
    }
}

template<class Tr>

void c_RBTRee<Tr>::balance(c_Node<T>**&t,int e)
{
    c_Node<T>**aux=t;
    cout<<"LLEGUE"<<endl;
    c_Node<T>*p,*s;
    p=(*t);

    s=p->m_child[!e];
    if(s->m_color=="black"){

        if( (!s->m_child[0] || s->m_child[0]->m_color=="black") && (!s->m_child[1] || s->m_child[1]->m_color=="black") ){
        /*  P
         * / \
          E   B
             / \
            B   B*/
            s->m_color="red";
            cout<<"S NEGRO NEGRO NEGRO"<<endl;
            if(p->m_color=="black"){

                p->m_color="black";
                if(!m_pila.empty()){
                    int new_e=m_pila.top().second;
                    m_pila.pop();
                    if(!m_pila.empty()) balance(m_pila.top().first,new_e);
                }
            }
            else p->m_color="black";
        }
        else if(s->m_child[!e] && s->m_child[!e]->m_color=="red"){
            /* P             P
            * / \           / \
             E   B    Ó    B   E
                / \       / \
               ?   R     R   ?            */
            s->m_child[!e]->m_color="black";
            cout<<"S NEGRO una ROTACION"<<endl;
            if(!e==1){

                c_Node<T>*temp=(*t);
                cout<<"entro "<<(*t)->m_data;
                (*t)=(*t)->m_child[1];
                temp->m_child[1]=temp->m_child[1]->m_child[0];
                (*t)->m_child[0]=temp;
                (*t)->m_color="red";
                (*t)->m_child[0]->m_color="black";

                //m_pila.push(make_pair(t,0));
                //m_pila.push(make_pair(&((*t)->m_child[0]),0));
            }
            else{
                //RIGHT LEFT
                c_Node<T>*temp=(*t);
                cout<<"entro "<<(*t)->m_data;
                (*t)=(*t)->m_child[0];
                temp->m_child[0]=temp->m_child[0]->m_child[1];
                (*t)->m_child[1]=temp;
                (*t)->m_color="red";
                (*t)->m_child[1]->m_color="black";
                //m_pila.push(make_pair(t,1));
                //m_pila.push(make_pair(&((*t)->m_child[1]),1));
            }
        }
        else{

            cout<<"S NEGRO D ROTACION"<<endl;
            t=&p->m_child[!e];
            //LEFT RIGHT
            if(!e==0){
                c_Node<T>*temp=(*t);
                cout<<"entro "<<(*t)->m_data;
                (*t)=(*t)->m_child[1];
                temp->m_child[1]=temp->m_child[1]->m_child[0];
                (*t)->m_child[0]=temp;
                (*t)->m_color="black";
                (*t)->m_child[0]->m_color="red";
                //m_pila.push(make_pair(t,0));
                //m_pila.push(make_pair(&((*t)->m_child[0]),0));
            }
            else{
                //RIGHT LEFT
                c_Node<T>*temp=(*t);
                cout<<"entro "<<(*t)->m_data;
                (*t)=(*t)->m_child[0];
                temp->m_child[0]=temp->m_child[0]->m_child[1];
                (*t)->m_child[1]=temp;
                (*t)->m_color="black";
                (*t)->m_child[1]->m_color="red";
                //m_pila.push(make_pair(t,1));
                //m_pila.push(make_pair(&((*t)->m_child[1]),1));
            }
            balance(aux,e);
        }
    }
    else{

        if(!e==1){

            c_Node<T>*temp=(*t);
            cout<<"entro "<<(*t)->m_data;
            (*t)=(*t)->m_child[1];
            temp->m_child[1]=temp->m_child[1]->m_child[0];
            (*t)->m_child[0]=temp;
            (*t)->m_color="black";
            (*t)->m_child[0]->m_color="red";
            aux=&(*t)->m_child[0];
            balance(aux,e);
            //m_pila.push(make_pair(t,0));
            //m_pila.push(make_pair(&((*t)->m_child[0]),0));
        }
        else{
            //RIGHT LEFT
            c_Node<T>*temp=(*t);
            cout<<"entro "<<(*t)->m_data;
            (*t)=(*t)->m_child[0];
            temp->m_child[0]=temp->m_child[0]->m_child[1];
            (*t)->m_child[1]=temp;
            (*t)->m_color="black";
            (*t)->m_child[1]->m_color="red";
            aux=&(*t)->m_child[1];
            balance(aux,e);
            //m_pila.push(make_pair(t,1));
            //m_pila.push(make_pair(&((*t)->m_child[1]),1));
        }
    }
}

template<class Tr>

bool c_RBTRee<Tr>::find(T x, c_Node<T>**&p)
{
    int e=0;
    for(p=&m_root; (*p) && (*p)->m_data!=x; p=&(*p)->m_child[ m_cmp((*p)->m_data,x)]) {

        m_pila.push(make_pair(p,e));
        e=m_cmp((*p)->m_data,x);
    }
    m_pila.push(make_pair(p,e));
    return (*p);
}

template<class Tr>

bool c_RBTRee<Tr>::insert(T x)
{
    c_Node<T>**p;
    cout<<"INSERTANDO "<<x<<endl;
    if(find(x,p)) return 0;

    *p=new c_Node<T>(x);
    check_balance();

    return 1;
}

template<class Tr>

bool c_RBTRee<Tr>::remove(T x)
{
    c_Node<T>** p;
    c_Node<T>* temp;
    int e;
    cout<<"BORRANDO"<<x<<endl;
    if(!find(x,p)) return 0;
    temp=(*p);
    if((*p)->m_child[0] && (*p)->m_child[1]){

        if((*p)->m_child[0]) m_pila.push(make_pair(&(*p)->m_child[0],0));
        for(p=&((*p)->m_child[0]); (*p)->m_child[1]; p=&((*p)->m_child[1])) m_pila.push(make_pair(&(*p)->m_child[1],1));
        swap((*p)->m_data,temp->m_data);
    }
    temp=(*p);
    if((*p)->m_color=="black" && ( !(*p)->m_child[!!(*p)->m_child[1]] || (*p)->m_child[!!(*p)->m_child[1]]->m_color=="black" )){

        cout<<"ENTRO NEGRO NEGRO"<<endl;
        (*p)=(*p)->m_child[!!(*p)->m_child[1]];
        e=m_pila.top().second;
        m_pila.pop();

        balance(m_pila.top().first,e);
    }
    else{

        cout<<"ENTRO BORRADO SIMPLE"<<endl;
        (*p)=(*p)->m_child[!!(*p)->m_child[1]];
        //cout<<(*p)->m_data<<endl;
        if( *p ) {
            (*p)->m_color="black";
        }
    }
    stack<pair<c_Node<T>**,int> > empty;
    m_pila=empty;
    m_root->m_color="black";
    return 1;
}

template<class Tr>

void c_RBTRee<Tr>::inorden(c_Node<T>*p){

    if(p){
        inorden(p->m_child[0]);
        inorden(p->m_child[1]);
        cout<<p->m_data<<endl;
    }
}

template<class Tr>

typename c_RBTRee<Tr>::inorder_iterator c_RBTRee<Tr>::inbegin()
{
    c_Node<T>* p=m_root;
    inorder_iterator it;

    it.m_i.push_front(make_pair(p,0));
    //IMPORTANTE!
    it++;

    return it;
}

template<class Tr>

typename c_RBTRee<Tr>::inorder_iterator c_RBTRee<Tr>::inend()
{
    return inorder_iterator();
}

template<class Tr>

typename c_RBTRee<Tr>::preorder_iterator c_RBTRee<Tr>::prebegin()
{
    c_Node<T>* p=m_root;
    preorder_iterator it;

    it.m_i.push_front(make_pair(p,1));

    return it;
}

template<class Tr>

typename c_RBTRee<Tr>::preorder_iterator c_RBTRee<Tr>::preend()
{
    return preorder_iterator();
}

template<class Tr>

typename c_RBTRee<Tr>::postorder_iterator c_RBTRee<Tr>::postbegin()
{
    c_Node<T>* p=m_root;
    postorder_iterator it;

    it.m_i.push_front(make_pair(p,2));
    //IMPORTANTE!
    it++;

    return it;
}

template<class Tr>

typename c_RBTRee<Tr>::postorder_iterator c_RBTRee<Tr>::postend()
{
    return postorder_iterator();
}

template<class Tr>

typename c_RBTRee<Tr>::bfs_iterator c_RBTRee<Tr>::bfsbegin()
{
    c_Node<T>* p=m_root;
    bfs_iterator it;

    it.m_i.push_front(make_pair(p,0));

    return it;
}

template<class Tr>

typename c_RBTRee<Tr>::bfs_iterator c_RBTRee<Tr>::bfsend()
{
    return bfs_iterator();
}
#endif // C_RBTREE_H
