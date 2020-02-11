#include <winbgim.h>
#include <fstream>
void waitForLeftMouseClick();

#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

template<class V,class E>
class Edge
{
    public:
        E   m_dato;
        V   *m_vertice;
        Edge()
        {

        }
        Edge(E d , V *p=0)
        {
            m_dato=d;
            m_vertice=p;
        }
};

struct Vertice
{
    string   m_Dato;
    int x;
    int y;
    bool vicitado;

    Vertice(){
              x=30;
              y=30;
              };
    Vertice(int a,int b)
    {
                x=a;
                y=b;
    }
    Vertice(string d):m_Dato(d),vicitado(0){};
    bool operator==(Vertice & t ){ return m_Dato == t.m_Dato;}
	bool operator<(Vertice & t ){ return m_Dato < t.m_Dato;}
	bool operator>(Vertice & t ){ return m_Dato > t.m_Dato;}
    bool operator()(const Vertice & s1, const Vertice & s2 )const  {return s1.m_Dato < s2.m_Dato; }
    friend ostream &  operator<<(ostream & os, Vertice & v)
    {
           os<<v.m_Dato<<"  ";
           return  os;
    }

};

template<class V,class E>
class Graph:public Vertice
{
    public:
    typedef multimap< V, Edge <V,E> *, Vertice >               T_grafo;
    typedef typename multimap< V, Edge<V,E> *> :: iterator     T_iter ;


    int cont_nodos;
    int cont_grades;
    int numero;
    
    ///topologia
    vector<string>cadena;
    vector<string> nodos;
    map<string , int> mapa;
    map<string , int> ::iterator it2;
    
    ///coordenadas:public Vertice
    int x;
    int y;

    private:
        T_grafo m_grafo;
    public:
        Graph()
        {
               x=30;
               y=30;
              cout << "x "<<x<<endl; 
              cout << "y "<<y<<endl;             
            cont_nodos = 0;
            cont_grades=0;
            }
        void Add_Vertex(V v)
        {
            m_grafo.insert(pair < V, Edge<V,E> * > (v,0));
            cont_nodos++;
            nodos.push_back(v.m_Dato);
        }

        void Add_Edge(V i,V f, E arist)
        {
            T_iter iteri= m_grafo.find( i );
            T_iter iterf= m_grafo.find( f );
            if ( iteri !=m_grafo.end() && iterf !=m_grafo.end())
            {
                V * p=(V *)&( iterf -> first );
                Edge<V,E> *pnuevo= new Edge<V,E> (arist,p);
                m_grafo.insert(pair<V, Edge<V,E> *>(i,pnuevo));
            }
            cont_grades++;


            ///para la ordenacion topologica
                    multimap<string,string> mapa;
                    multimap<string,string> ::iterator it;
                    mapa.insert (pair<string,string>(i.m_Dato,f.m_Dato));

                        for (it=mapa.begin();it!=mapa.end();it++)
                        {
                            cadena.push_back( (*it).second);
                           // cout << (*it).second <<endl;
                        }
             Almacenamiento(i,f);
        }

        ///hallamos las incidencias
        void hallar_incidencia()
        {
           int cont;
           for (int i=0 ; i < cont_nodos; i++)
            {
                cont=0 ;
                for (int j=0;j<cadena.size();j++)
                {
                    if(nodos[i] == cadena[j]) cont ++;
                }
            mapa.insert(pair<string,int>(nodos[i],cont));
            }

            ///para impresion de nodos
             cout << "Orden Topologico"<< endl;
              for (int i=0; i <= mayor_orden() ; i++)
              {
               for (it2=mapa.begin();it2!=mapa.end();it2++)
               {
                       if((*it2).second == i)
                     cout <<(*it2).first<<" , "<< (*it2).second <<endl;
               }
              }
            }

        int mayor_orden()
        {
            int mayor=0;
            for (it2=mapa.begin();it2!=mapa.end();it2++)
            {
                if(mayor< (*it2).second)
                    mayor=(*it2).second;
            }
            return mayor;
        }
        void orden_topologico()
        {
            for (it2=mapa.begin();it2!=mapa.end();it2++)
            {
                for (int i=0; i <= mayor_orden() ; i++)
                    if((*it2).second == i)
                        cout << (*it2).second<<" "<<endl;
            }
        }

        void Imprimir()
        {
             T_iter iti=m_grafo.begin();

            for (;iti!=m_grafo.end();iti++)
            {
                if(iti->second !=0 )
              cout << iti.first <<" ---> "<< *(iti.second.m_vertice) <<endl ;
            }

        }

        void Salidas_de(V o)
        {
            pair< T_iter , T_iter > it = m_grafo.equal_range(o);
            for (T_iter it2 = it.first;  it2 != it.second;    ++it2)
            {
              if( it2->second )
               cout << "  [" << (*it2).first << ", " << *((*it2).second->m_vertice) << "]" << endl;
            }
        }

      void Visitar(V vertece)
      {
            cout<<vertece<<endl;
		    vertece.vicitado = true;
            pair< T_iter , T_iter > it = m_grafo.equal_range(vertece);
            for (T_iter it2 = it.first;  it2 != it.second;    ++it2)
            {
              if( it2->second && !(it2->second->m_vertice->vicitado))
              {
                 V destino =  *(it2->second->m_vertice);
  	             if (!destino.vicitado)
                     Visitar(destino);
			  }
		    }
      }

      void Profundidad()
      {
          T_iter  it = m_grafo.begin();
	      for( ; it!=m_grafo.end();++it)
               Visitar(it->first);
      }
      
      void archivar(char *a, int nodos)
      {
            V v;
            numero =nodos;
            int temp= nodos;
            int temp2=nodos;
            string aux;
            aux=v.m_Dato;
            ofstream leer;
            leer.open(a);
            
            cout << "ingrese los valores de coordenadas x y y un Id para cada nodo"<<endl;
            cout<<"x "<< "\t" << " y "<<"\t" <<" id " <<endl;
            leer<<"x "<< "\t" << " y "<<"\t" <<" id " <<endl<<endl;
           initwindow(400,300);
            while (temp > 0)
            {
                cin >>x;
                cin >>y;
                cin >>aux;
                leer << x << "\t" << y <<"\t" << aux <<endl;    
                circle(x,y,12);
                outtextxy((x+15),y,"^_^");
            temp--;
            }
      }
      void Almacenamiento(V v1,V v2)
      {

         line ( v1.x , v1.y, v2.x, v2.y);
         cout <<  v1.x<<" "<< v1.y<< " "<< v2.x<<" " <<v2.y<<endl;
      }
      
      void Aristas_creacion(V v1, V v2, int peso)
      {
           ofstream leer;
           leer.open("archivo.txt");
           int temp2 = numero;
           int x= v1.m_Dato;
           int y=v2.m_Dato;
           cout << "Dar valores entre nodos, denominaremos pesos"<<endl;
           int aristas =temp2 *(temp2-1);
           cout << aristas<<endl;
            while (aristas >0)
            {
               cin >>x;
                if(x==999)
                return;
                cin >>y;
                cin >>peso;
                leer << x << "\t" << y <<"\t" << peso <<endl;    
                circle(x,y,12);
                outtextxy((x+15),y,"^_^");
            aristas--;
          }
      }      
};



int main()
{
initwindow(400,300); 
  
    Graph<Vertice,int> A;
    A.Add_Vertex(Vertice("aqp"));
    A.Add_Vertex(Vertice("cuzco"));
    A.Add_Vertex(Vertice("bolivia"));
    A.Add_Vertex(Vertice("trujillo"));
    A.Add_Vertex(Vertice("Lima"));
    A.Add_Edge(Vertice("aqp"),Vertice("cuzco"),2);
    A.Add_Edge(Vertice("aqp"),Vertice("trujillo"),12);
    A.Add_Edge(Vertice("cuzco"),Vertice("trujillo"),22);
    A.Add_Edge(Vertice("cuzco"),Vertice("Lima"),22);
    A.Add_Edge(Vertice("cuzco"),Vertice("aqp"),22);
    A.Add_Edge(Vertice("cuzco"),Vertice("bolivia"),22);
    A.Add_Edge(Vertice("trujillo"),Vertice("Lima"),22);
   // A.Almacenamiento(Vertice("trujillo"),Vertice("Lima"));
    //A.hallar_incidencia();
    
   // cout << "mayor "<<A.mayor_orden()<<endl;
    //A.archivar("archivo.txt", 2);    
    settextstyle(0,0,2);
    setcolor(RED);
  //  outtextxy(20,100,"Welcome to C++ graphics!");
    setcolor(GREEN);
   // outtextxy(60,130,"Click this window");
   // outtextxy(120,160,"to exit.");
    
    waitForLeftMouseClick(); 
    closegraph();       
	return 0;
}

void waitForLeftMouseClick()
{
    clearmouseclick(WM_LBUTTONDOWN);
    const int DELAY = 50;
    int x, y;
    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, x, y);
}

