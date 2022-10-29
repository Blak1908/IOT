#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#define MaxVertex 100
 
struct Graph
{
    int NumOfVertex; //Cho bi?t d? th? c� bao nhi�u d?nh
    //Khai b�o ma tr?n k? v?i s? d?nh t?i da s? d?ng m?ng tinh
    int Data[MaxVertex][MaxVertex];
};
 
void DFS(Graph MyGraph, int vertex, bool visitedVertex[])
{
    //��nh d?u d?nh d� x�t l� true, xu?t gi� tr? d?nh x�t
    visitedVertex[vertex] = true;
    cout << vertex << " -> ";
    //X�t t?t c? c�c d?nh k?, g?i d? quy t?i t?ng d?nh k?
    for (int i = 0; i < MyGraph.NumOfVertex; i++)
        if (MyGraph.Data[vertex][i] != 0 && visitedVertex[i] == false)
            DFS(MyGraph, i, visitedVertex);
}
void DFSRecursive(Graph MyGraph, int startVertex)
{
    //H�m duy?t to�n b? d? th? b?t d?u t? 1 d?nh s? d?ng DFS d? quy
    //Ki?m tra t�nh h?p l? c?a d?nh ban d?u
    if (startVertex >= MyGraph.NumOfVertex || startVertex < 0)
    {
        cout << "Dinh bat dau khong hop le" << endl;
        return;
    }
    bool visitedVertex[MaxVertex]; //M?ng luu l?i d?nh d� x�t hay chua?
    //Kh?i t?o m?ng c�c d?nh d� vi?ng tham ban d?u l� false
    for (int i = 0; i < MyGraph.NumOfVertex; i++)
        visitedVertex[i] = false;
    cout << "Thu tu duyet DFS bat dau tai dinh " << startVertex << " la: " << endl;
    //B?t d�u g?i h�m duy?t d? quy
    DFS(MyGraph, startVertex, visitedVertex);
    //Ki?m tra t?t c? c�c d?nh xem c� d?nh n�o n?m ri�ng l?, c� d? th? r?i kh�ng?
    for (int i = 0; i < MyGraph.NumOfVertex; i++)
        if (visitedVertex[i] == false)
            DFS(MyGraph, i, visitedVertex);
    cout << endl << "Ket thuc duyet do thi" << endl;
}
void ReadGraphFromFile(string filename, Graph& MyGraph)
{
    fstream MyFile;
    MyFile.open(filename, ios::in);
    if (MyFile.is_open())
    {
        //�?c v�o s? d?u ti�n th? hi?n cho s? d?nh
        MyFile >> MyGraph.NumOfVertex;
        //Hai v�ng l?p d? d?c tu?n t? gi� tr?
        for (int i = 0; i < MyGraph.NumOfVertex; i++)
            for (int j = 0; j < MyGraph.NumOfVertex; j++)
                MyFile >> MyGraph.Data[i][j];
    }
    MyFile.close();
}
void PrintGraphData(Graph MyGraph)
{
    cout << "Graph Data: " << MyGraph.NumOfVertex << "x" << MyGraph.NumOfVertex << endl;
    for (int i = 0; i < MyGraph.NumOfVertex; i++)
    {
        for (int j = 0; j < MyGraph.NumOfVertex; j++)
            cout << MyGraph.Data[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}
void DFSpath(Graph MyGraph, int startVertex, int endVertex)
{
    if (startVertex >= MyGraph.NumOfVertex || startVertex < 0)
    {
        cout << "Dinh bat dau khong hop le" << endl;
        return;
    }
    if (endVertex >= MyGraph.NumOfVertex || endVertex < 0)
    {
        cout << "Dinh ket thuc khong hop le" << endl;
        return;
    }
    if (startVertex == endVertex)
    {
        cout << "Duong di ngay tai cho, khong can di dau nua" << endl;
        return;
    }
    bool visitedVertex[MaxVertex];
    int Path[MaxVertex];
    int Cost[MaxVertex];
    for (int i = 0; i < MyGraph.NumOfVertex; i++)
    {
        visitedVertex[i] = false;
        Path[i] = -1;
        Cost[i] = -1;
    }
    Cost[startVertex] = 0;
    int minValue = 0;
    int minVertex = -1;
    while (visitedVertex[endVertex] == false)
    {
        minValue = -1;
        minVertex = -1;
        for (int i = 0; i < MyGraph.NumOfVertex; i++)
        {
            if (visitedVertex[i] == false && Cost[i] != -1 && (Cost[i] < minValue || minValue == -1))
            {
                minValue = Cost[i];
                minVertex = i;
            }
        }
        if (minValue == -1)
        {
            cout << "Khong tim thay duong di" << endl;
            return;
        }
        Cost[minVertex] = minValue;
        visitedVertex[minVertex] = true;
        for (int i = 0; i < MyGraph.NumOfVertex; i++)
        {
            if (visitedVertex[i] == false && MyGraph.Data[minVertex][i] != 0)
            {
                if (Cost[i] == -1 || Cost[i] > Cost[minVertex] + MyGraph.Data[minVertex][i])
                {
                    Cost[i] = Cost[minVertex] + MyGraph.Data[minVertex][i];
                    Path[i] = minVertex;
                }
            }
        }
    }
    if (Path[endVertex] == -1)
        cout << "Khong co duong di tu dinh " << startVertex << " toi dinh " << endVertex << endl;
    else
    {
        int temp = endVertex;
        cout << endVertex << " <= ";
        while (Path[temp] != startVertex)
        {
            cout << Path[temp] << " <= ";
            temp = Path[temp];
        }
        cout << startVertex << endl;
    }
}
 
void Dijkstra(Graph MyGraph, int startVertex, int endVertex)
{
    //Ki?m tra t�nh h?p l? c?a d?nh ban d?u
    if (startVertex >= MyGraph.NumOfVertex || startVertex < 0)
    {
        cout << "Dinh bat dau khong hop le" << endl;
        return;
    }
    //Ki?m tra t�nh h?p l? c?a d?nh k?t th�c
    if (endVertex >= MyGraph.NumOfVertex || endVertex < 0)
    {
        cout << "Dinh ket thuc khong hop le" << endl;
        return;
    }
    //X�t n?u v? tr� b?t d?u b?ng v? tr� d?n, xu�t ra v� kh�ng c?n t�m n?a
    if (startVertex == endVertex)
    {
        cout << "Duong di ngay tai cho, khong can di dau nua" << endl;
        return;
    }
    bool visitedVertex[MaxVertex]; //M?ng luu l?i d?nh d� x�t hay chua?
    int Path[MaxVertex]; //M?ng luu v?t du?ng di
    int Cost[MaxVertex]; //M?ng t�nh to�n gi� tr? tr?ng s?
    //Kh?i t?o m?ng c�c d?nh d� vi?ng tham ban d?u l� false
    //Kh?i t?o du?ng di d?n t?t c? d?nh l� s? �m
    for (int i = 0; i < MyGraph.NumOfVertex; i++)
    {
        visitedVertex[i] = false;
        Path[i] = -1;
        Cost[i] = -1;
    }
    Cost[startVertex] = 0;
    int minValue = 0;
    int minVertex = -1;
    //Trong khi chua t?i d?nh cu?i(x�t t?i d?nh cu?i v?n c�n b?ng false)
    while (visitedVertex[endVertex] == false)
    {
        //kh?i t?o gi� tr? nh? nh?t v� d?nh c� gi� tr? nh? nh?t l� -1
        minValue = -1;
        minVertex = -1;
        //Duy?t to�n b? t?t c? c�c d?nh, t�m d?nh c� cost nh? nh?t
        //d?nh d� ph?i l� d?nh chua x�t v� d?nh d� d� du?c t�nh to�n gi� tr?
        //N?u d?nh n�o chua di qua
        //N?u d?nh n�o d� c� cost (c� r?i m?i t�m cost min du?c)
        //N?u cost nh? hon nh? nh?t, g�n nh? nh?t = cost
        for (int i = 0; i < MyGraph.NumOfVertex; i++)
        {
            if (visitedVertex[i] == false &&
                Cost[i] != -1 &&
                (Cost[i] < minValue || minValue == -1))
            { //N?u ngay d?nh b?t d?u, cost chua c� (minvalue == Inf), cost t?i d?nh b?t d?u l� nh? nh?t
            //C?p nh?t l?i gi� tr? nh? nh?t l� du?ng di d?n d?nh i
                minValue = Cost[i];
                //C?p nh?t l?i d?nh c� gi� tr? nh? nh?t (ch�nh l� d?nh th? i)
                minVertex = i;
            }
        }
        //N?u gi� tr? nh? nh?t v?n chua c?p nh?t, t?c l� kh�ng t�m du?c du?ng di n?a
        //D�ng trong tru?ng h?p d? th? c� hu?ng, ko c� hu?ng di n?a n�n ko c� cost min
        if (minValue == -1)
        {
            cout << "Khong tim thay duong di" << endl;
            return;
        }
        //G�n gi� tr? nh? nh?t cho d? d�i d?nh nh? nh?t
        Cost[minVertex] = minValue;
        //��nh d?u d� di qua d?nh d�
        visitedVertex[minVertex] = true;
        //V�ng l?p c?p nh?t l?i gi� tr? cost d?n d?nh th? i
        for (int i = 0; i < MyGraph.NumOfVertex; i++)
        {
            //N?u d?nh hi?n t?i chua x�t v� c� li�n quan d?n d?nh nh? nh?t
            if (visitedVertex[i] == false && MyGraph.Data[minVertex][i] != 0)
            {
                //�i?u ki?n Cost == -1 d�ng d? ki?m tra n?u t?i d?nh d�, chua c� b?t k� du?ng di n�o (cost = -1), c?p nh?t cost di t?i du?ng d�
                //N?u c� du?ng di t?i d?nh d� r?i, n?u du?ng di m?i t?i d?nh d� t?n cost �t hon th� m?i c?p nh?t, kh�ng th� th�i
                if (Cost[i] == -1 || Cost[i] > Cost[minVertex] + MyGraph.Data[minVertex][i])
                {
                    Cost[i] = Cost[minVertex] + MyGraph.Data[minVertex][i];
                    Path[i] = minVertex;
                }
            }
        }
    }
    //Xu?t k?t qu? du?ng di, x�t n?u du?ng di -1 t?c l� kh�ng c� du?ng di d?n d?nh d�
    if (Path[endVertex] == -1)
        cout << "Khong co duong di tu dinh " << startVertex << " toi dinh " << endVertex << endl;
    else
    {
        int temp = endVertex; //G�n bi?n truy ngu?c k?t qu? l?i
        //Xu?t t? v? tr� cu?i di ngu?c l?i
        cout << endVertex << "<=";
        while (Path[temp] != startVertex)
        {
            cout << Path[temp] << "<=";
            temp = Path[temp];
        }
        cout << startVertex << endl;
    }
}
 
int main()
{
    fstream myfile;
    myfile.open("Maze.txt");
    ofstream xuatrafile("Result.txt");
    int dong, cot;
    myfile >> dong;
    cout << dong << "\t";
    myfile << "\0";
    myfile >> cot;
    cout << cot << endl;
    char m;
    for (int i = 0; i < dong; i++)
    {
        for (int j = 0; j < cot; j++)
        {
            myfile >> m;
            myfile << "\0";
            cout << m << "\t";
        }
        myfile << "\n";
        cout << "\n";
    }
    xuatrafile << "a";
    cout << "\n\n";
}
