#include <iostream>
#include <vector>
using namespace std;
#define LENGHT 19

class QuickSort {

    public:

        QuickSort(){};

        void CoremanQuickSort(int *a, int r, int q){

            if(q - r <= 0) {return;};

            int pivot = Partitioning(a, r, q);
            CoremanQuickSort(a, r, pivot - 1);
            CoremanQuickSort(a, pivot + 1, q); 

        };

    private:


        int Partitioning(int *a, int r, int q){

            int pivot = a[q];
            int i = r - 1;

            for (int j = r; j < q; j++)
            {
                if (a[j] < pivot) { 
                    Swap(a[++i], a[j]); 
                }
            }

            Swap(a[++i], a[q]);
            return i;

        };

        void Swap(int &a, int &b){

            int temp = a;
            a = b;
            b = temp;

        };



};


int main(){

    int a[LENGHT] = { 2, 53 ,34 ,7 ,5 ,4 ,32 ,23, 25, 53, 46, 54, 26, 23, 13, 56, 7, 77,43};

    for (int i = 0; i < LENGHT ; i++)
    {
        cout << a[i] << " ";
    }
    
    cout << endl;

    QuickSort *quickSort = new QuickSort(); 

    quickSort->CoremanQuickSort(a, 0, LENGHT - 1);

    for (int i = 0; i < LENGHT ; i++)
    {
        cout << a[i] << " ";
    }
    
    cout << endl;


    return 0;

}