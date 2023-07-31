// tryNN.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
//#include <fstream>

const int input = 3, HN1 = 35, HN2 = 20, output = 2;

// Define the activation function (ReLU) for the hidden layer
double relu(double x) 
{
    return (x > 0) ? x : 0;
}

// Define the activation function (Softmax) for the output layer
double softmax(double output[], int n_output) 
{
    double label = 0;
    double max_val = output[0];
    for (int i = 1; i < n_output; i++) {
        if (output[i] > max_val) 
        {
            max_val = output[i];
        }
    }

    double sum_exp = 0;
    for (int i = 0; i < n_output; i++) 
    {
        output[i] = exp(output[i] - max_val);
        sum_exp += output[i];
    }

    for (int i = 0; i < n_output; i++) 
    {
        output[i] /= sum_exp;
       // printf("\nOutput of the MLP : % lf", output[i]);
        
    }
    if (output[0] > output[1])
        label = 1;// return()printf("\n\nBefore Brushing\n");
    else
        label = 2; //printf("\n\nAter Brushing\n");

    return(label);
}

// Function to calculate the output of the MLP
double forward_propagation(double input_data[], double weights_ih1[][input], double bias1[],double weights_h1h2[][HN1], double bias2[], double weights_h2o[][HN2], double bias3[], double predict[])
{
    int n_output = output/* number of neurons in the output layer */;

    // Output of Hidden layer 1 
    int k = 0;
    double hidden_output1[HN1];
    for (int i = 0; i < HN1; i++) 
    {
        double z_h = bias1[i];
        for (int j = 0; j < input; j++) 
        {
            z_h += weights_ih1[i][j] * input_data[j];
            k = 1;
        }
        hidden_output1[i] = relu(z_h);
        k = 1;
    }

    // Output of Hidden layer 2 
    double hidden_output2[HN2];
    for (int i = 0; i < HN2; i++)
    {
        double z_h = bias2[i];
        for (int j = 0; j < HN1; j++)
        {
            z_h += weights_h1h2[i][j] * hidden_output1[j];
            k = 1;
        }
        hidden_output2[i] = relu(z_h);
        k = 1;
    }

    // Output layer calculations
    
    for (int i = 0; i < output; i++) 
    {
        double z_o = bias3[i];
        for (int j = 0; j < HN2; j++) 
        {
            z_o += weights_h2o[i][j] * hidden_output2[j];
            k = 1;
        }
        predict[i] = z_o;
        k = 1;
    }

    double label=softmax(predict, n_output);
    return(label);
}

int main() 
{
        // Define the file pointer
    FILE* file1, * file2, * file3, * file4, * file5, * file6, * file7;
        errno_t err;         
       
        // Open the file for reading
        file1 = fopen("Weight1.txt", "r");
       // file = fopen_s("");
        if (file1 == NULL)
        {
            printf("Error opening the file.\n");
            return 1;
        }        
        const int ROWS1 = HN1, COLUMNS1 = input;
        // Create a 2D array to store weight1 (weight between inputs and nodes in hidden layer 1)
        double weights_ih1[ROWS1][COLUMNS1];

        // Read the data from the file and store it in the array
        for (int i = 0; i < ROWS1; i++) {
            for (int j = 0; j < COLUMNS1; j++) {
                if (fscanf(file1, "%lf", &weights_ih1[i][j]) != 1)
                {
                    printf("Error reading data from the file.\n");
                    fclose(file1);
                    return 1;
                }
            }
        }    
        fclose(file1);
        //--------------------------------------------------------------------------------------
        file2 = fopen("Weight2.txt", "r");
        if (file2 == NULL)
        {
            printf("Error opening the file.\n");
            return 1;
        }
        const int ROWS2 = HN2, COLUMNS2 = HN1;
        // Create a 2D array to store the data
        double weights_h1h2[ROWS2][COLUMNS2];

        // Read the data from the file and store it in the array
        for (int i = 0; i < ROWS2; i++) {
            for (int j = 0; j < COLUMNS2; j++) {
                if (fscanf(file2, "%lf", &weights_h1h2[i][j]) != 1)
                {
                    printf("Error reading data from the file.\n");
                    fclose(file2);
                    return 1;
                }
            }
        }
        fclose(file2);
        //---------------------------------------------------------------------------------------
        file3 = fopen("Weight3.txt", "r");
        if (file3 == NULL)
        {
            printf("Error opening the file.\n");
            return 1;
        }
        const int ROWS3 = output, COLUMNS3 = HN2;
        // Create a 2D array to store the data
        double weights_h2o[ROWS3][COLUMNS3];

        // Read the data from the file and store it in the array
        for (int i = 0; i < ROWS3; i++) {
            for (int j = 0; j < COLUMNS3; j++) {
                if (fscanf(file2, "%lf", &weights_h2o[i][j]) != 1)
                {
                    printf("Error reading data from the file.\n");
                    fclose(file3);
                    return 1;
                }
            }
        }
        fclose(file3);
        //---------------------------------------------------------------------------------------
        file4 = fopen("Bias1.txt", "r");
        if (file4 == NULL)
        {
            printf("Error opening the file.\n");
            return 1;
        }
        const int ROWS4 = HN1;
        // Create a 2D array to store the data
        double bias1[ROWS4];

        // Read the data from the file and store it in the array
        for (int i = 0; i < ROWS4; i++) {
           if (fscanf(file4, "%lf", &bias1[i]) != 1)
           {
                printf("Error reading data from the file.\n");
                fclose(file4);
                return 1;                
            }
        }
        fclose(file4);        
        //---------------------------------------------------------------------------------------
        file5 = fopen("Bias2.txt", "r");
        if (file5 == NULL)
        {
            printf("Error opening the file.\n");
            return 1;
        }
        const int ROWS5 = HN2;
        // Create a 2D array to store the data
        double bias2[ROWS5];

        // Read the data from the file and store it in the array
        for (int i = 0; i < ROWS5; i++) {
            if (fscanf(file5, "%lf", &bias2[i]) != 1)
            {
                printf("Error reading data from the file.\n");
                fclose(file5);
                return 1;
            }
        }
        fclose(file5);
        //---------------------------------------------------------------------------------------
        file6 = fopen("Bias1.txt", "r");
        if (file6 == NULL)
        {
            printf("Error opening the file.\n");
            return 1;
        }
        const int ROWS6 = output;
        // Create a 2D array to store the data
        double bias3[ROWS6];

        // Read the data from the file and store it in the array
        for (int i = 0; i < ROWS6; i++) {
            if (fscanf(file6, "%lf", &bias3[i]) != 1)
            {
                printf("Error reading data from the file.\n");
                fclose(file6);
                return 1;
            }
        }
        fclose(file6);
        //---------------------------------------------------------------------------------------
        file7 = fopen("LatestData.txt", "r");
        if (file7 == NULL)
        {
            printf("Error opening the file.\n");
            return 1;
        }

        const int ROWS7 = 90, COLUMNS7 = 4;
        // Create a 2D array to store the data
        double inputData[ROWS7][COLUMNS7];

        // Read the data from the file and store it in the array
        for (int i = 0; i < ROWS7; i++) {
            for (int j = 0; j < COLUMNS7; j++) {
                if (fscanf(file7, "%lf", &inputData[i][j]) != 1)
                {
                    printf("Error reading data from the file.\n");
                    fclose(file7);
                    return 1;
                }
            }
        }

        // Close the file
        fclose(file7);

        /*printf("Data read from the file:\n");
        for (int i = 0; i < ROWS2; i++) 
        {
            for (int j = 0; j < COLUMNS2; j++) 
            {
                printf("%lf ", inputData[i][j]);
            }
            printf("\n");
        }*/
    
        double predict[output] = { 0,0 };
        double input_data[input] = { 0.0775,     0.141,     0.184 };
//        2	0.0775	0.141	0.184

        double out_data[90];
        double label = 0;
     
        // Call the forward_propagation function to get the output of the MLP
        label = forward_propagation(input_data, weights_ih1, bias1, weights_h1h2, bias2, weights_h2o, bias3, predict);
        
        if(abs(label)==1)
            printf("Before brushing\n");
        else
            printf("After brushing\n");
    
       
    return 0;
}
