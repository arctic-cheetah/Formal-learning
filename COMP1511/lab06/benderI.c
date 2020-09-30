//A demo of structs, strings and other C constructs
//Bender fighht pits four elemental benders against
//One strong enemy and simulates a fight between them


#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100
#define TEAM_SIZE 4


struct bender {
	char name [MAX_LENGTH];
	char element [MAX_LENGTH];
	int power;
	int health;
	
};

void attack (struct bender *attacker, struct bender *target);
int stillAlive(struct bender *solo, struct bender team[TEAM_SIZE]);



int main(){

	struct bender companions[TEAM_SIZE];
	//Aang
	strcpy (companions[0].name, "Avatar Aang");
	strcpy (companions[0].element, "Air");
	companions[0].power = 10;
	companions[0].health = 5;
	//Kitara
	strcpy (companions[1].name , "Kitara");
	strcpy (companions[1].element, "Water");
	companions[1].power = 7;
	companions[1].health = 7;
	//Sokka
	strcpy (companions[2].name, "Sokka");
	strcpy (companions[2].element, "None");
	companions[2].power = 2;
	companions[2].health = 10;
	//Toph
	strcpy (companions[1].name, "Toph");
	strcpy (companions[1].element, "Earth");
	companions[3].power = 6;;
	companions[3].health = 8;
	
	//Enemy! Prince Zuko
	struct bender Zuko;
	strcpy (Zuko.name, "Zuko");
	strcpy (Zuko.element, "Fire");
	Zuko.power = 20;
	Zuko.health = 20;
	
	//Single Attack Action
	attack(&Zuko, &companions[2] );
	attack(&companions[2], &Zuko );

	return 0;
}


void attack (struct bender *attacker, struct bender *target){
	printf("%s attacks %s for %d damage.\n",
		*attacker.name, *target.name, *attacker.power
	);
	
	*target.health -= *attacker.power;
	
	if(*target.health <= 0){
		printf("%s has been knocked out. \n", *target.name);
	}
}

//Are there combantants on both sides that are able to fight?
//Return yes = 1. No = 0
int stillAlive(struct bender *solo, struct bender team[TEAM_SIZE]){

	//int sAlive = 1;

	return 0;
}












































