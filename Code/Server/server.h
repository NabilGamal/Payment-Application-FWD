/*
 * server.h
 *
 *  Created on: AUG 04, 2022
 *      Author: Nabil Gamal
 */


#ifndef SERVER_H_
#define	SERVER_H_

#include "../Terminal/terminal.h"

#define DataBase_Max_SIZE	255



typedef enum EN_transState_t
{

	APPROVED, DECLINED_INSUFFECIENT_FUND,
	DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR


}EN_transState_t;


typedef struct ST_transaction_t
{
	ST_cardData_t		cardHolderData;
	ST_terminalData_t	terminalData;
	EN_transState_t		transState;
	uint32				transactionSequenceNumber;

}ST_transaction_t;


typedef enum EN_serverError_t
{
	OK_SER, SAVING_FAILED, ACCOUNT_NOT_FOUND, 
	TRANSACTION_NOT_FOUND, LOW_BALANCE

}EN_serverError_t;

typedef struct ST_accountsDB_t
{
	float				balance;
	uint8				primaryAccountNumber[MaxPanNO];
	uint8				uint32CardNameHolder[MaxCardHolderNameNo];

	//float				floatMaxTransAmount;

}ST_accountsDB_t;

EN_transState_t			recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t		isValidAccount(ST_cardData_t* cardData);
EN_serverError_t		isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t		saveTransaction(ST_transaction_t* transData);
EN_serverError_t		getTransaction(uint32 transactionSequenceNumber, ST_transaction_t* transData);

void					ST_Fill_Zero(ST_transaction_t* transactionDB, uint32 size);
EN_terminalError_t		isValidDATE(ST_terminalData_t* termData);

ST_accountsDB_t			Arr_accountsDB_t[DataBase_Max_SIZE];

ST_accountsDB_t			Arr_StolenAccountsDB_t[DataBase_Max_SIZE];

ST_transaction_t		Arr_transactionsDB_t[DataBase_Max_SIZE];



uint32					sequence;


#endif // !SERVER_H_
