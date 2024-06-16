#include "vaccine_registration.h"

int main()
{
	User *users = NULL;
	int count = 0;
	int choice;

	users = load_users("users_data.dat",&count);
	if(users == NULL)
	{
		printf("Error loading users\n");
		return 1;
	}
	
	while(1)
	{
	printf("\n *****VACCINE REGISTRATION SYSTEM***** \n");
	printf("\n1. User Registration\n");
	printf("2. View users\n");
	printf("3. Search user\n");
	printf("4. Delete user\n");
	printf("5. Count total users\n");
	printf("6. Count fully vaccinated users\n");
	printf("7. Calculate vaccination percentage\n");
	printf("8. Split users based on age group\n");
	printf("9. Check and send remainders\n");
	printf("10. Update the vaccination status\n");
	printf("0. Exit\n");
	printf("\nEnter your choice: \n");
	scanf("%d",&choice);
	printf("\n");
	
		switch(choice)
		{
		case 1 : 
		       users = register_user(users, &count);
			break;
	
		case 2:
			view_users(users, count);
			break;
	
		case 3:
			search_user(users, count);
			break;
	
		case 4:
			users = delete_user(users, &count);
			break;

		case 5: 
			printf("The total count of users are(including single dosed users also):%d \n", count_total_users(count));
			break;

		case 6:
			printf("The count of fully vaccinated users are:%d \n", count_fully_vaccinated_users(users, count));
			break;
	
		case 7:
			printf("The total of percantage of vaccination is:%.2f%% \n", vaccination_percentage(users, count));
			break;

		case 8:
			age_distribution(users,count);
			break;

		case 9: 
			check_and_send_reminders(users, count); 
			break;

		case 10:
			update_vaccination_status(users, count);
			break;

		case 0:
			save_users("users_data.dat", users, count);
			free(users);
			printf("\n*****Exiting the application*****\n");
			return 0;	
		
		default:
			printf("INVALID CHOICE! PLEASE TRY AGAIN.\n");
		}
	}
	return 0;
}	

