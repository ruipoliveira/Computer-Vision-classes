#include "fileSource.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;
using std::cout;

int main(int argc, char *argv[]){


    char selection;
    int val_return;

    do
    {
        cout << "  Visao por computador 2016 DETI/UA\n";
        cout << "  ====================================\n";
        cout << "  Exercicio 1\n";
        cout << "  Exercicio 2\n";
        cout << "  Exercicio 3\n";
        cout << "  Exercicio 4\n";
        cout << "  Exercicio 5\n";
        cout << "  Exercicio 6\n";
        cout << "  Exercicio 7\n";
        cout << "  8.  Exit\n";
        cout << "  ====================================\n";
        cout << "  Enter your selection: ";
        cin >> selection;
        cout << endl;

        switch (selection)
        {
            case '1':
                val_return = ex1();
                break;

            case '2':
                val_return = ex2();
                break;
            case '3':
                val_return = ex3();
                break;

            case '4':
                val_return = ex4();
                break;

            case '5':
                val_return = ex5();
                break;
            case '6':
                val_return = ex6();
                break;
            default: cout <<selection << "is not a valid menu item.\n";

                cout << endl;
        }

    }while (selection != '8' );







}



