#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERR 5
#define NOME 40
#define COR 20

typedef struct {
    char nome[NOME], cor[COR];
    int tropas, owner;
} Terr;

void limpa_buffer() { int c; while((c=getchar())!='\n' && c!=EOF); }
int le_int(const char *p, int min, int max){ int x; while(1){ printf("%s",p);
 if(scanf("%d",&x)!=1){limpa_buffer();continue;} limpa_buffer();
 if(x<min||x>max){printf("Valor inválido!\n");continue;} return x;}}
void le_str(const char *p,char *buf,int s){printf("%s",p);fgets(buf,s,stdin);
 size_t ln=strlen(buf); if(ln>0&&buf[ln-1]=='\n')buf[ln-1]='\0';}

void exibe(Terr *t,int n){printf("\n===== MAPA =====\n");
 for(int i=0;i<n;i++)printf("[%d] %-12s | %-7s | Tropas:%2d | Dono:%s\n",
 i+1,t[i].nome,t[i].cor,t[i].tropas,t[i].owner?"Jogador":"Oponente");
 printf("================\n");}

int dado(){return rand()%6+1;}

int batalha(Terr *a, Terr *d){
 if(a->tropas<=0||d->tropas<=0)return 0;
 int atk=dado(),def=dado();
 printf("%s(%d) rolou %d  vs  %s(%d) rolou %d\n",
 a->nome,a->tropas,atk,d->nome,d->tropas,def);
 if(atk>def){
  d->tropas--;
  printf("Atacante venceu! %s agora tem %d tropas\n",d->nome,d->tropas);
  if(d->tropas<=0){ d->owner=a->owner;
   if(a->tropas>1){a->tropas--; d->tropas=1;}
   printf("%s foi conquistado!\n",d->nome); return 1;}
 }else if(atk<def){ a->tropas--; printf("Defensor venceu! %s agora tem %d tropas\n",a->nome,a->tropas);}
 else printf("Empate!\n");
 return 0;
}

/* --- Nível Novato --- */
void novato(){
 Terr t[MAX_TERR];
 for(int i=0;i<MAX_TERR;i++){
  printf("\n--- Território %d ---\n",i+1);
  le_str("Nome: ",t[i].nome,NOME);
  le_str("Cor do exército: ",t[i].cor,COR);
  t[i].tropas=le_int("Tropas: ",0,1000);
  t[i].owner=0;
 }
 exibe(t,MAX_TERR);
}

/* --- Nível Aventureiro --- */
void aventureiro(){
 Terr *t=calloc(MAX_TERR,sizeof(Terr));
 for(int i=0;i<MAX_TERR;i++){
  le_str("Nome: ",t[i].nome,NOME);
  le_str("Cor: ",t[i].cor,COR);
  t[i].tropas=le_int("Tropas: ",0,1000);
  t[i].owner=rand()%2;
 }
 int op;
 while(1){
  exibe(t,MAX_TERR);
  op=le_int("1-Atacar | 0-Sair: ",0,1);
  if(!op)break;
  int a=le_int("Atacante(1-5): ",1,MAX_TERR)-1;
  int d=le_int("Defensor(1-5): ",1,MAX_TERR)-1;
  if(a!=d)batalha(&t[a],&t[d]);
 }
 free(t);
}

/* --- Nível Mestre --- */
void init_auto(Terr *t){
 const char *n[]={"Amazônia","Nordeste","Centro","Sul","Ilhas"};
 const char *c[]={"Verde","Azul","Vermelho","Amarelo","Verde"};
 for(int i=0;i<MAX_TERR;i++){strcpy(t[i].nome,n[i]);
  strcpy(t[i].cor,c[i]);t[i].tropas=rand()%5+1;t[i].owner=rand()%2;}
}
int missao_verde(Terr *t){for(int i=0;i<MAX_TERR;i++)
 if(!strcasecmp(t[i].cor,"Verde")&&t[i].tropas>0)return 0;return 1;}
int missao_tres(Terr *t){int c=0;for(int i=0;i<MAX_TERR;i++)if(t[i].owner==1)c++;return c>=3;}

void mestre(){
 Terr *t=calloc(MAX_TERR,sizeof(Terr));init_auto(t);
 int op=1;
 while(op){
  exibe(t,MAX_TERR);
  printf("1-Atacar | 2-Verificar Missões | 0-Sair\n");
  op=le_int("Escolha: ",0,2);
  if(op==1){
   int a=le_int("Atacante(1-5): ",1,MAX_TERR)-1;
   int d=le_int("Defensor(1-5): ",1,MAX_TERR)-1;
   if(a!=d)batalha(&t[a],&t[d]);
  }else if(op==2){
   printf("\nMissão Verde: %s\n",missao_verde(t)?"CUMPRIDA":"NÃO");
   printf("Missão 3 territórios: %s\n",missao_tres(t)?"CUMPRIDA":"NÃO");
   if(missao_verde(t)&&missao_tres(t)){printf("\n🎉 Todas as missões concluídas!\n");break;}
  }
 }
 free(t);
}

/* --- main --- */
int main(){
 srand(time(NULL));
 int op;
 do{
  printf("\n=== WAR Estruturado ===\n1-Novato\n2-Aventureiro\n3-Mestre\n0-Sair\n");
  op=le_int("Escolha: ",0,3);
  switch(op){case 1:novato();break;case 2:aventureiro();break;case 3:mestre();break;}
 }while(op);
 printf("Encerrando... Boa sorte, comandante!\n");
 return 0;
}
