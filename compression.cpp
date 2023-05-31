#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
using namespace std;



class node
{
public:
    char character;
    int counter = 0;
    node* childleft = NULL;
    node* childright = NULL;
    string bits="";
};


node arr[257];


void dedicate_bit(node* n, int how_many_char)
{
    node* l = n->childleft;
    node* r = n->childright;
    if(l==NULL)
    {
        for(int i=0;i<how_many_char;i++)
        {
            if(n->character == arr[i].character)
            {
                arr[i].bits = n->bits;
                break;
            }
        }
        return;
    }
    else if(l!=NULL)
    {
        l->bits = n->bits + "0";
        dedicate_bit(l,how_many_char);
        r->bits = n->bits + "1";
        dedicate_bit(r,how_many_char);
    }

}



class heap
{
public:
    node* harr[256];
    int capacity;
    int heap_size = 0;

    void MinHeapify(int i)  // to heapify a subtree with the root at given index
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap_size && (*(harr[l])).counter < (*(harr[i])).counter)
            smallest = l;
        if (r < heap_size && (*(harr[r])).counter < (*(harr[smallest])).counter)
            smallest = r;
        if (smallest != i)
        {
            swap(harr[i], harr[smallest]);
            MinHeapify(smallest);
        }
    }
    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }

    int parent(int i) { return (i-1)/2; }


    // Method to remove minimum element (or root) from min heap
    node* extractMin()
    {
        if (heap_size == 1)
        {
            heap_size--;
            return harr[0];
        }

        // Store the minimum value, and remove it from heap
        node* root = harr[0];
        harr[0] = harr[heap_size-1];
        heap_size--;
        MinHeapify(0);

        return root;
    }

    void insertKey(node* k)
    {
        if (heap_size == 256)
        {
            cout << endl << "Overflow: Could not insertKey" << endl;
            return;
        }

        // First insert the new key at the end
        heap_size++;
        int i = heap_size - 1;
        harr[i] = k;
        // Fix the min heap property if it is violated

        while (i != 0 && (*(harr[parent(i)])).counter > (*(harr[i])).counter)
        {
            swap(harr[i], harr[parent(i)]);
            i = parent(i);
        }
    }


    void decreaseKey(int i, node* new_val)
    {
        harr[i] = new_val;
        while (i != 0 && (*(harr[parent(i)])).counter > (*(harr[i])).counter)
        {
           swap(harr[i], harr[parent(i)]);
           i = parent(i);
        }
    }



    void deletekey(int i)
    {
        node* n = new node();
        n->counter = INT_MIN;
        decreaseKey(i, n);
        extractMin();
    }
};



int main()
{
    string directory, input, backs;
    input = "input.txt";
    cout << "Enter directory of input.txt file :" << endl;
    getline(cin,directory);
    directory.push_back('\\');
    string dir2 = directory;
    string dir3 = directory;
    for(int i=0;i<input.length();i++)
    {
        directory.push_back(input[i]);
    }
    char a[250]="";
    for(int i=0;i<directory.length();i++)
    {
        a[i] = directory[i];
    }

    FILE* fp;
    fp = fopen(a,"r");
    if(fp==NULL)
    {
        cout << "unable to read the file" << endl;
    }
    else
    {
        cout << "File was read" << endl;
        char c;
        int all_of_chars = 0;
        int how_many_char = 0;
        while(1)
        {

            c = fgetc(fp);

            if(c!=EOF)
            {
                for(int i=0;i<how_many_char+1;i++)
                {
                    if(arr[i].character == c)
                    {

                        arr[i].counter+=1;
                        all_of_chars++;
                        break;
                    }
                    if(i==how_many_char && arr[i].character != c)
                    {

                        arr[how_many_char].character = c;
                        arr[how_many_char].counter += 1;
                        all_of_chars++;
                        how_many_char++;
                        break;
                    }

                }
            }

            else
            {
                arr[how_many_char].character = 0;
                arr[how_many_char].counter = 0;
                all_of_chars++;
                how_many_char++;
                break;
            }


        }

        heap Heap1;
        for(int i=0;i<how_many_char;i++)
        {
            node* n=new node();
            n->character = arr[i].character;
            n->counter = arr[i].counter;
            Heap1.insertKey(n);
        }

        int loop = (Heap1.heap_size)-1;
        while(Heap1.heap_size > 1)
        {
            node* n = new node();
            node* left = Heap1.extractMin();
            node* right = Heap1.extractMin();
            n->counter = (*(right)).counter + (*(left)).counter;
            n->childleft = left;
            n->childright = right;
            Heap1.insertKey(n);
        }

        dedicate_bit(Heap1.harr[0],how_many_char);


        fclose(fp);

        FILE* fp;
        string huffman = "Huffman.txt";

        for(int i=0;i<huffman.length();i++)
            {
                dir2.push_back(huffman[i]);
            }
        char b[250]="";
        for(int i=0;i<dir2.length();i++)
            {
                b[i] = dir2[i];
            }
        fp = fopen(b,"w+");
        for(int i=0 ; i<how_many_char;i++)
        {

            int a = arr[i].bits.length();
            char c;
            if(arr[i].character != 0)
                {  fprintf(fp,"%c\t%d\t",arr[i].character,arr[i].bits.length())  ;}
            else
            {
                {fprintf(fp,"EOF\t%d\t",arr[i].bits.length());}
            }
            for (int j = 0; arr[i].bits[j] != '\0'; j++)
            {
                fprintf(fp,"%c", arr[i].bits[j]);
            }
            fprintf(fp,"\n");

        }
        fclose(fp);





        FILE* f;
        string zip = "Zip.txt";

        for(int i=0;i<zip.length();i++)
            {
                dir3.push_back(zip[i]);
            }
        char d[250]="";
        for(int i=0;i<dir3.length();i++)
            {
                d[i] = dir3[i];
            }
        f = fopen(d,"wb+");







        FILE* inp;
        inp=fopen(a,"r");

        string bin_d = "";

        int m = all_of_chars;
        while(m--)
        {

            char c;
            c = fgetc(inp);


            if(c!=EOF)
            {
                for(int i=0;i<how_many_char;i++)
                {
                    if( arr[i].character== c )
                    {
                        bin_d += arr[i].bits;
                        break;
                    }
                }
            }

            else
            {
                for(int i=0;i<how_many_char;i++)
                {
                    if( arr[i].character == 0)
                    {
                        bin_d += arr[i].bits;
                        break;
                    }
                }
            }

        }
        fclose(inp);


        int len = bin_d.length();
        int t=0;
        string ss;
        while(len >= 8)
        {
            int bin = 1;
            int a = 0;
            for(int i=0;i<8;i++)
            {
                int g;
                if(bin_d[t]=='1'){g=1;}
                else if(bin_d[t]=='0'){g=0;}
                a += bin*g;
                bin*=2;
                t++;
            }
            char y = a;

            fprintf(f,"%c",y);
            len-=8;
        }
        int bin=1;
        int a =0;
        for(int i=0;i<len;i++)
        {
            int g;
            if(bin_d[t]=='1'){g=1;}
            else if(bin_d[t]=='0'){g=0;}
            a += bin*g;
            bin*=2;
            t++;

        }
        if(len!=0)
        {
            char y = a;
            fprintf(f,"%c",y);
        }
        fclose(f);
    }
    return 0;
}
