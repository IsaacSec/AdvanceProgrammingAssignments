#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UserDefined.h"

int PrintItem (const void *data_p){

  if(data_p!=NULL){
    
    node_p node = (node_p) data_p;
    int number = node->number;
    char *string = node->theString;

    printf("Data element: %3d %s\n",number,string);
    return EXIT_SUCCESS;

  }else{

    return EXIT_FAILURE;
  }
}

int PrintList (GList * myList_p){
  GList * temp = myList_p;
  while (temp != NULL) {
    PrintItem(temp->data);
    temp = g_list_next(temp);
  }

  // WARNING
  return 0;
}

node_p NewItem (int theNumber, char * theString){
  node_p newNode = (node_p) malloc(sizeof(node_p));
  newNode->number = theNumber;
  newNode->theString = theString;
  return newNode;
}

int FreeItem (const void *data_p){
  //KEEP TESTING
  free((node_p)data_p);
  data_p = NULL;
  // WARNING
  return 0;
}

int DestroyList (GList * theList_p){

  // KEEEP TESTING ....
  GList * temp;

  do{
    temp = theList_p;
    theList_p = theList_p->next;
    FreeItem(temp->data);
    g_list_free(temp);
  }while (theList_p->next != NULL);


  g_list_free(theList_p);
  theList_p = NULL;

  if(theList_p != NULL){
    return 1;
  }else{
    return 0;
  }

}

int CompareItems (const void *item1_p, const void *item2_p){
  int a = ((node_p) item1_p)->number;
  int b = ((node_p) item2_p)->number;

  if(a<b){
    return LESS;
  }else if(a==b){
    return EQUAL;
  }else{
    return GREATER;
  }
}

int CompareItemsWithKey (const void *item1_p, const void *item2_p, int key){
  // WARNING
  return 0;
}

void * CopyItems (const void *source_p){
  node_p newItem = (node_p) malloc(sizeof(node_p));
  node_p srcItem = (node_p)source_p;

  newItem->number = srcItem->number;
  newItem->theString = (char*) malloc(sizeof(char));
  strcpy(newItem->theString,srcItem->theString);

  void * copyItem = (void*)newItem;
  return copyItem;
}

GList * CopyList (GList * inputList){
  GList * temp = g_list_first(inputList);
  GList * cpyList = g_list_copy(temp);
  cpyList = g_list_first(cpyList);

  do{
    gpointer cpyData = CopyItems(temp->data);
    cpyList->data = cpyData;
    temp = g_list_next(temp);
    cpyList = g_list_next(cpyList);
  }while(temp->next != NULL);

  cpyList = g_list_first(cpyList);
  return cpyList;
}

GList * FindInList (GList * myList_p, const void *value_p, int key){
  GList * temp = myList_p;
  printf("Key: %d\n",key);
  while (temp != NULL) {
    node_p node = (node_p)temp->data;

    switch(key){

      case INT:
        if(node->number == *((int*)value_p)){
          return temp;
        }
        break;
      case STR:
        if(strcmp(node->theString,(char*)value_p) == 0){
          return temp;
        }
        break;
      case SINGLEINT:
        if(node->number == *((int*)value_p)){
          return temp;
        }
        break;
      case SINGLESTR:
        if(strcmp(node->theString,(char*)value_p) == 0){
          return temp;
        }
        break;
    }

    temp = g_list_next(temp);
  }


  // WARNING
  return NULL;

}
