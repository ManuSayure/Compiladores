
#include <stdio.h>

enum cat
{
	pt = 1, ptvg, eof, se, entao, senao, fim, para, ate,
	repita, id, atr, opl, nao, verd, falso, opa, opm,
	abpar, fepar, cten
};

typedef struct token
{
	enum cat categ;
	char lex[10];
	int posicao[1][1];

}Token;

Token tk;
Token next();
void error(char mensagem,Token tk);


void fpgm();
void flsent();
void flsentr();
void fsent();
void fsenao();
void fatr();
void fexpr();
void feb();
void febr();
void ftb();
void fea();
void fear();
void fta();
void fatr();
void ftar();
void ffa();


int main(){

}

Token next()
{
	Token tk;

    return tk;
}

void error(char mensagem, Token tk){
    puts(mensagem);
}

void fpgm()
{
     tk = next();
     flsent();
     if (tk.categ == pt)
     {
     	next();
        if(tk.categ == eof)
        {
        	return;
        }
        else
        {
        	error("'EOF' ESPERADO", tk);
        }
     }
     else
     {
        	error("'.' ESPERADO",tk);
     }
}

void flsent()
{
	fsent();
	flsentr();
}

void flsentr()
{

	if(tk.categ == ptvg)
	{
		fsent();
		flsentr();
	}

}

void fsent()
{
	if (tk.categ == se)
	{
		next();
		feb();
		if(tk.categ == entao)
		{
			next();
			flsent();
			fsenao();
		}
		else
		{
			error("'entao' esperado", tk);
		}

	}
	if (tk.categ == para)
	{
		next();
		fatr();
		if(tk.categ == ate)
		{
			next();
			fea();
			if(tk.categ == repita)
			{
				flsent();
				if(tk.categ == fim)
				{
					return;
				}
				else
				{
					error("'fim' esperado", tk);
				}

			}
			else
			{
				error("'repita' esperado", tk);
			}


		}
		else
		{
			error("'ate' esperado", tk);
		}

	}
	else
	{
		fatr();
	}

}

void fsenao()
{
	if(tk.categ == fim)
	{
		next();
		return;

	}
	else if(tk.categ == senao)
	{
		next();
		flsent();
		if(tk.categ == fim)
		{
			next();
			return;
		}
		else
		{
			error("'fim' esperado", tk);
		}


	}
	else
	{
		error("'fim' ou 'senao' esperado", tk);
	}

}

void fexpr(){
	feb();
}

void feb()
{
	ftb();
	febr();
}

void febr()
{
	if(tk.categ == opl)
	{
        next();
        ftb();
        febr();
	}
	else
	{
		error("'opl' esperado", tk);

	}

}

void ftb()
{
	if(tk.categ == nao){
		next();
		ftb();

	}
	else if(tk.categ == verd)
	{
		next();
		return;

	}
	else if(tk.categ == falso)
	{
		next();
		return;
	}
	else
	{
		fea();

	}

}

void fea()
{
	fta();
	fear();
}

void fear()
{
	if(tk.categ == opa)
	{
		next();
		fta();
		fear();
	}
	else
	{
		error("'opa' esperado", tk);
	}

}

void fta()
{
	ffa();
	ftar();
}

void ftar(){
	if(tk.categ == opm){
		next();
		ffa();
		ftar();
	}
	else
	{
		error("'opm' esperado", tk);
	}
}

void fatr()
{
	if(tk.categ == id)
	{
         next();
         if(tk.categ == atr)
         {
         	next();
         	fexpr();
         }
         else
         {
         	error("'=' esperado", tk);

         }
	}
	else
	{
		error("'id' esperado", tk);

	}

}

void ffa()
{
	if(tk.categ == abpar)
	{
		next();
		fexpr();
		if(tk.categ == fepar)
		{
			next();
			return;
		}
		else
		{
			error("'fepar' esperado", tk);
		}
	}
	else if(tk.categ == id)
	{
		next();
		return;
	}
	else if(tk.categ == cten)
	{
		next();
		return;
	}

}
