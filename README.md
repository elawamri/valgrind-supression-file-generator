## Motivation 

I was looking for memory leaks in a complicated project using Valgrind. I encountered a problem where Valgrind detected many issues in the system libraries, like the C library that comes pre-installed with MacOS. These issues are difficult to fix, but I didn't want to see these errors because there were so many of them! 

Valgrind has a way to ignore specific errors by using a list of errors to suppress. The default suppression file is created when the system is built by running the "./configure" script, hoever it hansn't enough supressions.

So basically, this simple tool takes the Valgrind log file and extracts the suppression statements from it, saving them in a .supp file, in order to be used through valgrind command later.

## How to use ? 

1. Run Valgrind command to generate a report that includes statements to suppress certain errors, Use the following command :

`valgrind --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --log-file=leak-report.log ./your-program`

This will create a file "leak-report.log" with all the suppression statements.

2. Take the "leak-report.log" file and use the tool "valgrind-automatic-suppress" to extract the suppression file from it, you can directly use the the binary from bin directory (***it was built statically you don't need QT***)

`./valgrind-automatic-supress leak-report.log supp-file.supp`

3. Now, take the "supp-file.supp" and run Valgrind again after reviewing the suppressed errors. Make sure that these errors are related to third-party code. Use the following command:

`valgrind --leak-check=full --show-reachable=yes --error-limit=no --suppressions=./supp-file.supp ./your-program`

This will run Valgrind with the suppression file and check for memory leaks in your program.
