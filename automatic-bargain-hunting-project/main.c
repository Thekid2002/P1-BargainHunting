#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct grocery {
    char name[20];
    char grocery_type[20];
    int amount;
    double price;
    int organic;
};

struct store {
    char name[20];
    int no_of_groceries;
    int distance;
    double total_price;
    int total_groceries;
    struct grocery groceries[50];
};

struct shopping_list {
    char name[20];
    int no_of_groceries;
    struct grocery groceries[50];
};

struct user {
    char name[20];
    int no_of_shopping_lists;
    int willingness_to_travel;
};

enum types {
    enum_store, enum_groceries, enum_shopping_list
};


struct user users[5];
struct store stores[20];
struct shopping_list shopping_list[50];
int user_no;
int stores_amount;
int user_amount;

char file_divider[4];

/**
 * A function for editing and reading files
 *
 * @param file_name name of saved file
 * @param mode r for read and w for write
 * @param directory the directory to write files to
 * @return file opened
 */
FILE *open_file( char *file_name, char *mode, char *directory ) {
    char temp_file_name[60];
    strcpy( temp_file_name, "files" );
    if ( !strstr( "files", directory )) {
        strcat( temp_file_name, file_divider );
        strcat( temp_file_name, directory );
    }
    strcat( temp_file_name, file_divider );
    strcat( temp_file_name, file_name );
    strcat( temp_file_name, ".txt" );
    FILE *file = fopen( temp_file_name, mode );
    return file;
}

int scan_int() {
    char input_string[20];
    int input;
    scanf( " %s", input_string );
    if ( isalpha( input_string[0] )) {
        return -1;
    }
    sscanf( input_string, " %d", &input );
    return input;
}

/**
 * Turns string into lowered characters
 */
void string_lower( char *string ) {
    for ( int i = 0; i < strlen( string ); ++i ) {
        string[i] = tolower( string[i] );
    }
}

/**
 * Loading general user and store data
 */
void load_data() {
    FILE *file = open_file( "user_data", "r", "files" );
    if ( file != NULL) {
        fscanf( file, " %d", &user_amount );
        for ( int i = 0; i < user_amount; ++i ) {
            fscanf( file, " %s %d %d", users[i].name, &users[i].no_of_shopping_lists, &users[i].willingness_to_travel );
        }
    }
    fclose( file );

    file = open_file( "store_data", "r", "files" );
    if ( file != NULL) {
        fscanf( file, " %d", &stores_amount );
        for ( int i = 0; i < stores_amount; ++i ) {
            fscanf( file, " %s %d %d", stores[i].name, &stores[i].no_of_groceries,
                    &stores[i].distance );
        }
    }
    fclose( file );

    for ( int i = 0; i < stores_amount; ++i ) {
        file = open_file( stores[i].name, "r", "stores" );
        if ( file != NULL) {
            for ( int j = 0; j < stores[i].no_of_groceries; ++j ) {
                fscanf( file, " %s %s %d %lf %d", stores[i].groceries[j].name,
                        stores[i].groceries[j].grocery_type, &stores[i].groceries[j].amount,
                        &stores[i].groceries[j].price,
                        &stores[i].groceries[j].organic );
            }
        }
        fclose( file );
    }
}

/**
 * loads shopping lists from file
 */
void load_shopping_lists() {
    FILE *file = open_file( users[user_no].name, "r", "shopping_lists" );
    if ( file != NULL) {
        for ( int i = 0; i < users[user_no].no_of_shopping_lists; ++i ) {
            fscanf( file, " %s %d", shopping_list[i].name, &shopping_list[i].no_of_groceries );
        }
    }
    fclose( file );

    for ( int i = 0; i < users[user_no].no_of_shopping_lists; ++i ) {
        file = open_file( shopping_list[i].name, "r", "shopping_lists" );
        if ( file != NULL) {
            for ( int j = 0; j < shopping_list[i].no_of_groceries; ++j ) {
                fscanf( file, " %s %s %d", shopping_list[i].groceries[j].name,
                        shopping_list[i].groceries[j].grocery_type,
                        &shopping_list[i].groceries[j].amount );
            }
        }
        fclose( file );
    }
}

void print_greeting(){
    printf("\nHello and welcome to bargain hunting.\n\n");
    printf("This application will assist you to find the place to shop. If you only need to know where one grocery is cheapest,\n");
    printf("you can input \"search\" and search for the grocery.\n\n");
    printf("If you want to know which store to buy groceries in. You start of by creating a grocery list with \"new\",\n");
    printf("adding groceries wih \"add\" and then using the \"total\" function to get the cheapest store printed out.\n\n");
    printf("Before all of that please type \"create\" to make a new user or\n");
}

/**
 * Saving general user and store data
 */
void save_data() {
    FILE *file = open_file( "user_data", "w", "files" );
    if ( file != NULL) {
        fprintf( file, "%d\n", user_amount );
        for ( int i = 0; i < user_amount; ++i ) {
            fprintf( file, " %s %d %d\n", users[i].name, users[i].no_of_shopping_lists,
                     users[i].willingness_to_travel );
        }
    }
    fclose( file );

    file = open_file( "store_data", "w", "files" );
    if ( file != NULL) {
        fprintf( file, "%d\n", stores_amount );
        for ( int i = 0; i < stores_amount; ++i ) {
            fprintf( file, " %s %d %d\n", stores[i].name, stores[i].no_of_groceries,
                     stores[i].distance );
        }
    }
    fclose( file );

    for ( int i = 0; i < stores_amount; ++i ) {
        file = open_file( stores[i].name, "w", "stores" );
        if ( file != NULL) {
            for ( int j = 0; j < stores[i].no_of_groceries; ++j ) {
                fprintf( file, " %s %s %d %lf %d\n", stores[i].groceries[j].name,
                         stores[i].groceries[j].grocery_type, stores[i].groceries[j].amount,
                         stores[i].groceries[j].price,
                         stores[i].groceries[j].organic );
            }
        }
        fclose( file );
    }
}

/**
 * Saving shopping lists and their contents to a file
 */
void save_shopping_lists() {
    FILE *file = open_file( users[user_no].name, "w", "shopping_lists" );
    if ( file != NULL) {
        for ( int i = 0; i < users[user_no].no_of_shopping_lists; ++i ) {
            fprintf( file, " %s %d\n", shopping_list[i].name, shopping_list[i].no_of_groceries );
        }
    }
    fclose( file );

    for ( int i = 0; i < users[user_no].no_of_shopping_lists; ++i ) {
        file = open_file( shopping_list[i].name, "w", "shopping_lists" );
        if ( file != NULL) {
            for ( int j = 0; j < shopping_list[i].no_of_groceries; ++j ) {
                fprintf( file, " %s %s %d\n",
                         shopping_list[i].groceries[j].name, shopping_list[i].groceries[j].grocery_type,
                         shopping_list[i].groceries[j].amount );
            }
        }
        fclose( file );
    }
}

/**
 * Scans for the users willingness to travel
 */
int scan_willingness_to_travel() {
    printf( "How willing are you to travel? (1) Not willing to travel (2) willing to travel (3) very willing to travel>" );
    int willingness_to_travel = scan_int();
    if ( willingness_to_travel == 1 ) {
        return 400;
    } else if ( willingness_to_travel == 2 ) {
        return 200;
    } else if ( willingness_to_travel == 3 ) {
        return 100;
    } else {
        scan_willingness_to_travel();
    }
}

/**
 * Add new user
 */
void new_user() {
    struct user new_user;
    printf( "Input user name>" );
    scanf( " %s", new_user.name );
    new_user.willingness_to_travel = scan_willingness_to_travel();
    new_user.no_of_shopping_lists = 0;
    users[user_amount] = new_user;
    user_amount += 1;
}

/**
 * Authentication responsible for logins
 */
void authentication() {
    char user_input[20];
    printf( "Please log in>" );
    scanf( " %s", user_input );
    if ( strcmp( user_input, "exit" ) == 0 ) {
        exit( 0 );
    } else if ( strcmp( user_input, "create" ) == 0 ) {
        new_user();
        user_no = user_amount - 1;
        return;
    }
    for ( int i = 0; i < user_amount; ++i ) {
        if ( strcmp( user_input, users[i].name ) == 0 ) {
            user_no = i;
            printf( "\nLogged in as %s\n\n", users[i].name );
            return;
        }
    }
    printf( "Can't find user. \"exit\" to shut down app. \"create\" to add a new user.\n" );
    authentication();
}

/**
 * Add new store
 */
void new_store() {
    struct store new_store;
    printf( "Input store name>" );
    scanf( " %s", new_store.name );
    new_store.no_of_groceries = 0;

    printf( "Input store distance>" );
    scanf( " %d", &new_store.distance );

    stores[stores_amount] = new_store;
    stores_amount += 1;
}

/**
 * Add new shopping list
 */
void new_shopping_list() {
    struct shopping_list new_shopping_list;
    printf( "Input shopping list name>" );
    scanf( " %s", new_shopping_list.name );
    new_shopping_list.no_of_groceries = 0;
    shopping_list[users[user_no].no_of_shopping_lists] = new_shopping_list;
    users[user_no].no_of_shopping_lists += 1;
}

/**
 * Add new grocery to store
 */
void add_grocery_to_store( int input ) {
    struct grocery grocery;
    printf( "Input grocery name>" );
    scanf( " %s", grocery.name );
    printf( "Input grocery type>" );
    scanf( " %s", grocery.grocery_type );
    string_lower( grocery.grocery_type );
    printf( "Input grocery price>" );
    scanf( " %lf", &grocery.price );
    printf( "Input grocery amount>" );
    scanf( " %d", &grocery.amount );
    printf( "Input grocery organic>" );
    scanf( " %d", &grocery.organic );
    stores[input].groceries[stores[input].no_of_groceries] = grocery;
    stores[input].no_of_groceries += 1;
}

/**
 * Search grocery and add it to list
 */
struct grocery search_grocery_and_type() {
    char search_phrase[20];
    struct grocery grocerySearchedFor[50];
    printf( "\nInput search phrase>" );
    scanf( " %s", search_phrase );
    string_lower( search_phrase );
    char name[20];
    char type[20];
    int id = 0;
    for ( int i = 0; i < stores_amount; ++i ) {
        int print_store = 1;
        for ( int j = 0; j < stores[i].no_of_groceries; ++j ) {
            strcpy( name, stores[i].groceries[j].name );
            strcpy( type, stores[i].groceries[j].grocery_type );
            string_lower( name );
            string_lower( type );
            if ( strstr( name, search_phrase ) || strstr( type, search_phrase )) {
                if ( print_store ) {
                    printf( "Name: %s, No.: %d\n", stores[i].name, stores[i].no_of_groceries );
                    print_store = 0;
                }
                printf( "  %d Name: %s, Price: %lf, Amount: %d, Grocery type: %s \n", id,
                        stores[i].groceries[j].name, stores[i].groceries[j].price, stores[i].groceries[j].amount,
                        stores[i].groceries[j].grocery_type );
                grocerySearchedFor[id] = stores[i].groceries[j];
                id++;
            }
        }
        printf( "\n" );
    }
    printf( "\nPick a grocery to add to shopping list or search again (e)>" );
    scanf( " %s", search_phrase );
    if ( search_phrase[0] == 'e' ) {
        search_grocery_and_type();
    } else {
        sscanf( search_phrase, "%d", &id );
        return grocerySearchedFor[id];
    }
}

/**
 * Add items to a shopping list
 */
void add_grocery_to_shopping_list( int input ) {
    struct grocery grocery;
    grocery = search_grocery_and_type();
    printf( "Add grocery type (0) or specific grocery (1)>" );
    int user_input = scan_int();
    if ( user_input != 0 && user_input != 1 ) {
        printf( "Input was not 0 or 1\n" );
        return;
    }
    if ( user_input == 0 ) {
        strcpy( grocery.name, "empty" );
        grocery.price = 0;
        grocery.organic = 0;
    }
    printf( "\nInput amount of %s>", grocery.grocery_type );
    user_input = scan_int();
    grocery.amount = user_input;

    shopping_list[input].groceries[shopping_list[input].no_of_groceries] = grocery;
    shopping_list[input].no_of_groceries += 1;
}

/**
 * Print all stores
 */
void print_stores() {
    for ( int i = 0; i < stores_amount; ++i ) {
        printf( "Id: %d, Name: %s, No.: %d\n", i, stores[i].name, stores[i].no_of_groceries );
    }
}

/**
 * Print groceries
 */
void print_groceries() {
    for ( int i = 0; i < stores_amount; ++i ) {
        printf( "Id: %d, Name: %s, No.: %d\n", i, stores[i].name, stores[i].no_of_groceries );
        for ( int j = 0; j < stores[i].no_of_groceries; ++j ) {
            printf( "  Id: %d, Name: %s, Price: %lf, Amount: %d, Grocery type: %s \n", i, stores[i].groceries[j].name,
                    stores[i].groceries[j].price, stores[i].groceries[j].amount, stores[i].groceries[j].grocery_type );
        }
        printf( "\n" );
    }
}

/**
 * Print shopping list
 */
void print_shopping_lists() {
    for ( int i = 0; i < users[user_no].no_of_shopping_lists; ++i ) {
        printf( "Id: %d, Name: %s, No.: %d\n", i, shopping_list[i].name, shopping_list[i].no_of_groceries );

        for ( int j = 0; j < shopping_list[i].no_of_groceries; ++j ) {
            printf( " Name: %s, Grocery type: %s, Amount: %d\n", shopping_list[i].groceries[j].name,
                    shopping_list[i].groceries[j].grocery_type, shopping_list[i].groceries[j].amount );
        }
    }
}

/**
 * Print help
 */
void print_help() {
    printf( "Commands:\n");
    printf("   ls     - Print out either stores, groceries or shopping lists\n");
    printf("   exit   - Log out of the application\n");
    printf("   add    - Add groceries to either a store or a shopping list\n");
    printf("   new    - Create a new store, user or shopping list\n");
    printf("   save   - No changes made are saved until you input this command\n");
    printf("   search - Search for groceries and get them printed out\n");
    printf("   remove - Delete store, grocery or shopping list\n");
    printf("   total  - Prints out the best store to purchase groceries from, using a shopping list\n");
}

/**
 * Search data
 */
void search_data() {
    char search_phrase[20];
    printf( "\nInput search phrase>" );
    scanf( " %s", search_phrase );
    string_lower( search_phrase );
    for ( int i = 0; i < stores_amount; ++i ) {
        printf( "Name: %s, No.: %d\n", stores[i].name, stores[i].no_of_groceries );
        for ( int j = 0; j < stores[i].no_of_groceries; ++j ) {
            if ( round( stores[i].groceries[j].price ) != 0 ) {
                if ( strstr( search_phrase, stores[i].groceries[j].grocery_type ) || strstr( search_phrase,
                                                                                             stores[i].groceries[j].name )) {
                    printf( "   Name: %s, Price: %lf, Amount: %d, Grocery type: %s \n",
                            stores[i].groceries[j].name, stores[i].groceries[j].price,
                            stores[i].groceries[j].amount, stores[i].groceries[j].grocery_type );
                }
            }
        }
    }
}

/**
 * Comparing the price of two groceries
 * @param a grocery one
 * @param b grocery two
 * @return the difference in price
 */
int cmp_grocery_price( const void *a, const void *b ) {
    double price1 = (*( struct grocery * ) a).price;
    double price2 = (*( struct grocery * ) b).price;
    return round( price1 - price2 );
}

/**
 * Comparing the total price and amount of groceries for stores
 * @param a store one
 * @param b store two
 * @return the difference in amount or price
 */
int cmp_grocery_no_and_price( const void *a, const void *b ) {
    double no1 = (*( struct store * ) a).total_groceries;
    double no2 = (*( struct store * ) b).total_groceries;
    if ( no2 - no1 != 0 ) {
        return round( no2 - no1 );
    }
    double price1 = (*( struct store * ) a).total_price;
    double price2 = (*( struct store * ) b).total_price;
    return round( price1 - price2 );
}

/**
 * Sorting groceries in stores by price
 */
void sort_stores_price() {
    for ( int i = 0; i < stores_amount; ++i ) {
        stores[i].total_groceries = 0;
        qsort( stores[i].groceries, stores[i].no_of_groceries, sizeof( struct grocery ), cmp_grocery_price );
    }
}

/**
 * Setting the total price for each store the cost of traveling
 */
void add_distance_to_price() {
    for ( int i = 0; i < stores_amount; ++i ) {
        if ( stores[i].distance > 6000 ) {
            stores[i].total_price = users[user_no].willingness_to_travel;
        } else if ( stores[i].distance > 4000 ) {
            stores[i].total_price = users[user_no].willingness_to_travel / 2;
        } else if ( stores[i].distance > 2000 ) {
            stores[i].total_price = users[user_no].willingness_to_travel / 4;
        } else {
            stores[i].total_price = 0;
        }
    }
}

/**
 * Finds cheapest store for a input shopping list
 * @param input id of cheapest shopping list
 */
void search_cheapest_store( int input ) {
    add_distance_to_price();
    sort_stores_price();
    struct grocery *sl_groceries;
    struct grocery *store_groceries;
    for ( int i = 0; i < shopping_list[input].no_of_groceries; ++i ) {
        sl_groceries = shopping_list[input].groceries;
        for ( int j = 0; j < stores_amount; ++j ) {
            store_groceries = stores[j].groceries;
            for ( int k = 0; k < stores[j].no_of_groceries; ++k ) {
                if ( strcmp( sl_groceries[i].name, "emtpy" ) != 0 ) {
                    if ( strcmp( store_groceries[k].name, sl_groceries[i].name ) == 0 ) {
                        stores[j].total_groceries += 1;
                        stores[j].total_price += store_groceries[k].price * shopping_list[input].groceries[i].amount;
                        k += stores[j].no_of_groceries;
                    }
                } else if ( strcmp( store_groceries[k].grocery_type, sl_groceries[i].grocery_type ) == 0 ) {
                    stores[j].total_groceries += 1;
                    stores[j].total_price += store_groceries[k].price * shopping_list[input].groceries[i].amount;
                    k += stores[j].no_of_groceries;
                }
            }
            if ( stores[j].total_groceries == 0 ) {
                if ( strcmp( shopping_list[input].groceries[i].name, "emtpy" ) == 0 ) {
                    printf( " Store: %s does not have %s \n", stores[j].name,
                            shopping_list[input].groceries[i].grocery_type );
                } else {
                    printf( " Store: %s does not have %s \n", stores[j].name,
                            shopping_list[input].groceries[i].name );
                }
            }
        }
    }
    printf( "\n" );
    for ( int i = 0; i < stores_amount; ++i ) {
        qsort( stores, stores_amount - 1, sizeof( struct store ), cmp_grocery_no_and_price );
        printf( "Name: %s, total price: %lf, total no. of groceries:%d\n", stores[i].name, stores[i].total_price,
                stores[i].total_groceries );
    }
}

/**
 * Lists stores, groceries or shopping lists
 * @param input if input is < 0 the user is asked what they want
 * if the input is above 0 the right item is listed
 */
void list_items( int input ) {
    if ( input < 0 ) {
        printf( "Stores(0) Groceries(1) Shopping Lists(2)>" );
        input = scan_int();
    }

    switch ( input ) {
        case enum_store:
            print_stores();
            break;
        case enum_groceries:
            print_groceries();
            break;
        case enum_shopping_list:
            print_shopping_lists();
            break;
        default:
            printf( "ERROR: Cannot find input\n" );
            break;
    }
}

/**
 * Deleting groceries bt store id and grocery id
 */
void delete_groceries() {
    list_items( enum_groceries );
    printf( "\nPick a store by id>" );
    int input_store = scan_int();
    printf( "\nPick a grocery by id>" );
    int input = scan_int();
    if ( input < stores[input_store].no_of_groceries + 1 && input >= 0 ) {
        for ( int i = input; i < stores[input_store].no_of_groceries + 1; ++i ) {
            strcpy( stores[input_store].groceries[i].name, stores[input_store].groceries[i + 1].name );
            strcpy( stores[input_store].groceries[i].grocery_type, stores[input_store].groceries[i + 1].grocery_type );
            stores[input_store].groceries[i].price = stores[input_store].groceries[i + 1].price;
            stores[input_store].groceries[i].amount = stores[input_store].groceries[i + 1].amount;
            stores[input_store].groceries[i].organic = stores[input_store].groceries[i + 1].organic;
        }
        stores[input_store].no_of_groceries -= 1;
    } else {
        printf( "ERROR: No grocery found with id: %d in store id: %d\n", input, input_store );
    }
}

/**
 * Delete store by id
 */
void delete_store() {
    list_items( enum_store );
    printf( "\nPick a stores by id>" );
    int input = scan_int();
    if ( input < stores_amount + 1 && input >= 0 ) {
        for ( int i = input; i < stores_amount + 1; ++i ) {
            for ( int j = 0; j < stores[i + 1].no_of_groceries + 1; ++j ) {
                stores[i].groceries[j] = stores[i + 1].groceries[j];
            }
            stores[i].no_of_groceries = stores[i + 1].no_of_groceries;
            stores[i].distance = stores[i + 1].distance;
            strcpy( stores[i].name, stores[i + 1].name );
        }
        stores_amount -= 1;
    } else {
        printf( "ERROR: No store found with id: %d\n", input );
    }
}

/**
 * Delete shopping list by id
 */
void delete_shopping_list() {
    list_items( enum_shopping_list );
    printf( "\nPick a shopping list by id>" );
    int input = scan_int();
    if ( input < users[user_no].no_of_shopping_lists + 1 && input >= 0 ) {
        for ( int i = input; i < users[user_no].no_of_shopping_lists + 1; ++i ) {
            for ( int j = 0; j < shopping_list[i + 1].no_of_groceries + 1; ++j ) {
                shopping_list[i].groceries[j] = shopping_list[i + 1].groceries[j];
            }
            shopping_list[i].no_of_groceries = shopping_list[i + 1].no_of_groceries;
            strcpy( shopping_list[i].name, shopping_list[i + 1].name );
        }
        users[user_no].no_of_shopping_lists -= 1;
    } else {
        printf( "ERROR: No shopping list found with id: %d\n", input );
    }
}

/**
 * Add grocery to store or shopping lists
 */
void add_items() {
    printf( "Store(0) Groceries(1) Shopping list(2)>" );
    int input = scan_int();
    if ( input == enum_shopping_list ) {
        if ( users[user_no].no_of_shopping_lists == 0 ) {
            printf( "ERROR: No shopping list found create a (new)\n" );
            return;
        }
        list_items( 2 );
        printf( "\nPick a shopping list by id>" );
        input = scan_int();
        if(input >= 0 && input < users[user_no].no_of_shopping_lists) {
            add_grocery_to_shopping_list( input );
        }else{
            printf( "ERROR: Cannot find input: %d\n",input );
        }
    } else if ( input == enum_store || input == enum_groceries ) {
        list_items( 1 );
        printf( "\nPick a store by id>" );
        input = scan_int();
        if(input >= 0 && input < stores_amount) {
            add_grocery_to_store( input );
        }else{
            printf( "ERROR: Cannot find input: %d\n",input );
        }
    } else {
        printf( "ERROR: Cannot find input\n" );
    }
}

/**
 * Deletes store, grocery or shopping list
 */
void delete_item() {
    printf( "Store(0) Groceries(1) Shopping list(2)>" );
    int input = scan_int();

    switch ( input ) {
        case enum_store:
            delete_store();
            break;
        case enum_groceries:
            delete_groceries();
            break;
        case enum_shopping_list:
            delete_shopping_list();
            break;
        default:
            printf( "ERROR: Cannot find input\n" );
            break;
    }
}

/**
 * Create a store, user or shopping list
 */
void new_item() {
    printf( "Stores(0) Users(1) Shopping List(2)>" );
    int input = scan_int();
    switch ( input ) {
        case enum_store:
            new_store();
            break;
        case 1:
            new_user();
            break;
        case enum_shopping_list:
            new_shopping_list();
            break;
        default:
            printf( "ERROR: Cannot find input\n" );
    }
}


/**
 * Scan user input
 */
void scan_user_input() {
    char user_input[20];
    int input;
    printf( "\nWhat is your command %s>", users[user_no].name );
    scanf( " %s", user_input );
    string_lower( user_input );

    if ( strstr( user_input, "ls" )) {
        list_items( -1 );
    } else if ( strstr( user_input, "exit" )) {
        authentication();
    } else if ( strstr( user_input, "add" )) {
        add_items();
    } else if ( strstr( user_input, "remove" )) {
        delete_item();
    } else if ( strstr( user_input, "search" )) {
        search_data();
    } else if ( strstr( user_input, "save" )) {
        save_data();
        save_shopping_lists();
    } else if ( strstr( user_input, "new" )) {
        new_item();
    } else if ( strstr( user_input, "total" )) {
        if ( users[user_no].no_of_shopping_lists == 0 ) {
            printf( "No shopping list found create a (new)\n" );
            return;
        }
        print_shopping_lists();
        printf( "\nPick a shopping list by id>" );
        input = scan_int();
        if ( input >= 0 && input < users[user_no].no_of_shopping_lists ) {
            search_cheapest_store( input );
        } else {
            printf( "Cannot find shopping list with id: %d", input );
        }
    } else {
        print_help();
    }
}

/**
 * Asks the user if they are on mac or windows
 */
void mac_or_windows() {
    printf( "Are you using mac(0) or windows(1)>" );
    int input = scan_int();
    if ( input == 1 ) {
        strcpy( file_divider, "\\" );
    } else if ( input == 0 ) {
        strcpy( file_divider, "/" );
    } else {
        printf( "Input was not 0 or 1\n" );
        mac_or_windows();
    }
}

int main() {
    mac_or_windows();
    load_data();
    print_greeting();
    authentication();
    load_shopping_lists();
    print_help();
    while ( 1 ) {
        scan_user_input();
    }
}
