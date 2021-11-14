#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>  // fork() & wait()
#include <unistd.h>     // fork(), execvp()
#include <cstdlib>      // exit()
#include <wait.h>       // wait()
#include <vector>       // vector<>     // string
#include <bits/stdc++.h>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <stdlib.h>
#include <bits/stdc++.h> 
using namespace std;


vector<string> makeWord(string word, vector<string> command, string progname) {
    if (word != "") {
        if (isspace(word[0])) {
            word = word.erase(0, 1);
        }

        if ((word == "" || word == " ") == false) {
            if ((word != ")") & (word != "(")) {
                command.push_back(word);
                // cout << word<<"\n";
            }
        }
        word = "";
    }
    if ((word == "(") && (command.size() != 1)) {
        cerr << "Error in " << progname << "second word should be \"(\"\n";
        exit(0);
    }
    return command;
}


bool execute(vector<string> command) {
    // Convert vector of C++ strings to an array of C strings for exectp():
    vector<char*> argv;                // vector of C string pointers
    for (auto& v : command)             // for each C++ string:
        argv.push_back(v.data());       //    add address of C-string inside it
    argv.push_back(nullptr);            // argv ends with a null pointer

    // Duplicate ourself: -1:error, 0:child, >0:parent
    const auto pid = fork();            // step #1: copy ourself
    if (pid < 0)
        return false;                   // fork failure?
    if (pid == 0) {                     // child?
        execvp(argv[0], argv.data());   // step #2: replace child with new prog
        exit(0xff);                     // only got here if execvp() failed.
    }
    int status;
    wait(&status);                      // step #3: wait for child to finish
    return status != 0xff00;            // true iff we succeeded
}



vector<string> getcommand(bool v, int m, string s, string progName, vector<string>imput) {
    string word;
    vector<string> t;
    bool rpar = false;
    bool lpar = false;
    bool backcheck = false;
    for (string line : imput) {
        vector <string> command;
        for (char c : line) {
            if (backcheck == true) {
                word = word + c;
                backcheck = false;
                c = '\0';
            }
            else if (isspace(c)) {
                command = makeWord(word, command, progName);
                word = "";
            }
            else if (c == '\\') {
                backcheck = true;
            }
            else if (c == '\0') {
                continue;
            }
            else {
                bool added = false;
                for (char escaped : s) {
                    if (escaped == c) {
                        if (c == '(') {
                            if ((lpar == true)) {
                                cerr << "Error in " << progName << " Too many \"(\" Can only have 1 unescaped left paren\n";
                                exit(8);
                            }
                            else {
                                lpar = true;
                            }
                        }

                        if (c == ')') {
                            if ((rpar == true)) {
                                cerr << "Error in " << progName << " Too many \")\" Can only have 1 unescaped right paren\n";
                                exit(8);
                            }
                            else {
                                rpar = true;
                            }
                        }

                        command = makeWord(word, command, progName);
                        word = "";
                        word = word + c;
                        command = makeWord(word, command, progName);
                        word = "";
                        added = true;
                        break;
                    }
                }
                if (added == false) {
                    word = word + c;
                }
            }
        }

        command = makeWord(word, command, progName);
        if (v == true && command.size() > 0) {
            cout << "Executing:\n";
            for (long unsigned int i = 0; i < command.size(); i++) {
                cout << i << ": " << "\"" << command[i] << "\"" << "\n";
            }
        }
        if (command.size() > 1 && line.back() != ')') {
            cerr << "Error in " << progName << "last word should be \")\"\n";
            exit(3);
        }
        bool argchk = false;
        int count = 0;
        long unsigned int te = m + 1;
        for (long unsigned int i = 0; i < command.size(); i++) {
            if (command[i] == "(") {
                argchk = true;
            }
            if (argchk == true) {
                count++;
            }
            if (command.size() > te) {
                cerr << line << "Error in " << progName << " Too many arguments. Must contain 0-" << m << " arguments\n";
                exit(1);
            }
        }
        return command;
        //        bool checker = true;
        bool  checker = execute(command);

        if (checker == true) {
            command.clear();
            word = "";
            lpar = false;
            rpar = false;
        }
        else {
            cerr << "Error in " << progName << " the command " << line << " did not work\n";
            exit(4);
        }
    }
	return t;
}


void command(vector<string> words, int start, int end, bool v, int maxArg  ) {
	if(words.size() > 3){
		if(start >end){
			if(v){

	}
	}
			
	}
	if(maxArg > 4){
	 	maxArg ++; 
}
}

class Tempfile {
public:
    int fcount = 0;
    Tempfile() { close(mkstemp(name)); }
    ~Tempfile() { remove(name); }
    operator string() const { return name; }
private:
    char name[18] = "./tXXXXXX";
};

int main(int argc, char* argv[]) {
    string val[5] = { "F","F","F","F","F" };
    int opt;
    int maxArgs = INT_MAX - 1;
    bool v = false;
    string s = ")(";
    while ((opt = getopt(argc, argv, "m:s:v")) != -1) {
        switch (opt) {
        case 'm':
            if (val[0] == "T") {
                cerr << "Error in " << argv[0] << "the same option" << " m " << optarg << " was given more than 1 time\n";
                exit(5);
            }
            val[0] = "T";
            val[1] = optarg;
            maxArgs = atoi(optarg);
            if (maxArgs > 100 || maxArgs < 1) {
                cerr << "Error in " << argv[0] << " " << maxArgs << " is not in the range 1-100\n";
                exit(6);
            }
            break;
        case 's':
            if (val[2] == "T") {
                cerr << "Error in " << argv[0] << "the same option" << " s " << optarg << " was given more than 1 time\n";
                exit(5);
            }
            val[2] = "T";
            val[3] = optarg;
            s = optarg;
            break;
        case 'v':
            val[4] = "T";
            v = true;
            break;
        default: /* '?' */
            cerr << "Error in " << argv[0] << ":" << argv << " is not a valid option\n";
            exit(1);
        }
    }
    string line = "";
    string filestr = "";
    string myText = "";
    vector<string> args;
    int count = 1;
    for (int i = 1; i < argc; ++i) {
        string tempstr = argv[i];
        if (tempstr.front() == '-') {
            count++;
        }
    }
    if (argc == count) {
        while (cin) {
            getline(cin, line);
            args.push_back(line);

        }
    }
    else {



        for (int j = 1; j < argc; ++j) {
            string tempstr = argv[j];
            if (tempstr.front() == '-') {
                continue;
            }
            else {



                ifstream f;
                f.open(tempstr, ios::in);
                if (!f) {
                    cerr << "Error in " << argv[0] << ": No file named " << tempstr << " found\n";
                    exit(7);
                }
                else {
                    //	cout << "This worked file: " << tempstr;
                    while (!f.eof()) {
                        getline(f, filestr);
                        args.push_back(filestr);
                    }
                }
            }
        }
    }
    vector <string> words = getcommand(v, maxArgs, s, argv[0], args);
    command(words, 0, words.size(), v, maxArgs);
       
}

