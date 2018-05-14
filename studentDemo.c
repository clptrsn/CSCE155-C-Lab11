#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * A structure modeling a UNL student with
 * first name, last name, nuid and a birth date
 * (as a tm, "time" structure)
 */
typedef struct {
  char *firstName;
  char *lastName;
  int nuid;
  struct tm birthDate;
} Student;

/**
 * Creates an "empty" Student struct with default values
 */
Student *createEmptyStudent();

/**
 * Creates a Student struct with the given values
 */
Student *createStudent(const char *firstName, const char *lastName, int nuid,
                       const char *birthDate_str);

/**
 * Prints the given Student struct to the standard output
 */
void printStudent(Student *student);

int main(int argc, char **argv) {
  Student *me = createStudent("Joe", "Smith", 140602, "07/30/1980");
  printStudent(me);
}

char *studentToString(Student *student) {
  if (student == NULL) {
    char *result = (char *)malloc(sizeof(char) * 7);
    strcpy(result, "(null)");
    return result;
  }

  // compute the number of characters we'll need:
  int n = strlen(student->lastName) + strlen(student->firstName) + 8 + 10 +
          (2 + 2 + 2 + 1) + 1;

  // create a result string
  char *str = (char *)malloc(sizeof(char) * n);

  // format the student into the temporary string
  sprintf(str, "%s, %s (%08d, %4d-%02d-%02d)", student->lastName,
          student->firstName, student->nuid,
          (student->birthDate.tm_year + 1900), (student->birthDate.tm_mon + 1),
          student->birthDate.tm_mday);

  // return the result
  return str;
}

void printStudent(Student *student) {
  char *str = studentToString(student);
  printf("%s\n", str);
  free(str);
  return;
}

Student *createEmptyStudent() { return createStudent("", "", 0, ""); }

Student *createStudent(const char *firstName, const char *lastName, int nuid,
                       const char *birthDate_str) {
  Student *student = (Student *)malloc(sizeof(Student) * 1);

  student->firstName = (char *)malloc(sizeof(char) * (strlen(firstName) + 1));
  strcpy(student->firstName, firstName);

  student->lastName = (char *)malloc(sizeof(char) * (strlen(lastName) + 1));
  strcpy(student->lastName, lastName);

  student->nuid = nuid;

  strptime(birthDate_str, "%m/%d/%Y", &(student->birthDate));

  return student;
}
