#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#define MaxVertex 100
 
struct Graph
{
    int NumOfVertex; //Cho bi?t d? th? có bao nhiêu d?nh
    //Khai báo ma tr?n k? v?i s? d?nh t?i da s? d?ng m?ng tinh
    int Data[MaxVertex][MaxVertex];
};
 
void DFS(Graph MyGraph, int vertex, bool visitedVertex[])
{
    //Ðánh d?u d?nh dã xét là true, xu?t giá tr? d?nh xét
    visitedVertex[vertex] = true;
    cout << vertex << " -> ";
    //Xét t?t c? các d?nh k?, g?i d? quy t?i t?ng d?nh k?
    for (int i = 0; i < MyGraph.NumOfVertex; i++)
        if (MyGraph.Data[vertex][i] != 0 && visitedVertex[i] == false)
            DFS(MyGraph, i, visitedVertex);
}
void DFSRecursive(Graph MyGraph, int startVertex)
{
    //Hàm duy?t toàn b? d? th? b?t d?u t? 1 d?nh s? d?ng DFS d? quy
    //Ki?m tra tính h?p l? c?a d?nh ban d?u
    if (startVertex >= MyGraph.NumOfVertex || startVertex < 0)
    {
        cout << "Dinh bat dau khong hop le" << endl;
        return;
    }
    bool visitedVertex[MaxVertex]; //M?ng luu l?i d?nh dã xét hay chua?
    //Kh?i t?o m?ng các d?nh dã vi?ng tham ban d?u là false
    for (int i = 0; i < MyGraph.NumOfVertex; i++)
        visitedVertex[i] = false;
    cout << "Thu tu duyet DFS bat dau tai dinh " << startVertex << " la: " << endl;
    //B?t dâu g?i hàm duy?t d? quy
    DFS(MyGraph, startVertex, visitedVertex);
    //Ki?m tra t?t c? các d?nh xem có d?nh nào n?m riêng l?, có d? th? r?i không?
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
        //Ð?c vào s? d?u tiên th? hi?n cho s? d?nh
        MyFile >> MyGraph.NumOfVertex;
        //Hai vòng l?p d? d?c tu?n t? giá tr?
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
    //Ki?m tra tính h?p l? c?a d?nh ban d?u
    if (startVertex >= MyGraph.NumOfVertex || startVertex < 0)
    {
        cout << "Dinh bat dau khong hop le" << endl;
        return;
    }
    //Ki?m tra tính h?p l? c?a d?nh k?t thúc
    if (endVertex >= MyGraph.NumOfVertex || endVertex < 0)
    {
        cout << "Dinh ket thuc khong hop le" << endl;
        return;
    }
    //Xét n?u v? trí b?t d?u b?ng v? trí d?n, xuât ra và không c?n tìm n?a
    if (startVertex == endVertex)
    {
        cout << "Duong di ngay tai cho, khong can di dau nua" << endl;
        return;
    }
    bool visitedVertex[MaxVertex]; //M?ng luu l?i d?nh dã xét hay chua?
    int Path[MaxVertex]; //M?ng luu v?t du?ng di
    int Cost[MaxVertex]; //M?ng tính toán giá tr? tr?ng s?
    //Kh?i t?o m?ng các d?nh dã vi?ng tham ban d?u là false
    //Kh?i t?o du?ng di d?n t?t c? d?nh là s? âm
    for (int i = 0; i < MyGraph.NumOfVertex; i++)
    {
        visitedVertex[i] = false;
        Path[i] = -1;
        Cost[i] = -1;
    }
    Cost[startVertex] = 0;
    int minValue = 0;
    int minVertex = -1;
    //Trong khi chua t?i d?nh cu?i(xét t?i d?nh cu?i v?n còn b?ng false)
    while (visitedVertex[endVertex] == false)
    {
        //kh?i t?o giá tr? nh? nh?t và d?nh có giá tr? nh? nh?t là -1
        minValue = -1;
        minVertex = -1;
        //Duy?t toàn b? t?t c? các d?nh, tìm d?nh có cost nh? nh?t
        //d?nh dó ph?i là d?nh chua xét và d?nh dó dã du?c tính toán giá tr?
        //N?u d?nh nào chua di qua
        //N?u d?nh nào dã có cost (có r?i m?i tìm cost min du?c)
        //N?u cost nh? hon nh? nh?t, gán nh? nh?t = cost
        for (int i = 0; i < MyGraph.NumOfVertex; i++)
        {
            if (visitedVertex[i] == false &&
                Cost[i] != -1 &&
                (Cost[i] < minValue || minValue == -1))
            { //N?u ngay d?nh b?t d?u, cost chua có (minvalue == Inf), cost t?i d?nh b?t d?u là nh? nh?t
            //C?p nh?t l?i giá tr? nh? nh?t là du?ng di d?n d?nh i
                minValue = Cost[i];
                //C?p nh?t l?i d?nh có giá tr? nh? nh?t (chính là d?nh th? i)
                minVertex = i;
            }
        }
        //N?u giá tr? nh? nh?t v?n chua c?p nh?t, t?c là không tìm du?c du?ng di n?a
        //Dùng trong tru?ng h?p d? th? có hu?ng, ko có hu?ng di n?a nên ko có cost min
        if (minValue == -1)
        {
            cout << "Khong tim thay duong di" << endl;
            return;
        }
        //Gán giá tr? nh? nh?t cho d? dài d?nh nh? nh?t
        Cost[minVertex] = minValue;
        //Ðánh d?u dã di qua d?nh dó
        visitedVertex[minVertex] = true;
        //Vòng l?p c?p nh?t l?i giá tr? cost d?n d?nh th? i
        for (int i = 0; i < MyGraph.NumOfVertex; i++)
        {
            //N?u d?nh hi?n t?i chua xét và có liên quan d?n d?nh nh? nh?t
            if (visitedVertex[i] == false && MyGraph.Data[minVertex][i] != 0)
            {
                //Ði?u ki?n Cost == -1 dùng d? ki?m tra n?u t?i d?nh dó, chua có b?t kì du?ng di nào (cost = -1), c?p nh?t cost di t?i du?ng dó
                //N?u có du?ng di t?i d?nh dó r?i, n?u du?ng di m?i t?i d?nh dó t?n cost ít hon thì m?i c?p nh?t, không thì thôi
                if (Cost[i] == -1 || Cost[i] > Cost[minVertex] + MyGraph.Data[minVertex][i])
                {
                    Cost[i] = Cost[minVertex] + MyGraph.Data[minVertex][i];
                    Path[i] = minVertex;
                }
            }
        }
    }
    //Xu?t k?t qu? du?ng di, xét n?u du?ng di -1 t?c là không có du?ng di d?n d?nh dó
    if (Path[endVertex] == -1)
        cout << "Khong co duong di tu dinh " << startVertex << " toi dinh " << endVertex << endl;
    else
    {
        int temp = endVertex; //Gán bi?n truy ngu?c k?t qu? l?i
        //Xu?t t? v? trí cu?i di ngu?c l?i
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
