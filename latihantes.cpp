#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<regex>
#include<ctime>
#define SIZE 6

using namespace std;

struct Monster{
	char idbook[10];
	char nama[100];
	char typechar[20];
	float sizechar;
	char loc[50];
	struct Monster *next,*prev;
}*head[10],*tail[10],*curr;

//struct Data *listdata[6];

void inputdata(char id[], char nama1[], char typemonster[],float sizemonster, char loc[],int keyhash){
	curr = (struct Monster *)malloc(sizeof(struct Monster));
	curr->next = NULL;
	strcpy(curr->idbook,id);
	strcpy(curr->nama,nama1);
	
	strcpy(curr->typechar,typemonster);
	curr->sizechar = sizemonster;

	strcpy(curr->loc,loc);
	printf("%d\n", keyhash);
	
	if(head[keyhash] == NULL){
		head[keyhash] = tail[keyhash] = curr;
	}
	else{
		tail[keyhash]->next = curr;
		curr->prev=tail[keyhash];
		tail[keyhash] = curr;
	}
	tail[keyhash]->next=head[keyhash]->prev = NULL;
//	printf("\n%d\n", keyhash);
	printf("New data input successfully added!\n");
//	system("pause");
}

void menupage(){
	printf("==========================\n");
	printf("<< Monster Encyclopedia >>\n");
	printf("==========================\n");
	printf("1. Insert New Monster\n");
	printf("2. Change Monster Data\n");
	printf("3. Remove Monster\n");
	printf("4. Close Book\n");
}

int hashid(){
	int idm=0;
	srand((unsigned) time(NULL));
	
	idm=rand()%999+100;
	
	printf("%d\n",idm);
	return idm;
}

int keyhash(char key1[]){
	int len = strlen(key1);
	int i = 0, key = 0;
	int hashValue = 0;
	//ubah string jadi add up ascii
	for(i=0;i<len;i++){
		key += key1[i];
	}
	//division with size
	hashValue = key % SIZE;
	return hashValue;
}

bool ceknama(char nama[]){
	if(nama[0]<65)return false;
	else if(nama[0]>90)return false;
	else if(strlen(nama)<3)return false;
	else if(strlen(nama)>20)return false;
	else{
		for(int i=0;i<strlen(nama);i++){
			if(nama[i]==32)continue;
			else if(nama[i]<'A'||nama[i]>'z')return false;
		}
	}
	return true;
}

bool cektype(char type[]){
	if(strcmp(type,"Small")==0)return true;
	else if(strcmp(type,"Large")==0)return true;
	else if(strcmp(type,"Pets")==0)return true;
	return false;
}

void PrintHashTable(){
	for(int i= 0; i< SIZE; i++){
		curr = head[i];
		while(curr!=NULL){
			printf("=============================================\n");
			printf("ID\t\t: %s\n",curr->idbook);
			printf("Name\t\t: %s\n", curr->nama);
			printf("Type\t\t: %s\n", curr->typechar);
			printf("Size\t\t: %f\n", curr->sizechar);
			printf("Location\t\t: %s\n", curr->loc);
			printf("=============================================\n");
			curr = curr->next;
		}
	}
}


void updatedata(char idlook[]){
	for(int i= 0; i< SIZE; i++){
		curr = head[i];
		while(curr){
			
			char monstername[25];
			char typemonster[10];
			float sizemonster;
			char locate[25];
			char idgen[6];
			char idbook[6];
			int key;
			
			if(strcmp(curr->idbook, idlook)==0){
				printf("=============================================\n");
				printf("ID\t\t: %s\n",curr->idbook);
				printf("Name\t\t: %s\n", curr->nama);
				printf("Type\t\t: %s\n", curr->typechar);
				printf("Size\t\t: %f\n", curr->sizechar);
				printf("Location\t\t: %s\n", curr->loc);
				printf("=============================================\n");
				
				do{
					key=1;
					printf("Input monster name [3-20 character]: ");
					scanf("%[^\n]",monstername);fflush(stdin);
					if(strcmp("0",monstername)==0){
						key=0;
						break;
					}
				}while(!ceknama(monstername));
				if(key==1){
					strcpy(curr->nama,monstername);
				}
				
				do{
					key=1;
					printf("Input monster type [Small | Large | Pets]: ");
					scanf("%s",typemonster);fflush(stdin);
					if(strcmp("0",typemonster)==0){
						key=0;
						break;
					}
				}while(!cektype(typemonster));
				if(key==1){
					strcpy(curr->typechar,typemonster);
				}
				
				do{
					key=1;
					printf("Input monster size [100.0|5000.0]: ");
					scanf("%f",&sizemonster);fflush(stdin);
					if (sizemonster==0){
						key=0;
						break;
					}
				}while(sizemonster<100||sizemonster>5000);
				if(key==1){
					curr->sizechar=sizemonster;
				}
				
				do{
					printf("Input monster Location: ");
					scanf("%[^\n]",locate);fflush(stdin);
					if(strcmp("0",locate)==0){
						key=0;
						break;
					}
				}while(strstr(locate,"Biome")==0);
				if(key==1){
					strcpy(curr->loc, locate);
				}
				printf("Monster successfully updated!");
				getchar();
				return;
			}
					
			curr = curr->next;
		}
	}
	printf("Monster not found...");
	getchar();
	return;
}

void removedata(int keyhash1, char idlook[]){

	if(head[keyhash1]!=NULL){
	
		if(strcmp(head[keyhash1]->idbook, idlook)==0){
			curr=head[keyhash1];
			printf("%s\n",curr->nama);
			head[keyhash1] = head[keyhash1]->next;
			free(curr);
			if(head[keyhash1] != NULL) head[keyhash1]->prev = NULL;
			else head[keyhash1] = tail[keyhash1] = NULL;
		}
		else if(strcmp(tail[keyhash1]->idbook, idlook)==0){
			curr = tail[keyhash1];
			printf("%s\n",curr->nama);
			tail[keyhash1] = tail[keyhash1]->prev;
			free(curr);
			if(tail[keyhash1] != NULL) tail[keyhash1]->next = NULL;
			else head[keyhash1] = tail[keyhash1] = NULL;
		}
		else{
			curr = head[keyhash1];
			while(curr != NULL && strcmp(curr->idbook, idlook) != 0){
				curr = curr->next;
			}
			
			if(curr == NULL){
				printf("Data yang dicari tidak ada!");
			}
			else{
				printf("%s\n",curr->nama);
				struct Monster *temp = curr->prev;
				temp->next = curr->next;
				temp->next->prev = curr->prev;
				curr->next = curr->prev = NULL;
				free(curr);				
			}
		}
	
	} 
		
//	printf("Monster not found...");
	getchar();
	return;
}


int main(){
	
	int pilih=0;
	char angka[5];
	
	char monstername[25];
	char typemonster[10];
	float sizemonster;
	char locate[25];
	char idgen[6];
	char idbook[6];
	
	char value[10];
	
	inputdata("MON123", "Monsta","Large",3000, "Earth Biome", 3);
	inputdata("DEV143", "Devians","Large",200, "Earth Biome", 1);
	
	do{
		PrintHashTable();
		menupage();
		printf("Choose >> ");
		scanf("%d",&pilih);fflush(stdin);
		if(pilih==1){
			do{
				printf("Input monster name [3-20 character]: ");
				scanf("%[^\n]",monstername);fflush(stdin);
			}while(!ceknama(monstername));
			
			do{
				printf("Input monster type [Small | Large | Pets]: ");
				scanf("%s",typemonster);fflush(stdin);
			}while(!cektype(typemonster));
			
			do{
				printf("Input monster size [100.0|5000.0]: ");
				scanf("%f",&sizemonster);fflush(stdin);
			}while(sizemonster<100||sizemonster>5000);
			
			do{
				printf("Input monster Location: ");
				scanf("%[^\n]",locate);fflush(stdin);
			}while(strstr(locate,"Biome")==0);
			
			printf("Name: %s\n",monstername);
			printf("Type Monster: %s\n",typemonster);
			printf("Size Monster: %f\n",sizemonster);
			printf("Location Monster: %s\n",locate);
			
			strncpy(idbook, monstername, 3);
			strupr(idbook);
			sprintf(idgen, "%d", hashid());
			printf("Idgen: %s Idbook: %s\n",idgen,idbook);
			strcat(idbook,idgen);
			
			printf("ID Monster: %s\n",idbook);
			
			inputdata(idbook,monstername,typemonster,sizemonster,locate,keyhash(idbook));
			
			getchar();
		}
		
		if(pilih==2){
			PrintHashTable();
			printf("Input monster id to update: "); scanf("%s", value);fflush(stdin);
			updatedata(value);
		}
		
		if(pilih==3){
			PrintHashTable();
			printf("Input monster id to remove: "); scanf("%s", value);fflush(stdin);
			removedata(keyhash(value),value);
		}
		
	}while(pilih!=4);

//	sprintf(angka,"%d", hashid());
//	printf("%s",angka);
	
	return 0;
}