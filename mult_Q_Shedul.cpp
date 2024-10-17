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

using namespace std;

std::vector <string> sheduler;               //Variable GLOBAL, es un listado de registros.
string* d_apuntador=&sheduler[0];       //representa la primera ubicacion en la lista de ejecucion de las tareas.

/**
 * @brief variable GLOBAL
 * Corresponde al archivo de texto con los datos correspodientes a las
 * tareas por ejecutarse.
 */
string listaDatos="mlq001-a.txt";


/// @brief
/**
 * objeto que representa los datos de un registro correspondientes a
 * una tarea que espera su turno en la cola de "ready"
 */
struct job_ready
{
    string a_etiq;                        //representa la etiqueta de la tarea
    int b_burst;                          //representa el Burst time de la tarea
    int c_arrvt;                          //representa el arrival time de la tarea
    int d_quev;                           //representa una determinada cola de procesos de tareas
    int e_prior;                          //representa el indice de la prioridad de ejecucion de una tarea con relacion a las demas tareas

    
    void set_registro(string et, int bt, int at, int qv, int prio){
        a_etiq = et;
        b_burst = bt;
        c_arrvt = at;
        d_quev = qv;
        e_prior = prio;
    }                      
};

/**
 * @brief 
 * 
 * @param input 
 * @return std::vector<string> 
 */
std::vector<string> string_To_array(std::string input)
{
    std::replace(input.begin(), input.end(), ';', ' ');

    std::istringstream stringReader{ input };

    std::vector<string> str_arreglo;

    string receptor;

    string terminacion ="\0";


    while (stringReader >> receptor)
    {
        str_arreglo.push_back(receptor);
    }

    str_arreglo.push_back(terminacion);

    return str_arreglo;
}

job_ready config_registro(){  // parametros a subir string info_leida, pr_ready pr

    job_ready pr, otro;
   // pr.set_registro("A", 1, 2, 3, 4);



    return pr;
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
        if ( (cola_registros.at(i).e_prior - ref_priority) >
        (cola_registros.at(i+1).e_prior - ref_priority) )
        {
            cola_registros.at(i+1)=cola_registros.at(i);
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
    vector<string>lineas_recibidas;

    string receptorDatos;                   //obj que recepcionara los datos filtrados

    std::string auxiliar_line;

    char aauuxx[80];
    
    char salvador[100];                   //auxiliar de proceso recepciona un string
    
    char select_info;                       //auxiliar para validar renglon a leer
    
    std::ifstream lector(ubicacion_de_los_datos);       //obj stream que lee datos del archivo de texto

    if (lector.is_open())
    {
        do
        {
            select_info = lector.peek();

            if (!lector.fail())
            { 
                // char caracter_final;

                // caracter_final = lector.get();

                getline(lector, auxiliar_line);



                if ((select_info>=65 && select_info<=90) || (select_info>=97 && select_info<=122))// ASCII value range
                {

                    lineas_recibidas.push_back(auxiliar_line);


                }
                
            }
            
        } while (!lector.fail());
        
    }
    else{
        cout<<"problemas para lectura de datos\n";
    }

    lector.close();

    //verificacion del proceso 

    for(std::string dentro : lineas_recibidas){
        cout<<"en verificacion "<<dentro<<endl;
    }

    return lineas_recibidas;                                            
}



int main(int argc, char const *argv[])
{
    //prueba funcion de lectura de archivos

    string listaPrueba="mlq001-a.txt";

    lectura_archivo_txt(listaPrueba);

    






    cout<<"bendito Dios...\n";                     //agradecimiento a DIOS.

    return 0;
}
