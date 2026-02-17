#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 

int findCommonDigit(unsigned long long n1, unsigned long long n2);
int moveDuplicatV1(int* arr, int n);
int MoveDuplicatV2(int* arr, int n);
int stringPermutation(char* str);
int validateArray(int* arr, int n)
;

//EX1
int findCommonDigit(unsigned long long n1, unsigned long long n2)
{
	int x = n1 % 10;
	int y = n2 % 10;
	if (n1==0 || n2==0)
	{
		return -1;
	}
	if (x == y)
	{
		return x;

	}
	else if (x>y)
	{
		n1 = n1 / 10;

	}
	else
	{
		n2 = n2 / 10;
	}
	findCommonDigit(n1, n2);

}
//EX2A
int moveDuplicatV1(int* arr, int n) {
	int* monim = (int*)calloc(2 * n + 1, sizeof(int));//create array to 2*n +1 size to use for counting apearneces
	assert(monim);
	for (int i = 0; i < n; i++)//for fill up th monim array
	{
		if (monim[arr[i]] < 0)monim[-arr[i] + n]++;
		monim[arr[i] + n]++;
	}
	int uniqeIndex = 0;//counting the unique numbers
	for (int i = 0; i < n; i++)//the main loop for counting and flaggings tha duplicates numbres
	{
		int monimIndex = arr[i] + n; /*just easier to read*/
		if (monim[monimIndex] > 0)
		{
			arr[uniqeIndex] = arr[i]; /*chacking if there is a value that hasen't been used yet*/
			uniqeIndex++;
			monim[monimIndex] = -(monim[monimIndex] - 1);//flag the dup num
		}

	}
	int DuplicateIndex = uniqeIndex;
	for (int i = 0; i < n; i++)//to put all the dup num at the right 
	{
		int monimIndex = arr[i] + n;
		while (monim[monimIndex] < 0) {
			arr[DuplicateIndex] = arr[i];
			DuplicateIndex++;
			monim[monimIndex]++;
			if (monim[monimIndex] == 0)break;
		}
	}
	free(monim);
	return uniqeIndex;//return num of unique numbers
}

//EX2B
int MoveDuplicatV2(int* arr, int n) {
	int* duplicateArray = (int*)calloc(2 * n, sizeof(int));//create array of 0 size 2n
	int i, offSet = 0, k;//offset= for counting num of dup,k is for the target in binsearch
	for (i = 0; i < n; i++) {//fill up the left side of the array
		duplicateArray[i] = arr[i];
	}

	QuickSort(duplicateArray, 0, n - 1);//sort the left side of the array
	for (i = 0; i < n; i++)
	{
		k = leftBinsearch(arr[i], duplicateArray, n);//k=target (key) for the binsearch
		duplicateArray[k + n]++;//increases the num of the index at the right side according to the index of the original array
		if (duplicateArray[k + n] > 1) offSet++;//chaching if the index of side of monim in the array is bigger then 1 and counting the amount of dup .
		else if (offSet > 0) {//if there are dup in the araay , slide them to the right 
			swapEX4(&arr[i], &arr[i - offSet]);
		}
	}
	free(duplicateArray);//realse the memory that we took from the biginning...
	return n - offSet;// returning the num of unique numbers
}

//EX3
int stringPermutation(char* str) {
	int n = strlen(str);
	int i = n - 2, j = n - 1;

	// Step 1: Find the first character that is smaller than the character next to it
	while (i >= 0 && str[i] >= str[i + 1]) {
		i--; // Searching for the first jump (ascending) from the right
	}
	if (i < 0) return 0; // If there is no jump, return 0

	// Step 2: Find the smallest character on the right side of i that is larger than str[i]
	while (str[j] <= str[i]) {
		j--;
	}

	// Step 3: Swap the found characters
	char temp = str[i];
	str[i] = str[j];
	str[j] = temp;

	// Step 4: Reverse the sequence from i + 1 to the end of the string
	int left = i + 1;
	int right = n - 1;
	while (left < right) {
		char temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		left++;
		right--;
	}

	return 1; // Return 1 to indicate success
}
//EX4
int validateArray(int* arr, int n)
{
	// נוודא שהמספרים בטווח 0 עד n-1
	for (int i = 0; i < n; i++) {
		if (arr[i] < 0 || arr[i] >= n) {
			return 0; // מספר מחוץ לטווח
		}
	}

	// נשתמש בסימון כדי לבדוק אילו מספרים נראו
	for (int i = 0; i < n; i++) {
		// נחשב את המיקום של המספר
		int index = arr[i];

		// אם הערך במיקום הזה הוא שלילי, זה אומר שכבר ראינו את המספר
		if (arr[index] < 0) {
			return 0; // מספר חוזר על עצמו
		}

		// אחרת, נשנה את הערך למספר שלילי כדי לסמן שראינו את המספר
		arr[index] = -arr[index];
	}

	// אם הגענו לכאן, כל המספרים בטווח נמצאים
	return 1;
}

