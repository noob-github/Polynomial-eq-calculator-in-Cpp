#include <iostream>
#include <ostream>
using namespace std;

char **split_terms(char *arr, short count_two_dim_array) {
  short j = 0, i = 0, count = 0;
  char **splitted_terms = new char *[count_two_dim_array + 1];
  splitted_terms[count_two_dim_array] = nullptr;
  while (arr[j] != '\0' && arr[i] != '\0') {
    if (arr[i] == '+' || arr[i] == '-') {
      j++;

      while (arr[j] != '\0' && arr[j] != '+' && arr[j] != '-') {
        j++;
      }

      splitted_terms[count] = new char[j - i + 1];
      splitted_terms[count][j - i] = '\0';
      for (short k = 0; k + i < j; k++) {
        splitted_terms[count][k] = arr[i + k];
      }
      splitted_terms[count] = splitted_terms[count];
      count++;
      i = j;
    } else {
      i++, j++;
    }
  }
  return splitted_terms;
}

float *solve_term(float variable, char **splitted_terms,
                  short count_two_dim_array, char varChar) {
  short i = 0;
  float *result = new float[count_two_dim_array];
  cout << "variable character is " << varChar << endl;
  // cout<<"count_two_dim_array"<<count_two_dim_array<<endl;
  // cout<<"variable"<<variable<<endl;

  while (splitted_terms[i] != nullptr) {
    result[i] = 1;
    char *temp_array = splitted_terms[i];
    for (short j = 1; temp_array[j] != '\0'; j++) {
      cout << "temp_array - " << temp_array[j] << " ";
      if (temp_array[j] == '*') {
        continue;
      } else if (temp_array[j] == varChar) {
        result[i] = result[i] * variable;
        cout << "result by mult by variable x " << result[i] << endl;
      } else {
        short k = j;
        float temp_result = 0;
        short divideByMe = 1;
        bool isFloatingPoint = false;
        while (temp_array[k] != '*' && temp_array[k] != '\0') {
          if (isFloatingPoint)
            divideByMe = divideByMe * 10;

          if (temp_array[k] == '.')
            isFloatingPoint = true;
          if (temp_array[k] != '.') {
            temp_result = temp_result * 10;
            temp_result = temp_result + int(temp_array[k]) - 48;
          }
          k++;
        }
        j = k - 1;
        if (isFloatingPoint)
          temp_result = temp_result / divideByMe;
        result[i] = result[i] * temp_result;
        cout << result[i] << endl;
      }
    }
    // cout<<"temp array first sign"<<temp_array[0]<<endl;
    if (temp_array[0] == '-') {
      // cout<<"turning positive to -ve"<<endl;
      // cout<<result[i]<<"before turning to negetive"<<endl;
      result[i] = (-1.00) * result[i];
      // cout<<result[i]<<"after turning to negetive"<<endl;
    }
    cout << "array has result : " << temp_array << " i has value " << i
         << " and result " << result[i] << endl;
    i++;
  }

  return result;
}

char returnVarChar(char *equation) {
  short i = 0;
  while (int(equation[i]) < 65 ||
         (int(equation[i]) > 90 && int(equation[i]) < 97) ||
         equation[i] > 122) {
    i++;
  }
  return equation[i];
}

int main() {
  char equation[25];
  std::cout << "Enter your equation : " << std::endl;
  cin >> equation;
  cout << "Enter value of variable : ";
  float x;
  cin >> x;
  char varChar;

  char *offset_equation;
  short count_two_dim_array = 0, lenght = 0;

  for (short i = 0; equation[i] != '\0'; i++) {
    lenght++;
  }
  lenght++;

  if (equation[0] == '+' || equation[0] == '-') {
    // do nothing
    offset_equation = equation;
  } else {
    offset_equation = new char[lenght + 2];
    for (short i = 1; i <= lenght; i++) {
      offset_equation[i] = equation[i - 1];
    }
    offset_equation[0] = '+';
    lenght++;
  }

  for (short i = 0; offset_equation[i] != '\0'; i++) {
    if (offset_equation[i] == '+' || offset_equation[i] == '-') {
      count_two_dim_array++;
    }
  }

  varChar = returnVarChar(offset_equation);

  char **returnedSplittedterms =
      split_terms(offset_equation, count_two_dim_array);

  for (short i = 0; returnedSplittedterms[i] != nullptr; i++) {
    for (short j = 0; returnedSplittedterms[i][j] != '\0'; j++) {
      cout << returnedSplittedterms[i][j];
    }
    cout << endl;
  }

  cout << endl;

  float *addMe = solve_term(x, returnedSplittedterms, count_two_dim_array,
                            returnVarChar(offset_equation));

  short i = 0;

  float final_result = 0;
  while (i < count_two_dim_array) {
    final_result = final_result + addMe[i];
    i++;
  }
  cout << "Hoooray your equation gives value " << final_result
       << " at given value of variable" << endl;

  return 0;
}
