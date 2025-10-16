#include <iostream>

int Prods = 5;
int Semanas = 4;
int TiposMP = 4;
float PrecioMPbase = 10.5;

int requerimientos[5][4] = {
    {10, 5, 3, 2},
    {8, 6, 4, 3},
    {12, 4, 5, 1},
    {9, 7, 2, 4},
    {11, 3, 6, 2}
};

float** crea_mat(int a, int b) {
    float** mat_nueva = new float*[a];
    for(int i=0; i<a; i++) {
        mat_nueva[i] = new float[b];
        for(int j=0; j<b; j++) {
            mat_nueva[i][j] = 0.0;
        }
    }
    return mat_nueva;
}

void libera_matriz(float** matriz, int filas) {
    for(int i=0; i<filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

float** agr_sem(float** m_vieja, int prods, int sViejas, int &s_nuevas) {
    s_nuevas = sViejas + 1;
    float** mat_con_mas_semanas = crea_mat(prods, s_nuevas);
    
    for(int i=0; i<prods; i++){
        for(int j=0; j<sViejas; j++){
            mat_con_mas_semanas[i][j] = m_vieja[i][j];
        }
    }
    
    libera_matriz(m_vieja, prods);
    return mat_con_mas_semanas;
}

void verPlan(float** matriz, int prods, int sem) {
    std::cout << "\n--- Plan de Produccion (Valores) ---\n";
    std::cout << "Prod/Sem\t"; 
    for(int j=0; j<sem; j++) {
        std::cout << "Semana " << j << "\t";
    }
    std::cout << "\n";
    
    for(int i=0; i<prods; i++) {
        std::cout << "Prod " << i << "\t\t";
        for(int j=0; j<sem; j++){
            std::cout << matriz[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

void calculo_consumo(float** plan, float* inv_MP, int prods, int s) {
    float consumo[4] = {0,0,0,0}; 
    
    for(int i=0; i<prods; i++) {
        for(int j=0; j<4; j++) {
            consumo[j] += plan[i][s] * requerimientos[i][j];
        }
    }
    
    std::cout << "\n--- Consumo (Semana " << s << ") ---\n";
    for(int i=0; i<4; i++){
        std::cout << "MP Tipo " << (i+1) << ": " << consumo[i] << " uds\n";
        inv_MP[i] = inv_MP[i] - consumo[i];
    }
}

void costo_total(float** plan, float* costos_uni, int p, int s) {
    float costoTotalSemana = 0.0;
    float produccion_t = 0.0;
    
    for(int i=0; i<p; i++) {
        costoTotalSemana += plan[i][s] * costos_uni[i];
        produccion_t += plan[i][s];
    }
    
    std::cout << "\n--- Resultados de Costos (Semana " << s << ") ---\n";
    std::cout << "Total Unidades Producidas: " << produccion_t << "\n";
    std::cout << "Costo Venta: $" << costoTotalSemana << "\n";
}

int main() {
    float** planProd = crea_mat(Prods, Semanas);
    
    float* costos = new float[Prods];
    costos[0] = 5.5;
    costos[1] = 6.0;
    costos[2] = 4.8;
    costos[3] = 7.2;
    costos[4] = 5.0;
    
    float* inventarioMP = new float[TiposMP];
    inventarioMP[0] = 1000.0;
    inventarioMP[1] = 800.0;
    inventarioMP[2] = 600.0;
    inventarioMP[3] = 500.0;
    
    planProd[0][0] = 1000; planProd[0][1] = 1200;
    planProd[1][0] = 800; planProd[1][1] = 900;
    planProd[2][0] = 1500; planProd[2][1] = 1400;
    planProd[3][0] = 700; planProd[3][1] = 750;
    planProd[4][0] = 1100; planProd[4][1] = 1050;
    
    std::cout << "--- Sistema de Planif C++ (v0.1) ---\n";
    std::cout << "Iniciando con " << Prods << " productos y " << Semanas << " semanas.\n";
    
    int opc = 0;
    do {
        std::cout << "\n--- Menu Principal --- \n";
        std::cout << "1. Ver el Plan de Produccion\n";
        std::cout << "2. Agregar una Semana Nueva\n";
        std::cout << "3. Modificar la Produccion de una Semana\n";
        std::cout << "4. Hacer Calculos de Costos/Consumo\n";
        std::cout << "5. Salir del Programa\n";
        std::cout << "Elige una opcion: ";
        std::cin >> opc;
        
        if(opc == 1) {
            verPlan(planProd, Prods, Semanas);
        }
        else if(opc == 2) {
            planProd = agr_sem(planProd, Prods, Semanas, Semanas); 
            std::cout << "Hay " << Semanas << " semanas ahora.\n";
        }
        else if(opc == 3) {
            int prod_elegido, sem_elegida;
            float nueva_cant;
            
            std::cout << "Numero de Producto (de 0 a " << (Prods-1) << "): "; 
            std::cin >> prod_elegido;
            std::cout << "Numero de Semana (de 0 a " << (Semanas-1) << "): "; 
            std::cin >> sem_elegida;
            std::cout << "Nueva Cantidad: "; 
            std::cin >> nueva_cant;
            
            if(prod_elegido >= 0 && prod_elegido < Prods && sem_elegida >= 0 && sem_elegida < Semanas) {
                planProd[prod_elegido][sem_elegida] = nueva_cant;
                std::cout << "¡Produccion actualizada!\n";
            } else {
                std::cout << "Error: No existe ese producto o esa semana.\n";
            }
        }
        else if(opc == 4) {
            int sem_a_calcular;
            std::cout << "Que Semana quieres calcular (0 a " << (Semanas-1) << "): ";
            std::cin >> sem_a_calcular;
            
            if(sem_a_calcular >= 0 && sem_a_calcular < Semanas) {
                costo_total(planProd, costos, Prods, sem_a_calcular);
                calculo_consumo(planProd, inventarioMP, Prods, sem_a_calcular);
                
                float valor_final_MP = 0.0;
                for(int i=0; i<TiposMP; i++) {
                    valor_final_MP += inventarioMP[i] * PrecioMPbase; 
                }
                std::cout << "Valor final del Inventario MP: $" << valor_final_MP << "\n";
            } else {
                std::cout << "Semana invalida. Intenta otra vez.\n";
            }
        }
        
    } while(opc != 5);
    
    libera_matriz(planProd, Prods);
    delete[] costos;
    delete[] inventarioMP;
    
    std::cout << "\nSaliendo del programa...\n";
    
    return 0;
}