// BTL_PPT2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// BTL_PPT2 is reate by C++ language
// coppyright @ ThToan2510
#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>
using namespace  std;
void enterData(double X[], double Y[], int &cucDai, int &cucTieu);
void initMatrix(double X[], double Y[], double A[][15], int cucDai, int cucTieu);
void matrixBacThang(double A[14][15]);
void solutionMatrix(double solution[14], double A[14][15]);
int main(){
    double x = 0;
    double y = 0;
    int cucDai = 0;
    int cucTieu = 0;
    double KQ = 0;
    double X[10]; 
    double Y[10]; 
    double A[14][15];
    double solution[14];
    enterData(X, Y, cucDai, cucTieu);
    initMatrix(X, Y, A, cucDai, cucTieu);
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 15; j++) {
            cout << A[i][j] << "  ";
        }
        cout << endl;
    }
    matrixBacThang(A);
    cout << "========================================================\n";
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 15; j++) {
            cout << A[i][j] << "  ";
        }
        cout << endl;
    }
    solutionMatrix(solution, A);
    cout << "=======================================================\n";
    for (int i = 0; i < 14; i++) {
        cout << solution[i] << endl;
    }
    ofstream data;
    data.open("c:/Users/nttoa/desktop/data.tmp",ios::trunc);    // Thay đổi tuỳ theo địa chỉ của tuần máy
    for (x = X[0]; x < X[9]; x += 0.001){
        y = 0;
        for (int i = 0; i < 14; i++) {
            y += solution[i] * pow(x, i);
        }
        data << x << " " << y << endl;
    }
    cout << "Da thuc noi suy: " << endl;
    cout << "P(x) = ";
    for (int i = 0; i < 14; i++) {
        cout <<" +"<< solution[i] << "x^" << i;
    }
    return 0;
}
void enterData(double X[], double Y[], int &cucDai, int &cucTieu) {
    cout << "Nhap cac diem X noi suy: \n";
    for (int i = 0; i < 10; i++) {
        printf("X[%d]", i); cin >> X[i]; cout << endl;
    }
    cout << "Nhap cac diem Y noi suy: \n";
    for (int i = 0; i < 10; i++) {
        printf("Y[%d]", i); cin >> Y[i]; cout << endl;
    }
    cout << "Diem nut la diem cuc dai: "; cin >> cucDai; cout << endl;
    cout << "Diem nut la diem cuc tieu: "; cin >> cucTieu; cout << endl;
    cucDai--;
    cucTieu--;
}
void initMatrix(double X[], double Y[], double A[][15], int cucDai, int cucTieu) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 14; j++) {
            A[i][j] = pow(X[i], j);
        }
        A[i][14] = Y[i];
    }
    for (int i = 1; i < 14; i++) {
        A[10][i] = (1.0*i) * pow(X[cucDai], i-1);
    }
    A[10][0] = 0; A[10][14] = 0;            // Dao ham tai cuc đại = 0
    for (int i = 2; i < 14; i++) {
        A[11][i] = (1.0*i) * (1.0*i-1) * pow(X[cucDai], i-2);
    }
    A[11][1] = 0; A[11][0] = 0; A[11][14] = -50;        // đạo hàm cấp 2 = -10
    for (int i = 1; i < 14; i++) {
        A[12][i] = (1.0*i) * pow(X[cucTieu], i-1);
    }
    A[12][0] = 0; A[12][14] = 0;            // Dao ham tai cuc tieu = 0
    for (int i = 2; i < 14; i++) {
        A[13][i] = (1.0*i) * (1.0*i-1) * pow(X[cucTieu], i-2);
    }
    A[13][1] = 0; A[13][0] = 0; A[13][14] = 50;
}
void matrixBacThang(double A[14][15]) {
    double tempTu = 0;
    double tempMau = 0;
    double tempSwap[15];
    int counter = 0;
    for (int step = 0; step < 13; step++) {
        for (int i = step + 1; i < 14; i++) {
            counter = step + 1;
            tempTu = A[step][step];
            while (tempTu == 0 && counter != 14) {
                for (int t = 0; t < 15; t++) {
                    tempSwap[t] = A[step][t];
                    A[step][t] = A[counter][t];
                    A[counter][t] = tempSwap[t];
                }
                counter++;
            }
            tempMau = A[i][step];
            if (tempMau == 0) continue;
            for (int j = step; j < 15; j++) {
                A[i][j] = A[step][j] - (A[i][j] * tempTu / tempMau);
            }
        }
    }
}

void solutionMatrix(double solution[14], double A[14][15]) {
    for (int step = 13; step > -1; step--) {
        solution[step] = A[step][14];
        for (int i = 13; i > (step); i--) {
            solution[step] -= A[step][i]*solution[i];
        }
        solution[step] = solution[step] / A[step][step];
    }
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
