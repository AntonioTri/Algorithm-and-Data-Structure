#include <iostream>
#include <vector>
using namespace std;
#define LENGHT 19

class QuickSort {

    public:

        QuickSort(){};

        void CoremanQuickSort(int *a, int r, int q){

            if(q - r <= 0) {return;};

            int pivot = PartitioningCoreman(a, r, q);
            CoremanQuickSort(a, r, pivot - 1);
            CoremanQuickSort(a, pivot + 1, q); 

        };

        void HoareQuickSort(int *a, int r, int q){

            if (q- r < 0){ return;};

            int pivot = PartitioningHoare(a, r, q);
            HoareQuickSort(a, r, pivot -1);
            HoareQuickSort(a, pivot + 1, q);

        };

    private:


        int PartitioningCoreman(int *a, int r, int q){

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

        int PartitioningHoare(int *a, int r, int q){

            int pivot = a [q];
            int i = r - 1;
            int j = q;

            while (true)
            {
                while (a[++i] <= pivot && i < q )
                {
                    i++;
                }

                while (a[--j] >= pivot)
                {
                    j--;
                    if (j == r){ break; }

                }
                
                if (i < j){

                    Swap(a[i], a[j]);

                } else {
                    break;
                }
            }
           // Swap(a[i], a[j]);
            return i;
        };


        void Swap(int &a, int &b){

            int temp = a;
            a = b;
            b = temp;

        };



};


int main(){

    QuickSort *quickSort = new QuickSort(); 

    //Coreman QuickSort
    int a[LENGHT] = { 2, 53 ,34 ,7 ,5 ,4 ,32 ,23, 25, 53, 46, 54, 26, 23, 13, 56, 7, 77,43};

    cout << "Risoluzione con Partizionamento Coreman" << endl;
    for (int i = 0; i < LENGHT ; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    quickSort->CoremanQuickSort(a, 0, LENGHT - 1);

    for (int i = 0; i < LENGHT ; i++)
    {
        cout << a[i] << " ";
    }    
    cout << endl << endl;


    //Hoare QuickSort
    int b[LENGHT] = { 2, 53 ,34 ,7 ,5 ,4 ,32 ,23, 25, 53, 46, 54, 26, 23, 13, 56, 7, 77,43};

    cout << "Risoluzione con Partizionamento Hoare" << endl;
    for (int i = 0; i < LENGHT ; i++)
    {
        cout << b[i] << " ";
    }
    cout << endl;

    quickSort->HoareQuickSort(b, 0, LENGHT - 1);

    for (int i = 0; i < LENGHT ; i++)
    {
        cout << b[i] << " ";
    }
    cout << endl;

    return 0;

}