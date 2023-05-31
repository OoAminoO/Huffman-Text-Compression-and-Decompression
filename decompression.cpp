#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

char buff_h[100000];
bool bin_buf[1000000];
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

        // Stores the minimum value, and removes it from heap
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
    string directory, zip;
    zip = "Zip.txt";
    cout << "Enter directory of Zip.txt file :" << endl;
    getline(cin,directory);
    directory.push_back('\\');
    string dir2 = directory;
    string dir3 = directory;
    for(int i=0;i<zip.length();i++)
    {
        directory.push_back(zip[i]);
    }
    char a[250]="";
    for(int i=0;i<directory.length();i++)
    {
        a[i] = directory[i];
    }

    FILE* fp;
    fp = fopen(a,"rb");
    if(fp==NULL)
    {
        cout << "unable to read the file" << endl;
        return 0;
    }

    else
    {

        cout << "File was read" << endl;
        fclose(fp);

        int buf_count = 0;
        ifstream f(directory.c_str(), ios::binary);
        char c;
        int j = 0;
        while (f.get(c))
        {
            for(int i = 0; i < 8; i++)
            {
                buf_count += 1;
                bool tmp = ((c >> i) & 1);
                bin_buf[j++] = tmp;
            }

        }
        





        string huffman = "Huffman.txt";

        cout << "Enter directory of Huffman.txt file :" << endl;
        getline(cin,dir2);
        dir2.push_back('\\');

        for(int i=0;i<huffman.length();i++)
        {
            dir2.push_back(huffman[i]);
        }
        char b[250]="";
        for(int i=0;i<dir2.length();i++)
        {
            b[i] = dir2[i];
        }

        FILE* fp;
        fp = fopen(b,"rb");

        if(fp==NULL)
        {
            cout << "unable to read the file" << endl;
            return 0;
        }
        else
        {
            cout << "File was read" << endl;
            fread(buff_h,sizeof(buff_h),1,fp);
            int t=0;
            int char_count=0;
            int how_many_char = 0;
            while(char_count<strlen(buff_h))
            {
                string s="";
                string st = "";
                node n;
                if(buff_h[char_count]=='E' && buff_h[char_count+1]=='O' && buff_h[char_count+2]=='F')
                {
                    how_many_char++;
                    n.character = 0;
                    char_count += 4;

                }

                else if(buff_h[char_count]=='\r')
                {
                    how_many_char++;
                    n.character = '\n';
                    char_count+=3;
                }
                else
                {
                    how_many_char++;
                    n.character=buff_h[char_count];
                    char_count+=2;
                }

                while(buff_h[char_count]!='\t')
                {
                    s+=buff_h[char_count];
                    char_count++;
                }

                if(n.character == 0)
                {
                    n.counter = 0;
                }

                char_count+=1;  //Going to the binary number coming after the tab

                while(buff_h[char_count]=='0' || buff_h[char_count]=='1')
                {
                    st = st+buff_h[char_count];
                    char_count++;
                }
                n.bits = st;
                char_count+=2;
                arr[t++] = n;
            }
            fclose(fp);



            string input = "input.txt";
            for(int i=0;i<input.length();i++)
            {
                dir3.push_back(input[i]);
            }
            char c[250]="";
            for(int i=0;i<dir3.length();i++)
            {
                c[i] = dir3[i];
            }

            FILE* fp;
            fp = fopen(c,"w+");
            int cc = 0;
            int o = how_many_char;
            int ww = 0;
            while(1)
            {

                char p[10]="";
                for(int i=0;i<how_many_char;i++)
                {
                    int j=0;
                    int u = cc;
                    for(j;j<arr[i].bits.length();j++)
                    {
                        bool r;
                        if(arr[i].bits[j] == '0')
                            {r=0;}
                        else
                            {r=1;}
                        if(r!=bin_buf[u++])
                        {
                            break;
                        }
                    }


                    if(j==arr[i].bits.length())
                    {
                        if(arr[i].character == 0)
                        {
                            exit(1);
                        }
                        fprintf(fp,"%c",arr[i].character);
                        cc+=arr[i].bits.length();
                        break;
                    }
                }
            }
            fclose(fp);

        }


    }
    return 0;
}
