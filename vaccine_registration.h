
#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_LENGTH 256

typedef struct {
	int id;
	char name[MAX_LENGTH];
	int age;
	char vaccine_type[MAX_LENGTH];
	char first_dose_date[MAX_LENGTH];
	char second_dose_date[MAX_LENGTH];
	int vaccinated;
} User;


User* register_user(User *users, int *count);
void view_users(User *users, int count);
void search_user(User *users, int count);
User* delete_user(User *users, int *count);
void save_users(const char* filename, User *users, int count);
User* load_users(const char* filename , int *count);
int count_total_users(int count);
int count_fully_vaccinated_users(User *users, int count);
float vaccination_percentage(User *users, int count);
void age_distribution(User *users, int count);
void check_and_send_reminders(User *users, int count);
void update_vaccination_status(User *users, int count);
