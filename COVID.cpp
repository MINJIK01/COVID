#include <stdio.h>
#include <string.h>

struct node {
	char country[80];
	char country_code[3];
	int totalCases;
	int totalDeaths;
	struct node * NextPtr;
};

int Length(node * chain)
{
	int num = 0;
	struct node* ThisPtr = chain;
	while(ThisPtr != NULL)
	{
		ThisPtr = ThisPtr -> NextPtr;
		++num;
 	}
 	return num;
}

void PrintALL(node * chain)
{
	struct node* ThisPtr = chain;
	while(ThisPtr != NULL)
	{
		printf("Country = Name: %s; Country code: %s\nTotal Cases: %d\nTotal Death: %d\n", ThisPtr -> country, ThisPtr -> country_code, ThisPtr -> totalCases, ThisPtr -> totalDeaths);
		ThisPtr = ThisPtr -> NextPtr;
	}
}

node * FindCountryCode(node * chain, char * input)
{	
	struct node* ThisPtr = chain;
	int k = 0;
	int check = 0;
	
	while ((chain[k].country_code[0] != input[0] | chain[k].country_code[1] != input[1]) & k < 235)
	{
		k += 1;
	}
	
	if (k < 235)
	{
		int a = 0;
		for (a ; a < k; ++a)
		{
			ThisPtr = ThisPtr -> NextPtr;
		}
		return ThisPtr;
	}
	else
	{
		return 0;
	}
}

node * FindMaxCases(node * chain)
{
	struct node* ThisPtr = chain;
	
	int num = 0;
	while(ThisPtr != NULL)
	{
		ThisPtr = ThisPtr -> NextPtr;
		++num;
 	}
 	
 	int max = chain[0].totalCases;
 	int z = 1;
 	for (z ; z < num ; ++z)
 	{	
 		if(max > chain[z].totalCases){
 		}
 		else{
 			max = chain[z].totalCases;
 		}
	}
	
	int address;
	z = 0;
	for (z; z < num ; z++)
	{
		if (chain[z].totalCases == max)
		{
			address = z;
		}
	}
	
	int a = 0;
	ThisPtr = chain;
	for (a ; a < address; ++a)
	{
		ThisPtr = ThisPtr -> NextPtr;
	}
	return ThisPtr;
}

node * FindMaxDeaths(node * chain)
{
	struct node* ThisPtr = chain;
	
	int num = 0;
	while(ThisPtr != NULL)
	{
		ThisPtr = ThisPtr -> NextPtr;
		++num;
 	}
 	
 	int max = chain[0].totalDeaths;
 	int z = 1;
 	for (z ; z < num ; ++z)
 	{	
 		if(max > chain[z].totalDeaths){
 		}
 		else{
 			max = chain[z].totalDeaths;
 		}
	}
	
	int address;
	z = 0;
	for (z; z < num ; z++)
	{
		if (chain[z].totalDeaths == max)
		{
			address = z;
		}
	}
	
	int a = 0;
	ThisPtr = chain;
	for (a ; a < address; ++a)
	{
		ThisPtr = ThisPtr -> NextPtr;
	}
	return ThisPtr;
}

int main(void)
{	FILE * fPtr = fopen("covid-19.csv","r");
	char currentCountry[80] = "";
	int counter=0;
	node chain[235];
	node * maxTotalCases=0;
	node * maxTotalDeaths=0;
	node * head=&chain[0];

	
	char junk[80] = "";
	fscanf(fPtr, "%s", &junk);
	fscanf(fPtr, "%s %s", &chain[counter].country_code, &chain[counter].country);
	char countryCode[3] = "";
	strcpy(countryCode, chain[counter].country_code);
	
	int infection = 0;
	int death = 0;
	fscanf(fPtr, "%d %d", &infection, &death);	
	
	char compare_country[3] = "";
	
	int plus_infection = 0;
	int plus_death = 0;
	chain[counter].NextPtr = &chain[counter + 1];
	
	fscanf(fPtr, "%s", &junk);
	fscanf(fPtr, "%s", &compare_country);
	fscanf(fPtr, "%s", &junk);
	
	while(!feof(fPtr)){
		
		while (countryCode[0] == compare_country[0] & countryCode[1] == compare_country[1] & countryCode[2] == compare_country[2] & !feof(fPtr))
		{
			fscanf(fPtr, "%d %d", &plus_infection, &plus_death);
			infection = infection + plus_infection;
			death = death + plus_death;
			fscanf(fPtr, "%s", &junk);
			fscanf(fPtr, "%s", &compare_country);
			fscanf(fPtr, "%s", &junk);
		}

		chain[counter].totalCases = infection;
		chain[counter].totalDeaths = death;
		
		counter += 1;	
		
		if (counter< 235)
		{
			chain[counter].NextPtr = &chain[counter + 1]; //pointer change
			strcpy(chain[counter].country_code, compare_country);
			strcpy(chain[counter].country, junk);	
		}
		
		strcpy(countryCode, compare_country);	
		
		infection = 0;
		death = 0;
	}
	
	chain[counter-1].NextPtr = NULL;	
	
	fclose(fPtr);
	

	maxTotalCases = FindMaxCases(chain);
	maxTotalDeaths = FindMaxDeaths(chain);

	printf("There are %d countries in the data.\n",Length(chain));
	printf("Max Total Cases: %s %d\n",maxTotalCases->country,maxTotalCases->totalCases);
	printf("Max Total Deaths: %s %d\n",maxTotalDeaths->country,maxTotalDeaths->totalDeaths);
		
	char Input[4];
	while(strcmp(Input,"q"))
	{	printf("===============================\n");
		printf("Enter the country code to display the total number of cases and total number of death of the country.\n");
		printf("Enter \"ALL\" to display all data.\n");
		printf("Enter (q to quit): ");
		scanf("%s",Input);
		
		if(!strcmp(Input,"ALL"))
			PrintALL(chain);
		else if(!strcmp(Input,"q"))
			break;
		else
		{	node * ResultPtr = FindCountryCode(chain,Input);
			if (ResultPtr == 0)
				printf("Country Code not found!\n");
			else
				printf("Country: %s; Country code: %s\nTotal Cases: %d\nTotal Deaths: %d\n",ResultPtr->country,ResultPtr->country_code,ResultPtr->totalCases,ResultPtr->totalDeaths);
		}
	}

	return 0;
}
