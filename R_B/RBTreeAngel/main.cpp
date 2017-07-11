#include <iostream>
#include "c_rbtree.h"
#include <fstream>
#include <sstream>
#include <random>

//#include <gvc.h>

using namespace std;

void bst_print_dot_null(int key, string color,int nullcount, FILE* stream)
{
    fprintf(stream, "    null%d [fillcolor=black];\n", nullcount);
    //fprintf(stream, "    %d -> null%d;\n", key, nullcount);
    stringstream buffer1;
    string s1;
    buffer1<<key;
    buffer1>>s1;
    fprintf(stream, "    %d[label=%s fillcolor=%s]; %d-> null%d;\n", key,s1.c_str(),color.c_str(),key, nullcount);
}

template <class T>

void bst_print_dot_aux(c_Node<T>* node, FILE* stream)
{
    static int nullcount = 0;

    if (node->m_child[0])
    {
        stringstream buffer1;
        string s1,s2;
        buffer1<<node->m_data;
        buffer1>>s1;
        fprintf(stream, "    %d[label=%s fillcolor=%s] %d-> %d;\n", node->m_data,s1.c_str(), node->m_color.c_str(),node->m_data, node->m_child[0]->m_data);
        bst_print_dot_aux(node->m_child[0], stream);
    }
    else
        bst_print_dot_null(node->m_data,node->m_color, nullcount++, stream);

    if (node->m_child[1])
    {
        stringstream buffer1,buffer2;
        string s1,s2;
        buffer1<<node->m_data;
        buffer1>>s1;
        fprintf(stream, "    %d[label=%s fillcolor=%s]; %d-> %d;\n", node->m_data,s1.c_str(),node->m_color.c_str(),node->m_data, node->m_child[1]->m_data);
        bst_print_dot_aux(node->m_child[1], stream);
    }
    else
        bst_print_dot_null(node->m_data,node->m_color, nullcount++, stream);
}

template <class T>

void bst_print_dot(c_Node<T>* tree, FILE* stream)
{
    cout<<"hi";
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    graph [style=radial bgcolor=\"orange:white\"] node [shape = circle width = 0.75 fixedsize = true fontname=\"Arial\" fontcolor=white style = filled];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->m_child[1] && !tree->m_child[0])
        fprintf(stream, "    %d;\n", tree->m_data);
    else
        bst_print_dot_aux(tree, stream);

    fprintf(stream, "}\n");
}

template <class T>

struct c_less
{
    inline bool operator() (T a,T b)
    {return a<b;}
};

template <class T>

struct c_greater
{
    inline bool operator() (T a,T b)
    {return a>b;}
};

struct traits{

    typedef int T;
    typedef c_less<T> C;
};

int main()
{

    //srand(time(NULL));
    FILE * pFile;
    c_RBTRee<traits> arbol;
    c_RBTRee<traits>::inorder_iterator it;
    c_RBTRee<traits>::postorder_iterator post_it;
    c_RBTRee<traits>::preorder_iterator pre_it;
    c_RBTRee<traits>::bfs_iterator bfs_it;

    pFile = fopen ("tree.dot" , "w");
    if (pFile == NULL) perror ("Error opening file");
    int a,b,c,d,e,f,g;

    a=50;
    b=60;
    c=40;
    d=45;
    e=46;
    f=39;
    g=38;

    arbol.insert(18);
    arbol.insert(6);
    arbol.insert(16);
    arbol.insert(3);
    arbol.insert(10);
    arbol.insert(13);
    arbol.insert(11);

    arbol.remove(11);
    arbol.remove(3);
    arbol.remove(6);
    //arbol.insert(61);

    for(int i=0; i<15; i++) arbol.insert(rand()%100);

    //arbol.remove(21);

    //arbol.remove(35);
    //arbol.remove(27);

    arbol.inorden(arbol.m_root);

    /*for(it=arbol.inbegin();it!=arbol.inend(); it++){

        cout<<"h"<<endl;
        cout<<*it;
    }*/

    /*for(post_it=arbol.postbegin();post_it!=arbol.postend(); post_it++){

        cout<<"h"<<endl;
        cout<<*post_it;
    }*/

    /*for(pre_it=arbol.prebegin();pre_it!=arbol.preend(); pre_it++){

        cout<<"h"<<endl;
        cout<<*pre_it;
    }*/

    for(bfs_it=arbol.bfsbegin();bfs_it!=arbol.bfsend(); bfs_it++){

        cout<<"h"<<endl;
        cout<<*bfs_it;
    }

    bst_print_dot(arbol.m_root, pFile);

    fclose (pFile);
    system("dot -Tpng tree.dot -O");
    system("xdg-open tree.dot.png");


    return 0;
}
