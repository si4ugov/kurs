#define _CRT_SECURE_NO_WARNINGS
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
#define SIZE_NAME 64
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
enum EXTRA_FOOD_CATEGORY {
    MEAT = 1,
    VEGETABLES,
    CEREALS = 4,
    WATER = 8,
    FRUITS = 16,
    ANOTHER = 32
};
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
enum CATEGORIES {
    FOOD = 0,
    HOME,
    HEALTH,
    ELECTRONICS,
    HOBBIES,
    SERVICES,
    CLOTHES,
    REST,
    UNKNOWN
};
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
typedef struct node {
    char name_of_product[SIZE_NAME];
    int category;
    int price;
    char FOOD_category;

    struct node* prev;
    struct node* next;
} node;
///////////////////////////////////////////////////////////
//                    Создание узла                      //
///////////////////////////////////////////////////////////
node* create_node() {
    node* tmp;

    tmp = (node*)malloc(sizeof(node));

    if (tmp == NULL) {
        printf("|shop|> ERROR: can't create node...");
        exit(1);
    }

    tmp->next = NULL;
    tmp->prev = NULL;

    return tmp;
}
///////////////////////////////////////////////////////////
//                     Передача узла                     //
///////////////////////////////////////////////////////////
int push_node(node** head, node* elem) {
    node* tmp = *head;

    if (*head == NULL) {
        *head = elem;
        elem->prev = NULL;
    }
    else {
        while (tmp->next != NULL)
            tmp = tmp->next;

        elem->prev = tmp;
        tmp->next = elem;
    }

    elem->next = NULL;
    return 0;
}
///////////////////////////////////////////////////////////
//                    извлечение узла                    //
///////////////////////////////////////////////////////////
node* pop_node(node* elem, node **head) {
    // извлечь узел из списка
    // 1. в начале списка
    // 2. в середине списка
    // 3. в конце списка
    if (elem->prev == NULL) {
        *head = elem->next;

        if((*head) != NULL)
            (*head)->prev = NULL;
    }
    else if (elem->next == NULL) {
        (elem->prev)->next = NULL;
    }
    else {
        (elem->prev)->next = elem->next;
    }

    return elem;
}
///////////////////////////////////////////////////////////
//                Конвертироване регистра                // 
///////////////////////////////////////////////////////////
int convert_to_high_case(char *mass) {
    int i = 0;

    // нижний регистр преобразовываем в верхний
    while (mass[i] != '\0') {
        if (mass[i] > 96 && mass[i] < 123) // преобразовать в высокий регистр
            mass[i] = mass[i] - 32;
        i++;
    }

    return 0;
}
///////////////////////////////////////////////////////////
//                     Редактирование узла               //
///////////////////////////////////////////////////////////
int edit_node(node* elem) {
    char category[SIZE_NAME];
    category[0] = '\0';

    printf("|shop|> Enter data of product...\n");

    printf("\tname_of_product (string, size 64) = ");
    // стандартный ввод для корректной работы gets()
    while (fgetc(stdin) != '\n');
    gets(elem->name_of_product);

    printf("\tcategory = ");
    scanf("%s", category);

    convert_to_high_case(category);

    // провека введеной категории
    if (!strcmp(category, "FOOD"))
        elem->category = FOOD;
    else if (!strcmp(category, "HOME"))
        elem->category = HOME;
    else if (!strcmp(category, "HEALTH")) 
        elem->category = HEALTH;
    else if (!strcmp(category, "ELECTRONICS"))
        elem->category = ELECTRONICS; 
    else if (!strcmp(category, "HOBBIES"))
        elem->category = HOBBIES;
    else if (!strcmp(category, "SERVICES"))
        elem->category = SERVICES;
    else if (!strcmp(category, "CLOTHES"))
        elem->category = CLOTHES;
    else if (!strcmp(category, "REST"))
        elem->category = REST;
    else
        elem->category = UNKNOWN;

    elem->FOOD_category = 0;

    /*
        MEAT = 1,
        VEGETABLES,
        CEREALS = 4,
        WATER = 8,
        FRUITS = 16,
        ANOTHER = 32
    */


    if (elem->category == FOOD) {
        printf("\tFOOD category = ");
        scanf( "%s", category);

        convert_to_high_case( category);

        if (!strcmp(category, "MEAT"))
            elem->FOOD_category += MEAT;
        else if (!strcmp(category, "VEGETABLES"))
            elem->FOOD_category += VEGETABLES;
        else if (!strcmp(category, "CEREALS"))
            elem->FOOD_category += CEREALS;
        else if (!strcmp(category, "WATER"))
            elem->FOOD_category += WATER;
        else if (!strcmp(category, "FRUITS"))
            elem->FOOD_category += FRUITS;
        else 
            elem->FOOD_category += ANOTHER;
    }

    printf("\tprice (int) = ");
    scanf("%d", &(elem->price) );

    return 0;
}
///////////////////////////////////////////////////////////
//                    Удаление продукта                  //
///////////////////////////////////////////////////////////
void delete_product(node **head, node* elem) {
    //условия, которые помогают удалить элемент
    // 1. в конце 
    // 2. в середине 
    // 3. в начале
    if ((elem->next) == NULL && (elem->prev) != NULL) {
        (elem->prev)->next = NULL;
    }
    else if ((elem->next) != NULL && (elem->prev) != NULL) {
        (elem->prev)->next = (elem->next);
    }
    else if ((elem->next) != NULL && (elem->prev) == NULL) {
        *head = (elem->next);
    }

    free(elem);
}
///////////////////////////////////////////////////////////
// get_category_name(char* mass, int category) - func    // 
// функция сохранения массовое название в категории      //
///////////////////////////////////////////////////////////
void get_category_name(char* mass, int category) {
    // условия, которые помогают прочитать категорию продукта
    switch (category)
    {
    case FOOD:
        strcpy( mass, "FOOD");
        break;
    case HOME:
        strcpy( mass, "HOME");
        break;
    case HEALTH:
        strcpy( mass, "HEALTH");
        break;
    case ELECTRONICS:
        strcpy( mass, "ELECTRONICS");
        break;
    case HOBBIES:
        strcpy( mass, "HOBBIES");
        break;
    case SERVICES:
        strcpy(mass, "SERVICES");
        break;
    case CLOTHES:
        strcpy(mass, "CLOTHES");
        break;
    case REST:
        strcpy( mass, "REST");
        break;
    default:
        strcpy( mass, "UNKNOWN");
        break;
    }
}
///////////////////////////////////////////////////////////
//             Получени символа                          //
///////////////////////////////////////////////////////////
char find_first_char(node* tmp) {
    char ch = '\0';
    int j = 0;

    // получаем первый символ в назване продукта на англ
    while (tmp->name_of_product[j] != '\0') {
        ch = tmp->name_of_product[j];

        if ((ch > 64 && ch < 91) || (ch > 96 && ch < 123)) {
            ch = tmp->name_of_product[j];  // сохраняем первый символ из названия продукта
            break;
        }

        j++;
    }

    return ch;
}
///////////////////////////////////////////////////////////
//                     смена эл и узла                   //
///////////////////////////////////////////////////////////
void swap_data_nodes(node* elem) {
    // изменяем положение эл и узла (elem->next) 
    node tmp;

    // сохраняем данные node_1 в temp
    strcpy(tmp.name_of_product, elem->name_of_product);
    tmp.category = elem->category;
    tmp.price = elem->price;
    tmp.FOOD_category = elem->FOOD_category;

    //записываем в node_1 data из node_2
    strcpy(elem->name_of_product, (elem->next)->name_of_product);
    elem->category = (elem->next)->category;
    elem->price = (elem->next)->price;
    elem->FOOD_category = (elem->next)->FOOD_category;

    // переписываем из tmp в node_2
    strcpy((elem->next)->name_of_product, tmp.name_of_product);
    (elem->next)->category = tmp.category;
    (elem->next)->price = tmp.price;
    (elem->next)->FOOD_category = tmp.FOOD_category;
}
///////////////////////////////////////////////////////////
// sort_list() - функция сортировки списка по алфавиту   //
///////////////////////////////////////////////////////////
void sort_list(node *head) {
    if (head->next == NULL)
        return;

    node* tmp = head,
          *curr_elem = tmp;
    int cnt_elems = 0,
        i, j;
    char mass_1[] = { '\0', '\0' },
         mass_2[] = { '\0', '\0'};
    char flag = 1;

    if (head == NULL)
        return;

    // подсчет количества эл
    while (tmp != NULL) {
        cnt_elems++;        // подсчет количества эл
        tmp = tmp->next;
    }

    // сортируем  список пузырьком
    while (flag) {
        flag = 0;
        tmp = head;
        curr_elem = tmp;

        // меняем местами эл в списке
        for (i = 0; i < cnt_elems; ++i) {
            tmp = curr_elem;

            // первая буква текущего узла
            mass_1[0] = find_first_char(tmp);
            convert_to_high_case(mass_1);

            // первая буква второго узла
            mass_2[0] = find_first_char(tmp->next);
            convert_to_high_case(mass_2);

            if (mass_2[0] < mass_1[0] && (mass_1[0] != '\0' || mass_2[0] != '\0')) {
                flag = 1;
                swap_data_nodes(tmp);
            }

            curr_elem = curr_elem->next;
            if (curr_elem->next == NULL)
                break;
        }

        --cnt_elems;
    }
}
///////////////////////////////////////////////////////////
//                     вывод бд на экран                 //
///////////////////////////////////////////////////////////
void display_data(node* head) {
    char category[SIZE_NAME];
    int num_of_elem;
    node* tmp;

    // вывод заголовка табл
    printf("-------------------------------------------------------------------\n");
    printf("|  num  |     name_of_product     |     category     |    price   |\n");
    printf("-------------------------------------------------------------------\n");

    num_of_elem = 1;
    tmp = head;

    // отображение данных из списка
    while (tmp != NULL) {
        // вывод данных эл
        get_category_name(category, tmp->category);
        printf("| %5d | %23s | %16s | %10d |\n", num_of_elem, tmp->name_of_product, category, tmp->price);
        printf("-------------------------------------------------------------------\n");

        // переход к следующему эл
        num_of_elem++;
        tmp = tmp->next;
    }
}
///////////////////////////////////////////////////////////
//                   вывод категории                     //
///////////////////////////////////////////////////////////
void display_data_category(node* head) {
    char category[SIZE_NAME];
    int num_of_elem = 1,
        i;
    char flag;
    node* tmp;

    // циклы типов/категории
    for (i = 0; i <= UNKNOWN; ++i) {
        flag = 0;
        tmp = head;

        // поиск эл с текущей категорией
        while (tmp != NULL) {
            if (tmp->category == i) {
                flag = 1;
                break;
            }

            tmp = tmp->next;
        }           

        if (flag) {
            get_category_name(category, i);

            printf("------------------------------------------------\n");
            printf("|                 %14s               |\n", category);
            printf("------------------------------------------------\n");
            printf("|  num  |     name_of_product     |    price   |\n");
            printf("------------------------------------------------\n");
        }

        tmp = head;

        // отображение всех элементов текущей категории
        while (tmp != NULL) {
            // поиск следующего элемента категории
            while (tmp != NULL) {
                if (tmp->category == i)
                    break;
                tmp = tmp->next;
            }

            if (tmp != NULL) {
                // вывод данных эл          
                printf("| %5d | %23s | %10d |\n", num_of_elem, tmp->name_of_product, tmp->price);
                printf("------------------------------------------------\n");

                // переход к след эл
                num_of_elem++;
                tmp = tmp->next;
            }
            else
                break;
        }

        num_of_elem = 1;
    }

}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
node* get_node_by_num(node* head, int num_of_node) {
    int flag = 1;

    // поиск эл по номеру
    // кол эл начинающехся с 1
    while ((head->next) != NULL && flag < num_of_node) {
        head = head->next;
        flag++;
    }

    if (flag < num_of_node)
        return NULL;

    return head;
}
///////////////////////////////////////////////////////////
//                мин корзина                            //
///////////////////////////////////////////////////////////
void create_min_shop_cart(node* head) {
    node* food_list = NULL;
    node* min_cart = NULL;
    node* tmp , *tmp_1;
    char flag_products = 0;
    int cnt_category,
        num_of_food,
        i, j = 0;
    // искать все продукты из категории продуктов питания
    // и добовление в  food_list
    while (head != NULL) {
        if (head->category == FOOD) {
            tmp = create_node();
            push_node(&food_list, tmp);

            strcpy(tmp->name_of_product, head->name_of_product);
            tmp->category = head->category;
            tmp->price = head->price;
            tmp->FOOD_category = head->FOOD_category;
        }

        head = head->next;
    }

    srand(time(0));

    // отображение списка еды
    display_data(food_list);

    cnt_category = 0;
    tmp = food_list;

    // для кажой подкатегории поиск эл и выбор одного из них 
    for ( i = 1; i < 32; i *= 2) {
        // подсчет эл одной категории
        while (tmp != NULL) {
            if (((tmp->FOOD_category) == MEAT) && i == MEAT) {
                cnt_category++;
                flag_products = MEAT;
            }
            else if (((tmp->FOOD_category) == VEGETABLES) && i == VEGETABLES) {
                cnt_category++;
                flag_products = VEGETABLES;
            }
            else if (((tmp->FOOD_category) == CEREALS) && i == CEREALS) {
                cnt_category++;
                flag_products = CEREALS;
            }
            else if (((tmp->FOOD_category) == WATER) && i == WATER) {
                cnt_category++;
                flag_products = WATER;
            }
            else if (((tmp->FOOD_category) == FRUITS) && i == FRUITS) {
                cnt_category++;
                flag_products = FRUITS;
            }

            tmp = tmp->next;
        }

        Sleep(1000);

        if (cnt_category != 0) {
            num_of_food = rand() % cnt_category + 1;


            tmp = food_list;

            // сохранение эл в корзине
            while (tmp != NULL) {
                if (tmp->FOOD_category == flag_products)
                    j++;

                if (tmp->FOOD_category == flag_products && j == num_of_food) {
                    tmp_1 = create_node();
                    push_node( &min_cart, tmp_1);

                    strcpy(tmp_1->name_of_product, tmp->name_of_product);
                    tmp_1->category = tmp->category;
                    tmp_1->price = tmp->price;
                    tmp_1->FOOD_category = tmp->FOOD_category;
                }
                
                tmp = tmp->next;
            }
        }

        j = 0;
        flag_products = 0;
        cnt_category = 0;
        tmp = food_list;
    }

    printf("------------------------------------------------\n");
    printf("|           MINIMAL_SHOPPING_CART              |\n");
    printf("------------------------------------------------\n");

    display_data(min_cart);

    // особождение памяти
    while (food_list != NULL) {
        tmp = food_list;
        pop_node(tmp, &food_list);
        if (tmp != NULL)
            free(tmp);
    }

    while (min_cart != NULL) {
        tmp = min_cart;
        pop_node(tmp, &min_cart);
        if (tmp != NULL)
            free(tmp);
    }
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//________________Сохранение_&_загрузка__________________//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void save_list(char* name_of_db, node* head) {
    node* tmp = head;
    int cnt_elems = 0;
    FILE* save_db = fopen(name_of_db, "wb");

    if (save_db == NULL)
        exit(1);

    // подсчет количества эл
    while (tmp != NULL) {
        cnt_elems++;
        tmp = tmp->next;
    }

    fwrite(&cnt_elems, sizeof(int), 1, save_db);

    // цикл сохранения списка в файл
    // запись данных эл в файл
    if (head != NULL) {
        // сохраненя данных эл в узел
        do {
            fwrite(head, sizeof(char), sizeof(struct node) - 2 * sizeof(node*), save_db);

            head = head->next;
        } while (head != NULL);
    }

    fclose(save_db);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void read_db(char* name_of_db, node** head) {
    node* tmp = *head;
    node* help_tmp = NULL;
    int cnt_elems;
    FILE* read_db = fopen(name_of_db, "rb");

    if (read_db == NULL) {
        exit(1);
    }

    fread(&cnt_elems, sizeof(int), 1, read_db);

    // читаем список из файла
    while (cnt_elems > 0) {
        tmp = create_node();
        push_node(head, tmp);

        tmp->prev = help_tmp;
        tmp->next = NULL;
        if (help_tmp != NULL)
            help_tmp->next = tmp;

        fread(tmp, sizeof(node) - 2 * sizeof(node*), 1, read_db);

        help_tmp = tmp;
        cnt_elems--;
    }

    fclose(read_db);
}