#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct {
  char *firstName;
  char *lastName;
  int nuid;
  struct tm birthDate;
} Student;

Student * createEmptyStudent();
Student * createStudent(const char * firstName, const char *lastName, int nuid, const char * birthDate_str);
void printStudent(Student * student);

int main(int argc, char **argv) {

  Student *me = createStudent("Joe", "Smith", 140602, "07/30/1980");
  printStudent(me);

}

char *studentToString(Student *student) {
  //create a temporary string that is "large enough"
  char *tmp = (char *) malloc(sizeof(char) * 2000);
  //format the student into the temporary string
  sprintf(tmp, "%s, %s (%08d, %d-%d-%d)\n", student->lastName, student->firstName, student->nuid, (student->birthDate.tm_year+1900), (student->birthDate.tm_mon+1), student->birthDate.tm_mday);
  //create the final string that is the exact size needed
  char *result = (char *) malloc(sizeof(char) * (strlen(tmp)+1));
  //free up the temporary string
  free(tmp);
  //return the result
  return result;
}

void printStudent(Student * student) {
  printf("%s, %s (%08d, %d-%d-%d)\n", student->lastName, student->firstName, student->nuid, (student->birthDate.tm_year+1900), (student->birthDate.tm_mon+1), student->birthDate.tm_mday);
}

/**
 * A "factory" function to create a new student structure with everything initialized to 
 * default values (null or zero)
 */
Student * createEmptyStudent() {
  Student * student = (Student *) malloc(sizeof(Student) * 1);
  student->firstName = NULL;
  student->lastName = NULL;
  student->nuid = 0;
  return student;
}

/** 
 * A "factory" function to create a new student structure initialized with the given values
 * Strings are deep copied.
 */
Student * createStudent(const char * firstName, const char *lastName, int nuid, const char * birthDate_str) {

  Student * student = (Student *) malloc(sizeof(Student) * 1);

  student->firstName = (char *) malloc(sizeof(char) * (strlen(firstName)+1));
  strcpy(student->firstName, firstName);

  student->lastName = (char *) malloc(sizeof(char) * (strlen(lastName)+1));
  strcpy(student->lastName, lastName);

  student->nuid = nuid;
  
  strptime(birthDate_str, "%m/%d/%Y", &(student->birthDate));

  return student;
}
