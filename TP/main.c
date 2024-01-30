#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100

typedef struct {
    int code;
    char lastName[50];
    char firstName[50];
    char birthDate[20];
    char jobTitle[50];
    float salary;
} Employee;

void loadEmployees(Employee employees[], int *numEmployees) {
    FILE *file = fopen("employees.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%d %s %s %s %s %f",
                  &employees[*numEmployees].code,
                  employees[*numEmployees].lastName,
                  employees[*numEmployees].firstName,
                  employees[*numEmployees].birthDate,
                  employees[*numEmployees].jobTitle,
                  &employees[*numEmployees].salary) == 6) {
        (*numEmployees)++;
    }

    fclose(file);
}

void updateEmployeesFile(const Employee employees[], int numEmployees) {
    FILE *file = fopen("employees.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numEmployees; i++) {
        fprintf(file, "%d %s %s %s %s %.2f\n",
                employees[i].code,
                employees[i].lastName,
                employees[i].firstName,
                employees[i].birthDate,
                employees[i].jobTitle,
                employees[i].salary);
    }

    fclose(file);
}

void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Ajouter un nouvel employe\n");
    printf("2. Supprimer un employe existant\n");
    printf("3. Rechercher un employe\n");
    printf("4. Mettre a jour les informations d'un employe\n");
    printf("5. Enregistrer les informations dans le fichier\n");
    printf("6. Quitter\n");
    printf("Choix : ");
}


void addEmployee(Employee employees[], int *numEmployees) {
    printf("Entrez le nom : ");
    scanf("%s", employees[*numEmployees].lastName);

    printf("Entrez le prenom : ");
    scanf("%s", employees[*numEmployees].firstName);

    printf("Entrez la date de naissance : ");
    scanf("%s", employees[*numEmployees].birthDate);

    printf("Entrez le titre de poste : ");
    scanf("%s", employees[*numEmployees].jobTitle);

    printf("Entrez le salaire : ");
    scanf("%f", &employees[*numEmployees].salary);

    employees[*numEmployees].code = (*numEmployees) + 1;  // Assigning a unique code
    (*numEmployees)++;
    printf("Employe ajoute avec succes.\n");
}

void deleteEmployee(Employee employees[], int *numEmployees) {
    int code;
    printf("Entrez le code de l'employe à supprimer : ");
    scanf("%d", &code);

    int index = -1;
    for (int i = 0; i < *numEmployees; i++) {
        if (employees[i].code == code) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        printf("Etes-vous sur de vouloir supprimer l'employe %s %s ? (1 pour Oui, 0 pour Non): ",
               employees[index].firstName, employees[index].lastName);
        int confirm;
        scanf("%d", &confirm);

        if (confirm == 1) {
            for (int i = index; i < *numEmployees - 1; i++) {
                employees[i] = employees[i + 1];
            }
            (*numEmployees)--;
            printf("Employe supprime avec succes.\n");
        } else {
            printf("Suppression annulee.\n");
        }
    } else {
        printf("Aucun employe trouve avec le code %d.\n", code);
    }
}

void searchEmployee(const Employee employees[], int numEmployees) {
    int choice;
    printf("Recherche par :\n");
    printf("1. Code\n");
    printf("2. Nom\n");
    printf("3. Prenom\n");
    printf("Choix : ");
    scanf("%d", &choice);

    int found = 0;

    switch (choice) {
        case 1: {
            int code;
            printf("Entrez le code de l'employe : ");
            scanf("%d", &code);

            for (int i = 0; i < numEmployees; i++) {
                if (employees[i].code == code) {
                    printf("Employe trouve :\n");
                    printf("Code : %d\n", employees[i].code);
                    printf("Nom : %s\n", employees[i].lastName);
                    printf("Prenom : %s\n", employees[i].firstName);
                    printf("Date de naissance : %s\n", employees[i].birthDate);
                    printf("Titre de poste : %s\n", employees[i].jobTitle);
                    printf("Salaire : %.2f\n", employees[i].salary);
                    found = 1;
                    break;
                }
            }
            break;
        }
        case 2: {
            char lastName[50];
            printf("Entrez le nom de l'employe : ");
            scanf("%s", lastName);

            for (int i = 0; i < numEmployees; i++) {
                if (strcmp(employees[i].lastName, lastName) == 0) {
                    printf("Employé trouve :\n");
                    printf("Code : %d\n", employees[i].code);
                    printf("Nom : %s\n", employees[i].lastName);
                    printf("Prenom : %s\n", employees[i].firstName);
                    printf("Date de naissance : %s\n", employees[i].birthDate);
                    printf("Titre de poste : %s\n", employees[i].jobTitle);
                    printf("Salaire : %.2f\n", employees[i].salary);
                    found = 1;
                    break;
                }
            }
            break;
        }
        case 3: {
            char firstName[50];
            printf("Entrez le prenom de l'employe : ");
            scanf("%s", firstName);

            for (int i = 0; i < numEmployees; i++) {
                if (strcmp(employees[i].firstName, firstName) == 0) {
                    printf("Employe trouve :\n");
                    printf("Code : %d\n", employees[i].code);
                    printf("Nom : %s\n", employees[i].lastName);
                    printf("Prenom : %s\n", employees[i].firstName);
                    printf("Date de naissance : %s\n", employees[i].birthDate);
                    printf("Titre de poste : %s\n", employees[i].jobTitle);
                    printf("Salaire : %.2f\n", employees[i].salary);
                    found = 1;
                    break;
                }
            }
            break;
        }
        default:
            printf("Choix invalide.\n");
    }

    if (!found) {
        printf("Aucun employe trouve.\n");
    }
}

void updateEmployee(Employee employees[], int numEmployees) {
    int code;
    printf("Entrez le code de l'employe à mettre a jour : ");
    scanf("%d", &code);

    int index = -1;
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].code == code) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        printf("Mettre a jour le poste (actuel : %s) : ", employees[index].jobTitle);
        scanf("%s", employees[index].jobTitle);

        printf("Mettre a jour le salaire (actuel : %.2f) : ", employees[index].salary);
        scanf("%f", &employees[index].salary);

        printf("Informations mises a jour avec succes.\n");
    } else {
        printf("Aucun employe trouve avec le code %d.\n", code);
    }
}

void saveAndExit(const Employee employees[], int numEmployees) {
    updateEmployeesFile(employees, numEmployees);
    printf("Modifications enregistrees. Au revoir!\n");
}

int main() {
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    int choice;

    loadEmployees(employees, &numEmployees);

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &numEmployees);
                break;
            case 2:
                deleteEmployee(employees, &numEmployees);
                break;
            case 3:
                searchEmployee(employees, numEmployees);
                break;
            case 4:
                updateEmployee(employees, numEmployees);
                break;
            case 5:
                updateEmployeesFile(employees, numEmployees);
                break;
            case 6:
                saveAndExit(employees, numEmployees);
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choice != 6);

    return 0;
}

