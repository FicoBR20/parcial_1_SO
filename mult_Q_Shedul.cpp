/**
 * Archivo: mutl_Q_She.cpp
 * Autor: federico.barbetti@correounivalle.edu.co
 * Fecha creacion: 2024-10-13
 * Fecha ultima modificacion: 2024-11-08
 * Licencia: GNU-GPL
 */

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<sstream>
#include <bits/stdc++.h>
#include <unistd.h> // For sleep
#include<string>

using namespace std;

std::vector <string> sheduler;               //Variable GLOBAL, es un listado de registros.

/**
 * @brief variable GLOBAL
 * Corresponde al archivo de texto con los datos correspodientes a las
 * tareas por ejecutarse.
 */
string ubicaDatos="/home/fede/p_cpp_proyects/examen_parcial_1_SO/parcial_1_SO/mlq001.txt";


//string datos_recibidos;


/// @brief
/**
 * objeto que representa los datos de un registro correspondientes a
 * una tarea que espera su turno en la cola de "ready"
 */
struct job_ready
{
    int aa_serie;                         //particularizacion del objeto.
    string a_etiq;                        //representa la etiqueta de la tarea
   
    int b_burst;                          //representa el Burst time de la tarea
    int c_arrvt;                          //representa el arrival time de la tarea
    int d_quev;                           //representa una determinada cola de procesos de tareas
    int e_prior;                          //representa el indice de la prioridad de ejecucion de una tarea con relacion a las demas tareas

    void set_registro(int ser, string et, int bt, int at, int qv, int prio){
        aa_serie=ser;
        a_etiq = et;
        b_burst = bt;
        c_arrvt = at;
        d_quev = qv;
        e_prior = prio;
    }                      
};

string importante="";
string*imptr = &importante;

std::vector<string>recolector;


/**
 * @brief Construct a new vector<job ready>orden por prioridad object
 * ordena los elementos segun el orden de prioridad dado 5>1;
 * semantica; entre mas proximo a 5, es mas prioritaria la ejecucion de la tarea.
 */
std::vector<job_ready>orden_por_prioridad(vector<job_ready>cola_registros){

    vector<int>datos_finales;

    int ref_priority = 5;             //cota referencial que determina la prioridad

    for (int i = 0; i < cola_registros.size(); i++)
    {
        if (     (cola_registros.at(i).e_prior -  ref_priority) >
        (cola_registros.at(i+1).e_prior - ref_priority) )
        {
            cola_registros.at(i+1)=cola_registros.at(i);            //mayor hacia adelante
        }
        
    }

    return cola_registros;

}






/**
 * @brief funcion que a partir de un archivo de texto formateado debidamente, 
 * entrega un vector de tipo string con la informacion lista para ser procesada,
 * estos datos se usaran para inicializar los objetos de tipo job_ready necesarios
 * para ejecutar los procesos que la app abordara.
 * 
 * @param listadoDatos 
 * @return std::vector<string> 
 */
std::vector<string> leerDatos(string listadoDatos){

    ifstream mylector(listadoDatos);                      //objeto stream de lectura

    char muestra_simbolo;                               //contenedor de cada simbolo leido

    string st1, st2, st3, st4, st5;                     //contenedores de cadena formateada

    string for_used_lines = "";                         //contenedor de linea leida

    int curr_post = 0;                                  //contenedor de posicion de lectura



    if (mylector.is_open())
    {
        do
        {
            
            curr_post=mylector.tellg();
            muestra_simbolo=mylector.get();
            getline(mylector, for_used_lines, '\n');

            if (!mylector.fail()) 
            {

                if ( muestra_simbolo != '#' || muestra_simbolo=='\n')
                {
                    mylector.seekg(curr_post, ifstream::beg);

                    if(!for_used_lines.empty() && muestra_simbolo!='\0')
                    {
                        getline(mylector, st1,';');
                        sheduler.push_back(st1);
                        getline(mylector, st2,';');
                        sheduler.push_back(st2);
                        getline(mylector, st3,';');
                        sheduler.push_back(st3);
                        getline(mylector, st4,';');
                        sheduler.push_back(st4);
                        getline(mylector, st5,'\n');
                        sheduler.push_back(st5);
                    }
                
                    
                }
                    
            }
            
        } while (!mylector.fail());
        
    }
    mylector.close();

    cout<<"El size del vector es; "<<sheduler.size()<<endl;

    for(string x : sheduler){
        cout<<"El string es: "<<x<<" y el size del vector es; "
        <<sheduler.size()<<endl;
    }

    return sheduler;   
}






// job_ready config_job(string datos){
// z



//     int contador = 0;
//    // vector<char>paraDatos;
//     char misdatos[6];
//     misdatos[5]='\0';

//     for(char ch : datos){
//         if( ( (int)ch>47 && (int)ch<58 ) || ( (int)ch>96 && (int)ch<123 ) || ( (int)ch>64 && (int)ch<91 )  ) {
//            // paraDatos.push_back(ch);
//             misdatos[contador]=ch;
//             contador++;
//             cout<<" o soy letra o numero ..soy "<<ch<<" contador es "<<contador<<endl;

//         }
//         else{
//             cout<<ch<<" no soy ni letra ni numero \n";
//         } 
//     }
    
//     job_ready limpio_jr;

//     limpio_jr.a_etiq=misdatos[0];
//     limpio_jr.b_burst=misdatos[1] ;
//     limpio_jr.c_arrvt=misdatos[2];
//     limpio_jr.d_quev=misdatos[3];
//     limpio_jr.e_prior=misdatos[4];

//     //prueba
//     cout<<"\nSoy limpio mi etiqueta es: "<<limpio_jr.a_etiq
//     <<"\nSoy limpio mi burst time es: "<<limpio_jr.b_burst
//     <<"\nSoy limpio mi arrival time es: "<<limpio_jr.c_arrvt
//     <<"\nSoy limpio mi queve es: "<<limpio_jr.d_quev
//     <<"\nSoy limpio mi prioridad es: "<<limpio_jr.e_prior
//     <<endl;

//     return limpio_jr;
    
// }



int main(int argc, char const *argv[])
{
    //prueba funcion de lectura de archivos
    
    vector <string> el_probador;

    std::vector<job_ready>cola_trb;

    el_probador = leerDatos(ubicaDatos);  //vector con datos limpios para procesar

    //prueba de lectura ...aprobada....Nov-8-24

    










    cout<<"bendito Dios...\n";                     //agradecimiento a DIOS.

    return 0;
}   
