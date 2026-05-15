#include <stdio.h>
#include <math.h>

float calculate_operation(float num1, float num2, int operation) {
    float ans = 0;
    
    switch(operation) {
        case 1:
            ans = num1 + num2;
            break;
        case 2:
            ans = num1 - num2;
            break;
        case 3:
            ans = num1 * num2;
            break;
        case 4:
            if (num2 != 0) {
                    ans = num1 / num2;
                } else {
                    printf("Error: Division by zero.\n");
                }
                break;
        case 5:
            ans = pow(num1, num2);
            break;
        default:
            printf("Invalid operation.\n");
    }
    return ans;
}

void add_to_history(float history[], int index, float value) {
    if (index >= 0 && index < 100) {
        history[index] = value;
    }
}

int is_history_command(float num) {
    return num == 6.0f;
}
/*
int main() {
    float ans;
    float history[100]; 
    int run;

    printf("Insert Run count = ");
    scanf("%d", &run);

    for(int j = 0; j < run; j++) {
        printf("\n");
        printf("*****************************\n");
        printf("\n-------  Operations--------\n");
        printf("Addition \t->  1\n");
        printf("Subtraction \t->  2 \n");
        printf("Multiplication \t->  3\n");
        printf("Division \t->  4\n");
        printf("Power    \t -> 5\n");
        printf("History   \t  -> 6 \n");
        printf("\n******************************\n");

        printf("\n");

        float num1;
        printf("Insert Number 1: ");
        scanf("%f", &num1);

        float num2;
        printf("Insert Number 2: ");
        scanf("%f", &num2);

        int operation;
        printf("\nSelect your operation (Ex: 1): ");
        scanf("%d", &operation);

        if (is_history_command(operation)) {
            printf("History: \n");
            for (int i = 0; i < j; i++) {
                printf("%d: %.2f\n", i + 1, history[i]);
            }
            j--; 
            continue;
        }

        ans = calculate_operation(num1, num2, operation);

        printf("Answer is: %.2f\n\n", ans);
        add_to_history(history, j, ans);
    }

    return 0;
} */