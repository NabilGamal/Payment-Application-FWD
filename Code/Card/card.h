/*
 * card.h
 *
 *  Created on: AUG 04, 2022
 *      Author: Nabil Gamal
 */

#ifndef _CARD_H_
#define _CARD_H_

#include "STD_Types.h"

#define		MinID				20
#define		IDLength			24

#define		NULL			   '\0'

#define		Date_Length			5
#define		Slash				47
#define		MonthZero			'0'
#define		MonthMaxOnes		'2'
#define		MonthMaxTens		'1'

#define		PANLength			19
#define		MinPAN				16

#define		MaxPanNO			20
#define		MaxCardHolderNameNo	25
#define		ArrExDateLength		6


typedef enum EN_cardError_t
{

	OK_CARD, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN

}EN_cardError_t;



typedef struct ST_cardData_t
{
	uint8	cardExpirationDate[ArrExDateLength];
	uint8	primaryAccountNumber[MaxPanNO];
	uint8	cardHolderName[MaxCardHolderNameNo];
	

}ST_cardData_t;


EN_cardError_t		getCardHolderName	(ST_cardData_t* cardData);
EN_cardError_t		getCardExpiryDate	(ST_cardData_t* cardData);
EN_cardError_t		getCardPAN			(ST_cardData_t* cardData);



#endif // _CARD_H_