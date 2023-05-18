#include <stdio.h>
#include <stdint.h>

/** 
* Example depiction of hierarchy tree:
*
* ├── [Main Screen]
*      │
*      └── [Main Menu]
*           │
*           ├── [Sub menu 1]
*           │     │
*           │     ├── [Sub menu 1a] 
*           │     ├── [Sub menu 1b] 
*           │     ├── [Sub menu 1c] 
*           │    ...
*           │     └── [Sub menu 1N] 
*           │
*           ├── [Sub menu 2]
*           │     │
*           │     ├── [Sub menu 2a]
*           │    ...
*           │     └── [Sub menu 2N]
*           │
*           ├── [Sub menu 3]
*           │     │
*           │     ├── [Sub menu 3a]
*           │    ...
*           │     └── [Sub menu 3N]
*           │
*           └──  ...
*                 │
*                ...
*/

typedef enum
{
    KEY_NONE = -1,
    KEY_OK = 0,
    KEY_UP,
    KEY_DOWN,
    KEY_BACK = 3
} user_key_t;

// Declarations
typedef struct MenuNode MenuNode_t;
typedef void (*DisplayContents)(MenuNode_t*);
typedef void (*KeyHandler)(MenuNode_t**);

void print_menu_info(MenuNode_t* menu);
void main_screen(MenuNode_t*);
void main_menu(MenuNode_t*);
void sub_menu_1(MenuNode_t*);
void sub_menu_1a(MenuNode_t*);
void sub_menu_1b(MenuNode_t*);
void sub_menu_1c(MenuNode_t*);
void sub_menu_2(MenuNode_t*);
void sub_menu_2a(MenuNode_t*);
void sub_menu_3(MenuNode_t*);

void keyHandler_NULL(MenuNode_t**);
void keyHandler_Up(MenuNode_t**);
void keyHandler_Down(MenuNode_t**);
void keyHandler_Back(MenuNode_t**);
void keyHandler_Ok(MenuNode_t**);
void keyHandler_OkDownMainScreen(MenuNode_t**);
void keyHandler_UpMainMenu(MenuNode_t**);
void keyHandler_DownMainMenu(MenuNode_t**);
void keyHandler_OkMainMenu(MenuNode_t**);

// MenuNode definitions
typedef struct MenuNode
{
    const char title[16];
    DisplayContents display;
    MenuNode_t* parent;
    MenuNode_t* child;
    MenuNode_t* sibling;
    KeyHandler keyHandlers[4];
    uint8_t selection;
} MenuNode_t;

MenuNode_t mainScreen;
MenuNode_t mainMenu;
MenuNode_t subMenu1;
MenuNode_t subMenu1a;
MenuNode_t subMenu1b;
MenuNode_t subMenu1c;
MenuNode_t subMenu2;
MenuNode_t subMenu2a;
MenuNode_t subMenu3;

//****************** MAIN SCREEN ******************
MenuNode_t mainScreen = {
        /*    title    */   "Main Screen",
        /*   display   */   main_screen,
        /*   parent    */   NULL,
        /*   child     */   &mainMenu,
        /*  sibling    */   NULL,
        /*keyHandlers[]*/   {keyHandler_OkDownMainScreen, keyHandler_NULL, keyHandler_OkDownMainScreen, keyHandler_NULL},
        /*  selection  */   0   
                        };

//******************* MAIN MENU *******************
MenuNode_t mainMenu =   {
        /*    title    */   "Main Menu",
        /*   display   */   main_menu,
        /*   parent    */   &mainScreen,
        /*   child     */   &subMenu1,
        /*  sibling    */   NULL,
        /*keyHandlers[]*/   {keyHandler_OkMainMenu, keyHandler_UpMainMenu, keyHandler_DownMainMenu, keyHandler_Back},
        /*  selection  */   0   
                        };

//******************* SUB MENU 1 ******************
MenuNode_t subMenu1 =   {
        /*    title    */   "Sub Menu 1",
        /*   display   */   sub_menu_1,
        /*   parent    */   &mainMenu,
        /*   child     */   &subMenu1a,
        /*  sibling    */   &subMenu2,
        /*keyHandlers[]*/   {keyHandler_OkMainMenu, keyHandler_NULL, keyHandler_NULL, keyHandler_Back},
        /*  selection  */   0   
                        };

MenuNode_t subMenu1a =  {
        /*    title    */   "Sub Menu 1a",
        /*   display   */   sub_menu_1a,
        /*   parent    */   &subMenu1,
        /*   child     */   NULL,
        /*  sibling    */   &subMenu1b,
        /*keyHandlers[]*/   {keyHandler_NULL, keyHandler_NULL, keyHandler_NULL, keyHandler_Back},
        /*  selection  */   0   
                        };

MenuNode_t subMenu1b =  {
        /*    title    */   "Sub Menu 1b",
        /*   display   */   sub_menu_1b,
        /*   parent    */   &subMenu1,
        /*   child     */   NULL,
        /*  sibling    */   &subMenu1c,
        /*keyHandlers[]*/   {keyHandler_NULL, keyHandler_NULL, keyHandler_NULL, keyHandler_Back},
        /*  selection  */   0   
                        };

MenuNode_t subMenu1c =  {
        /*    title    */   "Sub Menu 1c",
        /*   display   */   sub_menu_1c,
        /*   parent    */   &subMenu1,
        /*   child     */   NULL,
        /*  sibling    */   NULL,
        /*keyHandlers[]*/   {keyHandler_NULL, keyHandler_NULL, keyHandler_NULL, keyHandler_Back},
        /*  selection  */   0   
                        };

//******************* SUB MENU 2 ******************
MenuNode_t subMenu2 =   {
        /*    title    */   "Sub Menu 2",
        /*   display   */   sub_menu_2,
        /*   parent    */   &mainMenu,
        /*   child     */   &subMenu2a,
        /*  sibling    */   &subMenu3,
        /*keyHandlers[]*/   {keyHandler_NULL, keyHandler_NULL, keyHandler_NULL, keyHandler_Back},
        /*  selection  */   0   
                        };

MenuNode_t subMenu2a =  {
        /*    title    */   "Sub Menu 2a",
        /*   display   */   sub_menu_2a,
        /*   parent    */   &subMenu1,
        /*   child     */   NULL,
        /*  sibling    */   NULL,
        /*keyHandlers[]*/   {keyHandler_NULL, keyHandler_NULL, keyHandler_NULL, keyHandler_Back},
        /*  selection  */   0   
                        }; 

//******************* SUB MENU 3 ******************
MenuNode_t subMenu3 =   {
        /*    title    */   "Sub Menu 3",
        /*   display   */   sub_menu_3,
        /*   parent    */   &mainMenu,
        /*   child     */   NULL,
        /*  sibling    */   NULL,
        /*keyHandlers[]*/   {keyHandler_NULL, keyHandler_NULL, keyHandler_NULL, keyHandler_Back},
        /*  selection  */   0   
                        };

/**
 * @brief Handles any key by producing a callback to the correct handle if any.
 * @param keyPressed        Key pressed.       
 * @param menuNodeHandle    Doucble pointer to current MenuNode_t instance.            
 */
void handleKey(user_key_t keyPressed, MenuNode_t** menuNodeHandle)
{
    if(keyPressed == KEY_NONE)
    {
        printf("Warning: Invalid key\n");
        return;
    }

    if((*menuNodeHandle)->keyHandlers[keyPressed] != NULL)
        (*menuNodeHandle)->keyHandlers[keyPressed](menuNodeHandle);
    else
        printf("Error: Call to NULL function by %p\n", (*menuNodeHandle));
}

/**
 * @brief Display the screen configured as callback in the structure initialization ('display' attribute).
 * @param menuNode  Pointer to current MenuNode_t instance.           
 */
void updateScreen(MenuNode_t* menuNode)
{
    menuNode->display(menuNode);
}

int main()
{
    uint8_t input_key;
    user_key_t key = KEY_BACK;

    MenuNode_t* currentMenu = &mainScreen;

    while(1)
    {  
        updateScreen(currentMenu);
        scanf("%d", &input_key);
        switch(input_key)
        {
            case 6:
                key = KEY_OK;
                break;
            case 8:
                key = KEY_UP;
                break;
            case 2:
                key = KEY_DOWN;
                break;
            case 4:
                key = KEY_BACK;
                break;
            default:
                printf("Incorrect key\n");
                key = KEY_NONE;
                break;
        }
        printf("Sending key %d\n", key);
        handleKey(key, &currentMenu);
        print_menu_info(currentMenu);
    }
    
    return 0;
}

// ************************************************* SCREENS *************************************************
void main_screen(MenuNode_t* menuNode)
{
    printf("\n\t\t\tTHIS IS THE MAIN SCREEN\t\t\t\n\n");
}

void main_menu(MenuNode_t* menuNode)
{
    printf("\n\t\t\tTHIS IS THE MAIN MENU\t\t\t\n\n");
}

void sub_menu_1(MenuNode_t* menuNode)
{
    printf("\n\t\t\tTHIS IS SUB MENU 1\t\t\t\n\n");
}

void sub_menu_1a(MenuNode_t* menuNode)
{
    printf("\n\t\t\tTHIS IS SUB MENU 1a\t\t\t\n\n");
}

void sub_menu_1b(MenuNode_t* menuNode)
{
    printf("\n\t\t\tTHIS IS SUB MENU 1b\t\t\t\n\n");
}

void sub_menu_1c(MenuNode_t* menuNode)
{
    printf("\n\t\t\tTHIS IS SUB MENU 1c\t\t\t\n\n");
}

void sub_menu_2(MenuNode_t* menuNode)
{
    printf("\n\t\t\tTHIS IS SUB MENU 2\t\t\t\n\n");
}

void sub_menu_2a(MenuNode_t* menuNode)
{
    printf("\n\t\t\tTHIS IS SUB MENU 2a\t\t\t\n\n");
}

void sub_menu_3(MenuNode_t* menuNode)
{
    printf("\n\t\t\tTHIS IS SUB MENU 3\t\t\t\n\n");
}

// *********************************************** KEY HANDLERS ************************************************
void keyHandler_NULL(MenuNode_t** menuNodeHandle)
{
}

void keyHandler_Ok(MenuNode_t** menuNodeHandle)
{
    printf("keyHandler_Ok() was called\n");
}

void keyHandler_Up(MenuNode_t** menuNodeHandle)
{
    printf("keyHandler_Down() was called\n");
    if((*menuNodeHandle)->selection > 0)
        (*menuNodeHandle)->selection--;
}

void keyHandler_Down(MenuNode_t** menuNodeHandle)
{
    printf("keyHandler_Down() was called\n");
    (*menuNodeHandle)->selection++;
}

void keyHandler_Back(MenuNode_t** menuNodeHandle)
{
    printf("keyHandler_Back() was called\n");
    // Reset selection
    (*menuNodeHandle)->selection = 0;
    // Go to parent
    if((*menuNodeHandle)->parent != NULL)
    {
        *menuNodeHandle = ((*menuNodeHandle)->parent);
    }
}

void keyHandler_OkDownMainScreen(MenuNode_t** menuNodeHandle)
{
    printf("keyHandler_OkDownMainScreen() was called\n");
    if((*menuNodeHandle)->child != NULL)
    {
        *menuNodeHandle = ((*menuNodeHandle)->child);
    }
}


void keyHandler_OkMainMenu(MenuNode_t** menuNodeHandle)
{
    printf("keyHandler_OkMainMenu() was called\n");
    MenuNode_t* temp;
    temp = (*menuNodeHandle)->child;
    printf("temp: %s\n", temp->title);
    for(uint8_t i = 0; i < (*menuNodeHandle)->selection; i++)
    {
        temp = temp->sibling;
        printf("temp: %s\n", temp->title);
    }
    *menuNodeHandle = temp;
}

/**
 * @brief Up key handle for main menu. Decreases selection value if it is greater than 0. Else, it will return to Main Screen. 
*/
void keyHandler_UpMainMenu(MenuNode_t** menuNodeHandle)
{
    printf("keyHandler_UpMainMenu() was called\n");
    if(((*menuNodeHandle)->selection == 0)&&((*menuNodeHandle)->parent != NULL))
    {
        *menuNodeHandle = ((*menuNodeHandle)->parent);
    }
    else if((*menuNodeHandle)->selection > 0)
    {
        (*menuNodeHandle)->selection--;
    }
    printf("Current selection: %d\n",(*menuNodeHandle)->selection);
}

/**
 * @brief Down key handle for main menu. Increases selection value if it is has not yet reached the limit.
*/
void keyHandler_DownMainMenu(MenuNode_t** menuNodeHandle)
{
    printf("keyHandler_DownMainMenu() was called\n");
    // temp pointer for counting max selection
    MenuNode_t* child = (*menuNodeHandle)->child;
    // go to selected child
    for(uint8_t i = 0; i < (*menuNodeHandle)->selection; i++)
    {
        child = child->sibling;
    }
    // take current selectionas initial value
    uint8_t numberOfChildren = (*menuNodeHandle)->selection;
    // increase max_selection until the rest of siblings are counted
    while(child->sibling != NULL)
    {
        numberOfChildren++;
        child = child->sibling;
    }
    // if current selection is less than the max selection value for current menu, increase selection
    if((*menuNodeHandle)->selection < numberOfChildren)
    {
        (*menuNodeHandle)->selection++;
    }
}


// ********************************************** AUX FUNCTIONS **********************************************
void print_menu_info(MenuNode_t* menu)
{
    // Print node's address
    printf("-> Node >>>>>> \t%p\n", menu);
    // Print title
    printf("title\t\t");
    for(int i = 0; i < (sizeof(menu->title)/sizeof(menu->title[0])); i ++)
    {
        printf("%c",menu->title[i]);
    }
    printf("\n");
    // Print display address
    printf("display\t\t%p\n", menu->display);
    // Print parent address
    printf("parent\t\t%p\n", menu->parent);
    // Print child address
    printf("child\t\t%p\n", menu->child);
    // Print sibling address
    printf("sibling\t\t%p\n", menu->sibling);
    // Print keyHandlers' address
    printf("keyHandlers\t");
    for(int i = 0; i < (sizeof(menu->keyHandlers)/sizeof(menu->keyHandlers[0])); i ++)
    {
        printf("%p",menu->keyHandlers[i]);
        printf("\t");
    }
    printf("\n");
    // Print selection
    printf("selection\t%d\n", menu->selection);

}