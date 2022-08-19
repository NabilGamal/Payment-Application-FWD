/*
 * card.c
 *
 *  Created on: AUG 04, 2022
 *      Author: Nabil Gamal
 */

#include	"Card.h"
#include	<stdio.h>
#include	<string.h>


#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS 1



EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
   
    printf("\nPlease Enter The Card Holder Name: ");
    gets(cardData->cardHolderName);


    /* a condition that checks if the length of the Card ID - Name isn't at the right format */
    if (cardData->cardHolderName[0] == NULL || strlen(cardData->cardHolderName) < MinID || strlen(cardData->cardHolderName) > IDLength)
    {

        return	WRONG_NAME;

    }

    else
    {

        return	OK_CARD;

    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    printf("\nPlease enter card Expiry Date (MM/YY): ");
    gets(cardData->cardExpirationDate);



    /* a condition that checks whether the expiration date is at the right format and if the legnth is accepted  */

    if ((cardData->cardExpirationDate[0] == NULL) || (strlen(cardData->cardExpirationDate) < Date_Length) || (strlen(cardData->cardExpirationDate) > Date_Length) || (cardData->cardExpirationDate[2] != Slash))
    {

        return WRONG_EXP_DATE;

    }

    /* a condition that ensures the "Month" spot isn't a blank or zero NO.  */

    else if ((cardData->cardExpirationDate[0]) == MonthZero && (cardData->cardExpirationDate[1]) == MonthZero)
    {

        return WRONG_EXP_DATE;

    }

    /* a condition checks that the month isn't higher than 12 (December)  */

    else if (((cardData->cardExpirationDate[0]) > MonthMaxTens) || ((cardData->cardExpirationDate[0]) == MonthMaxTens && (cardData->cardExpirationDate[1] > MonthMaxOnes)))
        
    {
        return WRONG_EXP_DATE;

    }

    else
    {
        return OK_CARD;

    }
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    printf("\nPlease enter account number: ");
    gets(cardData->primaryAccountNumber);


    /* a condition that checks if the legnth is at the right format  */

    if ((cardData->primaryAccountNumber[0] == NULL) || (strlen(cardData->primaryAccountNumber) < MinPAN) || (strlen(cardData->primaryAccountNumber) > PANLength))
    {

        return WRONG_PAN;

    }


    else
    {
        return OK_CARD;

    }
}