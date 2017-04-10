# DES
This is an implementation of Simple Data Encryption Standard program for the cryptography course.</br>
<b>Important</b>:<a href="https://en.wikipedia.org/wiki/Data_Encryption_Standard">DES is now considered to be insecure.</a></br>
This implementation also has a logger which prints to a log file the time of each event.</br>
The  encryption is now being done by argument parsing.</br>
e.g.</br>
```bash
-e -k -b 0001001100110100010101110111100110011011101111001101111111110001 -m -b  0000000100100011010001010110011110001001101010111100110111101111 -p -l
```
Where -e is encrypt, -k is key followed by it, same way the message -m, -b declares that the next argument is on bit format, -p is print the info and -l is write a log file.</br>
Type -help for help with the arguments.</br>
<b>Example:</b></br>
  Key
```bash
0001001100110100010101110111100110011011101111001101111111110001
```
  Message
```bash
0000000100100011010001010110011110001001101010111100110111101111
```
  Cyphertext
```bash
1000010111101000000100110101010000001111000010101011010000000101
```
<b>Image on action</b></br>
<img src="http://i.imgur.com/wc4wm6g.png" alt="" /></a>
<b>Developer advice</b></br>
  Do not upload unnecessary files.</br>
<b>Future request</b></br>
  File encryption aknowledges bit format too.</br>

