#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define START_DIR "./root"




typedef struct files{
	
	char *name;
	int how;
	struct files *next;

}files;

char *doWay(const char *way, char * dir){

	char *newWay = malloc((strlen(way) + strlen(dir)+3)*sizeof(char));		
	
	strcpy(newWay, way);
	strcat(newWay, "/");
	strcat(newWay, dir);
			
	return newWay;	
}

files* doElem(char *name, files *listOfFile){

	if(listOfFile == NULL){
	
		listOfFile = malloc(sizeof(files)); 
		listOfFile->name = malloc(strlen(name)*sizeof(char));
		strcpy(listOfFile->name, name);
		listOfFile->how = 1;
		listOfFile->next == NULL;
	
		return listOfFile;
	}

	else{

	files *newElem = malloc(sizeof(files));
	newElem->name = malloc(strlen(name)*sizeof(char));
	strcpy(newElem->name, name);
	newElem->how = 1;
	newElem->next = listOfFile;
	return newElem;

	}

}

int nameInList(char *name, files *list){

	files *elem = list;

	if(list == NULL) 
		return 0;
	

	while(elem){
	
	if(strcmp(elem->name, name) == 0)
		return 1;

	elem = elem->next;

	}

	return 0;
}




	

files *findDuplicate(char *way, files *listOfFile){


	DIR *dir;

	dir = opendir(way);

	if(dir){
		
		struct dirent *de = readdir(dir);
		
		while(de){

		

		if(strstr(de->d_name, ".") == NULL ){
			
			listOfFile = findDuplicate(doWay(way, de->d_name), listOfFile);
		}
			
		else if(strcmp(de->d_name, ".") && strcmp(de->d_name, "..") && !nameInList(de->d_name,listOfFile)){
		        
			listOfFile = doElem(de->d_name, listOfFile);
		}
		
		else if(strcmp(de->d_name, ".") && strcmp(de->d_name, "..") && nameInList(de->d_name,listOfFile)){
			files* find = listOfFile;

			while(find){
				if(strcmp(de->d_name, find->name) == 0){
					find->how += 1;
					remove(doWay(way, de->d_name));
					break;				
				}
			find = find->next;
			}
		        
		}
		
		de = readdir(dir);

		}


	}
	
	return listOfFile;

}







int main(){
	
	files *listOfFile = NULL;
	
	listOfFile = findDuplicate(START_DIR, listOfFile);

	while(listOfFile){

	printf("%s---%d\n", listOfFile->name, listOfFile->how);
	listOfFile = listOfFile->next;
	}






}














