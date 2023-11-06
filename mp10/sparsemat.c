#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>





sp_tuples * load_tuples(char* input_file)
{
    FILE *openfile = fopen(input_file,"r");             //open input file
    sp_tuples *matrix = malloc(sizeof(sp_tuples));      //allocate memory for matrix

    int rows, cols;
    fscanf(openfile, "%d %d", &rows, &cols);          //read matrix dimension from input file

    matrix->nz = 0;                                     //set non zero to 0
    matrix->m = rows;                                   //copy and setup dimension into new matrix
    matrix->n = cols;
    matrix->tuples_head = NULL;

    double tupleValue;                                  //variable to store locations from input file
    

    while (feof(openfile)==0) { 
        fscanf(openfile, "%d %d %lf", &rows, &cols, &tupleValue);       //read input file                                                       //create linked list
        set_tuples(matrix, rows, cols, tupleValue);
    }

    fclose(openfile);                                   //close input file
    return matrix;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node *traverse = mat_t->tuples_head;            //initialize pointer to traverse all cells 
    
    while (traverse!=NULL) {
        if (traverse->row==row && traverse->col==col) {
            return traverse->value;         //return the value at the corresponding coordinate
        }
        else {
            traverse = traverse->next;      //go to next cell
        }
    }
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    if (value==0) {         //if value is zero
        sp_tuples_node *current = mat_t->tuples_head;       //new node
        sp_tuples_node *before = NULL;

        while (current!=NULL) {    
            if (before==NULL && current->row==row && current->col==col) {      //if node with row and col is found but previous is NULL
                mat_t->tuples_head = mat_t->tuples_head->next;          //update to next next address
                free(current);                                          //delete this node by freeing memory
                mat_t->nz--;                                            //decrement nz counter
                return;                                           
            }
            else if (current->row==row && current->col==col) {      //if node with row and col is found but is linked
                before->next = current->next;       //use pointers to skip current node
                free(current);                      //delete current node by freeing memory    
                mat_t->nz--;                        //decrement nz counter
                return;
            }
            before = current;                     //now that node is disappeared, update before to current
            current = current->next;               //set current to next link for next while loop to traverse through cells  
        }
        return;
    }

    if(mat_t->tuples_head==NULL) {                  //if first node doesn't exist
        mat_t->tuples_head = malloc(sizeof(sp_tuples_node));    //allocate memory for the node
        mat_t->tuples_head->value = value;      //fill in given details
        mat_t->tuples_head->next = NULL;
        mat_t->tuples_head->col = col;
        mat_t->tuples_head->row = row;
        mat_t->nz++;                //increment nz counter
        return;
    }

    //if values do not exist append new list
    sp_tuples_node *append = malloc(sizeof(sp_tuples_node));
    append->col = col;
    append->row = row;
    append->value = value;

    //add new nodes current(state a) and next node (state b)
    sp_tuples_node *a = mat_t->tuples_head;
    sp_tuples_node *b = a->next;

    while (a!=NULL) {
        int newHead = mat_t->tuples_head->row*mat_t->n+mat_t->tuples_head->col;
        int aValue = a->row * mat_t->n + a->col;        //current value is curRow*row+col
        int bValue = append->row +mat_t->n +append->col; // same as above

        if (newHead > bValue) {     //if bValue is before head memory-wise
            mat_t->tuples_head = append;
            append->next = mat_t->tuples_head;
            mat_t->nz++;            //increment nz counter
            return;
        }
        else if (aValue == bValue) {        //if current and new nodes are at the same location
            a->value = append->value;
            mat_t->nz++;
            return;
        }
        else if (bValue>aValue && bValue < (b->row*mat_t->n+b->col)) { //if current node comes before next node
            a->next = append;
            append->next = b;
            mat_t->nz++;
            return;
        }
        else if (b==NULL && bValue>aValue) {        //if next tuple is tail, null
            append->next = NULL;
            a->next = append;
            mat_t->nz++;
            return;
        }
        a = b;                      //set current node to next then loop while loop
        if (b !=NULL) {
            b = b->next;
        }
    }
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE *openfile = fopen(file_name, "w");     //open file for writing
    fprintf(openfile ,"%d %d\n", mat_t->m, mat_t->n);   //print row and col
    sp_tuples_node *traverse = mat_t->tuples_head;
    
    for (int i=0;i<mat_t->nz;i++) {     //print triplets into file
        fprintf(openfile,"%d %d %lf\n", traverse->row, traverse->col, traverse->value);
        traverse = traverse->next;
    }
    fclose(openfile);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    sp_tuples *add = malloc(sizeof(sp_tuples)); //allocate memory for new node
    add->nz = 0;
    add->m = matA->m;
    add->n = matA->n;
    sp_tuples_node *traverse = matA->tuples_head;   //create current node

    while(traverse!=NULL) {
        set_tuples(add, traverse->row, traverse->col, traverse->value); //append tuples by calling previous function
        traverse = traverse->next;
    }
	return add;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return NULL;

}


	
void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node *temp = NULL;        //set temp to null
    sp_tuples_node *traverse = mat_t->tuples_head;  //copy traversing matrix cell
    while(traverse!=NULL) {
        temp = traverse->next;
        free(traverse);         //go through all cells and free memory
        traverse = temp;
    }  
    free(mat_t);        //free entire mat_t
    return;
}  






