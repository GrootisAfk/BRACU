%option noyywrap

%{
#include<bits/stdc++.h>
using namespace std;

ofstream yyoutlog; //output filestream for log file

string loglist = ""; //list of tokens along with line numbers

// define necessary c++ variables and functions here (if any)
int lines = 1;

%}

/* Regular Definitions */

delim	 [ \t\v\r]

/* write regular expressions for whitespace and newline */
ws		 

newline  

letter_	 [A-Za-z_]
digit	 [0-9]

/* write regular expressions for id, float and integers */
id		 


%%

{ws} { /* ignore whitespace */ }

{newline} {
			/* do necessary bookkeeping (line number tracking etc.) */
		}

{id} {
			loglist="Line no "+to_string(lines)+": Token <ID> Lexeme "+yytext+" found"+"\n"+"\n";
			yyoutlog<<loglist;
		}

if {
			loglist="Line no "+to_string(lines)+": Token <IF> Lexeme "+yytext+" found"+"\n"+"\n";
			yyoutlog<<loglist;
		}

while {
			loglist="Line no "+to_string(lines)+": Token <WHILE> Lexeme "+yytext+" found"+"\n"+"\n";
			yyoutlog<<loglist;
		}


"+"|"-" { /* to match two same operators use | */
			loglist="Line no "+to_string(lines)+": Token <ADDOP> Lexeme "+yytext+" found"+"\n"+"\n";
			yyoutlog<<loglist;
		}


%%

int main(int argc, char *argv[])
{

	if(argc != 2) //check if file name is given
	{
		cout<<"Please input file name"<<endl;
		return 0;
	}

	yyin = fopen(argv[1], "r"); //the file to be read must be assigned to yyin

	yyoutlog.open("my_log.txt", ios::trunc); // remember to rename the log file as mentioned in the spec
	
	if(yyin == NULL) // file does not exist
	{
		// print error message and exit
	}
	
	yylex(); // start reading the input file in a loop
	
	//print total number of lines found in the input file
	
	yyoutlog.close();  // close the log file
	
	fclose(yyin); // close the input file
}
