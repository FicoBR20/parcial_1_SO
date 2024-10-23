/**
 * Archivo: mutl_Q_She.cpp
 * Autor: federico.barbetti@correounivalle.edu.co
 * Fecha creacion: 2024-10-13
 * Fecha ultima modificacion: 2024-10-16
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
string* d_apuntador=&sheduler[0];       //representa la primera ubicacion en la lista de ejecucion de las tareas.
stringstream sst;




/**
 * @brief variable GLOBAL
 * Corresponde al archivo de texto con los datos correspodientes a las
 * tareas por ejecutarse.
 */
string listaDatos="/home/fede/p_cpp_proyects/examen_parcial_1_SO/parcial_1_SO/mlq025.txt";

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

/**
 * @brief funcion que elimina simbolos no necesarios
 * para el proceso de los datos
 * @param input 
 * @return std::vector<string> 
 */
std::vector<string> string_To_array(std::string input)
{
    std::replace(input.begin(), input.end(), ';', ' ');

    std::istringstream stringReader{ input };

    std::vector<string> str_arreglo;

    string receptor;

    while (stringReader >> receptor)
    {

        str_arreglo.push_back(receptor);
    }

    return str_arreglo;
}


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
 * @brief funcion que lee los datos de un archivo de texto suministrado
 * y retorna un vector<string> con los datos leidos.
 * 
 * @param ubicacion_de_los_datos 
 */
std::vector<string>lectura_archivo_txt(const string ubicacion_de_los_datos)
{
    vector<string>bloqueDatos;

    vector<char*>nuevos_Datos;


    vector<char*>lineas_recibidas;

    string receptorDatos;                   //obj que recepcionara los datos filtrados
    
    string esperanza="";

    char receptor[] ="";
    
    char select_info; 
    
    char destino[200] ="";                     //auxiliar para validar renglon a leer
    
    char b_destino[20]="";

    char sx_elemento[8];                       //cadena hasta el ";"

    char osx_elemento[10];
    
    int zt_cuenta=0;                            //cuantnos simbolos fueron leidos la ultima vez
    
    std::ifstream lector(ubicacion_de_los_datos);       //obj stream que lee datos del archivo de texto


    
    if (lector.is_open())
    {
        do
        {

            //char detenedor=lector.get();
            
           // select_info=lector.peek();

            getline(lector, receptorDatos, ';');

            if (!lector.fail() )                 //aqui empieza realmente el buffer
            {


                // if (select_info=='#' && !receptorDatos.empty())
                // {
                //     select_info=lector.peek();
                //     cout<<receptorDatos<<endl;
                    
                // }

                cout<<receptorDatos<<endl;

                bloqueDatos.push_back(receptorDatos);


                


                
            }
            else{
                cout<<".... latencia positiva...."<<endl;
            }

            
        } while (!lector.fail());
        
        
    }
    else{

        cout<<"no se pudo abrir el stream"<<endl;
    }

    //veficaciones

    for (int i = 0; i < bloqueDatos.size(); i++)
    {
        cout<<" Posicion [ "<<i<<" ] es "<<bloqueDatos.at(i)<<endl;
    }
    




    return bloqueDatos;                                            
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

    job_ready jr1;  
    
    char* infoLista; 
    
    int largo;                                                      //instania

    string listaPrueba="/home/fede/p_cpp_proyects/examen_parcial_1_SO/parcial_1_SO/mlq025.txt";
    
    vector <string> el_probador;

    std::vector<job_ready>cola_trb;

    el_probador=lectura_archivo_txt(listaPrueba);  //vector con punteros char* 

    cout<<"size de el vector de salida "<<el_probador.size()<<endl;

    // infoLista = el_probador.at(1);

    // largo = sizeof(infoLista);

    // cout<<largo<<endl;

    // for (int i = 0; i < largo; i++)
    // {
    //     cout<<(char) infoLista[i]<<endl;
    // }
    







    cout<<"bendito Dios...\n";                     //agradecimiento a DIOS.

    return 0;
}   
