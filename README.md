# cplusplus-rot-cipher  
C++ Class that is used to Encrypt, Decrypt, and Detect ROT Ciphers  

Included methods - encrypt(int rot, string), decrypt(int rot, string), detect(string, mode), console_test()  

detect() has 3 modes - default is mode 0  
0 - tests if first 3 words in text are a rot cipher using a dictionary of top 3000 english words.  
1 - tests 5 words in the text  
2 - tests 7 words in the text  

console_test() - gets ROT1-25 of text inputed from user into console  
