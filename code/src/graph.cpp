/**
 * @file graph.cpp
 * @author Gabriel Alves (https://github.com/Nerd100oculoS)
 * @brief Arquivo de Implementação
 * @version 0.1
 * @date 2022-11-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/graph.hpp"

// --------------------------- Vertex --------------------------------

/**
 * @brief Construtor tipo Vertex.
 * 
 * @param name Nome do Vertex.
 */
Vertex::Vertex(string name){

    this->name_vertex = name;
    this->grade_input = 0;
    this->grade_output = 0;
    this->grade = 0;
}

/**
 * @brief Destrutor do tipo Vertex
**/
Vertex::~Vertex(){}

/**
 * @brief set grande_input
**/
void Vertex::setGradeIn(){

    this->grade_input++;
}

int Vertex::getGradeIn(){return grade_input;}

void Vertex::setGradeOut(){

    this->grade_output++;
}

int Vertex::getGradeOut(){return grade_output;}

void Vertex::setGrade(){

    this->grade = getGradeIn()+getGradeOut();
}

int Vertex::getGrade(){return grade;}

string Vertex::getNameVertex(){return name_vertex;}

// --------------------------- Graph --------------------------- 

/**
 * @brief Construct a new Graph:: Graph object
 * 
 * @param name_file Nome do aquivo com extensão
 */
Graph::Graph(string name_file){

    string str_file = "./src/input/";
    str_file.append(name_file);
    string str_token;

    cout << str_file << endl;
    ifstream file(str_file);

    if(file.is_open()){

        while(getline(file,str_token)){

            Vertex v = Vertex(str_token);
            vertex.push_back(v);
        }

        this->size_graph = vertex.size();
        this->count_edges = 0;

    }else{

        cout << "ERRO - " << name_file << endl << endl;
    }

    file.close();

    MatrixAdjNull(size_graph);
}

Graph::~Graph(){}

int Graph::getEdgesSize(){

    return count_edges;
}

string Graph::getNameVertex(int index){

    return vertex[index].getNameVertex();
}

float Graph::getWeightIndex(int i1, int i2){

    return matrix_adj[i1][i2];
}

Matrix Graph::getMatrixAdj(){

    return matrix_adj;
}

Matrix Graph::getMatrixFinal(){

    return matrix_final;
}


void Graph::MatrixAdjNull(int size){

    vector<float> aux1, aux2;
    for(int i = 0; i < size; i++){
        aux1.push_back(INF);
        aux2.push_back(-1);
    }

    for(int i = 0; i < size; i++){

        matrix_adj.push_back(aux1);
        matrix_final.push_back(aux2);
    }

    for(int i = 0; i < size; i++){

        matrix_adj[i][i] = 0.0;
    }
}


void Graph::PrintMatrix(Matrix m){

    int size = vertex.size();

    for(int i = 0; i < size; i++){
        
        for(int j = 0; j < size; j++){
            
            if(m[i][j] == INF){

                cout << 0 << " ";

            }else{

                cout << m[i][j] << " ";
            }
        }
        cout << endl;
    }
}


void Graph::PrintVertex(){

    for(int i = 0; i < vertex.size(); i++){

        cout << vertex[i].getNameVertex() << " - " << vertex[i].getGrade() << endl;
    }
}

void Graph::MakeConection(string name1, string name2, float weight){

    int index_v1 = getIndexVertex(name1);
    int index_v2 = getIndexVertex(name2);

    if(index_v1 != -1 && index_v2 != -1){

        matrix_adj[index_v1][index_v2] = weight;
        count_edges++;
        UpdateGrade(index_v1, index_v2);
    }

}

int Graph::getIndexVertex(string name){

    for(int i = 0; i < vertex.size(); i++){

        if(vertex[i].getNameVertex() == name){

            return i;
        }
    }

    return -1;
}

void Graph::UpdateGrade(int i1, int i2){

    vertex[i1].setGradeOut(); // vertice do qual sai uma aresta.
    vertex[i2].setGradeIn(); // vertice o qual chega uma aresta.

    // Atualiza o grau total
    vertex[i1].setGrade();
    vertex[i2].setGrade(); 
} 

void Graph::ReadFileConections(string name_file){

    string str_file = "./src/input/";
    str_file.append(name_file);

    ifstream file(str_file);

    if(file.is_open()){

         string line_token, token;
        char del = '/';

        while(getline(file,line_token)){

            stringstream sstream(line_token);
            string str1, str2;
            float w_ref;

            int control = 0;
            
            while(getline(sstream,token,del)){

                switch(control){

                    case 0:
                        str1 = token;
                    break;

                    case 1:
                        str2 = token;
                    break;

                    case 2:
                        w_ref = stof(token);
                    break;
                }
                
                control++;
            }

            control = 0;
            
            MakeConection(str1, str2, w_ref);
            MakeConection(str2, str1, w_ref);   
        }

    }else{

        cout << "ERRO - " << name_file << endl;
    }
}

void Graph::MakeFloydWarshall(){

    int N = vertex.size();
    
    for(int k = 0; k < N; k++){             //Nessa parte analisamos a ditância entre um ponto intermediario entre i e j 
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(matrix_adj[i][j] > matrix_adj[i][k]+matrix_adj[k][j]){
                    
                    matrix_adj[i][j] = matrix_adj[i][k] + matrix_adj[k][j];
                    matrix_final[i][j] = k;
                }
            }
        }
    }
}


void Graph::ShortPathAux(int index1, int index2){

    if(matrix_final[index1][index2] == -1){

        cout << vertex[index2].getNameVertex();
        return;
    }
    ShortPathAux(index1,matrix_final[index1][index2]);
    cout << " --> ";
    ShortPathAux(matrix_final[index1][index2],index2);
}

void Graph::MakePath(string name1, string name2){

    int i = getIndexVertex(name1);
    int j = getIndexVertex(name2);


    cout<< "\n[" << getNameVertex(i) << "] para [" << 
    getNameVertex(j) << "]: " << getNameVertex(i) << " --> "; 
    ShortPathAux(i, j);
}

void Graph::MakeMinPath3_Sequential(string name1, string name2, string name3){

    int index1 = getIndexVertex(name1);
    int index2 = getIndexVertex(name2);
    int index3 = getIndexVertex(name3);
    int index_loja = getIndexVertex(LOJA);

    float custo_t = 0.0;

    MakePath(LOJA, name1);
    cout << endl;
    custo_t += getWeightIndex(index_loja,index1);
    MakePath(name1, name2);
    cout << endl;
    custo_t += getWeightIndex(index1,index2);
    MakePath(name2, name3);
    cout << endl;
    custo_t += getWeightIndex(index2,index3);

    cout << "\nCusto Total = " << custo_t << " Km" << endl;

}
