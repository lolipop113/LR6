#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

void removeVertex(vector<vector<int>>& matrix, int vertex) {
    int size = matrix.size();

    // Удаление вершины и рёбер
    matrix.erase(matrix.begin() + vertex);
    for (int i = 0; i < size - 1; i++) {
        matrix[i].erase(matrix[i].begin() + vertex);
    }
}

void identifyVertices(vector<vector<int>>& matrix, int vertex1, int vertex2) {
    int size = matrix.size();

    // Отождествление вершин vertex1 и vertex2
    for (int i = 0; i < size; i++) {
        matrix[vertex1][i] = matrix[vertex1][i] || matrix[vertex2][i];
    }
    for (int i = 0; i < size; i++) {
        matrix[i][vertex1] = matrix[i][vertex1] || matrix[i][vertex2];
    }

    removeVertex(matrix, vertex2);
}

void contractEdge(vector<vector<int>>& matrix, int vertex1, int vertex2) {
    int size = matrix.size();

    matrix[vertex1][vertex2] = 0;
    matrix[vertex2][vertex1] = 0;

    identifyVertices(matrix, vertex1, vertex2);
}

void abiba(vector<vector<int>>& matrix, int vertex1, int vertex2) {
    int size = matrix.size();

    // Новая матрица смежности с дополнительной вершиной
    vector<vector<int>> newMatrix(size + 1, vector<int>(size + 1, 0));

    // Копия значения из старой матрицы в новую 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    // Соединение новой вершины с введёнными
    newMatrix[vertex1][size] = newMatrix[size][vertex1] = 1;
    newMatrix[vertex2][size] = newMatrix[size][vertex2] = 1;

    matrix = newMatrix;
}


void printMatrix(const vector<vector<int>>& matrix) {
    int size = matrix.size();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Объединение графов
void mergeGraphs(vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int size1 = matrix1.size();
    int size2 = matrix2.size();

    int maxSize = max(size1, size2);
    vector<vector<int>> newMatrix(maxSize, vector<int>(maxSize, 0));

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size1; j++) {
            newMatrix[i][j] = matrix1[i][j];
        }
    }

    for (int i = 0; i < size2; i++) {
        for (int j = 0; j < size2; j++) {
            newMatrix[i][j] = newMatrix[i][j] || matrix2[i][j];
        }
    }

    cout << "Первый граф:" << endl;
    printMatrix(matrix1);

    cout << "Второй граф:" << endl;
    printMatrix(matrix2);

    cout << "Результат объединения графов:" << endl;
    printMatrix(newMatrix);

    cout << "Графы успешно объединены!" << endl;

    matrix1 = newMatrix;
}



void intersectionGraphs(vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int size1 = matrix1.size();
    int size2 = matrix2.size();
    int maxSize = max(size1, size2);
    vector<vector<int>> newMatrix(maxSize, vector<int>(maxSize, 0));

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size1; j++) {
            newMatrix[i][j] = matrix1[i][j];
        }
    }

    for (int i = 0; i < size2; i++) {
        for (int j = 0; j < size2; j++) {
            newMatrix[i][j] = newMatrix[i][j] && matrix2[i][j];
        }
    }


    for (int i = 0; i < maxSize; i++) {
        bool isolated = true;
        for (int j = 0; j < maxSize; j++) {
            if (newMatrix[i][j] != 0 || newMatrix[j][i] != 0) {
                isolated = false;
                break;
            }
        }
        if (isolated) {
            removeVertex(newMatrix, i);
            maxSize--;
            i--;
        }
    }



    cout << "Первый граф:" << endl;
    printMatrix(matrix1);

    cout << "Второй граф:" << endl;
    printMatrix(matrix2);

    cout << "Результат пересечения графов:" << endl;
    printMatrix(newMatrix);

    cout << "Графы успешно пересечениы!" << endl;

    matrix1 = newMatrix;
}


void XORGraphs(vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int size1 = matrix1.size();
    int size2 = matrix2.size();

    int maxSize = max(size1, size2);
    vector<vector<int>> newMatrix(maxSize, vector<int>(maxSize, 0));

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size1; j++) {
            newMatrix[i][j] = matrix1[i][j];
        }
    }
    for (int i = 0; i < size2; i++) {
        for (int j = 0; j < size2; j++) {
            newMatrix[i][j] = newMatrix[i][j] xor matrix2[i][j];
        }
    }

    cout << "Первый граф:" << endl;
    printMatrix(matrix1);

    cout << "Второй граф:" << endl;
    printMatrix(matrix2);

    cout << "Результат кольцевой суммы:" << endl;
    printMatrix(newMatrix);

    cout << "Кольцевая сумма построена!" << endl;

    matrix1 = newMatrix;
}


vector<vector<int>> generateAdjacencyList(const vector<vector<int>>& adjacencyMatrix) {
    int size = adjacencyMatrix.size();
    vector<vector<int>> adjacencyList(size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (adjacencyMatrix[i][j] != 0) {
                adjacencyList[i].push_back(j);
            }
        }
    }

    return adjacencyList;
}

void printAdjacencyList(const vector<vector<int>>& adjacencyList) {
    int size = adjacencyList.size();
    for (int i = 0; i < size; i++) {
        cout << "Вершина " << i << ": ";
        for (int j = 0; j < adjacencyList[i].size(); j++) {
            cout << adjacencyList[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    int size;
    cout << "Введите размер матрицы смежности G1: ";
    cin >> size;

    // Создание матрицы смежности
    vector<vector<int>> adjacencyMatrix(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int randomNum = getRandomNumber(0, 1);
            adjacencyMatrix[i][j] = randomNum;
            adjacencyMatrix[j][i] = randomNum;
        }
    }
   
    int size1;
    cout << "Введите размер матрицы смежности G2: ";
    cin >> size1;

    vector<vector<int>> adjacencyMatrix1(size1, vector<int>(size1, 0));
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size1; j++) {
            if (i != j) {
                int randomNum = getRandomNumber(0, 1);
                adjacencyMatrix1[i][j] = randomNum;
                adjacencyMatrix1[j][i] = randomNum;
            }
        }
    }
    vector<vector<int>> adjacencyList = generateAdjacencyList(adjacencyMatrix);
    vector<vector<int>> adjacencyList1 = generateAdjacencyList(adjacencyMatrix1);


    int choice;
    cout << endl;
    cout << "=====================================================================" << endl;
    cout << "=======================| Операции с графами |========================" << endl;
    cout << "=====================================================================" << endl;
    do {
        cout << "1. Отождествление вершин" << endl;
        cout << "2. Стягивание ребра" << endl;
        cout << "3. Вывод матрицы и списка смежности G1" << endl;
        cout << "4. Вывод матрицы и списка смежности G2" << endl;
        cout << "5. Расщепление вершины" << endl;
        cout << "6. Объединение графов" << endl;
        cout << "7. Пересечение графов" << endl;
        cout << "8. Кольцевая сумма" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите операцию: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int vertex1, vertex2;
            cout << "Введите номера вершин для отождествления: ";
            cin >> vertex1 >> vertex2;

            if (vertex1 >= 0 && vertex1 < size && vertex2 >= 0 && vertex2 < size) {
                identifyVertices(adjacencyMatrix, vertex1, vertex2);
                size--;
                cout << "Вершины успешно отождествлены!" << endl;
            }
            else {
                cout << "Некорректные номера вершин!" << endl;
            }

            break;
        }
        case 2: {
            int vertex1, vertex2;
            cout << "Введите номера вершин для стягивания ребра: ";
            cin >> vertex1 >> vertex2;

            if (vertex1 >= 0 && vertex1 < size && vertex2 >= 0 && vertex2 < size) {
                contractEdge(adjacencyMatrix, vertex1, vertex2);
                size++;
                cout << "Ребро стянуто и создана новая вершина" << endl;
            }
            else {
                cout << "Некорректные номера вершин!" << endl;
            }

            break;
        }
        case 3: {
            cout << "Матрица смежности графа G1:" << endl;
            printMatrix(adjacencyMatrix);
            cout << "Список смежности:" << endl;
            printAdjacencyList(adjacencyList);
            break;
        }
        case 4: {
            cout << "Матрица смежности графа G2:" << endl;
            printMatrix(adjacencyMatrix1);
            cout << "Список смежности:" << endl;
            printAdjacencyList(adjacencyList1);
            break;
        }
        case 5: {
            int vertex1, vertex2;
            cout << "Введите вершины на участке расщепления: ";
            cin >> vertex1 >> vertex2;

            if (vertex1 >= 0 && vertex1 < size && vertex2 >= 0 && vertex2 < size) {
 
                abiba(adjacencyMatrix, vertex1, vertex2);
                size++;
                cout << "Расщепление выполнено!" << endl;
            }
            else {
                cout << "Некорректные номера вершин!" << endl;
            }

            break;
        }

        case 6: {


            mergeGraphs(adjacencyMatrix, adjacencyMatrix1);
            break;
        }

        case 7: {
            intersectionGraphs(adjacencyMatrix, adjacencyMatrix1);
            break;
        }

        case 8: {

            XORGraphs(adjacencyMatrix, adjacencyMatrix1);
            break;
        }
        case 0: {
            cout << "Выход из программы." << endl;
            break;
        }
        default: {
            cout << "Некорректный выбор операции!" << endl;
            break;
        }
        }
    } while (choice != 0);

    return 0;
}
