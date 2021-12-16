#define SIZE_NAME 64
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
typedef struct node {
    char name_of_pruduct[SIZE_NAME];
    int price;
    struct node* prev;
    struct node* next;
} node;
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
node* create_node();
int push_node(node** head, node* elem);
node* pop_node(node* elem, node** head);
int convert_to_high_case(char* mass);
int edit_node(node* elem);
void delete_product(node** head, node* elem);
void get_category_name(char* mass, int category);
char find_first_char(node* tmp);
void swap_data_nodes(node* elem);
void sort_list(node* head);
void display_data(node* head);
void display_data_category(node* head);
node* get_node_by_num(node* head, int num_of_node);
void create_min_shop_cart(node* head);
void save_list(char* name_of_db, node* head);
void read_db(char* name_of_db, node** head);