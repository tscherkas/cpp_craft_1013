/* 
 * File:   main.cpp
 * Author: user
 * 
 * Входные данные: файл input.txt. Выходные данные: файл output.txt.
 * Файл содержит два массива рациональных чисел, массив кодов и массив паролей,
 * заданных следующим образом: Сначала в файле находится целое число
 * N – количество рациональных значений первого массива. Затем N рациональных
 * значений массива кодов. Затем идут M рациональных значений массива
 * паролей (до конца файла). N <= 1000000. Для каждого значения массива
 * паролей выдать в выходной файл “YES” если существует код идентичный
 * данному паролю и “NO” если не существует. Запись в выходной файл
 * произвести в том же порядке, в котором находились значения массива
 * паролей. Все рациональные значения имеют точность 10^(-4).
 * 
 * Created on чацвер, 18, кастрычніка 2013, 11.28
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>

#define MAX_N_SIZE 100000


void printToOutput(std::ofstream & outputfile , std::string msg) {
    outputfile << msg <<"\n";
    std::cout << msg << std::endl;
}

void task1p4(std::ifstream & inputfile, std::ofstream & outputfile)
{
    std::string line;
    while ( getline (inputfile,line) )
    {
        
    }   
}

bool openFiles(std::ifstream & inputfile, std::ofstream & outputfile) 
{
    return ( (inputfile.is_open()) && (outputfile.is_open()));
}

int main(int argc, char** argv) 
{   
    std::ifstream inputfile ("/tmp/input.txt");
    std::ofstream outputfile ("/tmp/output.txt");
    if (openFiles(inputfile,outputfile)) {
        task1p4(inputfile,outputfile);
        inputfile.close();
        outputfile.close();
    } else {
        std::cout << "fail" << std::endl;
    }
    
    return 0;
}

