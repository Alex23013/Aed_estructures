#ifndef FUNCTORS_H
#define FUNCTORS_H

template<typename T>
struct cFxC{
    int operator()(T n,int size){
        return n % size;
        cout<<n<<","<<size<<"\n";
    }

};

template<typename T>
class cFxB{
public:
    int operator()(T n,int size){
        int y =0;
        for(int i=0;i< n.size();i++){
            y+=n[i];
        }
        return (y) % size;
        //cout<<n<<","<<size<<"\n";
    }
};

template<typename T>
class cFxA{
//lo clasifica en razon de la primera letra de la palabra a indexar
public:
    int operator()(T n,int size){
       return (n[0] -97) % size;
       // cout<<int(x)-97<<"%"<<Size<<"="<<x%Size<<endl;
    }

};

#endif // FUNCTORS_H
