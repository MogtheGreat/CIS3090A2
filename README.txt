README.txt
Michael Oranski
0557701

Compile
Use make command in the command line to compile the program.

run:
mpiexec -n # ./a2
where # equals the number of unique char entered into the program.


Timing information
Timing is done by using the time command in the command line. This was approved by the professor on Oct.26 in class.

The size the alphabet becomes too large to decrypt is at 8 unique char if looking at the system time. 9 unique char if looking at real and user time. Please note that for 9 unique chars, requires only single words. 

Timing test was done on student laptop not on server.

TIMING DATA

3 unique chars
'the'
real	0m3.082s
user	0m1.086s
sys	0m3.062s

'and'
real	0m5.765s
user	0m2.281s
sys	0m7.242s

4 unique chars
'blood'
real	0m3.158s
user	0m1.533s
sys	0m4.840s

'find'
real	0m6.990s
user	0m3.753s
sys	0m14.084s


5 unique chars
'is the'
real	0m5.432s
user	0m3.860s
sys	0m13.139s
*apprently despite the use of regular expression ts, hie, ti, sh are in the dictionary (WTF)

'the end'
real	0m5.280s
user	0m3.575s
sys	0m13.022s

'finds'
real	0m4.452s
user	0m2.821s
sys	0m10.540s

6 unique chars
'the and'
real	0m6.488s
user	0m6.224s
sys	0m14.526s

'the time is'
real	0m8.282s
user	0m8.875s
sys	0m18.647s

7 unique chars
'the blood'
real	0m17.912s
user	0m18.691s
sys	0m45.036s

8 unique chars
'the blood a'
real	3m20.100s
user	6m9.735s
sys	6m31.896s

'abdomens'
real	0m55.987s
user	0m50.227s
sys	2m25.231s

'captions'
real	0m56.088s
user	0m51.259s
sys	2m28.629s

9 unique chars
'machinery'
real	8m31.852s
user	10m31.043s
sys	20m46.922s