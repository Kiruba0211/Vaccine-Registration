#include "vaccine_registration.h"

User* register_user(User* users, int *count)
{
	User newUser;

	strcpy(newUser.second_dose_date, "");

	printf("Enter the user ID: \n");
	scanf("%d", &newUser.id);

	printf("Enter the user name: \n");
	scanf("%s", newUser.name);

	printf("Enter the user age: \n");
	scanf("%d", &newUser.age);

	printf("Enter the vaccine type: \n");
	scanf("%s", newUser.vaccine_type);

	printf("Enter the date of first dose (YYYY-MM-DD): \n");
	scanf("%s",newUser.first_dose_date);

	printf("Enter the date of second dose (YYYY-MM-DD): \n");
	scanf("%s", newUser.second_dose_date);

	printf("Is the user fully vaccinated? (1 for Yes, 0 for No): \n");
	scanf("%d", &newUser.vaccinated);

	users = realloc(users, (*count+1)*sizeof(User));
	if(users == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(1);
	}

	users[*count] = newUser;
	(*count)++;

	save_users("users_data.dat", users, *count);

	return users;
	
}

void view_users(User* users, int count)
{
	if(count == 0)
	{
		printf("No users registered\n");
		return;
	}

	printf("Registered Users\n");
	for(int i = 0 ; i<count; i++)
	{
		printf("User id: %d\n", users[i].id);
		printf("Name of the user: %s\n", users[i].name);
		printf("User's age: %d\n", users[i].age);
		printf("Vaccine type: %s\n", users[i].vaccine_type);
		printf("Date of first dose: %s\n", users[i].first_dose_date);
		printf("Date of second dose: %s\n", users[i].second_dose_date);
		printf("Fully vaccinated? %d \n", users[i].vaccinated); 	
		printf("\n     *****     \n");
	}
	
}

void search_user(User* users, int count)
{
	int user_id;
	printf("Enter the user id to be searched:\n");
	scanf("%d",&user_id);
	for(int i = 0; i<count; i++)
	{
		if(users[i].id == user_id)
		{
                printf("User id: %d\n", users[i].id);
                printf("Name of the user: %s\n", users[i].name);
                printf("User's age: %d\n", users[i].age);
                printf("Vaccine type: %s\n", users[i].vaccine_type);
                printf("Date of first dose: %s\n", users[i].first_dose_date);
                printf("Date of second dose: %s\n", users[i].second_dose_date);
		printf("Fully vaccinated? %d\n",users[i].vaccinated);
		return;
		}
		
	}
         printf("USER NOT FOUND!\n");

}

User* delete_user(User* users, int *count)
{
	int user_id;
	printf("Enter the user id to delete:\n");
	scanf("%d",&user_id);

	for(int i = 0; i < *count; i++)
	{
		if(users[i].id == user_id)
		{
			for(int j = i; j < *count - 1; j++)
			{
				users[j] = users[j+1];
			}
		(*count)--;
		
		users = realloc(users, (*count)*sizeof(User));
		if(users == NULL && *count>0)
		{
			printf("Memory allocation failed!\n");
			exit(1);
		}
		printf("\n*****USER DELETED SUCCESSFULLY*****\n");
		save_users("users_data.dat", users, *count);
		return users;
		}	
	}
	printf("USER NOT FOUND!\n");
	return users;
}
	

void save_users(const char* filename, User* users, int count)
{
	FILE *file = fopen(filename, "w");

	if(!file)
	{
		printf("Could not open file for writing.\n");
		return;
	}

	fprintf(file, "%d\n", count);
	for(int i = 0; i < count; i++)	
	{
		fprintf(file, "%d %s %d %s %s %s %d\n",users[i].id, users[i].name, users[i].age, users[i].vaccine_type, users[i].first_dose_date, users[i].second_dose_date, users[i].vaccinated);
	}
	fclose(file);
}

User* load_users(const char* filename, int* count)
{
	FILE *file = fopen(filename, "r");
	if(!file)
	{
		printf("Could not open file for reading,\n");
		return NULL;
	}

	fscanf(file,"%d\n",count);
	
	User *users = malloc(*count * sizeof(User));
	if(!users)
	{
		printf("Memory allocation failed!\n");
		fclose(file);
		return NULL;
	}

	for(int i = 0; i < *count; i++)
	{
 		fscanf(file, "%d %s %d %s %s %s %d\n",&users[i].id,users[i].name, &users[i].age, users[i].vaccine_type, users[i].first_dose_date, users[i].second_dose_date, &users[i].vaccinated);
	}
	fclose(file);
	return users;
	
}

int count_total_users(int count)
{
	return count;
}

int count_fully_vaccinated_users(User *users, int count)
{
	int vaccinated_count = 0;
	for(int i = 0; i < count; i++)
	{
		if(users[i].vaccinated)
		{
			vaccinated_count++;
		}
	}
	return vaccinated_count;
}

float vaccination_percentage(User* users, int count)
{
	int vaccinated_count = count_fully_vaccinated_users(users,count);
	return ((float)vaccinated_count/count) * 100;
}

void age_distribution(User *users, int count)
{
	int age_groups[10] = {0};
	
	for(int i = 0; i < count; i++)
	{
		int age_group = users[i].age/10;
		if(age_group < 100)
		{
			age_groups[age_group]++;
		}
		else
		{
			age_groups[9]++;
		}
	}
	printf("Age Distribution:\n");
	for(int i = 0; i < 10; i++)
	{
		printf("Age group %d - %d: %d users\n",i*10,(i+1)*10 - 1, age_groups[i]);
	}
}

void check_and_send_reminders(User *users, int count)
{
	time_t now = time(NULL);
	struct tm first_dose_time;
	for(int i = 0; i < count; i++)
	{
		if(!users[i].vaccinated)
		{

			strptime(users[i].first_dose_date,"%Y-%m-%d",&first_dose_time); 
		

			time_t first_dose_date = mktime(&first_dose_time);

			double difference = difftime(now, first_dose_date);
			if(difference > 30*24*60*60)
			{
				printf("Reminder : User %s (ID: %d) should get second dose vaccinated.\n", users[i].name, users[i].id);
			}
	   	}
	}
}


void update_vaccination_status(User* users, int count)
{
	int id;
	char vaccine_date[MAX_LENGTH];

	printf("Enter user ID to update vaccination status: \n");
	scanf("%d",&id);

	for(int i = 0; i < count; i++)
	{
		if(users[i].id == id)
		{
			if(users[i].vaccinated)
			{
				printf("User is already fully vaccinated.\n");
				return;
			}	
		
		printf("Enter second dose date (YYYY-MM-DD): ");
		scanf("%s", vaccine_date);
		
		strcpy(users[i].second_dose_date, vaccine_date);
		users[i].vaccinated = 1;
		
		printf("Vaccination status updated successfully.\n");
		save_users("users_data.dat", users, count);
		return;
		}
	}
	printf("User not found.\n");
}
