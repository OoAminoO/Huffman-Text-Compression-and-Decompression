## Overview
This project contains a text compression and decompression program using the powerful Huffman coding algorithm.

**"compression.cpp"** is used to compress the **"input.txt"** file, resulting in two output files:
- **"Zip.txt"** : Contains the final compressed data achieved through Huffman encoding.
- **"Huffman.txt"** : Presents the bit sequence assigned to each character, achieved through the construction of the Huffman tree.

**"decompression.cpp"** retrieves the original **"input.txt"** file by utilizing the compressed file (**"Zip.txt"**) and the Huffman tree (**"Huffman.txt"**).


## Text Files and Compression Ratio
The sample **"input.txt"** file is not just an ordinary text! It contains the lyrical medley of 10 beloved songs that hold a special place in my heart ❤️, including ***Ending*** by Isak Danielson, ***Arcade*** by Duncan Laurence, ***Long Long Time*** by Linda Ronstadt, ***My Immortal*** by Evanescence, ***Someone Like You (Live from the BRIT Awards)*** by Adele, ***Stuck*** by Imagine Dragons, ***Sweet Creature*** by Harry Styles, ***The Night We Met*** by Lord Huron, ***The Scientist*** by Coldplay, and ***True Colours*** by Tom Odell.

For this specific input file :
- The **"input.txt"** size is **12.1 KB**.
- The combined size of **"Huffman.txt"** (0.87 KB) and **"Zip.txt"** (6.69 KB) is only **7.56 KB**.
- The compression ratio would be about **1.6x**.

This impressive compression ratio of about **1.6x** demonstrates the efficiency of the algorithm, even for this relatively small file.


## Running the Program
1. Compile the **"compression.cpp"** file using <code>g++ compression.cpp -o compression</code>.
2. Execute the compiled file with <code>./compression</code> on Linux or <code>compression.exe</code> on Windows.
3. Enter the directory path of the **"input.txt"** file to compress (something like <code>C:\Desktop\Huffman</code>).
4. The program will generate **"Zip.txt"** (compressed data) and **"Huffman.txt"** (Huffman tree representation).
5. To decompress, compile **"decompression.cpp"** with <code>g++ decompression.cpp -o decompression</code>.
6. Run the compiled file with <code>./decompression</code> on Linux or <code>decompression.exe</code> on Windows.
7. Enter the directory path of **"Zip.txt"** and **"Huffman.txt"**.
8. The program will reconstruct the original input file and save the decompressed output in **"input.txt"**.
