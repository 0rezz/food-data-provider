#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FOOD_NAME 20
#define MAX_TYPE_NAME 30
#define MAX_DRINK_NAME 30
#define MAX_LINE 100
#define DATA "Please load the data"


void inputLogIn (char username[], char password[]);
void chooseFood (int noFoods, char **foods);
void chooseType (char foods[], int noTypes,  char **types, double price[] );
int getChoiceIndex(int noChoices, int *state);
void printDrinkChoices (int noDrinks, char **drinks, double drinkPrice[]);
int chooseDrinks(int noDrinks, int chosenDrinks[], int *state);
void readAdditionalInfo (char str[], int *state);
void chooseCutlery (int *cutlery, int *state, char choice);
void displayOrder(char type[], double price, int noDrinksChosen, int chosenDrink[], char drinks[], double drinkPrice[], char str[],int *cutlery,int *state, char choice, int *ordersigned);


void reformatLine(char *token, char itemLength[MAX_LINE], int nrOfCharactersToRemove);
char *extractFoods(char *token, char line[MAX_LINE]);
char *extractTypes(char *token, char line[MAX_LINE]);
int extractNoTypes(char *token, char line[MAX_LINE]);
double extractPrice(char  *token, char line[MAX_LINE]);


int main() {
    int noFoods, noDrinks;
    int *noTypes;

    int choice, foodChoice, typeChoice, cutlery;

    char **foods;
    char ***types;
    double **price;

    foods = (char **) malloc(noFoods * sizeof(char *));
    types = (char ***) malloc(noFoods * sizeof(char **));
    price = (double **) malloc(noFoods * sizeof(double *));
    noTypes = (int *) malloc(noFoods * sizeof(int));

    char info[100], username[20], password[30], token[MAX_LINE], line[MAX_LINE];

    printf("%s\n", DATA);
    scanf("%d",&noFoods);
    getchar();

    for(int i=0;i<noFoods;i++){
        foods[i] = (char *) malloc(MAX_FOOD_NAME * sizeof(char));
        scanf("%[^'\n']s", token);
        getchar();
        strcpy(line, token);
        char *foodsPointer=extractFoods(token,line);
        strcpy(foods[i], foodsPointer);
        strcpy(line, token);
        noTypes[i]=extractNoTypes(token, line);
        strcpy(line, token);

        types[i] = (char **) malloc(noTypes[i] * sizeof(char *));
        price[i] = (double *) malloc(noTypes[i] * sizeof(double));
        int k=0;
        for(int j=0;j<noTypes[i];j++){
            types[i][k]=(char*)malloc(MAX_TYPE_NAME*sizeof(char));
            char *typePointer=extractTypes(token, line);
            strcpy(types[i][k],typePointer);
            strcpy(line, token);
            double Price = extractPrice(token, line);
            price[i][k]=Price;
            strcpy(line, token);
            k++;

        }
    }
    char **drinks;
    double *drinkPrice;
    drinks = (char **) malloc(noDrinks * sizeof(char *));
    drinkPrice=(double*)malloc(noDrinks*sizeof(char*));

    scanf("%s\n",&noDrinks);
    getchar();

    int e=0;
    for (int d=0;d<noDrinks;d++){
        drinks[e]=(char*)malloc(MAX_DRINK_NAME*sizeof(char*));
        char *drinksPointer=extractTypes(line,token);
        strcpy(drinks[e],drinksPointer);

        strcpy(line,token);
        double drinkPricePointer=extractPrice(line,token);
        drinkPrice[e]=drinkPricePointer;
        strcpy(line,token);
    }
    printf ("Welcome to food thingies!\nPlease sign in to continue:\n");

    int noDrinksChosen;


    int chosenDrink[3];
    int state=0;
    int ordersigned=0;
    while (ordersigned==0) {
        switch (state) {
            case 0: {
                inputLogIn (username, password);
                state++;
                break;
            }
            case 1: {
                chooseFood (noFoods, foods);
                foodChoice= getChoiceIndex( noFoods, &state);
                break;}
            case 2: {
                chooseType (foods[foodChoice], noTypes[foodChoice],  types[foodChoice],  price[foodChoice]);
                typeChoice= getChoiceIndex (noTypes[foodChoice], &state);
                break;
            }
            case 3: {
                printDrinkChoices (noDrinks, drinks, drinkPrice);
                noDrinksChosen = chooseDrinks (noDrinks, chosenDrink, &state);
                break;
            }
            case 4: {
                chooseCutlery (&cutlery, &state,choice);
                break;
            }
            case 5: {
                readAdditionalInfo (info, &state);
                break;
            }
            case 6: {
                displayOrder(types[foodChoice][typeChoice], price[foodChoice][typeChoice], noDrinksChosen,  chosenDrink,  drinks,  drinkPrice, info, &cutlery, &state,choice,&ordersigned);
            }
                getchar();
                break;
        }
    }
}
void inputLogIn (char username[], char password[]){
    printf("---Username");
    gets(username);
    printf("---Password");
    gets(password);
}
void chooseFood (int noFoods, char **foods){

    printf("Please choose the food you feel like eating today:\n");
    for (int i = 0; i < noFoods; i++) {
        putchar('a' + i);
        printf(") %s \n", foods[i]);
    }
    printf("%c) Go back\n", 'a' + noFoods);
}
void chooseType (char foods[], int noTypes,  char **types, double price[]){
    printf("Please select a type of %s\n", foods);
    for (int i = 0; i<noTypes; i++) {
        putchar('a' + i);
        printf(") %s (%.2f)\n", types[i], price[i]);
    }
    printf("%c) Go back\n", 'a' + noTypes);
}
int getChoiceIndex(int noChoices, int *state){
    int choiceIndex;
    char choice=getchar();
    getchar();
    if(choice=='a'+noChoices) {
        (*state)--;
    }
    else {
        choiceIndex=choice-'a';
        (*state)++;
    }
    return choiceIndex;
}
void printDrinkChoices (int noDrinks, char **drinks, double drinkPrice[]){
    printf("Choose additional items (separated by comma)\n");
    for (int i = 0; i < noDrinks; i++) {
        putchar('a' + i);
        printf(") %s (%.2f)\n", drinks[i], drinkPrice[i]);
    }
    printf("%c) Go back\n", 'a' + noDrinks);
}

int chooseDrinks(int noDrinks, int chosenDrinks[], int *state){
    int noDrinksChosen=0;
    char choice=getchar();
    if (choice=='a'+ noDrinks){
        (*state)--;
    } else (*state)++;
    while(choice!='\n') {
        chosenDrinks[noDrinksChosen] = choice - 'a';
        noDrinksChosen++;
        char comma = getchar();
        if (comma == '\n') {
            break;
        }
        choice = getchar();
    }
    return noDrinksChosen;
}
void readAdditionalInfo (char str[], int *state) {
    printf("Any additional info?\n");
    fgets(str, 100, stdin);
    (*state)++;
}
void chooseCutlery (int *cutlery, int *state, char choice){
    printf("Do you want cutlery?\n");
    printf("a) Yes\n"
           "b) No, thanks!\n"
           "c) Go back\n");
    choice = getchar();
    if (choice == 'a' + 2) {
        (*state)--;

    }else{ if(choice == 'a') {
            (*cutlery) =1;
            (*state)++;

        }else {
            (*cutlery) = 0;
            (*state)++;

        }}
    getchar();
}

void displayOrder(char type[], double price, int noDrinksChosen, int chosenDrink[], char drinks[], double drinkPrice[], char str[],int *cutlery,int *state,char choice, int *ordersigned) {
    printf("This is your order:\n""-------------------\n");
    printf("Food items:\n""---%s (%.2f)\n", type, price);
    double totalDrinkPrice = 0;
    for(int i=0;i<noDrinksChosen;i++) {
        totalDrinkPrice+= drinkPrice[chosenDrink[i]];}
    if(noDrinksChosen!=0){
        for(int i=0;i<noDrinksChosen;i++) {
            printf("--%s (%.2f)\n", drinks[chosenDrink[i]], drinkPrice[chosenDrink[i]]);}}
    printf("Cutlery:");
    if ((*cutlery) == 1) {
        printf(" yes\n");
    }    else {
        printf(" no\n");}
    printf("Additional info:\n");
    printf("%s", str);
    printf("Payment amount: %.2f\n", price + totalDrinkPrice);
    printf("a) Sign\n");
    printf("b) Go back\n");
    choice = getchar();
    if (choice == 'a') {
        (*ordersigned) = 1;
    } else {
        (*state)--;}
};

//use reformatLine to remove each item from the line and to remove additional characters such as spaces brackets or dashes

void reformatLine(char *token, char itemLength[MAX_LINE], int noCharactersToRemove ){
    for(int i=0; i<strlen(itemLength)+ noCharactersToRemove;i++)
        for(int j=0; j<strlen(token);j++)
            token[j]=token[j+1];
}
char *extractFoods(char *token, char line[MAX_LINE]){
    char *item;
    item=strtok(line," ");
    reformatLine(token, item, 1);
    return item;
}
char *extractTypes(char *token, char line[MAX_LINE]) {
    char *delim, *item, *result;
    delim = strtok(line, ")");
    item = strtok(delim, "-");
    char bracket='(';
    result=strchr(item,bracket);
    reformatLine(result," ",0);
    reformatLine(token,item,2);
    return result;
}
int extractNoTypes(char *token, char line[MAX_LINE]){
    char *result;
    result=strtok(line, ":");
    reformatLine(token,result,0);
    return atoi(result);

}
double extractPrice(char  *token, char line[MAX_LINE]){
        char *delim;
        delim = strtok(line, ")");
        double result;
        result = atof(delim);
        reformatLine(token,delim,1);
        return result;
}


