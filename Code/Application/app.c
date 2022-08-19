/*
 * app.c
 *
 *  Created on: AUG 04, 2022
 *      Author: Nabil Gamal
 */

#define _CRT_SECURE_NO_WARNINGS 1

#include "app.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

#include <stdio.h>
#include <string.h>

uint32	AnotherTransaction = 'y';

void appStart(void)
{

	ST_transaction_t transData;
	ST_transaction_t* transactionPtr = &transData;


	ST_terminalData_t MaxAmount;
	ST_terminalData_t* PTR_MaxAmount = &MaxAmount;

	uint8   isValidTransDate;

	//  isValidTransDate = getTransactionDate(&(transData->terminalData));

	//setMaxAmount(&(PTR_MaxAmount->maxTransAmount));
	//setMaxAmount(&(transactionptr->terminalData), 5000);
	//getTransactionDate(&(transactionptr->terminalData));

	isValidTransDate = isValidDATE(&(transData.terminalData));

	ST_Fill_Zero(Arr_transactionsDB_t, DataBase_Max_SIZE);

	

	//while (AnotherTransaction == 'y')
	while (1)
	{
		recieveTransactionData(transactionPtr);
		uint32 i = 0;
		uint8 flag = 0;
		for (i = 0; i < DataBase_Max_SIZE; i++)
		{
			if ((strcmp(transactionPtr->cardHolderData.primaryAccountNumber, Arr_accountsDB_t[i].primaryAccountNumber) == 0) && isCardExpired(transactionPtr->cardHolderData, transactionPtr->terminalData) == OK_TER)
			{
				flag = 1;
				printf("PAN: %s\t\tCard Name - ID: %s\t\tBalance: %0.2f\n", Arr_accountsDB_t[i].primaryAccountNumber, Arr_accountsDB_t[i].uint32CardNameHolder, Arr_accountsDB_t[i].balance);
				//printf("%d", flag);
				printf("Transaction NO.: %d\n", sequence - 1);
			}

			else if ((strcmp(transactionPtr->cardHolderData.primaryAccountNumber, Arr_StolenAccountsDB_t[i].primaryAccountNumber) == 0))
			{
				flag = 2;
				printf("Transaction NO.: %d\n", sequence - 1);
				
			}


		}

		uint8 Case = 0;

		if (flag == 0)
		{
			
			printf("Transaction number: %d\n", sequence - 1);
			flag = 2;
		}
		//printf("%s\t", &(accountsDB[i].primaryAccountNumber));
		//printf("%d", flag);
		//printf("%s\n", &(transactionptr->cardHolderData.primaryAccountNumber));


		else if (flag == 1)
		{
			do
			{
				printf("Do you want to get transaction in details? (Yes/No) : ");
				scanf(" %c", &Case);

				switch (Case)
				{
				case 'y':
					uint32 uint32Sequence;
					printf("\nEnter the sequence: ");
					scanf("%d", &uint32Sequence);
					getTransaction(uint32Sequence, Arr_transactionsDB_t);
					break;

				case 'n':
					printf("\n\nAnother transaction? (y/n): ");
					scanf(" %c", &AnotherTransaction);
					break;

				default:
					break;
				}
				/*if (Case == 'y')
				{
					uint32 uint32Sequence;
					printf("\nEnter the sequence: ");
					scanf("%d", &uint32Sequence);

					getTransaction(uint32Sequence, Arr_transactionsDB_t);
				}
				else if (Case == 'n')
				{
					printf("\n\nAnother transaction? (y/n): ");
					scanf(" %c", &AnotherTransaction);

					
				}*/
			} while (Case == 'y');
			
		}

		if (flag == 2)
		{
			if (isCardExpired(transactionPtr->cardHolderData, transactionPtr->terminalData) == EXPIRED_CARD)
			{
				printf("\nThe Card has been withdrawn because it is Expired\n");
				break;
			}
			printf("\nThe Card has been withdrawn because it was blocked by the owner\nContact your bank for more info\n");
			break;
		}

		if (AnotherTransaction == 'n')
		{
			printf("\nThank You\n");
			break;
		}

		
	}  

	
}


	/*uint8 AnotherTransaction;
	AnotherTransaction = 'Yes';*/

//	uint8 another;
//	another = 'y';
//
//	do
//	{
//		
//
//		recieveTransactionData(transactionPtr);
//		uint32 i = 0;
//		uint8 flag = 0;
//		for (i = 0; i < DataBase_Max_SIZE; i++)
//		{
//			if ((strcmp(transactionPtr->cardHolderData.primaryAccountNumber, Arr_accountsDB_t[i].primaryAccountNumber) == 0) && isCardExpired(transactionPtr->cardHolderData, transactionPtr->terminalData) == OK_TER)
//			{
//				flag = 1;
//				printf("Your PAN NO.: %s\t\tYour Card Name.: %s\t\tYour Balance: %0.2f\n", Arr_accountsDB_t[i].primaryAccountNumber, Arr_accountsDB_t[i].uint32CardNameHolder, Arr_accountsDB_t[i].balance);
//				  
//				printf("Transaction number: %d\n", sequence - 1);
//			}
//
//			
//
//			
//		}
//		
//		uint8 c = 0;
//
//		if (flag == 0)
//		{
//			printf("Transaction number: %d\n", sequence - 1);
//		}
//		//printf("%s\t", &(accountsDB[i].primaryAccountNumber));
//		//printf("%d", flag);
//		//printf("%s\n", &(transactionptr->cardHolderData.primaryAccountNumber));
//
//
//		
//
//		else if (flag == 1)
//		{
//			do
//			{
//				printf("\nDo you want to show transaction details (y/n) : ");
//				scanf(" %c", &c);
//
//					if (c == 'y')
//					{
//						uint32 num;
//						printf("\nEnter the sequence of the transaction: ");
//						scanf("%d", &num);
//
//						getTransaction(num, Arr_transactionsDB_t);
//					}
//					else if (c == 'n')
//					{
//						printf("\n\nDo you want another transaction? (y/n): ");
//						scanf(" %c", &another);
//					}
//			} while (c == 'y');
//			
//				
//		}
//		
//	} while (another == 'y');
//
//
//}

/*

	
*/