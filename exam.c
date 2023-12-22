#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StudentNode {
  char name[50];
  int mark;
  int rollno;
  struct StudentNode* next;
} StudentNode;

StudentNode* addStudent(StudentNode* last, char name[], int mark, int rollno) {
  if(rollno <= 0 || mark < 0 || mark > 100) {
      printf("Invalid roll number or mark.\n");
      return last;
  }

  StudentNode* temp = (StudentNode*)malloc(sizeof(StudentNode));
  strcpy(temp->name, name);
  temp->mark = mark;
  temp->rollno = rollno;

  if(last == NULL) {
      temp->next = temp;
  } else {
      temp->next = last->next;
      last->next = temp;
  }

  last = temp;
  return last;
}

void displayStudents(StudentNode* last) {
  if(last == NULL) {
      printf("No students.\n");
      return;
  }

  StudentNode* temp = last->next;
  do {
      printf("Name: %s, Mark: %d, Roll No: %d\n", temp->name, temp->mark, temp->rollno);
      temp = temp->next;
  } while(temp != last->next);
}

void displayHighestMarkStudent(StudentNode* last) {
  if(last == NULL) {
      printf("No students.\n");
      return;
  }

  StudentNode* temp = last->next;
  char highestMarkStudentName[50];
  int highestMark = -1;
  do {
      if(temp->mark > highestMark) {
          highestMark = temp->mark;
          strcpy(highestMarkStudentName, temp->name);
      }
      temp = temp->next;
  } while(temp != last->next);

  printf("Student with highest mark: %s, Mark: %d\n", highestMarkStudentName, highestMark);
}

void splitStudents(StudentNode* last, StudentNode** failedList, StudentNode** passedList) {
  if(last == NULL) {
      printf("No students.\n");
      return;
  }

  StudentNode* temp = last->next;
  do {
      if(temp->mark < 40) {
          *failedList = addStudent(*failedList, temp->name, temp->mark, temp->rollno);
      } else {
          *passedList = addStudent(*passedList, temp->name, temp->mark, temp->rollno);
      }
      temp = temp->next;
  } while(temp != last->next);
}

int main() {
  StudentNode* last = NULL; 
  char name[50];
  int mark, rollno;

  printf("Enter student details (name, mark, rollno): ");
  scanf("%s %d %d", name, &mark, &rollno);
  last = addStudent(last, name, mark, rollno);

  printf("Enter more student details (name, mark, rollno): ");
  scanf("%s %d %d", name, &mark, &rollno);
  last = addStudent(last, name, mark, rollno);

  displayStudents(last);

  displayHighestMarkStudent(last);

  StudentNode* failedList = NULL;
  StudentNode* passedList = NULL;
  splitStudents(last, &failedList, &passedList);

  printf("Failed students:\n");
  displayStudents(failedList);

  printf("Passed students:\n");
  displayStudents(passedList);

  return 0;
}

