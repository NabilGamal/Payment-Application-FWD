/*
 * terminal.c
 *
 *  Created on: AUG 04, 2022
 *      Author: Nabil Gamal
 */



#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS 1


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{

	printf("Please enter Transaction Date (DD/MM/YYYY) : ");
	gets(termData->transactionDate);
	//scanf_s("%c", &(termData->transactionDate));

	//uint8	flag = 0;



	/*Conditions to check if the Date with DD/MM/YYYY format is right*/

	if ((termData->transactionDate[0]) == NULL || strlen(termData->transactionDate) < TransDateLen || strlen(termData->transactionDate) > TransDateLen || termData->transactionDate[2] != Slash || termData->transactionDate[5] != Slash)
	{
		//flag = 1;
		//printf("%d\n", flag);
		return WRONG_DATE;
	}
	else if (termData->transactionDate[0] == DayZero && termData->transactionDate[1] == DayZero)
	{
		//flag = 2;
		//printf("%d\n", flag);
		return WRONG_DATE;


	}

	else if (((termData->transactionDate[0]) > DayTENS_3) || ((termData->transactionDate[0]) == DayTENS_3 && (termData->transactionDate[1] > DayONES_1)))
	{
		//flag = 3;
		//printf("%d\n", flag);
		return WRONG_DATE;
	}
	else if (termData->transactionDate[3] == MonthZero && termData->transactionDate[4] == MonthZero)
	{
		//flag = 4;
		//printf("%d\n", flag);
		return WRONG_DATE;
	}

	else if (((termData->transactionDate[3]) > MonthMaxTens) || ((termData->transactionDate[3]) == MonthMaxTens && (termData->transactionDate[4] > MonthMaxOnes)))
	{
		//flag = 5;
		//printf("%d\n", flag);
		return WRONG_DATE;

	}


	return OK_TER;
		
			
	
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	uint8* uint32CardExpirationYear	 = &(cardData.cardExpirationDate[3]);

	uint8* uint32CardExpirationMonth = &(cardData.cardExpirationDate[0]);

	uint8* uint32TransactionYear	 = &(termData.transactionDate[8]);

	uint8* uint32TransactionMonth	 = &(termData.transactionDate[3]);


	/*Using atoi function to get the percise number of the year and month*/

	uint32 expirationDate = (atoi(uint32CardExpirationYear) + atoi(uint32CardExpirationMonth));
	uint32 terminalDate =	(atoi(uint32TransactionYear) + atoi (uint32TransactionMonth));


	if (expirationDate < terminalDate)
	{

		return EXPIRED_CARD;

	}


	else
	{
		return OK_TER;
	}


}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{

	printf("\nEnter Your Transaction Amount: ");
	scanf_s("%f", &(termData->transAmount));


	/*Checks if the transaction amount is valid*/
	if (termData->transAmount <= Zero)
	{

		return INVALID_AMOUNT;

	}

	else
	{
		return OK_TER;

	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{

	/*Checks if the transaction amount is lower than the Max Amount that is allowed to be transacted each time*/
	if (termData->transAmount > termData->maxTransAmount)
	{

		printf("\nYou Exceeded The allowed amount to be transacted\n");
		return EXCEED_MAX_AMOUNT;

	}

	else
	{
		return OK_TER;

	}

}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	/*if (max <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}

	termData->maxTransAmount = max;
	return OK_TER;*/


	printf("\nEnter Your MAX Amount: ");
	scanf_s("%f", &(termData->maxTransAmount));
	//gets(termData->maxTransAmount);

	if (termData->maxTransAmount == NULL || termData->maxTransAmount <= Zero)
	{
		return	INVALID_MAX_AMOUNT;
	}

	else
	{
		return	OK_TER;
	}
}