#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/** Denizkaan Araci*/
/** 21426606 */

typedef struct data_list{
    char *val;
    char *format;
    struct data_list * next;
} OUTPUT;

typedef struct operand_operator{

    char *element;

    struct operand_operator * next;

} STACKS;

void command_definer(FILE *,FILE *,OUTPUT *);
void parse_expression(char *, char **,char *,int *);
void init(STACKS* );
void syntax_test(char *, char **,int *);
void push(STACKS **,char *);
void pop(STACKS ** ,char **);
void push_data(OUTPUT **,char *, char *);
void Print(OUTPUT **,FILE *);


/*this is calculation function. it determines format and calculates.*/
void Calculate(char *pop_operator,char *pop_operand1,char *pop_operand2,char **calculated_operand, char *format){

    int number1;
    int number2;
    int cal_result;

    if (!strcmp(format, "integer")){

        number1 = strtol(pop_operand1,NULL,10);
        number2 = strtol(pop_operand2,NULL,10);
    }
    else if(!strcmp(format, "hex")){
        number1 = strtol(pop_operand1,NULL,16);
        number2 = strtol(pop_operand2,NULL,16);
    }

    if(pop_operator == '+'){
        cal_result = number1 + number2;
    }
    else if(pop_operator == '-'){
        cal_result = number1 - number2;
    }
    else if(pop_operator == '*'){
        cal_result = number1 * number2;
    }
    else if(pop_operator == '/'){
        cal_result = number1 / number2;
    }

    char buff[256];

    if (!strcmp(format, "integer")){

        sprintf(buff,"%d",cal_result);
        *calculated_operand=(char*)malloc(strlen(buff)+1);
        strcpy(*calculated_operand,buff);
    }
    else if(!strcmp(format, "hex")){

        sprintf(buff,"%X",cal_result);
        *calculated_operand=(char*)malloc(strlen(buff)+1);
        strcpy(*calculated_operand,buff);
    }


}
/*this function pops element from stacks */
void pop(STACKS ** Start,char **popped_element){

        if(*Start == NULL){
            return 0;
        }

        STACKS* temp = (*Start) -> next;


        if((*Start)->element == '+' || (*Start)->element == '-' || (*Start)->element == '*' || (*Start)->element == '/'
                || (*Start)->element == '(' || (*Start)->element == ')'|| (*Start)->element == '$'|| (*Start)->element == '£'){


            *popped_element = (*Start)->element;
        }

        else{
            *popped_element = (char*)malloc(strlen(((*Start)->element)+1));
            strcpy(*popped_element, (*Start)->element);
        }



        free(*Start);
        if(temp == NULL){

        }
        *Start = temp;
}
/*this function pushes element to stacks*/
void push(STACKS **Start,char *element){

    STACKS* temp;
    temp = (STACKS*)malloc(sizeof(STACKS));

    if(element == '+' || element == '-' || element == '*' || element == '/' || element == '(' || element == ')' || element == '$' || element == '£'){
        temp->element =element;
    }
    else if(element == NULL){

    }
    else{
        temp ->element = (char*)malloc(strlen(element+1));
        strcpy(temp->element, element);
    }


    temp -> next = *Start;
    *Start = temp;

}
/*this function checks syntax with given rules*/
void syntax_test(char *expression,char **result,int *error_counter){

    int exp_length = strlen(expression);
    int i;
    int left_para=0;
    int right_para=0;


    for(i=0;i<exp_length;i++){

        if(expression[i] == '('){
            left_para++;
        }
        if(expression[i] == ')'){
            right_para++;
        }
        if(((expression[i] != '+') && (expression[i] != '-') && (expression[i] != '*') && (expression[i] != '/')
                 && (expression[i] != '(') && (expression[i] != ')') && isalnum(expression[i]) ==0)){

           *error_counter=1;
            break;
        }

        else if(i == 0 && exp_length == 1){

            if(isalnum(expression[i]) ==0){
                *error_counter=1;
                break;
            }
        }
        else if(i == 0 && exp_length>1) {

            if(exp_length==2){
                if(isalnum(expression[0]) == 0 && isalnum(expression[1]) == 0){
                    *error_counter=1;
                    break;
                }
                else if((expression[0] != '+' && expression[0] != '-')){
                    if(isalnum(expression[0]) == 0 && !isalnum(expression[1]) == 0){
                        *error_counter=1;
                        break;
                    }
                    else if(!isalnum(expression[0]) == 0 && isalnum(expression[1]) == 0){
                        *error_counter=1;
                        break;
                    }
                }

            }
            else if(expression[0] == ')' || expression[0] == '*' || expression[0] == '/'){
                *error_counter=1;
                break;
            }
            else if(expression[0] == '(' && expression[1] == ')'){
                *error_counter=1;
                break;
            }
            else if(expression[0] == '+' && expression[1] == '+'){
                *error_counter=1;
                break;
            }
            else if(expression[0] == '+' && expression[1] == '-'){
                *error_counter=1;
                break;
            }
            else if(expression[0] == '+' && expression[1] == '*'){
                *error_counter=1;
                break;
            }
            else if(expression[0] == '+' && expression[1] == '/'){
                *error_counter=1;
                break;
            }
            else if(expression[0] == '-' && expression[1] == '-'){
                *error_counter=1;
                break;
            }
            else if(expression[0] == '-' && expression[1] == '+'){
                *error_counter=1;
                break;
            }
            else if(expression[0] == '-' && expression[1] == '*'){
                *error_counter=1;
                break;
            }
            else if(expression[0] == '-' && expression[1] == '/'){
                *error_counter=1;
                break;
            }

        }
        else if(exp_length>1 && i<exp_length-1){


            if(expression[i] == '(' && expression[i+1] ==')'){
                *error_counter=1;
                break;
            }
            else if(expression[i] == ')' && expression[i+1] =='('){
                *error_counter=1;
                break;
            }
            else if(expression[i] == '(' && expression[i+1] =='*'){
                *error_counter=1;
                break;
            }
            else if(expression[i] == '(' && expression[i+1] =='/'){
                *error_counter=1;
                break;
            }
            else if(expression[i] == '(' && (expression[i+1] =='+' || expression[i+1] =='-') && isalnum(expression[i+2]) == 0 && expression[i+2] !=')' && expression[i+2] !='('){
                *error_counter=1;

                break;
            }
            else if((expression[i] == '+' || expression[i] == '-') && (expression[i+1] == '+' || expression[i+1] == '-') && (expression[i+2] == '+' || expression[i+2] == '-')){
                *error_counter=1;
                break;
            }
            else if(expression[i] == '*' && expression[i+1] == '+' ){
                if(expression[i+2] =='+' || expression[i+2] == '-' || expression[i+2] == '*' || expression[i+2] == '/' || expression[i+2] == ')' ){
                    *error_counter=1;
                    break;
                }
            }
            else if(expression[i] == '*' && expression[i+1] == '-' ) {
                if(expression[i+2] =='+' || expression[i+2] =='-' || expression[i+2] =='*' || expression[i+2] =='/' || expression[i+2] ==')' ){
                    *error_counter=1;
                    break;
                }
            }
            else if(expression[i] == '/' && expression[i+1] == '+' ) {
                if(expression[i+2] =='+' || expression[i+2] == '-' || expression[i+2] =='*' || expression[i+2] =='/' || expression[i+2] ==')' ){
                    *error_counter=1;
                    break;
                }
            }
            else if(expression[i] == '/' && expression[i+1] == '-' ) {
               if(expression[i+2] =='+' || expression[i+2] =='-' || expression[i+2] =='*' || expression[i+2] =='/' || expression[i+2] ==')' ){
                    *error_counter=1;
                    break;
                }
            }
            else if(expression[i] == '*' && expression[i+1] == '*' ) {
                *error_counter=1;
                break;
            }
            else if(expression[i] == '*' && expression[i+1] == '/' ) {
                *error_counter=1;
                break;
            }
            else if(expression[i] == '/' && expression[i+1] == '/' ) {
                *error_counter=1;
                break;
            }
            else if(expression[i] == '/' && expression[i+1] == '*' ) {
                *error_counter=1;
                break;
            }
            else if(expression[i] == '+' && expression[i+1] == '*' ) {
                *error_counter=1;
                break;
            }
            else if(expression[i] == '+' && expression[i+1] == '/' ) {
                *error_counter=1;
                break;
            }
            else if(expression[i] == '-' && expression[i+1] == '*' ) {
                *error_counter=1;
                break;
            }
            else if(expression[i] == '-' && expression[i+1] == '/' ){
                *error_counter=1;
                break;
            }

        }

	}
	/*error occures if right brackets not equal right brackets*/
	if(left_para != right_para){
        *error_counter=1;
	}

}



void init(STACKS* head)
{
    head = NULL;
}

void parse_expression(char *expression_raw, char **result,char *format,int *error_counter){

    STACKS *operator_stack = NULL;
    STACKS *operand_stack = NULL;

    init(operator_stack);
    init(operand_stack);
    syntax_test(expression_raw,&result,error_counter);
    /*if any error in syntax test, parse will stop*/
    if(*error_counter == 1){

        return ;
    }


    char *element = NULL;
    char *oprtr;
    char *pop_operator;
    char *pop_operand1;
    char *pop_operand2;
    char *calculated_operand;
    char *unary_minus = '£';
    char *unary_plus = '$';
    char buffer[256];

    int i;
    int j=0;
    char* tempstr = calloc(strlen(expression_raw)+1, sizeof(char));
    strcpy(tempstr, expression_raw);

    for(i=0;i<strlen(expression_raw);i++){

        oprtr = expression_raw[i];

        if(!isalnum(expression_raw[i]) == 0){

            if(element==NULL && j == 0){
                element=strtok(tempstr,"+-*/()");

                j=1;
                push(&operand_stack,element);

            }
            else if(element ==NULL && j == 1){

                element=strtok(NULL,"+-*/()");
                push(&operand_stack,element);

            }
        }


        else if (oprtr == '+' || oprtr == '-' || oprtr == '*' || oprtr == '/'){

            element = NULL;


            if(oprtr == '+' || oprtr == '-'){


                if(i == 0){
                    if(oprtr == '+'){

                        push(&operator_stack,unary_plus);

                    }
                    else{
                        push(&operator_stack,unary_minus);
                    }
                }
                else{
                    if(expression_raw[i-1] == ')' || !isalnum(expression_raw[i-1]) == 0){
                        if(operator_stack == NULL){

                            push(&operator_stack,oprtr);
                        }
                        else{
                            pop(&operator_stack,&pop_operator);
                            if(pop_operator == '+' || pop_operator == '-' || pop_operator == '*' || pop_operator == '/'){

                                pop(&operand_stack,&pop_operand2);
                                pop(&operand_stack,&pop_operand1);
                                Calculate(pop_operator,pop_operand1,pop_operand2,&calculated_operand,format);
                                push(&operand_stack,calculated_operand);
                                push(&operator_stack,oprtr);
                            }
                            else if(pop_operator == unary_plus || pop_operator == unary_minus){

                                pop(&operand_stack,&pop_operand2);
                                if(pop_operator == unary_plus){
                                    Calculate('*',"1",pop_operand2,&calculated_operand,format);
                                }
                                else if(pop_operator == unary_minus){
                                    Calculate('*',"-1",pop_operand2,&calculated_operand,format);
                                }

                                push(&operand_stack,calculated_operand);
                                pop(&operator_stack,&pop_operator);

                                push(&operator_stack,oprtr);

                            }
                            else{

                                push(&operator_stack,pop_operator);
                                push(&operator_stack,oprtr);

                            }
                        }

                    }
                    else{
                        if(oprtr == '+' && expression_raw[i-1]=='('){     /****/

                            push(&operator_stack,unary_plus);
                        }
                        else if(oprtr == '-' && expression_raw[i-1]=='('){
                            push(&operator_stack,unary_minus);
                        }
                        else if(oprtr == '-' && expression_raw[i-1]=='-'){
                            pop(&operator_stack,&pop_operator);
                            push(&operator_stack,'+');
                        }
                        else if(oprtr == '-' && expression_raw[i-1]=='+'){
                            pop(&operator_stack,&pop_operator);
                            push(&operator_stack,'-');
                        }

                        else if(oprtr == '-'  && (expression_raw[i-1]=='*' || expression_raw[i-1]=='/')){
                            push(&operator_stack,unary_minus);
                        }
                    }
                }
            }
            else if(oprtr == '*' || oprtr == '/'){

                if(operator_stack == NULL){
                    push(&operator_stack,oprtr);
                }
                else{
                    pop(&operator_stack,&pop_operator);
                    if(pop_operator == '*' || pop_operator == '/'){
                        pop(&operand_stack,&pop_operand2);
                        pop(&operand_stack,&pop_operand1);
                        Calculate(pop_operator,pop_operand1,pop_operand2,&calculated_operand,format);

                        push(&operand_stack,calculated_operand);

                        push(&operator_stack,oprtr);
                    }
                    else if(pop_operator == unary_plus || pop_operator == unary_minus){
                        pop(&operand_stack,&pop_operand2);

                        if(pop_operator == unary_plus){
                            Calculate('*',"1",pop_operand2,&calculated_operand,format);
                        }
                        else{
                            Calculate('*',"-1",pop_operand2,&calculated_operand,format);
                        }
                        push(&operand_stack,calculated_operand);
                        push(&operator_stack,oprtr);


                    }
                    else{
                        push(&operator_stack,pop_operator);
                        push(&operator_stack,oprtr);
                    }
                }
            }
        }
        else if(oprtr =='('){
            element = NULL;

            push(&operator_stack,oprtr);

        }
        else if(oprtr ==')'){
            element = NULL;
            pop(&operator_stack,&pop_operator);

            while(pop_operator != '('){
                pop(&operand_stack,&pop_operand2);
                if(pop_operator == unary_plus){
                    Calculate('*',"1",pop_operand2,&pop_operand2,format);
                }
                else if(pop_operator == unary_minus){
                    Calculate('*',"-1",pop_operand2,&pop_operand2,format);
                }
                if(operand_stack ==NULL){
                    push(&operand_stack,pop_operand2);
                    pop(&operator_stack,&pop_operator);
                    continue;
                }
                pop(&operand_stack,&pop_operand1);
                Calculate(pop_operator,pop_operand1,pop_operand2,&calculated_operand,format);
                push(&operand_stack,calculated_operand);
                pop(&operator_stack,&pop_operator);

            }
        }

    }

    if(operator_stack == NULL){

        pop(&operand_stack,&pop_operand2);
        if(operand_stack == NULL){
            calculated_operand=(char*)malloc(strlen(pop_operand2)+1);
            strcpy(calculated_operand,pop_operand2);

            *result=(char*)malloc(strlen(pop_operand2)+1);
            strcpy(*result,pop_operand2);
        }
        else{
            *error_counter=1;
            return;
        }


    }
    else{

        while(operator_stack !=NULL && *error_counter != 1){



            pop(&operator_stack,&pop_operator);
            if(pop_operator == unary_plus || pop_operator == unary_minus){
                pop(&operand_stack,&pop_operand2);
                if(pop_operator == unary_plus){
                    Calculate('*',"1",pop_operand2,&calculated_operand,format);
                }
                else if(pop_operator == unary_minus){
                    Calculate('*',"-1",pop_operand2,&calculated_operand,format);
                }
                push(&operand_stack,calculated_operand);
                if(operator_stack ==NULL){
                    break;
                }


            }
            else{
                push(&operator_stack,pop_operator);
            }
            /* error occures if operator stack is not empty but operand stack is empty*/
            if(operand_stack ==NULL && operator_stack !=NULL){
                *error_counter=1;

                return;
            }

            pop(&operator_stack,&pop_operator);

            if(pop_operator =='('){
                *error_counter = 1;
                return;
            }
            pop(&operand_stack,&pop_operand2);
            pop(&operand_stack,&pop_operand1);
            Calculate(pop_operator,pop_operand1,pop_operand2,&calculated_operand,format);
            push(&operand_stack,calculated_operand);

        }
        *result=(char*)malloc(strlen(calculated_operand)+1);
        strcpy(*result,calculated_operand);
    }


}

void Print(OUTPUT **Data,FILE *file_output){
    OUTPUT *current = *Data;

    while(current != NULL){
        if(!strcmp(current->val,"error")){

            fprintf(file_output,"error\n");

        }
        else{
            fprintf(file_output,"%s %s\n",current->format,current->val);

        }
        current = current->next;
    }

    *Data = NULL;
    int i;

}

void push_data(OUTPUT **Data,char *format, char *value) {

    OUTPUT *new_node = (OUTPUT*)malloc(sizeof(OUTPUT));
    OUTPUT *last = *Data;

    new_node->val = (char*)malloc(strlen(value+1));
    strcpy(new_node->val, value);
    new_node->format = (char*)malloc(strlen(value+1));
    strcpy(new_node->format, format);
    new_node->next = NULL;

    if(*Data ==NULL){
        *Data = new_node;
        return;
    }
    while(last->next != NULL){
        last = last->next;
    }
    last->next = new_node;
    return;

}

void command_definer(FILE *file_input,FILE *file_output,OUTPUT *Data){

    char line[1024];
    char *command_name;
    char *expression_raw;
    char *command_print;
    char *result;
    char *format;
    int error_counter;

    while (fgets(line, sizeof(line), file_input)){

        error_counter=0;
        command_name = strtok(line,"\"");
        expression_raw = strtok(NULL,"\"");

        if (!strcmp(command_name, "calculate integer ")){


            result = "integer expression";

            format ="integer";
            parse_expression(expression_raw,&result,format,&error_counter);
            if(error_counter == 1){
                result="error";
            }
            push_data(&Data,format,result);

        }
        else if(!strcmp(command_name, "calculate hex ")){


            result = "hex expression";
            format ="hex";

            parse_expression(expression_raw,&result,format,&error_counter);

            if(error_counter == 1){
                result="error";
            }

            push_data(&Data,format,result);
        }

        else{

            Print(&Data,file_output);


        }

    }

}

int main(int argc,char *argv[])
{

    FILE *file_input;
    FILE *file_output;


    OUTPUT * Data = NULL;
    file_input = fopen(argv[1], "r");
    file_output =fopen(argv[2], "w");


    command_definer(file_input,file_output,Data);

    fclose(file_input);
    fclose(file_output);

    return 0;
}
