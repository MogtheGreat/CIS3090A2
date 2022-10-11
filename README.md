<h1>Parallel Programming Assignment: Password Bruteforce</h1>
<h2>Intro</h2>
<div>
	<p>Uses Message Passing Interface (mpi) library for parallelism optimization. Process 0 gets a single word from the user and encrypts the word by scrambling it. Once encrypted the other processes will attempt to decrypt the word by guessing it. All guesses are verified through the os dictionary file. The number of processes in the program are determined at execution time by the user.</p>
</div>
<h2>Requirements</h2>
<div>
	<ul>
		<li>OS: Unix (Ubuntu preferred)</li>
		<li>c compiler (gcc prefered)</li>
		<li>mpi (sudo apt install mpich)</li>
	</ul>
</div>
<h2>To Run</h2>
<div>
	<p>To compile both program, move into the main directory where the source code is located and type make. The makefile should compile both programs with no warnings. </p>
	<p>Run program by typing in: mpiexec -n # ./a2</p>
	<ul>
		<li>mpiexec = Runs an MPI program.</li>
		<li>-n = Specify the number of processes to use</li>
		<li># = the number of processes to use.</li>
		<li>./a2 = the program being run.</li>
	</ul>
	<p>To run the program with preset command line arguements type in:</p>
	<ul>
		<li><code>make run</code> for <code></code></li>
		<li><code>make run3</code> for <code>mpiexec -n 4 ./a2</code></li>
		<li><code>make run4</code> for <code>mpiexec -n 5 ./a2</code>
	</ul>
</div>
<h2>To Clean</h2>
<div>
	<p>To clean up the project, move into the main directory and type make clean to clean up the entire project.</p>
</div>
<h2>Note</h2>
<div>
	<p>Program may not run on Windows since the program requires access to the dictionary under: /usr/share/dict/words. Program does work on Ubuntu and Mac's OS X.</p>
</div>
