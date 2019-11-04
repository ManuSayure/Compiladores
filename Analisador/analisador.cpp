#include <iostream>
#include <bits/stdc++.h>

#define MAX_STRING 100

using namespace std;

enum Category {
    PtVg, Se, Entao, Senao, Fim, Enquanto, Eof, Repita,
    Id,Atr,Opl,Opa,Ou, E,Verd,Falso,Opm,AbPar,FePar,CteI
};

FILE *file;
class Token{

    private:
        void verif_token(){
            while (strcmp(lexema, "\n") == 0){
                linha++;
                get_next_token();
            }
             if(feof(file)){
                categ = Eof;
                memset(lexema, 0, MAX_STRING);
                return;
            }
            if (strcmp(lexema, "se") == 0){
                categ = Se;
            }else if (strcmp(lexema, "então") == 0){
                categ = Entao;
            }else if (strcmp(lexema, "fim") == 0){
                categ = Fim;
            }else if (strcmp(lexema, ";") == 0){
                categ = PtVg;
            }else if (strcmp(lexema, "enquanto") == 0){
                categ = Enquanto;
            }else if (strcmp(lexema, "repita") == 0){
                categ = Repita;
            }else if (strcmp(lexema, "=") == 0){
                categ = Atr;
            }else if (strcmp(lexema, "opl") == 0){
                categ = Opl;
            }else if (strcmp(lexema, "opm") == 0){
                categ = Opm;
            }else if (strcmp(lexema, "opa") == 0){
                categ = Opa;
            }else if (strcmp(lexema, "(") == 0){
                categ = AbPar;
            }else if (strcmp(lexema, ")") == 0){
                categ = FePar;
            }else if (strcmp(lexema, "não") == 0){
                categ = Nao;
            }else if (strcmp(lexema, "verd") == 0){
                categ = Verd;
            }else if (strcmp(lexema, "falso") == 0){
                categ = Falso;
            }else{
                categ = Id;
            }
        }

        void get_next_token(){
            coluna+=strlen(this->lexema);
            fscanf(file, "%s", this->lexema);
        }
        public:
        Category categ;
        char lexema[MAX_STRING];
        int linha=1, coluna=1;

        void next(){
            get_next_token();
            verif_token();
        }

        Token(){
            strcpy(this->lexema, "");
            get_next_token();
            verif_token();
        }
};

Token *tk;

void fPgm();
void fLSent();
void fLSentr();
void fSent();
void fSCond()
void fEb();
void fEbr();
void fAtr();
void fEa();
void fEar();
void fTa();
void fTar();
void fTb();
void fFa();
void fExpr();
void fPa();

void fPgm(){
    fLSent();
    if(tk->categ == Pt){
        tk->next();
        if(tk->categ == Eof){
            return;
        }else printf("EOF esperado lin:%d col:%d\n",tk->linha, tk->coluna);
    }else printf("'.' esperado lin:%d col:%d\n", tk->linha, tk->coluna);
}

void fLSent(){
    fSent();
    fLSentr();
}

void fLSentr(){
    if(tk->categ == PV){
        tk->next();
        fSent();
        fLSentr();
    }
}
void fSent(){
    if(tk->categ == Se){
        tk->next();
        fSCond();
    }
    else if (tk->categ == Enquanto || tk->categ == Repita){
        tk->next();
        fSiter();
    }
    else if (tk->categ == Id){
        tk->next();
        fSAtr()
    }
    else{
         printf("'se', 'enquanto', 'repita', ou 'id' esperado lin:%d col:%d\n", tk->linha, tk->coluna);
    }
}
void fSCond(){
     if(tk->categ == Se){
            tk->next();
            fSEb();
            if(tk->categ == Entao){
                     tk->next();
                     fLSent();
                     if(tk->categ == Senao){
                            tk->next();
                            fLSent();
                     }
                     if(tk->categ == Fim){
                        tk->next();
                     }
                     else{
                            printf("'fim' esperado lin:%d col:%d\n", tk->linha, tk->coluna);
                     }
            }
            else{
                 printf("'entao' esperado lin:%d col:%d\n", tk->linha, tk->coluna);
            }
     }
}

void fSIter(){
    if(tk->categ == Enquanto){
        tk->next();
        fSEb();
        if(tk->categ == Repita){
            tk->next();
            fLSent();
            if(tk->categ == Fim){
                 tk->next();
            }else{  printf("'fim' esperado lin:%d col:%d\n", tk->linha, tk->coluna);
            }
        }else{printf("'repita' esperado lin:%d col:%d\n", tk->linha, tk->coluna);
        }
    }else{
            tk->next();
            fLSent();
            if(tk->categ == Enquanto){
                tk->next();
                fSEb();
                if(tk->categ == Repita){
                    tk->next();
                    fLSent();
                    if(tk->categ == Fim){
                        tk->next();
                    }else{
                          printf("'fim' esperado lin:%d col:%d\n", tk->linha, tk->coluna);
                    }
                 }
            }else{
                printf("'repita' esperado lin:%d col:%d\n", tk->linha, tk->coluna);
            }
        }
}

void fAtr(){
     if(tk->categ == Id){
        tk->next();
        if (tk->categ == Atr){
            tk->next();
            fExpr();
        }
     }
}
void fExpr(){
    fEb();
}
void fEb(){
    fTb();
    fEbr();
}
void fEbr(){
    if(tk->categ == Ou){
        tk->next();
        fTb();
        fEbr();
    }
}
void fEb(){
    fEa();
    if(tk->categ == Opl){
        tk->next();
        fEa();
    }

}
void fEa(){
    fTa();
    fEa();
}
void fEar(){
    if(tk->categ == Opa){
        tk->next();
        fPa();
        fTar();

    }
}
void fTar(){
   if(tk->categ == Opm){
        tk->next();
        fPa();
        fTar();
}
void fPa(){
   if(tk->categ == AbPar){
        tk->next();
        fExpr();
        if (tk->categ == FePar){
            tk->next();
            return;
        }else printf("')' esperado lin:%d col:%d\n", tk->linha, tk->coluna);
    }else if (    tk->categ == Id
                ||tk->categ == CteI
                ||tk->categ == Verd)
                || tk->categ == Falso{
                tk->next();
        return;
    }else printf("fator aritmético esperado lin:%d col:%d\n", tk->linha, tk->coluna);
}
}
