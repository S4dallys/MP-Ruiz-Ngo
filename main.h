// h files
#ifndef GLOBAL
#define GLOBAL

#include "global.h"

#endif

// c files
#include "prompt.c"
#include "display.c"
#include "files.c"
#include "user.c"
#include "item.c"
#include "string_funcs.c"
#include "cart.c"

// switch case macros
#define USER_REGISTRATION        'A'
#define USER_MODE                'B'
#define ADMIN_MODE               'C'
#define EXIT_PROGRAM             'D'

#define SELL_MENU                'A'
#define BUY_MENU                 'B'
#define EXIT_USER                'C'

#define ADD_NEW_ITEM             'A'
#define EDIT_STOCK               'B'
#define SHOW_MY_PRODUCTS         'C'
#define SHOW_MY_LOW_STOCK        'D'
#define EXIT_SELL                'E'

#define VIEW_ALL_PRODUCTS        'A'
#define USE_SELLER_LENS          'B'
#define USE_CATEGORY_LENS        'C'
#define USE_NAME_LENS            'D'
#define ADD_TO_CART              'E'
#define EDIT_CART                'F'
#define CHECK_OUT                'G'
#define EXIT_BUY                 'H'

#define REPLENISH                'A'
#define CHANGE_PRICE             'B'
#define CHANGE_ITEM_NAME         'C'
#define CHANGE_CATEGORY          'D'
#define CHANGE_DESCRIPTION       'E'
#define FINISH_EDITING           'F'

#define REMOVE_ITEMS_OF_SELLER   'A'
#define REMOVE_SPECIFIC_ITEM     'B'
#define EDIT_QUANTITY            'C'
#define FINISH_EDIT_CART         'D'

#define BUY_ALL                  'A'
#define BUY_BY_CERTAIN_SELLER    'B'
#define BUY_SPECIFIC_ITEM        'C'
#define EXIT_CHECK_OUT           'D'

#define SHOW_ALL_USERS           'A'
#define SHOW_ALL_SELLERS         'B'
#define SHOW_TOTAL_SALES_IN_GIVEN_DURATION 'C'
#define SHOW_SELLERS_SALES       'D'
#define SHOW_SHOPAHOLICS         'E'
#define EXIT_ADMIN               'F'