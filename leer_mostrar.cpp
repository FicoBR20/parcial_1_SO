#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

string paht_text = "/home/fede/p_cpp_proyects/examen_parcial_1_SO/parcial_1_SO/mlq006.txt";

char recolectora(string receptor){

    int numerador = 0;

    char recibe;

    char selecccionador;

    ifstream lector;

    getline(cin, paht_text);

    lector.open(paht_text);

    if (lector.open())
    {
        do
        {
            selecccionador = lector.peek();

            if (!lector.fail())
            {
                while (lector.get())
                {
                    while (selecccionador!='#')
                    {
                        cin>>recibe;
                    }
                    
                }
                
            }
            
        } while (!lector.fail());
        
    }

    lector.close();

    for (int i = 0; i < sizeof(recibe); i++)
    {
        cout<<"Posicion [ "<<i<<" ] "<<recibe.at(i)<<endl;
    }
    
    return recibe;
    
}

int main()
{  

    char recibira;

    recibira.recolectora(paht_text);
    
    
    cout<<"gracias a Dios..bendito seas por siempre"<<endl;

    return 0;
}
