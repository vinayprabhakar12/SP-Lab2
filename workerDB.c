#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "readfile.h"

#define MAXNAME 64
#define NULL ((void *)0)

extern FILE *file; // File variable used to read the data from txt file

//Definition of the employee structure
struct employee {
    int id;
    char firstName[MAXNAME];
    char lastName[MAXNAME];
    int salary;
};

//Function to read firstname from user
int read_firstName(char (*firstName)[64]){
    char test[128];
    bool valid = false;
    printf("Enter the first name of the employee: ");
    scanf("%s", test);
    do{
        if(strlen(test)<63){
            strcpy(*firstName,test);
            valid = true;
        }
        else {
            printf("Enter a valid first name with only 63 characters: ");
            scanf("%s", test);
        }  
    } while(valid != true);
    
}

//Function to read lastname from user
int read_lastName(char (*lastName)[64]){
    char test[128];
    bool valid = false;
    printf("Enter the last name of the employee: ");
    scanf("%s", test);
    do{
        if(strlen(test)<63){
            strcpy(*lastName,test);
            valid = true;
        }
        else {
            printf("Enter a valid last name with only 63 characters: ");
            scanf("%s", test);
        }  
    } while(valid != true);
}

//Function to read salary from user
int read_salary(int* salary){
    bool valid = false;
    printf("Enter employee's salary (30,000 to 1,50,000): ");
    scanf("%d", salary);
    do{
        if(*salary>=30000 && *salary<=150000){
            valid = true;
        }
        else {
            printf("Enter a valid valid salary in the range 30,000 to 1,50,000 (inclusive): ");
            scanf("%d", salary);
        }
    } while(valid != true);
}

//Function to print each employee
void printEmployee(struct employee *empPtr){
    printf("%-10s %-18s $%7d %10d\n", (*empPtr).firstName, (*empPtr).lastName, (*empPtr).salary, (*empPtr).id);
}

//Function to print the structure array
void printDB(struct employee (*empList)[1024], int *numEmployees){
    printf("%-10s %-18s  %7s %10s\n", "NAME", "", "SALARY", "ID");
    printf("-------------------------------------------------\n");
    for(int i=0; i<*numEmployees;i++){
        printEmployee(&(*empList)[i]);
    }
    printf("-------------------------------------------------\n");
    printf("Number of Employees = %d\n\n", *numEmployees);
}

//Funciton to sort the strucutre based on ID
void sortDB(struct employee (*empList)[1024], int *numEmployees){   
    int i, j;
    int swapped;
    struct employee temp;
    for (i = 0; i < *numEmployees - 1; i++) {
        swapped = 0;
        for (j = 0; j < *numEmployees - i - 1; j++) {
            if ((*empList)[j].id > (*empList)[j + 1].id) {
                temp = (*empList)[j];
                (*empList)[j] = (*empList)[j + 1];
                (*empList)[j+1] = temp;
                swapped = 1;
            }
        }
    }
}

//Function to lookup by ID
int lookUpID(struct employee (*empList)[1024], int *numEmployees){
    printf("Enter a 6 digit employee id: ");
    int searchID = 999999;
    fflush(stdout);
    scanf("%d", &searchID);
    printf("The search ID is : %d\n", searchID);
    int found=0;
    int i=0;
    while(!found && i<*numEmployees){ 
        if((*empList)[i].id == searchID){
            found = 1;
            printf("%-10s %-18s  %7s %10s\n", "NAME", "", "SALARY", "ID");
            printf("-------------------------------------------------\n");
            printEmployee(&(*empList)[i]);
            printf("-------------------------------------------------\n\n");
        }
        else
            i++;
    }

    //IF no matching iD is found
    if(!found){
        i = -1;
        printf("Employee with that ID not found !\n\n");
    }

    //return index to use in allLastName function
    return i;
}

//Function to lookup by lastname
void lookUpLastName(struct employee (*empList)[1024], int *numEmployees){
    char searchName[64];
    printf("Enter Employee's last name (no extra spaces & case insensitive): ");
    fflush(stdout);
    scanf("%s", searchName);
    printf("The search Last Name is : %s\n", searchName);
    int found=0;
    int i=0;
    while(!found && i<*numEmployees){
        if(stricmp((*empList)[i].lastName,searchName)==0){
            found = 1;
            printf("%-10s %-18s  %7s %10s\n", "NAME", "", "SALARY", "ID");
            printf("-------------------------------------------------\n");
            printEmployee(&(*empList)[i]);
            printf("-------------------------------------------------\n\n");
        }
        i++;
    }
    if(!found){
        printf("Employee with that last name not found !\n\n");
    }
}

//Funciton to take in details of a new employee from user 
void enterEmp(struct employee *emp){
    read_firstName(&(*emp).firstName);
    read_lastName(&(*emp).lastName);
    int ret = -1;
    while(ret!=0)
        ret = read_salary(&(*emp).salary);
}

//Function to remove an employee
void removeEmp(struct employee (*empList)[1024], int *numEmployees){
    printf("Enter the following details the employee to be removed");
    int i = lookUpID(empList, numEmployees);
    if(i>=0){
        printf("Do you want to remove the above employee ?\n");
        printf("Enter 1 for yes, 0 for no: ");
        fflush(stdout);
        int confirm = 0;
        scanf("%d", &confirm);
        if(confirm){
            for(int j = i; j < *numEmployees -1; j++){
                (*empList)[j] = (*empList)[j+1];
            }
            strcpy(((*empList)[*numEmployees-1]).firstName, "------" );
            strcpy((*empList)[*numEmployees-1].lastName, "------");
            (*empList)[*numEmployees-1].id = 0;
            (*empList)[*numEmployees-1].salary = 0;
            printf("Employee removed...\n\n");
            (*numEmployees)--;
        }
        else
            printf("Employee not removed...\n\n");
    }
}

//Function to update details of an employee
void updateEmp(struct employee (*empList)[1024], int *numEmployees){
    printf("Enter the following details the employee to be removed\n");
    int i = lookUpID(empList, numEmployees);
    printf("%d\n",i);
    int updateChoice = 0;
    int counter = 0;
    while((updateChoice<1 || updateChoice>5) && i>=0){
        printf("(1) First Name\n");
        printf("(2) Last Name\n");
        printf("(3) Salary Name\n");
        printf("(4) ID\n");
        printf("(5) All\n");
        printf("Enter your update choice: ");
        fflush(stdout);
        scanf("%d", &updateChoice);
        printf("Your update choice is : %d\n\n", updateChoice);
        
        //Update first name
        if(updateChoice == 1){
            printf("Update as per the following...\n");
            read_firstName(&((*empList)[i].firstName));
            printf("Employee first name updated successfully\n\n");
        }

        //Update last name
        else if(updateChoice == 2){
            printf("Update as per the following...\n");
            read_lastName(&((*empList)[i].lastName));
            printf("Employee last name updated successfully\n\n");
        }

        //Update salary
        else if(updateChoice == 3){
            printf("Update as per the following...\n");
            read_salary(&((*empList)[i].salary));
            printf("Employee salary updated successfully\n\n");
        }

        //Update ID
        else if(updateChoice == 4){
            printf("Update as per the following...\n");
            printf("Enter the new ID: ");
            scanf("%d", &((*empList)[i].id));
            sortDB(empList, numEmployees);
            printf("Employee ID updated successfully\n\n");
        }

        //Update all fields
        else if(updateChoice == 5){
            printf("Update as per the following...\n");
            read_firstName(&((*empList)[i].firstName));
            read_lastName(&((*empList)[i].lastName));
            read_salary(&((*empList)[i].salary));
            printf("Enter the new ID: ");
            scanf("%d", &((*empList)[i].id));
            sortDB(empList, numEmployees);
            printf("Employee details updated successfully\n\n");
        }

        //Choice validation
        else{
            printf("Enter a valid choice ---\n");
        }
    }
}

//Function to print the details of 'm' employees with highest salary 
void mSalary(struct employee (*empList)[1024], int *numEmployees){
    struct employee salaryList[1024];
    memcpy(salaryList, *empList, sizeof(*empList));
    int i, j;
    int swapped;
    struct employee temp;
    //Sort as per salary (highest to lowest)
    for (i = 0; i < *numEmployees - 1; i++) {
        swapped = 0;
        for (j = 0; j < *numEmployees - i - 1; j++) {
            if (salaryList[j].salary < salaryList[j + 1].salary) {
                temp = salaryList[j];
                salaryList[j] = salaryList[j + 1];
                salaryList[j+1] = temp;
                swapped = 1;
            }
        }
    }
    int m;
    printf("Enter the number of employees with highest salaries to be printed: ");
    fflush(stdout);
    scanf("%d", &m);
    printf("The details of %d Employees with the highest salaries:\n", m);
    printf("%-10s %-18s  %7s %10s\n", "NAME", "", "SALARY", "ID");
    printf("-------------------------------------------------\n");
    for(i=0; i<m; i++){
        printEmployee(&salaryList[i]);
    }
    printf("-------------------------------------------------\n");
    printf("\n\n");
}

//Function to search for all matching employees with a last name
void allLastName(struct employee (*empList)[1024], int *numEmployees){
    char searchName[64];
    printf("Enter the Last Name (case insensitive) : ");
    fflush(stdout);
    scanf("%s", searchName);
    printf("The search Last Name is : %s\n", searchName);
    int found=0;
    int i=0;
    int lastNameIndex[1024];
    int lastNamefrequency = 0;
    while(i<*numEmployees){
        if(stricmp((*empList)[i].lastName,searchName)==0){
            found = 1;
            lastNameIndex[lastNamefrequency] = i;
            lastNamefrequency++;
        }
        i++;
    }

    //If there is atleast 1 employee with the matching last name
    if(found){
        printf("%-10s %-18s  %7s %10s\n", "NAME", "", "SALARY", "ID");
        printf("-------------------------------------------------\n");
        int j;
        for(i=0; i<lastNamefrequency; i++){
            printEmployee(&(*empList)[(lastNameIndex[i])]);
        }
        printf("-------------------------------------------------\n\n");
    }

    //If there is no match found
    else{
        printf("Employee with that last name not found !\n\n");
    }   
}

//Main Function to run the program
int main(int argc, char **argv) {

    char *filename = argv[1]; //Assinged the string passed in commandline to the filename to be opened

    struct employee empList[1024], temp;
    int numEmployees = 0;
    int i = 0;

    if (open_file(filename) == 0)
    {
        char buffer[135];
        int ret;
        while (fgets(buffer, sizeof(buffer), file))
        {
            ret = read_int(buffer, 1, &empList[numEmployees].id);
            ret = read_int(buffer, 2, &empList[numEmployees].salary);
            ret = read_string(buffer, 1, empList[numEmployees].firstName);
            ret = read_string(buffer, 2, empList[numEmployees].lastName);
            numEmployees++;
        }
        
        if (feof(file)) // hit end of file
        {
            close_file(file);
        }
    }
    else{
        printf("Error! Re-run the program with a proper filename");
        return -1;
    }

   
    // Sort the structure 
    sortDB(&empList, &numEmployees);

    int choice;

    //Loop for main menu with choices for the user
    while(choice!=5){
        printf("Employee Database Menu:\n");
        printf("--------------------------------\n");
        printf("    (1) Print the Database\n");
        printf("    (2) Lookup by ID\n");
        printf("    (3) Lookup by Last Name\n");
        printf("    (4) Add an Employee\n");
        printf("    (5) Quit\n");
        printf("    (6) Remove an Employee\n");
        printf("    (7) Update Employee Information\n");
        printf("    (8) Print the 'M' employees with the highest salaries\n");
        printf("    (9) Find all employees with matching Last Name\n");
        printf("--------------------------------\n");
        printf("Enter your main menu choice : ");
        fflush(stdout);
        scanf("%d", &choice);
        printf("Your choice is : %d\n\n", choice);

        //Printing entire database
        if(choice == 1){
            printDB(&empList, &numEmployees);
        }

        //Lookup employee by id
        else if(choice == 2){
            lookUpID(&empList, &numEmployees);
        }

        //Lookup employee by last name
        else if(choice == 3){
            lookUpLastName(&empList, &numEmployees);
        }

        //Add a new employee
        else if(choice == 4){
            int confirm = 0;
            struct employee userEmp;
            enterEmp(&userEmp); 
            printf("Do you want to add the following employee to the DB?\n %20s, %s, Salary: %d\n", userEmp.firstName, userEmp.lastName, userEmp.salary);
            printf("Enter 1 for YES, 0 for NO: ");
            fflush(stdout);
            scanf("%d", &confirm);
            if(confirm){
                userEmp.id = empList[numEmployees-1].id + 1;
                empList[numEmployees] = userEmp;
                numEmployees++;
                printf("New employee added!\n");
            }
            printf("\n\n");
        }  

        //Exit choice for the user
        else if(choice == 5){
            printf("Goodbye!");
        }

        else if(choice == 6){
            removeEmp(&empList, &numEmployees);
        }

        else if(choice == 7){
            updateEmp(&empList, &numEmployees);
        }

        else if(choice == 8){
            mSalary(&empList, &numEmployees);
        }

        else if(choice == 9){
            allLastName(&empList, &numEmployees);
        }

        //Reprompt the user if wrong choice entered
        else{
            printf("Hey, %d is not between 1 and 9, try again...\n\n", choice);
        }
    }
    return 0;
}