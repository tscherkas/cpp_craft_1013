/* 
 * File:   main.cpp
 * Author: user
 *
 * 1.3. Задача «Перевёрнутые строки».
 * Входные данные: файл input.txt. Выходные данные: файл output.txt.
 * 1ая строка файла содержит текст. Длина строки не более 100000 символов.
 * Все следующие строки файла содержат текстовые ключи.
 * Для каждого текстового ключа выяснить, есть ли ключ в тексте в перевёрнутом
 * виде (без учёта символов пробела “ “, тире “-“ и слеша “\”; все заглавные
 * символы равноценны строчным). Для каждого ключа требуется выдать «YES»
 * если он содержится в тексте и «NO» если не содержится. Ответ требуется
 * дать выходной файл в том же порядке, в котором ключи расположены
 * во входном файле.
 * 
 * Created on чацвер, 17, кастрычніка 2013, 22.09
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>


bool puzzle(std::string line)
{
    return false;
}

void task1p3(std::ifstream & inputfile, std::ofstream & outputfile)
{
    std::string line;
    while ( getline (inputfile,line) )
    {
        if (puzzle(line)) 
        {
            outputfile << "YES\n";
            std::cout << "YES" << std::endl;
        } else {
            outputfile << "NO\n";
            std::cout << "NO" << std::endl;
        }
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
        task1p3(inputfile,outputfile);
        inputfile.close();
        outputfile.close();
    } else {
        std::cout << "fail" << std::endl;
    }
    return 0;
}

