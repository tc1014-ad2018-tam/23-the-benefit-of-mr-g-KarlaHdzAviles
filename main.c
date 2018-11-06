/*This program sells tickets to the Benefit of Mr. G.
 * The venue has 400 rows, 50 seats on the side, 100 on the center and other 50 in the other side.
 * this program also stores the purchase data, as well as gives a feedback of all purchases,
 * places occupied by area and in total, etc.
 *
 * Author: Karla Alexandra Hernandez Aviles
 * Email: A01411843@itesm.mx
 * Date: 04/11/18
 */
//Liberias que el programa usa
#include <stdio.h>
#include <string.h> //strcpy.
#include <stdbool.h> //bool library

//Menu de las zonas del show
void Zones() {
    printf("Zones of the venue:\n"
           "1. VIP: $100\n"
           "2. Platinum: $85\n"
           "3. Gold: $70\n"
           "4. Silver: $55\n"
           "5. Green: $45\n"
           "6. Yellow: $40\n"
           "7. Red: $30\n"
           "8. Sky Blue: $50\n"
           "9. Navy Blue: $35\n"
           "10. Deep Blue: $20\n");
}
//Struct para los asientos
struct Seats {
    char name[100];
    bool taken;
    int price;
    int paymethod;   //metodo de pago
}
seatings [400][200];

//Funcion para el file
void SFile(FILE *fd) {
    fd = fopen("TheBenefitofMrG.txt", "wb");

    // por cada asiento los valores son comparados
    for (int k = 0; k < 400; k++) {
        for (int a = 0; a < 200; a++) {
            strcpy(seatings[k][a].name, "");
            seatings[k][a].paymethod = 0;
            seatings[k][a].taken = false;

            // los precios son de acuerdo al lugar que el usuario seleccione

            if (a < 50 || a > 149) {

                if (k < 100) {
                    seatings[k][a].price = 50;
                } else if (k < 300) {
                    seatings[k][a].price = 35;
                } else {
                    seatings[k][a].price = 20;
                }

            } else {

                if (k < 5) {
                    seatings[k][a].price = 100;
                } else if (k < 10) {
                    seatings[k][a].price = 85;
                } else if (k < 50) {
                    seatings[k][a].price = 70;
                } else if (k < 100) {
                    seatings[k][a].price = 55;
                } else if (k < 250) {
                    seatings[k][a].price = 45;
                } else if (k < 350) {
                    seatings[k][a].price = 40;
                } else {
                    seatings[k][a].price = 30;
                }

            }
        }
    }
    // el lugar de asiento se guarda dentro del archivo
    fwrite(&seatings, sizeof(seatings), 1, fd);

}
//Funcion para la suma de todos las ventas acumuladas
int SoldSum(int fstrow, int lstrow, int fstseat, int lstseat, int sold) {
    int count = 0;
    int sales = 0;
    for (int k = fstrow - 1; k < lstrow; k++) {
        for (int a = fstseat - 1; a < lstseat; a++) {
            if (seatings[k][a].taken) {
                count++;
                sales += seatings[k][a].price;
            }
        }
    }

    if (sold) {
        return count;
    }

    return sales;

}
//Funcion para deliverar en que zona se debe sumar, o en este caso las zonas que se requiera saber cuanto vendio
int ZoneSold(int zone, int sold) {
    int count = 0;
    int initialrow;
    int finalrow;

    //Switch para cada caso, o cada zona con su fila inicial y final
    switch (zone) {
        case 1:
            initialrow = 1;
            finalrow = 5;
            break;
        case 2:
            initialrow = 6;
            finalrow = 10;
            break;
        case 3:
            initialrow = 11;
            finalrow = 50;
            break;
        case 4:
            initialrow = 51;
            finalrow = 100;
            break;
        case 5:
            initialrow = 101;
            finalrow = 250;
            break;
        case 6:
            initialrow = 251;
            finalrow = 350;
            break;
        case 7:
            initialrow = 351;
            finalrow = 400;
            break;
        case 8:
            initialrow = 1;
            finalrow = 100;
            break;
        case 9:
            initialrow = 101;
            finalrow = 300;
            break;
        case 10:
            initialrow = 301;
            finalrow = 400;
            break;
        default:
            initialrow = 1;
            finalrow = 200;
            break;
    }
    //En caso de que la zona sea en opciones menores o igual a 7
    if (zone >= 7) {
        count += SoldSum(initialrow, finalrow, 1, 50, sold);
        count += SoldSum(initialrow, finalrow, 151, 200, sold);
        //En caso de que las zonas sean en sky blue,navy blue,etc.
    } else {
        count += SoldSum(initialrow, finalrow, 51, 150, sold);
    }

    return count;
}

//Funcion para guardar los datos en el file
void SaveDataw(FILE *fd) {
    fd = fopen("TheBenefitofMrG.txt", "wb");
    fwrite(&seatings, sizeof(seatings), 1, fd);
    fclose(fd);
}

int main (){
    //Declaracion de Variables

    int options;
    int option;
    int row;
    int initialrow;
    int finalrow;
    int sit;
    int paymethod;//metodo de pago
    int zone = 0;
    int count = 0;
    char name[100];
    int confirm;
    float rowsize;

    FILE *fd;

    //Opens file
    fd = fopen("TheBenefitofMrG.txt", "rb");

    // If the file doesnt exists we initialize it.
    if (fd == NULL) {
        SFile(fd);
    } else {
        // If the file exists the data will be stored in the program
        while (fread(&seatings, sizeof(seatings), 1, fd));
    }
    // The file is closed.
    fclose(fd);

    printf("The benefit of Mr.G");
    fprintf(fd,"REPORT OF THE SHOW OF MR.G");

    do {
        printf("\nWelcome to the venue. What would you like to do?\n"
               "Select an option:\n"
               "1. Buy a ticket.\n"
               "2. Save sells data.\n"
               "3. Reports.\n"
               "4. Exit.\n");
        scanf("%i", &options);

        //En caso de que quiera comprar un boleto
        if (options == 1) {
            {
                Zones();
                printf("Thanks for buy a ticket. Please select the zone where you want to sit:\n");
                scanf("%d", &option);

                // Por cada zona, se establecio el numero de filas que abarca
                switch (option) {
                    case 1:
                        initialrow = 1;
                        finalrow = 5;
                        break;
                    case 2:
                        initialrow = 6;
                        finalrow = 10;
                        break;
                    case 3:
                        initialrow = 11;
                        finalrow = 50;
                        break;
                    case 4:
                        initialrow = 51;
                        finalrow = 100;
                        break;
                    case 5:
                        initialrow = 101;
                        finalrow = 250;
                        break;
                    case 6:
                        initialrow = 251;
                        finalrow = 350;
                        break;
                    case 7:
                        initialrow = 351;
                        finalrow = 400;
                        break;
                    case 8:
                        initialrow = 1;
                        finalrow = 100;
                        break;
                    case 9:
                        initialrow = 101;
                        finalrow = 300;
                        break;
                    case 10:
                        initialrow = 301;
                        finalrow = 400;
                        break;
                    default:
                        printf("Invalid zone");
                }

                //Despues de seleccionar la zona, se le pide al usuario que seleccione una columna
                do {
                    printf("Select a row between %d-%d", initialrow, finalrow);
                    scanf("%d", &row);

                } while (row < initialrow || row > finalrow);

                //En caso de que seleccione zonas como sky blue, blue navy, etc
                if (option >= 7) {
                    do {
                        printf("Select a sit between 1-50 or 151-200");
                        scanf("%d", &sit);
                    } while ((sit < 1 || sit > 50) && (sit < 151 || sit > 200));

                } else {
                    do {
                        printf("Select a sit between 51-150");
                        scanf("%d", &sit);
                    } while (sit < 51 || sit > 150);

                    //Se le pide al usuario seleccionar su metodo de pago
                    printf("Select one payment method,\n"
                           "1.Visa\n"
                           "2.MasterCard\n"
                           "3.American Express\n");
                    scanf("%d", &paymethod);

                    //Ya sea cualquiera de las 3 opciones, le pide al usuario su nombre
                    printf("Please, Enter your complete name:\n");
                    fflush(stdin);
                    fgets(name, sizeof(name), stdin);

                    //Le pide al usuario confirmar su compra
                    printf("Your'e shoure to confirm the purshase? Enter 0 to accept.\n");
                    scanf("%i", &confirm);

                    if (!confirm) {

                        //En caso de que el asiento este ocupado
                        if (seatings[row - 1][sit - 1].taken= false) {
                            printf("This sit is occupied.\n");

                        //Para confirmar la compra del usuario
                        } else {
                            seatings[row - 1][sit - 1].taken = true;
                            seatings[row - 1][sit - 1].paymethod = paymethod;
                            strcpy(seatings[row - 1][sit - 1].name, name);
                            printf("Purchase Transaction confirmed.\n");
                        }

                    } else{
                        printf("Returning to main menu.");
                    }
                }
            }

            //Para guardar los datos de compra
        } else if (options == 2);{
            fd = fopen("TheBenefitofMrG.txt", "wb");
            SaveDataw(fd);
            printf("Data saved.\n");

            //En caso de que se quiera saber el reporte del show, se despliega un menu para que el usuario seleccione
            //lo que quiere o necesita saber
        } if (options == 3){
            printf("Choose an option,\n"
                   "1. Total tickets sold.\n"
                   "2. Total tickets sold per zone.\n"
                   "3. Total income.\n"
                   "4. Total income per zone.\n"
                   "5. Occupation rate.\n"
                   "6. Occupation rate per zone.\n"
                   "7. Return to menu\n");
            scanf("%d", &option);

            //Tickets vendidos en total
            if(option==1){
                count = ZoneSold(zone, 1);
                printf("Total tickets sold: %d\n", count);

                //El total de tickets vendidos por zona
            } else if (option==2) {
                do {
                    Zones();
                    printf("Enter the zone you want to know about\n:");
                    scanf("%d", &zone);
                } while (zone < 1 || zone > 10);

                count = ZoneSold(zone, 1);
                printf("Total tickets sold in this zone: %d\n", count);

                //El total de compra por todos
            } else if (option==3) {
                count = ZoneSold(zone, 0);
                printf("Total purchase: $%d\n", count);

                //El total de compra por zona
            }else if (option==4) {
                do {
                    Zones();
                    printf("Enter the zone do you want to know about:\n");
                    scanf("%d", &zone);
                } while (zone < 1 || zone > 10);

                count = ZoneSold(zone, 0);
                printf("Total purchase in this zone: $%d\n", count);

                //Si se quiere saber cuantos asientos se ocuparon en total
            } else if(option==5) {
                // Count es igual al total de tickets y el porcentaje vendido en el show
                count = ZoneSold(zone, 1);
                printf("Occupation rate: %f%%\n", count * 100.00 / 80000);

                //En caso de que quiera saber cuantos se ocuparon por zona
            } else if (option==6){
                do {
                    Zones();
                    printf("Enter the zone you want info about:\n");
                    scanf("%d", &zone);
                } while (zone < 1 || zone > 10);
                count = ZoneSold(zone, 1);

                // el tamaño de las columnas esta establecido de acuerdo a las zonas
                switch (zone) {
                    case 1:
                    case 2:
                        rowsize = 5;
                        break;
                    case 3:
                        rowsize = 40;
                        break;
                    case 4:
                    case 6:
                    case 7:
                        rowsize = 50;
                        break;
                    case 8:
                    case 10:
                        rowsize = 100;
                        break;
                    case 5:
                        rowsize = 150;
                        break;
                    case 9:
                    default:
                        rowsize = 200;
                        break;
                }
                //Le entrega el esultado al usuario
                printf("Occupation rate in this zone is: %f%%\n", count / rowsize);
                break;

                //Si la opcion es exit, regresa al menu principal
            } else if (option==7){
                printf("Return to main menu\n");

            }

        }

        //Cierra el files
        fclose(fd);

        //En caso de que la opcion sea exit, se termina el programa
    } while (options != 4);


    return 0;
}