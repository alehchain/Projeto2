/*----------------------------------------------------------+
|Implementacao dos Algoritmos Prim & Kruskal			     
|					      		                            
|Implementado por:
|				      		                            
| Alexandre Chain - 3924  
| Igor Oliveira - 3672
| Fl�vio Ramos - 4809          
+-----------------------------------------------------------+ */


// Bibliotecas 
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------

typedef struct sARESTA{
    
	double distancia;
    int origem, destino;
    struct sARESTA *next,*prev;
    
}Aresta;


//-------------------------------------------------- PRIM PRIM---------------------------------------------------------------------------

void novaArestaPrioridade(Aresta** vetor,Aresta*nova){             // Fun��o para adicionar as arestas da fila de prioridade.
	
	Aresta* aux = (*vetor);
	nova->next=NULL;
	nova->prev=NULL;
	if((*vetor)==NULL){                                            // Se n�o existir nenhuma aresta na fila de prioridade apenas retornar para a fun��o anterior.
		(*vetor)=nova;
		return;
	}
	if(nova->distancia<aux->distancia){                            // Checar se a distancia da nova aresta � menor que a antiga.
		nova->next=aux;
		aux->prev=nova;
		(*vetor)=nova;
		return;
	}
	while(aux->next!=NULL&&aux->next->distancia<=nova->distancia){ // Checar se existe alguma aresta com menor peso que a antiga.
		aux=aux->next;
	}
	nova->next=aux->next;
	if(aux->next!=NULL)                                            
		aux->next->prev=nova;
	aux->next=nova;
	nova->prev=aux;

}


void novaAresta(Aresta** vetor,Aresta novaAresta){                 // Fun��o para criar o grafo de arestas.
	
	Aresta* nova = malloc(sizeof(struct sARESTA));
	Aresta* aux = (*vetor);
	if (nova == NULL){
		printf("Erro ao allocar!");                                // Mensagem de erro caso n�o seja poss�vel alocar o espa�o.
		exit (1);
	}
	nova->destino = novaAresta.destino;
	nova->origem = novaAresta.origem;
	nova->distancia = novaAresta.distancia;
	nova->next=NULL;
	nova->prev=NULL;
	
	if((*vetor)==NULL){                                            // Colocar a primeira aresta do grafo.
		(*vetor)=nova;
		return;
	}
	while(aux->next!=NULL){                                        // Loop para colocar a proxima aresta no final.
		aux=aux->next;
	}
	
	nova->next=aux->next;
	aux->next=nova;
	nova->prev=aux;	
}
void mostrarCaminho(Aresta**lista){                                // Fun��o para mostrar o caminho gerado pelo Prim ou Kruskal
	
	Aresta* aux;
	aux = (*lista);
	if(aux==NULL){                                                 // Se o caminho n�o existe apenas retorna para a fun��o anterior.
		
		return;
	}
	do{                                                            // Loop para printar todo o caminho que foi criado.
		printf("\nOrigem: %d Destino: %d Custo: % d",aux->origem,aux->destino,aux->distancia);
		aux=aux->next;
	}while(aux!=NULL);
	printf("\n----------------------------------");
}

int existe(Aresta** vetor,int origem,int destino){                 // Fun��o para verificar se a nova aresta existe.
	Aresta *aux = *vetor;
	if(aux==NULL)
		return 0;                                                  // Retornar para a fun��o anterior se n�o existir nenhuma aresta.
	while(aux!=NULL){                                              // Loop para checar todas arestas existentes.
		if((aux->destino==destino&&aux->origem==origem)||(aux->destino==origem&&aux->origem==destino))
			return 1;
		aux = aux->next;
	}
	return 0;                                                      // Retornar para a fun��o anterior.
	
}
void lerArquivo(Aresta** vetor){                                   //  Fun��o de ler o arquivo para usar no Prim.                                  
	
	Aresta nova;
	nova.next = NULL;
	nova.prev = NULL;
	FILE *arq ;
    int x,y,j = 0;
    double z;
    
	arq = fopen( "dados.txt" , "r" );                              // Abrir o arquivo de dados.
    
	if (arq==NULL){                                                // Retornar para a fun��o anterior caso o arquivo n�o exista.
    	printf("Erro ao abrir arquivo!");
    	exit (1);
	}
	do{                                                            // Loop para ler e gravar os vertices e arestas.        
		j++;
		fscanf(arq,"%d%d%d",&x,&y,&z);
		if(existe(vetor,x,y)==0){
			nova.origem=x;
			nova.destino=y;
			nova.distancia=z;
			novaAresta(vetor,nova);
			nova.origem=y;
			nova.destino=x;
			novaAresta(vetor,nova);
		}
		
	}while (!feof(arq));
	fclose(arq);
	
	printf("\nArquivo Aberto com Sucesso!");                       // Mensagem de sucesso na leitura do arquivo.
	
}
void gravarArquivo(Aresta** vetor){                                // Fun��o para criar o arquivo e gravar os resultados do Prim.
	
	Aresta* aux=(*vetor);
	FILE *arq ;
    
	arq = fopen( "ResultadoPrim.txt" , "w" );                      // Criar o arquivo e abrir o arquivo de resultados.
    
	if (arq==NULL){
    	printf("Erro ao abrir arquivo!");                          // Mensagem de erro caso n�o seja poss�vel criar ou abrir o arquivo.
    	exit (1);
	}
	do{                                                            // Loop para gravar o resultado no arquivo.
		fprintf(arq,"%d %d %d\n",aux->origem,aux->destino,aux->distancia);
		aux= aux->next;
	}while (aux!=NULL);
	fclose(arq);
	
	printf("\nArquivo Gerado com Sucesso!\n");                     // Mensagem de sucesso na cria��o do arquivo.
	
}
void removerTodos(Aresta**lista,int elemento){                     // Fun��o para excluir as arestas que foram adicionadas na arvore geradora minima.
	Aresta*aux=(*lista);
	Aresta*excluido;
	while(aux!=NULL){                                              // Loop para excluir a aresta.
		if(aux->destino==elemento){
			excluido=aux;
			if(aux->next==NULL&&aux->prev==NULL){                  // Checar se existe apenas uma aresta.
				(*lista)=NULL;
				free(excluido);                                    // Excluir a aresta e liberar o espa�o.
				return;                                            // Retornar para a fun��o anterior.
			}
			if(aux->prev==NULL){                                   // Checar se existe uma aresta anterior.
				aux->next->prev=NULL;
				(*lista)=(*lista)->next;
			}else{
				if(aux->next==NULL){                               // Checar se existe uma proxima aresta.
					aux->prev->next=NULL;
				}else{
					aux->next->prev=excluido->prev;
					excluido->prev->next = excluido->next;         
				}
			}
			free(excluido);                                        // Excluir a aresta e liberar seu espa�o.
		}
		aux=aux->next;
	}
}

void addCaminho(Aresta**vetor,Aresta*novo){                        // Fun��o para adicionar nova aresta.
	novo->next=NULL;
	novo->prev==NULL;
	Aresta*aux = (*vetor);
	if (aux==NULL){
		(*vetor) = novo;                                           // Caso n�o exista nenhuma aresta retorna para a fun��o anterior.
		return;
	}
	
	while(aux->next!=NULL){                                        // Loop para inserir a nova aresta no final.
		aux=aux->next;
	}
	aux->next=novo;
	novo->prev=aux;
	novo->next=NULL;                                               
}
void freeAll(Aresta**lista){                                       // Fun��o para liberar o espa�o alocado para as arestas e vertices.            
	
	Aresta* excluido;
	while((*lista)!=NULL){                                         // Loop para liberar todas as arestas.
		excluido = (*lista);
		(*lista)=(*lista)->next;
		free(excluido);
		excluido=NULL;
	}
}
void addPrioridade(Aresta**lista,Aresta**filaDePrioridade,int i){  // Fun��o para adicionar todas arestas de um vertice na fila de prioridade.
	
	Aresta*aux=(*lista);
	Aresta*aux2 = aux;
	
	while(aux2!=NULL){                                             
		aux=aux2;
		aux2=aux2->next;
		if(aux->origem==i){                                        // Checar se o vertice escolhido � o mesmo de origem.
			
			if(aux->prev==NULL && aux->next==NULL){                // Checar se existe um vertice anterior e um proximo.
				
				(*lista)=NULL;
			}
			if(aux->prev==NULL){                                   // Checar se existe um vertice anterior.
				
				aux->next->prev=NULL;
				(*lista)=(*lista)->next;
			}else{
				if(aux->next==NULL){                               // Checar se existe um proximo vertice.
					
					aux->prev->next=NULL;
				}else{
					
					aux->next->prev=aux->prev;
					aux->prev->next=aux->next;
				}
			}
			
			novaArestaPrioridade(filaDePrioridade,aux);            // Chamar a fun��o para adicionar a aresta na fila de prioridade.
		}
		
	}
}

void prim(Aresta** lista){                                         // Algoritmo do Prim.
	
	int k;
	Aresta* menor;
	Aresta* caminho=NULL;
	Aresta* filaDePrioridade = NULL;
	printf("\nQual Vertice deseja Comecar: ");
	scanf("%d",&k);
	addPrioridade(lista,&filaDePrioridade,k);
	removerTodos(&filaDePrioridade,k);
	
	do{                                                            // Loop para criar o menor caminho das arestas.
		menor = filaDePrioridade;
		filaDePrioridade=filaDePrioridade->next;
		addPrioridade(lista,&filaDePrioridade,menor->destino);
		if(filaDePrioridade!=NULL){
			filaDePrioridade->prev=NULL;
		}
		addCaminho(&caminho,menor);                                // Chamar a fun��o para adicionar o caminho.
		removerTodos(lista,menor->origem);                         // Chamar fun��o para excluir arestas j� adicionadas no menor caminho.
		removerTodos(lista,menor->destino);                        // Chamar fun��o para excluir arestas j� adicionadas no menor caminho.
		removerTodos(&filaDePrioridade,menor->origem);             // Chamar fun��o para excluir arestas j� adicionadas no menor caminho.
		removerTodos(&filaDePrioridade,menor->destino);            // Chamar fun��o para excluir arestas j� adicionadas no menor caminho.
	}while(filaDePrioridade!=NULL);
	
	printf("\n----------------------------------");
	printf("\nArvore Geradora Minima");                            
	
	
	gravarArquivo(&caminho);                                       // Chama a fun��o para criar um arquivo e gravar os resultados nele.
	mostrarCaminho(&caminho);                                      // Printa no terminal os caminhos.
	freeAll(&caminho);                                             // Libera o espa�o alocado para as arestas.
	
}

//--------------------------------------------------Kruskal---------------------------------------------------------------------------


 
void gravarArquivoKruskal(Aresta** vetor){                         // Fun��o para criar o arquivo e gravar os resultados do Kruskal.                                                                                          
	
	Aresta* aux=(*vetor);
	FILE *arq ;
    
	arq = fopen( "ResultadoKruskal.txt" , "w" );                   // Escreve os caminhos no arquivo 
    
	if (arq==NULL){
    	printf("Erro ao abrir arquivo!");                          // Mensagem de erro se n�o for poss�vel abrir o arquivo.
    	exit (1);
	}
	do{
		fprintf(arq,"%d %d %d\n",aux->origem,aux->destino,aux->distancia);
		aux= aux->next;
	}while (aux!=NULL);
	fclose(arq);
	
                                                                   
	printf("\nArquivo Gerado com Sucesso!\n");                     // Mensagem de retorno mostrando que deu certo gravar os resultados.
	
}

void novaArestaKruskal(Aresta** vetor,Aresta novaAresta){          // Fun��o para criar o grafo de arestas. 
	Aresta* nova = malloc(sizeof(struct sARESTA));
	Aresta* aux = (*vetor);
	if (nova == NULL){                                             // Mensagem de erro se n�o for possivel alocar o espa�o para ser utilizado.
		printf("Erro ao allocar!");
		exit (1);
	}
	nova->destino = novaAresta.destino;
	nova->origem = novaAresta.origem;
	nova->distancia = novaAresta.distancia;
	nova->next=NULL;
	nova->prev=NULL;
	if((*vetor)==NULL){                                            // Retornar a fun��o normal caso o vetor esteja vazio.
		(*vetor)=nova;
		return;
	}
	if(nova->distancia<aux->distancia){                            // Ordenar as arestas pelo peso.
		nova->next=aux;
		aux->prev=nova;
		(*vetor)=nova;
		return;                                                    // Retornar para a fun��o anterior.
	}
	while(aux->next!=NULL&&aux->next->distancia<=nova->distancia){ // Checar se existe alguma aresta com peso menor que o da nova aresta.
		aux=aux->next;
	}
	nova->next=aux->next;
	if(aux->next!=NULL)                                            
		aux->next->prev=nova;
	aux->next=nova;
	nova->prev=aux;

}

lerArquivoKruskal(Aresta** vetor){                                 // Fun��o para ler o arquivo com os Vertices e Arestas a ser utilizado no Kruskal.     
	Aresta nova;
	nova.next = NULL;
	nova.prev = NULL;
	FILE *arq ;
    int x,y,j = 0;
    double z;
	arq = fopen( "dados.txt" , "r" );                              // Abrir o arquivo de dados onde as arestas est�o armazenadas.
    
	if (arq==NULL){
    	printf("Erro ao abrir arquivo!");                          // Mensagem de erro caso o arquivo esteja vazio.
    	exit (1);
	}
	do{                                                            // Loop para ler e gravar os vertices e arestas.
		j++;
		fscanf(arq,"%d%d%d",&x,&y,&z);
		if(existe(vetor,x,y)==0){
			nova.origem=x;
			nova.destino=y;
			nova.distancia=z;
			novaArestaKruskal(vetor,nova);                         // Chamar a fun��o para criar as arestas e ordenar pelo peso.
			nova.origem=y;
			nova.destino=x;
			novaArestaKruskal(vetor,nova);                         // Chamar a fun��o para criar as arestas e ordenar pelo peso.
		}
		
	}while (!feof(arq));
	fclose(arq);                                                   
	
	printf("\nArquivo Aberto com Sucesso!");
	
}

void kruskal(Aresta** lista){                                      // Algoritmo do Kruskal.      

	Aresta* menor;
	Aresta* caminho=NULL;
	
	do{                                                            // Loop para pegar o menor peso das arestas e criar o menor caminho.
		menor = (*lista);
		(*lista)=(*lista)->next;
		if((*lista)!=NULL){
			(*lista)->prev=NULL;
		}
		
		addCaminho(&caminho,menor);                                // Chamar a fun��o de adicionar a aresta no menor caminho.
		
		removerTodos(lista,menor->origem);                      
	}while((*lista)!=NULL);
	
	printf("\n----------------------------------");                
	printf("\nArvore Geradora Minima");                            // Mensagem para mostrar que a Arvore Geradora Minima foi criada.
	
	
	gravarArquivoKruskal(&caminho);                                // Chamar a fun��o de gravar o resultado do menor caminho no arquivo.
	mostrarCaminho(&caminho);                                      // Chamar a fun��o de mostrar o caminho gerado.
	freeAll(&caminho);                                             // Liberar o espa�o alocado na mem�ria.
	
}
int verifica(Aresta** lista1,Aresta** lista2){                     // Fun��o de Verificar resultado dos algoritmos.   
	Aresta*aux1=(*lista1);
	Aresta*aux2=(*lista2);
	int existe=0;
	while(aux1!=NULL){                                             // Loop de verifica��o das arestas do Prim.
		while(aux2!=NULL){                                         // Loop de verifica��o das arestas do Kruskal.
			
			if(aux1->origem==aux2->origem&&aux1->destino==aux2->destino&&aux1->distancia==aux2->distancia){      // Verificar se o vertice origem o destino e o peso entre os resultados s�o iguais.
				existe=1;
				break;
			}else{
				existe=0;
			}
			aux2=aux2->next;                                       // Mudar para a proxima aresta do Kruskal a ser checada.      
		}
		if(existe==1){
			aux1=aux1->next;                                       // Mudar para a proxima aresta do Prim a ser checada.
		}else{
			return 0;                                              // Retornar o valor 0 para mostrar que as respostas s�o diferentes.
		}
	}
	return 1;                                                      // Retornar o valor 1 para mostrar que as respostas s�o iguais.
}
void lerArquivoResultados(Aresta** vetor1,Aresta** vetor2){        // Fun��o de ler arquivos de resultado.
	
	Aresta nova;
	FILE *arq ;
    int x,y,j = 0;
    double z;
	arq = fopen( "ResultadoPrim.txt" , "r" );                      // Abrir arquivo resultado do PRIM.
    
	if (arq==NULL){
    	printf("Erro ao abrir arquivo!");                          // Mensagem de erro se n�o for poss�vel abrir arquivo.
    	exit (1);
	}
	do{                                                            // Loop de leitura dos resultados.
		j++;
		fscanf(arq,"%d%d%d",&x,&y,&z);
		
		if(existe(vetor1,x,y)==0){
             nova.next = NULL;
		     nova.prev = NULL;
		     nova.origem=x;
		     nova.destino=y;
		     nova.distancia=z;
             novaAresta(vetor1,nova);
        }
		
		
	}while (!feof(arq));
	fclose(arq);
	
	
	
	arq = fopen( "ResultadoKruskal.txt" , "r" );                   // Abrir arquivo resultado do KRUSKAL.
    
	if (arq==NULL){
    	printf("Erro ao abrir arquivo!");                          // Mensagem de erro caso o arquivo esteja vazio.
    	exit (1);
	}
	do{                                                            // Loop de leitura dos resultados.
		j++;
		fscanf(arq,"%d%d%d",&x,&y,&z);
		
		if(existe(vetor2,x,y)==0){
		    nova.next = NULL;
		    nova.prev = NULL;
		    nova.origem=x;
		    nova.destino=y;
		    nova.distancia=z;
		    novaAresta(vetor2,nova);
       }
		
	}while (!feof(arq));
	fclose(arq);
	
	printf("\nArquivo Aberto com Sucesso!");
	
}

int main(){
	
	int op;
	Aresta* lista =NULL;
	Aresta* vetor1 = NULL,*vetor2 = NULL;
	do{
	
		printf("\n");        // Menu de sele��o do algoritmo a ser executado.
		
		printf("\n[1] Executar Algoritmo Prim");
		printf("\n[2] Executar Algorritmo Kruskal");
		printf("\n[3] Verificar os Algoritmos");
		printf("\n[0] Sair.\n");
		
		scanf("%d",&op);
	
		switch(op){
		
		case 1:              // Parte de chamar e executar o algoritmo de PRIM.
			
			lerArquivo(&lista);          // Ler o arquivo de dados para ser executado utilizando o Prim.
			prim(&lista);                // Chamar e executar o Prim.
			break;
		
		case 2:              // Parte de chamar e executar o algoritmo de KRUSKAL.
			
			lerArquivoKruskal(&lista);   // Ler o arquivo de dados para ser executado utilizando o Kruskal.
			kruskal(&lista);             // Chamar e executar o Kruskal.
			break;
		
		case 3:              // Parte de chamar para verificar se as respostas de ambos algoritmos est�o iguais.
			
			lerArquivoResultados(&vetor1,&vetor2);        // Ler arquivos de resultado do PRIM e KRUSKAL.
			mostrarCaminho(&vetor1);                      // Mostrar caminho resultado do PRIM.
			printf("\n");
			mostrarCaminho(&vetor2);                      // Mostrar caminho resultado do KRUSKAL.
			if(verifica(&vetor1,&vetor2)==1){             // Chamar fun��o para verificar se os resultados s�o iguais.
				printf("\nAlgoritmos Iguais! ");
			}else{
				printf("\nAlgoritmos Diferentes!");
			}
			freeAll(&vetor1);                             // Liberar o espa�o alocado na mem�ria.
			freeAll(&vetor2);                             // Liberar o espa�o alocado na mem�ria.
			break;
		
		}
		
	}while(op != 0);
	
	system("pause>>nul");
	return 0;
	
}
