#include "common.h"

int detect_collision(Entity *entity1, Entity *entity2){

	Entity *e1 = entity1;
	Entity *e2 = entity2;

	if((entity1->rect.w * entity1->rect.h) < (entity2->rect.w * entity2->rect.h)){
		e1 = entity2;
		e2 = entity1;
	}

	if(e2->rect.x <= e1->rect.x + e1->rect.w && e2->rect.x >= e1->rect.x && e2->rect.y >= e1->rect.y && e2->rect.y <= e1->rect.y + e1->rect.h){
		printf("bonk\n");
		return TRUE;
	}
	if(e2->rect.x + e2->rect.w <= e1->rect.x + e1->rect.w && e2->rect.x + e2->rect.w >= e1->rect.x && e2->rect.y >= e1->rect.y && e2->rect.y <= e1->rect.y + e1->rect.h){
		printf("benk\n");
		return TRUE;
	}
	if(e2->rect.x <= e1->rect.x + e1->rect.w && e2->rect.x >= e1->rect.x && e2->rect.y + e2->rect.h >= e1->rect.y && e2->rect.y + e2->rect.h <= e1->rect.y + e1->rect.h){
		printf("bink\n");
		return TRUE;
	}
	if(e2->rect.x + e2->rect.w <= e1->rect.x + e1->rect.w && e2->rect.x + e2->rect.w >= e1->rect.x && e2->rect.y + e2->rect.h >= e1->rect.y && e2->rect.y + e2->rect.h <= e1->rect.y + e1->rect.h){
		printf("bank\n");
		return TRUE;
	}
	return FALSE;
}

int rspeed(void){

	int num = (rand() % 6) + 1;
	printf("speed: %d\n", (num + 14) * 10);
	printf("time: %ld\n", time(0));
	int coin = (rand() % 2) + 1;
	printf("coin: %d\n", coin);
	num += 14;
	if(coin == 1){
		num *= -1;
	}
	return num * 10;
}
