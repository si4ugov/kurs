#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
#define true 1
#define false 0
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
#define SIZE_64 64
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
int main() {
    node* head = NULL;
    node* tmp;
    char command[SIZE_64];
    char file_name[SIZE_64];
    char ch;
    int num_of_elem;

    printf("|shop|> Enter \"help\" for more info...\n");

    // ����������� ���� ��� ��������� � ������
    // ������� ��������
    while (true) {
        printf("|shop|> ");
        scanf("%s", command);

        // ������� ������
        if (!strcmp(command, "help")) {
            printf("This is list of command in program...\n");
            // ���� ������
            printf("\thelp - command that display list of commands;\n");
            printf("\tadd_product - add product to database;\n");
            printf("\tdisplay_database - display table of database;\n");
            printf("\tdelete_product - delete product from database;\n");
            printf("\tedit_product - edit info of product (need num of product in database);\n");
            printf("\tcreate_min_shop_cart - create minimal shopping cart;\n");
            printf("\tsave_data - save database in file;\n");
            printf("\tread_data - read database from file;\n");
            printf("\texit - exit from program;\n");
            printf("\tcls - clearing the console;\n");

            printf("\n| CATEGORIES |\n");
            printf("\tFOOD\n");
            printf("\tHOME\n");
            printf("\tHEALTH\n");
            printf("\tELECTRONICS\n");
            printf("\tHOBBIES\n");
            printf("\tCLOTHES\n");
            printf("\tSERVICES\n");
            printf("\tREST\n");
            printf("\tUNKNOWN\n");

            continue;
        }

        // �������� ����� � ������
        if (!strcmp(command, "add_product")) {
            // �������� ���������� � �������������� ����
            printf("\t\n");
            printf("\tMEAT\n");
            printf("\tVEGETABLES\n");
            printf("\tCEREALS\n");
            printf("\tWATER\n");
            printf("\tFRUITS\n");
            printf("\tANOTHER\n");
            tmp = create_node();
            push_node(&head, tmp);
            edit_node(tmp);

            if(head->next != NULL)
                sort_list(head);

            continue;
        }

        // ����������� ������ �� �������� ��� �� ���������
        if (!strcmp(command, "display_database")) {
            if (head != NULL) {
                sort_list(head);
                printf("|shop|> types:\ta - althabet\n\t\tc - category\n");
                printf("\tchoose type of table = ");
                // ������ _flushall()
                while (fgetc(stdin) != '\n');
                scanf("%c", &ch);

                if (ch == 'a')
                    display_data(head);
                else if (ch == 'c')
                    display_data_category(head);
                else
                    printf("|shop|> ERROR_TYPE_TABLE...\n");
            }
            else
                printf("|shop|> empty list...\n");

            continue;
        }

        // �������������� ������ � ������
        if (!strcmp(command, "edit_product")) {
            // �������������� ����
            printf("|shop|> enter num of elem in list...\n\tnum = ");
            scanf("%d", &num_of_elem);

            // ��������� ����
            tmp = get_node_by_num( head, num_of_elem);
            if(tmp != NULL)
                edit_node(tmp);

            sort_list(head);
            display_data(head);

            continue;
        }

        // �������� �������� �� ������
        if (!strcmp( command, "delete_product")) {
            printf("|shop|> enter num of elem in list that need remove...\n\tnum = ");
            scanf("%d", &num_of_elem);

            // ��������� ����
            tmp = get_node_by_num(head, num_of_elem);
            if (tmp != NULL)
            {
                delete_product(&head, tmp);
                display_data(head);
            }
              

            continue;
        }

        if (!strcmp(command, "create_min_shop_cart")) {
            create_min_shop_cart(head);

            continue;
        }

        // ��������� ������ � �������� ����
        if (!strcmp( command, "save_data")) {
            printf("\tfile_name = ");
            scanf( "%s", file_name);

            sort_list(head);
            save_list( file_name, head);

            continue;
        }

        // ������ ������ �� ��������� �����
        if (!strcmp(command, "read_data")) {
            while (head != NULL) {
                tmp = head;
                pop_node(tmp, &head);
                if(tmp != NULL)
                    free(tmp);
            }

            printf("\tfile_name = ");
            scanf("%s", file_name);

            read_db(file_name, &head);
            display_data(head);

            continue;
        }


        // ������� ��� ������
        if (!strcmp(command, "exit")) {
            printf("Exit from program...");

            // ��������� ������� �����
            _flushall();
            getchar();
            break;
        }

        // cls - �������� �������
        if (!strcmp(command, "cls")) {
            system("cls");

            continue;
        }

        if (true)
            printf("|shop|> ERROR_UNKMOWN_COMMAND...\n");
    }

    return 0;
}