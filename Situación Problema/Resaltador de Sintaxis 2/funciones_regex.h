#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <string>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <regex>

using namespace std;

// Ayuda a llenar correctamente el vector de Palabras
bool isdelimitador (char letra) {
    char delimitadores[] = { '(', ')', '[', ']', '{', '}', '<', '>', ',', ';', '+', '-', '*', '%', '/', '\n', ' ', '\t' };
    for(int i = 0; i < 18; i++){
        if(letra == delimitadores[i]){
            return true;
        } 
    }
    return false;
    
}


//Se necesita saber lo de saltos de linea y espacios. Ya que en nuestro vectorPalabras los tenemos guardado.
bool isSalto(string palabra){
    if(palabra == "\n"){
		return true;
	}
	return false;
}

bool isEspacio(string palabra){
    if(palabra == " "){
		return true;
	}
	return false;
}

bool isTab(string palabra){
    if(palabra == "\t"){
		return true;
	}
	return false;
}

bool isInclude(string palabra){
    regex reg("#include.*");
    if (regex_match(palabra, reg)){
		return true;
	}
	return false;
}

bool isFromLanguage(string palabra){
    regex reg("push_back|string|using|namespace|asm|double|new|switch|auto|else|operator|template|break|enum|private|this|case|extern|protected|throw|catch|float|public|trychar|for|register|typedef|class|friend|return|union|const|goto|short|unsigned|continue|if|signed|virtual|default|inline|sizeof|void|delete|int|static|volatile|do|long|struct|while|cout|cin|true|false|char|void|bool|null|printf|scanf|delete|endl");
    if (regex_match(palabra, reg)){
		return true;
	}
	return false;
}

bool isComment(string palabra){
    regex reg("[/][/][ a-zA-Z0-9]*[.,_;()]*");
    if (regex_match(palabra, reg)){
		return true;
	}
	return false;
}

bool isOperador(string palabra){
    regex reg("[+]|[-]|[!]|[=]|[*]|[/]|[<]|[>]|[%]|[&]");
    if (regex_match(palabra, reg)){
		return true;
	}
	return false;
}

bool isCadena(string palabra){
    regex reg("[\"][ a-zA-Z0-9_;,.!]*[\"]");
    if (regex_match(palabra, reg)){
		return true;
	}
	return false;
}

bool isNumero(string palabra){
    regex reg("([0-9]+)|([0-9]+[.][0-9]+)");
    if (regex_match(palabra, reg)){
		return true;
	}
	return false;
}

bool isVariable(string palabra){
    regex reg("[a-zA-Z_]+[a-zA-Z_0-9]*");
    if (regex_match(palabra, reg)){
		return true;
	}
	return false;
}

bool isEncierra(string palabra){
    if(palabra == "(" || palabra == ")" || palabra == "[" || palabra == "]" || palabra == "{" || palabra == "}"){
        return true;
    }
}

bool isPuntuacion(string palabra){
    regex reg(";|,|:");
	if (regex_match(palabra, reg)) {
		return true;
	}
	return false;
}