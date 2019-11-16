#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DRINK_NAME 20
#define MAX_FOOD_NAME 30
#define MAX_LINE 20

void readSpecific(char * specific);


int main() {
    int noOfFoodTypes = 0;
    printf("Hello, please enter the number of food types !\n");
    scanf("%d", &noOfFoodTypes);
    printf("Please enter the food types\n");
    char **foodTypes;
    int *noOfSpecificFoods = (int *) malloc(noOfFoodTypes * sizeof(int));
    char ***specificFoods = (char ***) malloc(noOfFoodTypes * sizeof(char **));
    double **prices = (double **) malloc(noOfFoodTypes * sizeof(double *));
    foodTypes = (char **) malloc(noOfFoodTypes * sizeof(char *));
    int noOfDrinks = 0;
    char **drinks = (char **) malloc(noOfDrinks * sizeof(char *));
    double *drinkPrices = (double *) malloc(noOfDrinks * sizeof(double));
    for (int i = 0; i < noOfFoodTypes; i++) {
        foodTypes[i] = (char *) malloc(MAX_FOOD_NAME * sizeof(char));
        scanf("%s", foodTypes[i]);
    }
    for (int i = 0; i < noOfFoodTypes; i++) {
        printf("Please  enter the of specific foods for %s. \n", foodTypes[i]);
        scanf("%d", &noOfSpecificFoods[i]);
        getchar();
        specificFoods[i] = (char **) malloc(noOfSpecificFoods[i] * sizeof(char *));
        prices[i] = (double *) malloc(noOfSpecificFoods[i] * sizeof(double));
        printf("Please enter the specific food types and prices. (food, price)\n");
        for (int j = 0; j < noOfSpecificFoods[i]; j++) {
            specificFoods[i][j] = (char *) malloc(MAX_FOOD_NAME * sizeof(char));
            readSpecific(specificFoods[i][j]);
            char line[MAX_LINE];
            gets(line);
            sscanf(line, "%lf", &prices[i][j]);
        }
    }
    printf("Please enter the number of drinks. \n");
    scanf("%d", &noOfDrinks);
    getchar();

    printf("Please enter the drinks (drink, price). \n");
    for (int i = 0; i < noOfDrinks; i++) {
        readSpecific(drinks[i]);
        char line[MAX_LINE];
        gets(line);
        sscanf(line, "%lf", &drinkPrices[i]);
    }
    printf("\nThis is the food: ");
    for (int i = 0; i < noOfFoodTypes; i++) {
        printf("%s: ", foodTypes[i]);
        for (int j = 0; j < noOfSpecificFoods[i]; j++) {
            printf("(%s, %.2lf) ", specificFoods[i][j], prices[i][j]);
        }
        printf("\n");
    }

    printf("These are the drinks : ");
    {
        for (int i = 0; i < noOfDrinks; i++) {
            printf(" %s ", drinks[i]);
        }
    }

    printf("\nDrink prices : ");
    {
        for (int i = 0; i < noOfDrinks; i++) {
            printf(" %.2lf ", drinkPrices[i]);
        }
    }
    for (int i = 0; i < noOfFoodTypes; i++) {
        for (int j = 0; j < noOfSpecificFoods; j++) {
            free(specificFoods[i][j]);
        }
        free(specificFoods[i]);
        free(prices[i]);
        free(foodTypes[i]);
    }
    free(specificFoods);
    free(prices);
    free(foodTypes);
    free(noOfSpecificFoods);
    free(drinks);
}

void readSpecific(char * specific) {
    char c = getchar();
    int i=0;
    while(c!=',') {
        specific[i] = c;
        c = getchar();
        i++;
    }
    specific[i] = '\0';
}
