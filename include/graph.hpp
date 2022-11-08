#ifndef GRAPH_HPP
#define GRAPH_HPP

#include<bits/stdc++.h>

using namespace std;

class Vertex{

    private:

        string name_vertex;
        int grade_input;
        int grade_output;
        int grade;
    public:

        Vertex(string name);
        ~Vertex();

        void setGradeIn();
        int getGradeIn();

        void setGradeOut();
        int getGradeOut();

        void setGrade();
        int getGrade();
        string getNameVertex();
};


class Graph{

    private:

        int size_graph; //quantidade de vertices no grafo.
        int count_edges; // Quantidade de arestas no grafo todo
        vector<Vertex> vertex; // Lista de vertices para se obter indice
        vector<vector<float>> matrix_adj;

    public:

        Graph(string name_file);
        ~Graph();
        
        void PrintVertex();
        void PrintMatrix();
        void MatrixAdjNull(int size);
        void MakeConection(string name1, string name2, float weight);
        int getIndexVertex(string name);
        void UpdateGrade(int i1, int i2);

};

#endif