# include <stdio.h>
# include <string.h>
# include <iostream>
# include <boost/algorithm/string.hpp>
# include "node.h"

# define MAX 20
void infixtoprefix(vector<string>& infix, vector<string>& prefix);
void reverse(vector<string> arr);
/*char pop();
void push(char symbol);*/
int isOperator(string symbol);
int prcd(string symbol);
string parenthesize(vector<string> &arr);
vector<string> withUnary(vector<string> symbols);
