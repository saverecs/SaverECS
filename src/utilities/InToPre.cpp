# include "InToPre.h"
# include "node.h"
# include <stdio.h>
# include <string.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <iterator>
#include<bits/stdc++.h>
#include <boost/tokenizer.hpp>

# define MAX 20
int top=-1;
stack<string> charstack;

using namespace std;

//--------------------------------------------------------
void infixtoprefix(vector<string>& infix, vector<string>& prefix) {
/*	for(int i=0;i<infix.size();i++){
		//cout<<"size is: "<<infix.size()<<" "<<infix[i]<<endl;
	}*/
	int i,j=0;
	string symbol;
	charstack.push("#");
	infix = withUnary(infix);
	std::reverse(begin(infix),end(infix));
	for (i=0;i<infix.size();i++) {
		symbol=infix[i];
		//when an operand :
		if (isOperator(symbol)==0) {
			prefix[j]=symbol;
			j++;
		}
		//when operator:
		else {
			//if its a ')'
			if (symbol==")") {
				charstack.push(symbol);
			} //if its a '('
			else if(symbol == "(") {
				//pop and add to the post fix string till it gets a ')'
				while (charstack.top()!=")") {
					prefix[j]=charstack.top();
					charstack.pop();
					j++;
				}
				charstack.pop();
			}//if anything other than parentheses
			else {
				if (prcd(charstack.top())<=prcd(symbol)) {
					charstack.push(symbol);
				} else {
					while(prcd(charstack.top())>=prcd(symbol)) {
						prefix[j]=charstack.top();
						charstack.pop();
						j++;
					}
					charstack.push(symbol);
				}
				//end for else
			}
		}
		//end for else
	}
	//end for for
	while (charstack.top()!="#") {
		prefix[j]=charstack.top();
		charstack.pop();
		j++;
	}
}////--------------------------------------------------------
string parenthesize(vector<string>& arr){
	int i;
	stack<node> st;
	for(i=0;i<arr.size();i++){
		string c= arr[i];
		if(!c.empty()){
//			cout<<arr.size()<<" parsing for parenthesizing :"<<c<<" this"<<std::endl;
		if(isOperator(c)==1){
			node op(c);
			vector<node> operands;
			operands.push_back(st.top());
			st.pop();
			operands.push_back(st.top());
			st.pop();
			op.append(operands);
			st.push(op);
//			cout<<"test binary "<<op.to_prefix()<<endl;
		}
		else if(isOperator(c)==2){
			node op;
			if(c=="um"){
				op.addVal("-");
			}
			if(c=="up"){
				op.addVal("-");
			}
//			node op(c);
			vector<node> operands;
			op.append(st.top());
			st.pop();
			op.append(operands);
			st.push(op);
//			cout<<"test unary "<<op.to_prefix()<<endl;
		}
		else {
//			node n=new node(c);
			node n(c);
			st.push(n);
//			cout<<"test operands "<<n.to_prefix()<<endl;
		}
		}
	}
	node root=st.top();
//	cout<<"root.to_infix() = "<<root.to_infix()<<std::endl;
	st.pop();
	return root.to_prefix();
}////--------------------------------------------------------
vector<string> withUnary(vector<string> symbols){
	int flag=0;
	list<int> indices;
	//cout<<"for->"<<symbols[0]<<endl;
	if((prcd(symbols[0])!=1) && isOperator(symbols[0])){
		//cout<<"for->"<<symbols[0]<<endl;
		//cout<<"unary->if first element operator but not brackets"<<endl;
		flag=2;
		indices.push_back(0);
		//cout<<"unary found at"<<0<<endl;
		flag=0;
	}
	else if(symbols[0]=="("){
			//cout<<"for->"<<symbols[0]<<endl;
			//cout<<"unary->if brackets"<<endl;
			flag=1;
	}
	//cout<<flag<<" at "<<symbols[0]<<endl;
	for(int i=1;i<symbols.size();i++){
		//cout<<"for->"<<symbols[i]<<endl;
		if(prcd(symbols[i])!=1 && isOperator(symbols[i])){
			//cout<<"unary->if operator not brackets"<<endl;
			flag++;
		}
		else if(!isOperator(symbols[i])){
			//cout<<"unary->if not operator reset"<<endl;
					flag=0;
		}
		else if(symbols[i]=="("){
			//cout<<"unary->if brackets"<<endl;
					flag=1;
		}
		if(flag==2){
			indices.push_back(i);
			//cout<<"unary found at"<<i<<endl;
			flag=0;
		}
	/*if(isOperator(symbols[i])&&( i==0 || isOperator(symbols[i-1]) || symbols[i-1]='('))
		return true;
	}*/
		//cout<<flag<<" at "<<symbols[i]<<endl;
	}
	for(int i:indices){
		if(symbols[i]=="+"){
			//cout<<"replacing with up at"<<i<<endl;
			symbols[i]="up";
		}
		else if(symbols[i]=="-"){
			//cout<<"replacing with um at"<<i<<endl;
			symbols[i]="um";
		}
	}
	return symbols;
}
int prcd(string symbol) // returns the value that helps in the precedence
{
//	//cout<<"entering prcd with: " <<symbol<<std::endl;

	if((symbol=="+")||(symbol=="-")){
		return 2;
	}
	else if((symbol=="*")||(symbol=="/")){
		return 4;
	}
	else if((symbol=="$")||(symbol=="^")||(symbol=="up")||(symbol=="um")){
		return 6;
	}
	else if((symbol=="(")||(symbol==")")||(symbol=="#")){
		return 1;
}
}
//-------------------------------------------------
int isOperator(string symbol) {
	//binary operators
	if((symbol=="+")||(symbol=="-")||(symbol=="*")||(symbol=="/")||(symbol=="^")||(symbol=="$")||(symbol=="&")||(symbol=="(")||(symbol==")")){
//			cout<<"an operator "<<symbol<<std::endl;
			return 1;
	}//unary operators
	else if((symbol=="up")||(symbol=="um")){
//			cout<<"an operator "<<symbol<<std::endl;
			return 2;
	}//operands
	else{
//			cout<<"not an operator "<<symbol<<std::endl;
			return 0;
// 			returns 0 if the symbol is other than given above
	}
}




