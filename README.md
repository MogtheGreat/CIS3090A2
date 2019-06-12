# CIS3090A2
Guelph CIS 3090 Parallel Programming Assignment Two

<p>Uses Message Passing Interface (mpi) library for parallelism optimization. Process 0 gets the input from user and encrypts. Then it divides the work amongst all the other processes and decrypts it. Number of processes in program determined at execution time by the user.</p>

<p>Run program by typing in: mpiexec -n # ./a2</p>
<ul>
	<li>mpiexec = Runs an MPI program.</li>
	<li>-n = Specify the number of processes to use</li>
	<li># = the number of processes to use.</li>
	<li>./a2 = the program being run.</li>
</ul>

<h3>Note</h3>
<p>Program may not run on Windows since the program requires access to the dictionary under: /usr/share/dict/words. Program does work on Ubuntu and Mac's OS X.</p>